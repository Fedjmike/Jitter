#include "debug.h"

#include "stdlib.h"
#include "stdarg.h"
#include "stdio.h"

FILE* debug_log;
debug_mode mode;

void debug_init (FILE* nlog) {
    debug_log = nlog;
    debug_set_mode(debug_full);
}

debug_mode debug_set_mode (debug_mode nmode) {
    debug_mode old = mode;
    mode = nmode;
    return old;
}

void debug_wait () {
    #ifdef JITTER_DEBUG
    if (mode <= debug_minimal)
        getchar();
    #endif
}

void debug_msg (const char* format, ...) {
    va_list args;
    va_start(args, format);
    debug_vmsg(format, args);
    va_end(args);
}

void debug_vmsg (const char* format, va_list args) {
    debug_vout(format, args);
    debug_out("\n");
}

void debug_out (const char* format, ...) {
    va_list args;
    va_start(args, format);
    debug_vout(format, args);
    va_end(args);
}

void debug_vout (const char* format, va_list args) {
    (void) args;
    (void) format;

    #ifdef JITTER_DEBUG

    if (mode == debug_silent)
        return;

    vfprintf(debug_log, format, args);

    #endif
}

/*:::: INTERNAL ERRORS ::::*/

void debug_error (const char* function_name,
                  const char* format, ...) {
    fprintf(debug_log, "internal error(%s): ", function_name);

    va_list args;
    va_start(args, format);
    vfprintf(debug_log, format, args);
    va_end(args);

    fputc('\n', debug_log);

    debug_wait();
}

void debug_assert (const char* function_name,
                   const char* testName,
                   bool result) {
    if (!result)
        debug_error(function_name, "%s assertion failed", testName);
}

void debug_error_unhandled (const char* function_name,
                            const char* tag_name,
                            const char* tag_str) {
    debug_error(function_name, "unhandled %s: '%s'", tag_name, tag_str);
}

void debug_error_unhandled_int (const char* function_name,
                                const char* class_name,
                                int class_int) {
    debug_error(function_name, "unhandled %s: %d", class_name, class_int);
}
