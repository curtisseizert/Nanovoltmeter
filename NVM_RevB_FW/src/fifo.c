
#include "fifo.h"

/// @brief Writes a v_avg value to the FIFO and performs FIFO housekeeping
/// @param fifo Container of data to be output to the user
/// @param v_avg voltage to write to the FIFO
/// @return FIFO_STATUS_OK if no errors, other values if the write caused an error.
/// @note See FIFOStatus_t declaration in acq.h for full error explanations 
FIFOStatus_t fifo_write_v_avg(FIFO_t * fifo, double v_avg)
{
	FIFOStatus_t status = FIFO_STATUS_OK;
	// Check if all elements have been previously written. If so, increment the index
	// and write the element. The later conditionals are not applicable to this case,
	// so return out of this conditional to avoid evaluating those.
	if((fifo->data_written & fifo->data_reqd) == fifo->data_reqd) 
	{
		status = fifo_increment_in_index(fifo);
		fifo->data[fifo->in_index].v_avg = v_avg;
		fifo->data_written |= FIFO_VAVG_MASK;
		return status;
	}

	// Check if the element has been written, if not write it
	if(!(fifo->data_written & FIFO_VAVG_MASK))
	{
		fifo->data[fifo->in_index].v_avg = v_avg;
		fifo->data_written |= FIFO_VAVG_MASK;
	}
	// if the element has been written, write element at next index,
	// increment the index, and return FIFO_STATUS_INDEX_INCOMPLETE
	// or FIFO_STATUS_INCOMPLETE_OVERFLOW if FIFO has also overflowed.
	// This behavior is only for v_avg; other AcqData_t elements are overwritten
	// with a return of FIFO_STATUS_INDEX_OVERWRITE.
	else
	{
		FIFOStatus_t status = FIFO_STATUS_INDEX_INCOMPLETE;
		fifo->data[fifo->in_index + 1].v_avg = v_avg;
		status += fifo_increment_in_index(fifo);
		fifo->data_written = FIFO_VAVG_MASK;
		return status;
	}

	// If all requested data at that index are written, increment data_written
	if((fifo->data_written & fifo->data_reqd) == fifo->data_reqd) 
	{
		status = fifo_increment_in_index(fifo);
	}

	return status;
}

/// @brief Increments the FIFO input index and detects errors
/// @param fifo Container of data to be output to the user
/// @return FIFO_STATUS_OK if no errors, FIFO_STATUS_OVERFLOW if an overwrite of data not yet
/// @return sent out will occur at the new index, which will give data loss and out of order
/// @return results.
FIFOStatus_t fifo_increment_in_index(FIFO_t * fifo)
{
	// Increment in_index and zero out data_written bitfield
	fifo->in_index++;
	fifo->in_index %= FIFO_LEN;
	fifo->data_written = 0;

	// If incrementing the index caused in_index to catch out_index
	// return status indicates buffer overflow
	if(fifo->in_index == fifo->out_index) return FIFO_STATUS_OVERFLOW;

	return FIFO_STATUS_OK;
}

/// @brief Writes a value other than v_avg to the FIFO and performs housekeeping
/// @param fifo Container of data to be output to the user
/// @param in_data Data to write to the FIFO
/// @param mask Bitmask for the (single) element to write data to 
/// @return FIFO_STATUS_OK if no errors, other values if the write caused an error
/// @note See FIFOStatus_t declaration in acq.h for error explanations 
FIFOStatus_t fifo_write_other(FIFO_t * fifo, float in_data, FIFOMask_t mask)
{
	FIFOStatus_t status = FIFO_STATUS_OK;

	// Check if all elements have been previously written. If so, increment in_index
	if((fifo->data_written & fifo->data_reqd) == fifo->data_reqd) 
	{
		status = fifo_increment_in_index(fifo);
	}
	// Use the mask parameter to determine the element to write
	switch(mask)
	{
		case FIFO_VAVG_MASK:
			return FIFO_STATUS_INVALID_MASK;
		case FIFO_VOS_MASK:
			fifo->data[fifo->in_index].v_os = in_data;
			break;
		case FIFO_TEMP1_MASK:
			fifo->data[fifo->in_index].temps[0] = in_data;
			break;
		case FIFO_TEMP2_MASK:
			fifo->data[fifo->in_index].temps[1] = in_data;
			break;
		case FIFO_TEMP3_MASK:
			fifo->data[fifo->in_index].temps[2] = in_data;
			break;						
	}
	
	// If the written data had already been written, return appropriate status.
	// This cannort happen if in_index was incremented at the beginning, so
	// there is no need for status to indicate more than one error.
	if(fifo->data_written & mask) return FIFO_STATUS_INDEX_OVERWRITE;

	fifo->data_written |= mask;

	// If all requested data at that index are written, increment data_written
	if((fifo->data_written & fifo->data_reqd) == fifo->data_reqd) 
	{
		status = fifo_increment_in_index(fifo);
	}

	return status;
}

/// @brief Zeros out the FIFO but maintains the data_reqd bitmask
/// @param fifo Container of data to be output to the user
/// @return FIFO_STATUS_OK
FIFOStatus_t fifo_clear_data(FIFO_t * fifo)
{
	fifo->in_index = 0;
	fifo->out_index = 0;
	fifo->data_written = 0;

	for(uint16_t i = 0; i < FIFO_LEN; i++)
	{
		fifo->data[i].v_avg = 0;
		fifo->data[i].v_os = 0;
		fifo->data[i].temps[0] = 0;
		fifo->data[i].temps[1] = 0;
		fifo->data[i].temps[2] = 0;
	}

	return FIFO_STATUS_OK;
}

/// @brief Defines the requested set of data. If all are written, in_index will increment
/// @param fifo Container of data to be output to the user
/// @param mask Bitmask corresponding to all requested values
/// @return FIFO_STATUS_OK if no errors
/// @return FIFO_STATUS_INVALID_MASK if bits were set outside the valid bitfield
/// @note data_reqd bitmask is updated for both return values
/// @note mask is |='ed to FIFO_VAVG_MASK to ensure proper functioning of other functions
FIFOStatus_t fifo_set_data_req(FIFO_t * fifo, uint8_t mask)
{
	FIFOStatus_t status = FIFO_STATUS_OK;

	// Check if any invalid bits are set
	if(mask & ~(0x1F)) status = FIFO_STATUS_INVALID_MASK;

	// Zero any invalid bits before copying the mask
	mask &= 0x1F;
	fifo->data_reqd = mask;
    fifo->data_reqd |= FIFO_VAVG_MASK;

	return status;
}

/// @brief Outputs data from the FIFO and increments the index if the data were complete
/// @param fifo Container of data to be output to the user
/// @param dataptr Pointer whose value is modified to match that of the current output
/// @return FIFO_STATUS_OK if the data were ready and the index was incremented
/// @return FIFO_STATUS_INDEX_NOT_FILLED if the data are not ready and the index was not incremented
FIFOStatus_t fifo_output_data(FIFO_t * fifo, AcqData_t ** dataptr)
{
    FIFOStatus_t status = FIFO_STATUS_OK;

    * dataptr = &(fifo->data[fifo->out_index]);

    if(fifo->in_index == fifo->out_index) status = FIFO_STATUS_INDEX_NOT_FILLED;
    else 
		{
			fifo->out_index++;
			fifo->out_index %= FIFO_LEN;
		}

    return status;
}

/// @brief Returns the most recently written value of v_avg
/// @param fifo Container of data to be output to the user
/// @return 
double fifo_get_last_v_avg(FIFO_t * fifo)
{
    uint16_t index = fifo->in_index;
    if(!(fifo->data_written & FIFO_VAVG_MASK)) 
    {
        index--;
        index %= FIFO_LEN;
    }

    return fifo->data[index].v_avg;
}
