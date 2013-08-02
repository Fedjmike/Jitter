#include "jitter.h"

#include "stdio.h"
#include "stdarg.h"

typedef enum {
    debug_full,
    debug_compressed,
    debug_minimal,
    debug_silent
} debug_mode;

void debug_init (FILE* log);

debug_mode debug_set_mode (debug_mode mode);

void debug_wait ();

void debug_msg (const char* format, ...);
void debug_vmsg (const char* format, va_list args);
void debug_out (const char* format, ...);
void debug_vout (const char* format, va_list args);

void debug_error (const char* function_name,
                  const char* format, ...);

void debug_assert (const char* function_name,
                   const char* test_name,
                   bool result);

void debug_error_unhandled (const char* function_name,
                            const char* tag_name,
                            const char* tag_str);

void debug_error_unhandled_int (const char* function_name,
                                const char* class_name,
                                int class_int);
