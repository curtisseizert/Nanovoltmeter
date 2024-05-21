

#ifndef FIFO_H_
#define FIFO_H_

#include "stdint.h"

#define FIFO_LEN				1024
#define FIFO_SIZE_BYTES			READING_FIFO_LEN * sizeof(AcqData_t)

typedef struct{
	double v_avg;
	float v_os;
	float temps[3];
}AcqData_t;

typedef AcqData_t * pAcqData_t;

typedef struct{
	AcqData_t data[FIFO_LEN];
	uint16_t in_index;
	uint16_t out_index;
	uint8_t data_reqd;
	uint8_t data_written;
}FIFO_t;


/// @brief Typedef of the possible FIFO errors
/// @note FIFO_STATUS_OK: No error
/// @note FIFO_STATUS_INDEX_INCOMPLETE: An attempted overwrite of a V_avg value caused the index to increment without writing all requested data to the previous index
/// @note FIFO_STATUS_OVERFLOW: An overwrite of data not yet sent will occur at this index
/// @note FIFO_STATUS_INCOMPLETE_OVERFLOW: Combined ..._INDEX_INCOMPLETE and ..._OVERFLOW
/// @note FIFO_STATUS_INDEX_OVERWRITE: A valid value of v_os or temps[i] was overwritten at this index
/// @note FIFO_STATUS_INVALID_MASK: An invalid bitmask value was passed
/// @note FIFO_STATUS_INDEX_NOT_FILLED: The data pointer corresponds to an incomplete index
typedef enum{
	FIFO_STATUS_OK						= 0U,
	FIFO_STATUS_INDEX_INCOMPLETE		= 1U,
	FIFO_STATUS_OVERFLOW				= 2U,
	FIFO_STATUS_INCOMPLETE_OVERFLOW		= 3U,
	FIFO_STATUS_INDEX_OVERWRITE			= 4U,
	FIFO_STATUS_INVALID_MASK			= 5U,
	FIFO_STATUS_INDEX_NOT_FILLED		= 6U
}FIFOStatus_t;

typedef enum{
	FIFO_VAVG_MASK			= (1U << 0),
	FIFO_VOS_MASK			= (1U << 1),
	FIFO_TEMP1_MASK			= (1U << 2),
	FIFO_TEMP2_MASK			= (1U << 3),
	FIFO_TEMP3_MASK			= (1U << 4)
}FIFOMask_t;

FIFOStatus_t fifo_write_v_avg(FIFO_t * fifo, double v_avg);
FIFOStatus_t fifo_increment_in_index(FIFO_t * fifo);
FIFOStatus_t fifo_write_other(FIFO_t * fifo, float in_data, FIFOMask_t mask);
FIFOStatus_t fifo_clear_data(FIFO_t * fifo);
FIFOStatus_t fifo_set_data_req(FIFO_t * fifo, uint8_t mask);
FIFOStatus_t fifo_output_data(FIFO_t * fifo, AcqData_t ** dataptr);
double fifo_get_last_v_avg(FIFO_t * fifo);

#endif // FIFO_H_
