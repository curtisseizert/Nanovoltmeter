
#ifndef CMD_HANDLER_H_
#define CMD_HANDLER_H_

#include <stdint.h>
#include "lexer.h"
#include "serial_io.h"

    /** In the annotations for each #define, a brief explanation is given
     * about the node and a paranthetical notation of whether it can be
     * a command (c) or query (q). If there is no c or q, then it is not
     * a terminal node */



CmdErr command_handler(CmdString_t * cmd);

#endif // CMD_HANDLER_H_
