
#ifndef _DBG_
#define _DBG_

typedef struct code_line CODE_LINE;
typedef struct code_info CODE_INFO;

typedef struct code_line
{
        char oldcode[20];
        char newcode[20];
        int  bytes;
};
typedef struct code_info
{
        int line_count;                         //total line
        int bytes;                              //total bytes
        CODE_LINE code_lines[MAX_CODE_LINE];
};

#endif
