
    /* lexer.c */
    /* Command tokenizer functions for NVM Rev B*/

#include <stdlib.h>
#include "lexer.h"

/// @brief Parses a character array to an array of command tokens and parameters
/// @param s pointer to the character array
/// @param end pointer to the end of the character array
/// @return Cmd_t tokenized character array
Cmd_t parse_string_to_command(char * restrict s, char * restrict end)
{
    Cmd_t c = {.err = CMD_ERROR_NO_ERROR };
		char * iter = (char *)end;

    // Ensure that the command is not too long
    if(end - s > MAX_SERIAL_COMMAND_LEN)
    {
        c.err = CMD_ERROR_END_INDEX_OOR;
        return c;
    } 
    
    // Set the appropriate status if it's a *XXXX type command and
    // advance the iterator
    if(*s == 0x2A) // ASCII "*"
    {
        c.flags = CMD_FLAG_STAR_PREFIX;
        s++;
    }

    // Iterate through the character array and pull out tokens
    uint16_t cmd_index = 0;
    for(c.cmd[cmd_index] = get_token(s, (char ** restrict)&iter, &c.flags);
         s != end && cmd_index < MAX_HIERARCHY_DEPTH;
         c.cmd[cmd_index] = get_token(s, (char ** restrict)&iter, &c.flags)) 
    {
        cmd_index++;
        s = iter;
				iter = end;
    }

    // If a floating point parameter is passed, it will be the first number
    // Do not move the iterator so this can be parsed as an int32_t as well
    c.fp_param = strtod(s, (char ** restrict)&end);
    cmd_index = 0;

    // Parse the integer parameters passed to the function
    for(c.int_param[cmd_index] = strtol(s, (char ** restrict)&iter, 0);
        s!= end && cmd_index < MAX_INTEGER_PARAMETERS;
        c.int_param[cmd_index] = strtol(s, (char ** restrict)&iter, 0))
    {
        cmd_index++;
        s = iter;
    }

    return c;
}

/// @brief Converts a string to a token and sets the query flag if it contains "?"
/// @param s pointer to the beginning of the character array
/// @param end address of the pointer to the end of the array
/// @param flags pointer to a CmdFlag_t type to set the query flag if applicable
/// @return CmdToken_t for the string
CmdToken_t get_token(const char * restrict s, char ** restrict end, CmdFlag_t * flags)
{
    CmdToken_t token = {.num = 0};
    const char * iter = s;

    // If the string does not begin with a capital letter, return a NULL token
    if( *iter < 0x41 || *iter > 0x5A)
		{
			*end = (char * restrict)s;
			return token;
		}
    // Copy a maximum of four bytes to the token but stop if the end is reached or
    // a NULL, ":", LF, or SP is found.
    for(uint16_t i = 0; i < 4 && iter != (*end - 1); i++)
    {
        token.str[i] = *iter;
        iter++;
        switch(*iter)
        {
            case 0x00: 
                goto breakloop;
            case 0x3A: // :
                goto breakloop;
            case 0x0A: // LF
                goto breakloop;
            case 0x20: // space
                goto breakloop;
            case 0x3F: // ?
                *flags |= (1U << CMD_FLAG_QUERY_Pos);
                goto breakloop;
        }
    }

    // Iterate through the token until the end is reached or a NULL, ":", LF, or SP
    // is found.
    for(; iter++ != *end;)
    {
        switch(*iter)
        {
            case 0x00:
                goto breakloop;
            case 0x3A: // :
                goto breakloop;
            case 0x0A: // LF
                goto breakloop;
            case 0x20: // space
                goto breakloop;
                        case 0x3F: // ?
            *flags |= (1U << CMD_FLAG_QUERY_Pos);
            goto breakloop;
        }
    }

    breakloop:

    // Advance the iterator and copy it to *end if it hasn't overrun the array
    if(++iter < *end) *end = (char *) iter;
    
    // Zero out lowercase letters so that e.g., "SERi" and "SER" give the same token
    trim_non_caps(&token);

    return token;
}

/// @brief Trims non-capital letters from the string representation of the token
/// @param c CmdToken_t to be trimmed
void trim_non_caps(CmdToken_t * c)
{
    for(uint16_t i = 3; i != 0; i--)
    {
        // Zero a byte if it is not ASCII ?, @, or uppercase A-Z
        if(c->str[i] < 0x41 || c->str[i] > 0x5A) c->str[i] = 0x00;
        else break;
    }
}
