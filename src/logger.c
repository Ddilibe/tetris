/* Simple thread-friendly logger implementation (no external deps)
 * Writes timestamped logs to a file or stderr.
 */

#include "logger.h"
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

static FILE *g_log_file = NULL;
static log_level_t g_level = LOG_LEVEL_DEBUG;

static const char *level_names[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
};

int logger_init(const char *filename, log_level_t level)
{
    if (filename == NULL || strcmp(filename, "-") == 0)
    {
        g_log_file = stderr;
    }
    else
    {
        FILE *f = fopen(filename, "a");
        if (!f)
            return 0;
        g_log_file = f;
    }
    g_level = level;
    return 1;
}

void logger_set_level(log_level_t level)
{
    g_level = level;
}

void logger_close(void)
{
    if (g_log_file && g_log_file != stderr)
    {
        fclose(g_log_file);
    }
    g_log_file = NULL;
}

void logger_log(const char *file, int line, log_level_t level, const char *fmt, ...)
{
    if (level < g_level)
        return;
    if (!g_log_file)
        g_log_file = stderr;

    /* timestamp */
    time_t t = time(NULL);
    struct tm tm;
#if defined(_POSIX_THREAD_SAFE_FUNCTIONS) || defined(__APPLE__) || defined(__linux__)
    localtime_r(&t, &tm);
#else
    struct tm *tmp = localtime(&t);
    if (tmp)
        tm = *tmp;
    else
        memset(&tm, 0, sizeof(tm));
#endif

    char timestr[32];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", &tm);

    /* write header */
    fprintf(g_log_file, "%s [%s] %s:%d: ", timestr, level_names[level], file, line);

    va_list ap;
    va_start(ap, fmt);
    vfprintf(g_log_file, fmt, ap);
    va_end(ap);
    fprintf(g_log_file, "\n");
    fflush(g_log_file);
}
