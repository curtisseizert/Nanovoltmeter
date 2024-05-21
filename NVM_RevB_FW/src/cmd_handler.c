
    /* cmd_handler.c */
    /* Source file defining the command parser and handler functions for NVM Rev B */

#include "cmd_handler.h"
#include "acq.h"
#include "serial_io.h"
#include <math.h>

static const char idnq_string[] = "Nanovoltmeter Rev B, FW v2.0";

/// @brief Handles user input commands
/// @param cs CmdString_t * container for fixed length char arrays copied from the Uart_Rx_t circular buffer
/// @return CmdErr status of the operation
CmdErr command_handler(CmdString_t * cs)
{
    Cmd_t cmd = parse_string_to_command((char * restrict)cs->buffer,(char * restrict)&cs->buffer[MAX_SERIAL_COMMAND_LEN - 1]);

    if(cmd.flags & (1U << CMD_FLAG_STAR_PREFIX))
    {
        switch(cmd.cmd[0].num)
        {
            case CMD_STAR_ESE:
                STAR_ESE_handler(&cmd);
                break;
            case CMD_STAR_ESR:
                STAR_ESR_handler(&cmd);
                break;
            case CMD_STAR_IDN:
                STAR_IDN_handler(&cmd);
                break;
            case CMD_STAR_RST:
                STAR_RST_handler(&cmd);
                break;
        }
    }
    else
    {
        switch(cmd.cmd[0].num)
        {
            case CMD_TOP_SYST:
                TOP_SYST_handler(&cmd);
                break;
            case CMD_TOP_STAT:
                TOP_STAT_handler(&cmd);
                break;
            case CMD_TOP_MEAS:
                TOP_MEAS_handler(&cmd);
                break;
            case CMD_TOP_FORM:
                TOP_FORM_handler(&cmd);
                break;
            case CMD_TOP_MEM:
                TOP_MEM_handler(&cmd);
                break;
            case CMD_TOP_TRIG:
                TOP_TRIG_handler(&cmd);
                break;
        }
    }

    return cmd.err;
}

/// @brief Handler for SYSTem:... commands
/// @param cmd 
void TOP_SYST_handler(Cmd_t * cmd)
{
    switch(cmd->cmd[1].num)
    {
        default:
            cmd->err = CMD_ERROR_BAD_SYNTAX;
            break;
        case CMD_SYST_ERR:
            if(!(cmd->flags & (1U << CMD_FLAG_QUERY_Pos))){
                cmd->err = CMD_ERROR_QUERY_ONLY;
                break;
            }else{
                // Do something
                break;
            }
        case CMD_SYST_VERS:
            if(!(cmd->flags & (1U << CMD_FLAG_QUERY_Pos))){
                cmd->err = CMD_ERROR_QUERY_ONLY;
                break;
            }else{
                // Do something
                break;
            }
        case CMD_SYST_SER:
            if(cmd->cmd[2].num == CMD_SYST_SER_BAUD){
                SYST_SER_BAUD_handler(cmd);
                break;
            }else{
                cmd->err = CMD_ERROR_BAD_SYNTAX;
                break;
            }
    }
}

/// @brief Handler for *ESE and *ESE?
/// @param cmd 
void STAR_ESE_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED\n\r");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for *ESR?
/// @param cmd 
void STAR_ESR_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED\n\r");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for *IDN?
/// @param cmd 
void STAR_IDN_handler(Cmd_t * cmd)
{
    serial_print((char *)idnq_string);
}

/// @brief Handler for *RST
/// @param cmd 
void STAR_RST_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED\n\r");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;    
}

/// @brief Handler for STATus:... commands
/// @param cmd 
void TOP_STAT_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED\n\r");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;    
}

/// @brief Handler for MEASure:... commands
/// @param cmd 
void TOP_MEAS_handler(Cmd_t * cmd)
{
    switch(cmd->cmd[1].num)
    {
        case CMD_MEAS_CONF:
            CMD_MEAS_CONF_handler(cmd);
            break;
        case CMD_MEAS_INIT:
            CMD_MEAS_INIT_handler(cmd);
            break;
        case CMD_MEAS_FETC:
            CMD_MEAS_INIT_handler(cmd);
				
        __attribute__ ((fallthrough)); 
				case CMD_MEAS_READ:
            CMD_MEAS_READ_handler(cmd);

    }
}

/// @brief Handler for MEASure:CONFigure:... commands
/// @param cmd 
void CMD_MEAS_CONF_handler(Cmd_t * cmd)
{
    switch(cmd->cmd[2].num)
    {
        case CMD_MEAS_CONF_MODF:
            acq2.mod_freq = (float) cmd->fp_param;
            break;
        case CMD_MEAS_CONF_AVG:
            acq2.mod_cycles_per_avg = (uint16_t) *cmd->int_param;
            break;
        case CMD_MEAS_CONF_DFRE:
            acq2.mod_cycles_per_update = (uint16_t) *cmd->int_param;
            break;
        case CMD_MEAS_CONF_CDSF:
            acq2.mod_cycles_per_cds = (uint16_t) *cmd->int_param;
            break;
        case CMD_MEAS_CONF_ADFS:
            acq2.adc_samp_freq = (uint32_t) *cmd->int_param;
            break;
        case CMD_MEAS_CONF_LOGS:
            acq2.log2SampAvg = (uint16_t) *cmd->int_param;
            break;
        case CMD_MEAS_CONF_SETT:
            acq2.settle_time_us = (float) cmd->fp_param;
            break;
        case CMD_MEAS_CONF_DBAN:
            acq2.Vos_dac_deadband_nV = (float) cmd->fp_param;
            break;
        case CMD_MEAS_CONF_DTIM:
            acq2.mod_deadtime_us = (float) cmd->fp_param;
            break;
        case CMD_MEAS_CONF_DTID:
            acq2.demod_deadtime_us = (float) cmd->fp_param;
            break;
        case CMD_MEAS_CONF_SINC:
            acq2.sinc_order = (uint16_t) *cmd->int_param;
            break;
       // case CMD_MEAS_CONF_DACA:
       //     queue_dac_write()

    }
}

/// @brief Handler for MEASure:READ:... commands
/// @param cmd 
void CMD_MEAS_READ_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for MEASure:INITiate
/// @param cmd 
void CMD_MEAS_INIT_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for FORMat:... commands
/// @param cmd 
void TOP_FORM_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for MEMory:... commands
/// @param cmd 
void TOP_MEM_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for TRIGger:... commands
/// @param cmd 
void TOP_TRIG_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}

/// @brief Handler for SYSTem:SERial:BAUD
/// @param cmd 
void SYST_SER_BAUD_handler(Cmd_t * cmd)
{
    serial_print("ERROR: FEATURE NOT IMPLEMENTED");
    cmd->err = CMD_ERROR_NOT_IMPLEMENTED;
}
