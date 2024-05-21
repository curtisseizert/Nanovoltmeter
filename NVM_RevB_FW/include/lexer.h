
#ifndef LEXER_H_
#define LEXER_H_

#include <stdint.h>

#define MAX_SERIAL_COMMAND_LEN      64
#define MAX_HIERARCHY_DEPTH         4
#define MAX_INTEGER_PARAMETERS      4


typedef union{
    uint8_t str[4];
    uint32_t num;
}CmdToken_t;

typedef enum{
    CMD_ERROR_NO_ERROR,
    CMD_ERROR_END_INDEX_OOR,
    CMD_ERROR_IMPLIED_READ,
    CMD_ERROR_STAR_PREFIX,
    CMD_ERROR_BAD_SYNTAX,
    CMD_ERROR_QUERY_ONLY,
    CMD_ERROR_CMD_ONLY,
    CMD_ERROR_NOT_IMPLEMENTED
}CmdErr;

#define CMD_FLAG_STAR_PREFIX_Pos    0
#define CMD_FLAG_QUERY_Pos          1

typedef enum{
    CMD_FLAG_NONE           = 0,
    CMD_FLAG_STAR_PREFIX    = 1,
    CMD_FLAG_QUERY          = 2,
    CMD_FLAG_STAR_QUERY     = 3
}CmdFlag_t;

typedef struct{
    double fp_param;
    CmdToken_t cmd[MAX_HIERARCHY_DEPTH];
    int32_t int_param[MAX_INTEGER_PARAMETERS];
    CmdErr err;
    CmdFlag_t flags;
}Cmd_t;

Cmd_t parse_string_to_command(char * restrict s, char * restrict end);
CmdToken_t get_token(const char * restrict s, char ** restrict end, CmdFlag_t * flags);
void trim_non_caps(CmdToken_t * c);

#endif // LEXER_H_
