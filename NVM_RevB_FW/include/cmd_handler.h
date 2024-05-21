
#ifndef CMD_HANDLER_H_
#define CMD_HANDLER_H_

#include <stdint.h>
#include "lexer.h"
#include "serial_io.h"

    /** In the annotations for each #define, a brief explanation is given
     * about the node and a paranthetical notation of whether it can be
     * a command (c) or query (q). If there is no c or q, then it is not
     * a terminal node */


#define CMD_STAR_ESE            0x00455345  // Standard Event Status Enable (c,q)
#define CMD_STAR_ESR            0x00525345  // Standard Event Status Register (q)
#define CMD_STAR_IDN            0x004e4449  // Identification (q)
#define CMD_STAR_RST            0x00545352  // Reset (c)

#define CMD_TOP_SYST            0x54535953   // SYSTem
#define CMD_TOP_STAT            0x54415453   // STATus
#define CMD_TOP_MEAS            0x5341454d   // MEASure
#define CMD_TOP_FORM            0x4d524f46   // FORMat
#define CMD_TOP_MEM             0x004d454d   // MEMory
#define CMD_TOP_TRIG            0x47495254   // TRIGger

#define CMD_SYST_ERR            0x00525245   // ERRor (q)
#define CMD_SYST_VERS           0x53524556   // VERSion (q)
#define CMD_SYST_SER            0x00524553   // SERial 

#define CMD_SYST_SER_BAUD       0x44554142   // BAUD rate (c,q)

#define CMD_STAT_OPER           0x5245504f   // OPERation
#define CMD_STAT_QUES           0x53455551   // QUEStionable
#define CMD_STAT_PRES           0x53455250   // PRESet

#define CMD_MEAS_CONF           0x464e4f43   // CONFigure (c,q)
#define CMD_MEAS_INIT           0x54494e49   // INITiate (c)
#define CMD_MEAS_READ           0x44414552   // READ (q)
#define CMD_MEAS_FETC           0x43544546   // FETCh (q)

#define CMD_MEAS_CONF_MODF      0x46444f4d   // Modulator Frequency
#define CMD_MEAS_CONF_AVG       0x00475641   // Modulator cycles per average
#define CMD_MEAS_CONF_DFRE      0x45524644   // DAC Update Frequency
#define CMD_MEAS_CONF_CDSF      0x46534443   // CDS Frequency (as a fraction of MODF)
#define CMD_MEAS_CONF_ADFS      0x53464441   // ADC Sampling Frequency
#define CMD_MEAS_CONF_LOGS      0x53474f4c   // Log2 samples per ADC block
#define CMD_MEAS_CONF_SETT      0x54544553   // Modulator settling time in us
#define CMD_MEAS_CONF_DBAN      0x4e414244   // DAC Update deadband in nV
#define CMD_MEAS_CONF_DTIM      0x4d495444   // Modulator deadtime in us
#define CMD_MEAS_CONF_DTID      0x44495444   // Demodulator deadtime in us
#define CMD_MEAS_CONF_SINC      0x434e4953   // Sinc filter order (1 - 3)

#define CMD_MEAS_CONF_DACA      0x41434144   // DAC Channel A code (MOD1 HIGH LEVEL)
#define CMD_MEAS_CONF_DACB      0x42434144   // DAC Channel B code (VOS COMP)
#define CMD_MEAS_CONF_DACC      0x43434144   // DAC Channel C code (MOD2 HIGH LEVEL)
#define CMD_MEAS_CONF_DACD      0x44434144   // DAC Channel D code (MOD LOW LEVEL)
#define CMD_MEAS_CONF_DACE      0x45434144   // Internal (DEMOD) DAC code (12 bit)

extern AcqParam_t acq1, acq2;

CmdErr command_handler(CmdString_t * cmd);

void STAR_ESE_handler(Cmd_t * cmd);
void STAR_ESR_handler(Cmd_t * cmd);
void STAR_IDN_handler(Cmd_t * cmd);
void STAR_RST_handler(Cmd_t * cmd);

void TOP_SYST_handler(Cmd_t * cmd);
void TOP_STAT_handler(Cmd_t * cmd);
void TOP_MEAS_handler(Cmd_t * cmd);
void TOP_FORM_handler(Cmd_t * cmd);
void TOP_MEM_handler(Cmd_t * cmd);
void TOP_TRIG_handler(Cmd_t * cmd);

void SYST_SER_BAUD_handler(Cmd_t * cmd);

void CMD_MEAS_CONF_handler(Cmd_t * cmd);
void CMD_MEAS_READ_handler(Cmd_t * cmd);
void CMD_MEAS_INIT_handler(Cmd_t * cmd);


#endif // CMD_HANDLER_H_
