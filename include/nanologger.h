#ifndef NANOLOGGER_H
#define NANOLOGGER_H

#include <stdarg.h>

// Macro definitions
/*****************************************************************************
 *                                   !DEBUG                                  *
 *****************************************************************************/
#ifndef DEBUG

#define CRITICAL(...)                                                          \
  {                                                                            \
  }

#define ERROR(...)                                                             \
  {                                                                            \
  }

#define WARN(...)                                                              \
  {                                                                            \
  }

#define LOG_INIT(...)                                                          \
  {                                                                            \
  }

#define LOG_END(...)                                                           \
  {                                                                            \
  }

#define LOG(...)                                                               \
  {                                                                            \
  }

/*****************************************************************************
 *                                    DEBUG                                  *
 *****************************************************************************/
#else

void log_critical(const char *file, int line, const char *func, const char *fmt,
                  ...) __attribute__((format(printf, 4, 5)));

void log_error(const char *file, int line, const char *func, const char *fmt,
               ...) __attribute__((format(printf, 4, 5)));

void log_warn(const char *file, int line, const char *func, const char *fmt,
              ...) __attribute__((format(printf, 4, 5)));

void log_init(const char *file, int line, const char *func, const char *fmt,
              ...) __attribute__((format(printf, 4, 5)));

void log_end(const char *file, int line, const char *func, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));

void log_debug(const char *file, int line, const char *func, const char *fmt,
               ...) __attribute__((format(printf, 4, 5)));

/*****************************************************************************
 *                                   DEBUG 0                                 *
 *****************************************************************************/
#if DEBUG >= 0

#define CRITICAL(fmt, ...)                                                     \
  log_critical(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif // !DEBUG >= 0

/*****************************************************************************
 *                                   DEBUG 1                                 *
 *****************************************************************************/
#if DEBUG >= 1

#define ERROR(fmt, ...)                                                        \
  log_error(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif // !DEBUG >= 1

/*****************************************************************************
 *                                   DEBUG 2                                 *
 *****************************************************************************/
#if DEBUG >= 2

#define WARN(fmt, ...)                                                         \
  log_warn(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif // !DEBUG >= 2

/*****************************************************************************
 *                                   DEBUG 3                                 *
 *****************************************************************************/
#if DEBUG >= 3

#define LOG_INIT(fmt, ...)                                                     \
  log_init(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define LOG_END(fmt, ...)                                                      \
  log_end(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define LOG(fmt, ...)                                                          \
  log_debug(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif // !DEBUG >= 3

/*****************************************************************************
 *                                   DEBUG !3                                *
 *****************************************************************************/
#if DEBUG < 3

#define LOG_INIT(...)                                                          \
  {                                                                            \
  }

#define LOG_END(...)                                                           \
  {                                                                            \
  }

#define LOG(...)                                                               \
  {                                                                            \
  }

#endif // !DEBUG < 3

/*****************************************************************************
 *                                   DEBUG !2                                *
 *****************************************************************************/
#if DEBUG < 2

#define WARN(...)                                                              \
  {                                                                            \
  }

#endif // !DEBUG < 2

/*****************************************************************************
 *                                   DEBUG !1                                *
 *****************************************************************************/
#if DEBUG < 1

#define ERROR(...)                                                             \
  {                                                                            \
  }

#endif // !DEBUG < 1

/*****************************************************************************
 *                                   DEBUG !0                                *
 *****************************************************************************/
#if DEBUG < 0

#define CRITICAL(...)                                                          \
  {                                                                            \
  }

#endif // !DEBUG < 0
#endif // !DEBUG

#endif // NANOLOGGER_H
