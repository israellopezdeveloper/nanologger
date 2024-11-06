#ifndef LOGGER_H
#define LOGGER_H

// Nivel de depuración por defecto si no se define
#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG >= 0

#include <stdarg.h>

// Prototipos de las funciones de logging
void log_critical(const char *file, int line, const char *func, const char *fmt,
                  ...) __attribute__((format(printf, 4, 5)));

#if DEBUG >= 1

void log_error(const char *file, int line, const char *func, const char *fmt,
               ...) __attribute__((format(printf, 4, 5)));

#if DEBUG >= 2

void log_warn(const char *file, int line, const char *func, const char *fmt,
              ...) __attribute__((format(printf, 4, 5)));

#if DEBUG >= 3

void log_init(const char *file, int line, const char *func, const char *fmt,
              ...) __attribute__((format(printf, 4, 5)));
void log_end(const char *file, int line, const char *func, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));
void log_debug(const char *file, int line, const char *func, const char *fmt,
               ...) __attribute__((format(printf, 4, 5)));

#endif // DEBUG >= 3
#endif // DEBUG >= 2
#endif // DEBUG >= 1
#endif // DEBUG >= 0

// Definición de macros para facilitar el uso
#if DEBUG >= 0

#define CRITICAL(fmt, ...)                                                     \
  log_critical(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#if DEBUG >= 1

#define ERROR(fmt, ...)                                                        \
  log_error(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#if DEBUG >= 2

#define WARN(fmt, ...)                                                         \
  log_warn(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#if DEBUG >= 3

#define LOG_INIT(fmt, ...)                                                     \
  log_init(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_END(fmt, ...)                                                      \
  log_end(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG(fmt, ...)                                                          \
  log_debug(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#else // DEBUG < 3

#define LOG_INIT(...) ((void)0)
#define LOG_END(...) ((void)0)
#define LOG(...) ((void)0)

#endif // DEBUG >= 3
#else  // DEBUG < 2

#define WARN(...) ((void)0)
#define LOG_INIT(...) ((void)0)
#define LOG_END(...) ((void)0)
#define LOG(...) ((void)0)

#endif // DEBUG >= 2
#else  // DEBUG < 1

#define ERROR(...) ((void)0)
#define WARN(...) ((void)0)
#define LOG_INIT(...) ((void)0)
#define LOG_END(...) ((void)0)
#define LOG(...) ((void)0)

#endif // DEBUG >= 1
#else  // DEBUG < 0

#define CRITICAL(...) ((void)0)
#define ERROR(...) ((void)0)
#define WARN(...) ((void)0)
#define LOG_INIT(...) ((void)0)
#define LOG_END(...) ((void)0)
#define LOG(...) ((void)0)

#endif // DEBUG >= 0

#endif // LOGGER_H

