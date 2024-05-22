
    /* cmd_handler.c */
    /* Source file defining the command parser and handler functions for NVM Rev B */

#include "cmd_handler_private.h"
#include "nvmb.h"
#include "acq.h"
#include "serial_io.h"
#include "dac.h"
#include <math.h>

static const char idnq_string[] = "Nanovoltmeter Rev B, FW v2.0";

/// @brief Returns whether a command is a query or not
/// @param cmd 
/// @return 1 if the command is a query
/// @return 0 if the command is not a query 
static int16_t is_query(const Cmd_t * cmd)
{
    if(cmd->flags & (1U << CMD_FLAG_QUERY_Pos)) return 1;
    return 0;
}

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
            default:
                cmd.err = CMD_ERROR_BAD_SYNTAX;
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
            case CMD_INP:
                TOP_INP_handler(&cmd);
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
            default:
                cmd.err = CMD_ERROR_BAD_SYNTAX;
                break;
        }
    }

    switch(cmd.err)
    {
        case CMD_ERROR_BAD_SYNTAX:
            serial_print("COMMAND ERROR: BAD SYNTAX\n\r");
            break;
        case CMD_ERROR_NOT_IMPLEMENTED:
            serial_print("COMMAND ERROR: FEATURE NOT IMPLEMENTED\n\r");
            break;
        case CMD_ERROR_QUERY_ONLY:
            serial_print("COMMAND ERROR: QUERY ONLY");
            break;
        case CMD_ERROR_CMD_ONLY:
            serial_print("COMMAND ERROR: NO QUERY AVAILABLE");
            break;
        default:
            break;
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
            if(!is_query(cmd)){
                cmd->err = CMD_ERROR_QUERY_ONLY;
                break;
            }else{
                // Do something
                break;
            }
        case CMD_SYST_VERS:
            if(!is_query(cmd)){
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
    serial_print("SYSTEM RESET\n\r");
		Reset_Handler();
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
    pause_acquisition(&acq1);
    switch(cmd->cmd[2].num)
    {
        case CMD_MODF:
            if(!is_query(cmd)) acq1.mod_freq = (float) cmd->fp_param;
            break;
        case CMD_AVG:
            acq1.mod_cycles_per_avg = (uint16_t) *cmd->int_param;
            break;
        case CMD_DFRE:
            acq1.mod_cycles_per_update = (uint16_t) *cmd->int_param;
            break;
        case CMD_CDSF:
            acq1.mod_cycles_per_cds = (uint16_t) *cmd->int_param;
            break;
        case CMD_ADFS:
            acq1.adc_samp_freq = (uint32_t) *cmd->int_param;
            break;
        case CMD_LOGS:
            acq1.log2SampAvg = (uint16_t) *cmd->int_param;
            break;
        case CMD_SETT:
            acq1.settle_time_us = (float) cmd->fp_param;
            break;
        case CMD_DBAN:
            acq1.Vos_dac_deadband_nV = (float) cmd->fp_param;
            break;
        case CMD_DTIM:
            acq1.mod_deadtime_us = (float) cmd->fp_param;
            break;
        case CMD_DTID:
            acq1.demod_deadtime_us = (float) cmd->fp_param;
            break;
        case CMD_SINC:
            acq1.sinc_order = (uint16_t) *cmd->int_param;
            break;
        case CMD_DACA:
           queue_dac_write(AD5686_DAC_A, (uint16_t) *cmd->int_param);
           break;
        case CMD_DACB:
           queue_dac_write(AD5686_DAC_B, (uint16_t) *cmd->int_param);
           break;
        case CMD_DACC:
           queue_dac_write(AD5686_DAC_C, (uint16_t) *cmd->int_param);
           break;
        case CMD_DACD:
           queue_dac_write(AD5686_DAC_D, (uint16_t) *cmd->int_param);
           break;
        case CMD_DACE:
           dac_write_code((uint16_t) *cmd->int_param);
           break;           
        case CMD_GAIN:
            set_gain(&acq1, (GainState_t) *cmd->int_param);
            break;
        case CMD_MOD:
            CMD_MEAS_CONF_MOD_handler(cmd);
            break;
        case CMD_CDS:
            CMD_MEAS_CONF_CDS_handler(cmd);
            break;


    }
}

void CMD_MEAS_CONF_MOD_handler(Cmd_t * cmd)
{
    if(cmd->cmd[3].num == CMD_ON) acq1.flags &= ~ACQ_FLAG_GPIOMOD_SET;
    else if(cmd->cmd[3].num == CMD_OFF) 
    {
				acq1.flags |= ACQ_FLAG_GPIOMOD_SET;
        gpio_mod_clocks(&acq1);
        set_mod_phase(&acq1, (ModPhase_t) *cmd->int_param);
    }
    else cmd->err = CMD_ERROR_BAD_SYNTAX;
}

void CMD_MEAS_CONF_CDS_handler(Cmd_t * cmd)
{
    if(cmd->cmd[3].num == CMD_ON) acq1.flags &= ~ACQ_FLAG_GPIOCDS_SET;
    else if(cmd->cmd[3].num == CMD_OFF) 
    {
				acq1.flags |= ACQ_FLAG_GPIOCDS_SET;
        gpio_cds_clocks(&acq1);
        set_cds_phase(&acq1, gen_cds_phase(cmd->int_param[0], cmd->int_param[1]));
    }
    else cmd->err = CMD_ERROR_BAD_SYNTAX;
}

/// @brief Handler for MEASure:READ:... commands
/// @param cmd 
void CMD_MEAS_READ_handler(Cmd_t * cmd)
{
    start_acquisition(&acq1);
}

/// @brief Handler for MEASure:INITiate
/// @param cmd 
void CMD_MEAS_INIT_handler(Cmd_t * cmd)
{
    setup_acquisition(&acq1);
    start_acquisition(&acq1);
}

/// @brief Handler for INPut:... commands
/// @param cmd 
void TOP_INP_handler(Cmd_t * cmd)
{
    if(cmd->cmd[1].num == CMD_RELA)
    {
        Relay_t relay = Relay_K1;
        switch(cmd->cmd[2].num)
        {
            case CMD_INP:
                relay = Relay_K1;
                break;
            case CMD_CAP:
                relay = Relay_K2;
                break;
            case CMD_RES:
                relay = Relay_K3;
                break;
            default:
                cmd->err = CMD_ERROR_BAD_SYNTAX;
        }

        switch(cmd->cmd[3].num)
        {
            case CMD_SET:
                relay_set_state(&relay, RELAY_SET);
                break;
            case CMD_RESE:
                relay_set_state(&relay, RELAY_RESET);
                break;

        }
    }
    else cmd->err = CMD_ERROR_BAD_SYNTAX;
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
