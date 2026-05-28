#include <stdio.h>
#include "logger.h"

static FILE *log_file = NULL;
static int success_calls = 0;

void logSetFile(FILE *file){
    log_file = file;
}

void logPrintf(const char *format, ...){
    if (log_file==NULL){
        return;
    }

    va_list args;
    va_start(args, format);
    int res = vfprintf(log_file, format, args);
    va_end(args);
    
    if (res>=0) success_calls++;
}

int getLogCallsCount(){
    return success_calls;
}