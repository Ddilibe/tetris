/* Simple logger for the tetris project
 * Usage:
 *   logger_init("logfile.log", LOG_LEVEL_DEBUG);
 *   LOG_INFO("started, port=%d", port);
 *   logger_close();
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef enum
{
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
} log_level_t;

/* Initialize the logger.
 * filename: path to logfile. If NULL or "-" use stderr.
 * level: minimum log level (LOG_LEVEL_DEBUG..LOG_LEVEL_ERROR)
 * Returns 1 on success, 0 on failure.
 */
int logger_init(const char *filename, log_level_t level);

/* Change the runtime log level */
void logger_set_level(log_level_t level);

/* Close the logger and flush outputs */
void logger_close(void);

/* Core logging function - include file/line for context */
void logger_log(const char *file, int line, log_level_t level, const char *fmt, ...);

/* Convenience macros that include source location */
#define LOG_DEBUG(fmt, ...) logger_log(__FILE__, __LINE__, LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) logger_log(__FILE__, __LINE__, LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) logger_log(__FILE__, __LINE__, LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) logger_log(__FILE__, __LINE__, LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)

#endif /* LOGGER_H */
