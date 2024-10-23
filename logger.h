#ifndef LOGGER_H
#define LOGGER_H

#if DEBUG >= 0

#include <execinfo.h>
#include <libgen.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Include time.h for clock_gettime
#include <unistd.h>

// Function prototypes for the logging functions
void log_critical (const char *file, int line, const char *func,
                   const char *fmt, ...)
    __attribute__ ((format (printf, 4, 5)));
void log_error (const char *file, int line, const char *func, const char *fmt,
                ...) __attribute__ ((format (printf, 4, 5)));
void log_warn (const char *file, int line, const char *func, const char *fmt,
               ...) __attribute__ ((format (printf, 4, 5)));
void log_init (const char *file, int line, const char *func, const char *fmt,
               ...) __attribute__ ((format (printf, 4, 5)));
void log_end (const char *file, int line, const char *func, const char *fmt,
              ...) __attribute__ ((format (printf, 4, 5)));
void log_debug (const char *file, int line, const char *func, const char *fmt,
                ...) __attribute__ ((format (printf, 4, 5)));

#define CRITICAL(fmt, ...)                                                    \
  log_critical (__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#if DEBUG >= 1

#define ERROR(fmt, ...)                                                       \
  log_error (__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#if DEBUG >= 2

#define WARN(fmt, ...)                                                        \
  log_warn (__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#if DEBUG >= 3

#define LOG_INIT(fmt, ...)                                                    \
  log_init (__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_END(fmt, ...)                                                     \
  log_end (__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG(fmt, ...)                                                         \
  log_debug (__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

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

// Implementations of the logging functions

#if DEBUG >= 0

void
log_critical (const char *file, int line, const char *func, const char *fmt,
              ...)
{
  struct timespec timespec;
  clock_gettime (CLOCK_MONOTONIC, &timespec);

  void **buffer = (void **)malloc (50 * sizeof (void *));
  if (!buffer)
    return;

  int deep = backtrace (buffer, 50);
  void **deep_ptr = buffer;

  char *parents = (char *)malloc ((size_t)(deep * 15) * sizeof (char));
  if (!parents)
    {
      free (buffer);
      return;
    }
  char *parents_ptr = parents;

  for (int i = 0; i < deep; i++)
    {
      if ((i > 0) && (i < deep))
        {
          *parents_ptr = ',';
          ++parents_ptr;
        }
      sprintf (parents_ptr, "%p", *deep_ptr);
      parents_ptr += 14; // Assuming 14 characters per address
      deep_ptr++;
    }

  flockfile (stderr);
  va_list args;
  va_start (args, fmt);

  if (fmt && fmt[0] != '\0') // Check if format string is not empty
    {
      fprintf (stderr,
               "< 💣 > th_id=%zu time=%zu |> file=%-25s line=%-4d deep=%-2d "
               "function=%-30s function_id=%-14p parents=<%s> |> "
               "position=punctual |> ",
               pthread_self () % 1000,
               (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
               basename ((char *)file), line, deep, func, *(buffer + 2),
               parents);
      vfprintf (stderr, fmt, args);
    }

  fprintf (stderr, "\n"); // Always add a newline to stderr for formatting

  va_end (args);
  funlockfile (stderr);

  free (buffer);
  free (parents);
}

#if DEBUG >= 1

void
log_error (const char *file, int line, const char *func, const char *fmt, ...)
{
  struct timespec timespec;
  clock_gettime (CLOCK_MONOTONIC, &timespec);

  void **buffer = (void **)malloc (50 * sizeof (void *));
  if (!buffer)
    return;

  int deep = backtrace (buffer, 50);
  void **deep_ptr = buffer;

  char *parents = (char *)malloc ((size_t)(deep * 15) * sizeof (char));
  if (!parents)
    {
      free (buffer);
      return;
    }
  char *parents_ptr = parents;

  for (int i = 0; i < deep; i++)
    {
      if ((i > 0) && (i < deep))
        {
          *parents_ptr = ',';
          ++parents_ptr;
        }
      sprintf (parents_ptr, "%p", *deep_ptr);
      parents_ptr += 14;
      deep_ptr++;
    }

  flockfile (stderr);
  va_list args;
  va_start (args, fmt);

  if (fmt && fmt[0] != '\0') // Check if format string is not empty
    {
      fprintf (stderr,
               "< ⏰ > th_id=%zu time=%zu |> file=%-25s line=%-4d "
               "deep=%-2d function=%-30s function_id=%-14p "
               "parents=<%s> |> position=punctual |> ",
               pthread_self () % 1000,
               (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
               basename ((char *)file), line, deep, func, *(buffer + 2),
               parents);
      vfprintf (stderr, fmt, args);
    }

  fprintf (stderr, "\n");

  va_end (args);
  funlockfile (stderr);

  free (buffer);
  free (parents);
}

#if DEBUG >= 2

void
log_warn (const char *file, int line, const char *func, const char *fmt, ...)
{
  struct timespec timespec;
  clock_gettime (CLOCK_MONOTONIC, &timespec);

  void **buffer = (void **)malloc (50 * sizeof (void *));
  if (!buffer)
    return;

  int deep = backtrace (buffer, 50);
  void **deep_ptr = buffer;

  char *parents = (char *)malloc ((size_t)(deep * 15) * sizeof (char));
  if (!parents)
    {
      free (buffer);
      return;
    }
  char *parents_ptr = parents;

  for (int i = 0; i < deep; i++)
    {
      if ((i > 0) && (i < deep))
        {
          *parents_ptr = ',';
          ++parents_ptr;
        }
      sprintf (parents_ptr, "%p", *deep_ptr);
      parents_ptr += 14;
      deep_ptr++;
    }

  flockfile (stderr);
  va_list args;
  va_start (args, fmt);

  if (fmt && fmt[0] != '\0') // Check if format string is not empty
    {
      fprintf (stderr,
               "< ❗ > th_id=%zu time=%zu |> file=%-25s line=%-4d "
               "deep=%-2d function=%-30s function_id=%-14p "
               "parents=<%s> |> position=punctual |> ",
               pthread_self () % 1000,
               (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
               basename ((char *)file), line, deep, func, *(buffer + 2),
               parents);
      vfprintf (stderr, fmt, args);
    }

  fprintf (stderr, "\n");

  va_end (args);
  funlockfile (stderr);

  free (buffer);
  free (parents);
}

#if DEBUG >= 3

void
log_init (const char *file, int line, const char *func, const char *fmt, ...)
{
  struct timespec timespec;
  clock_gettime (CLOCK_MONOTONIC, &timespec);

  void **buffer = (void **)malloc (50 * sizeof (void *));
  if (!buffer)
    return;

  int deep = backtrace (buffer, 50);
  void **deep_ptr = buffer;

  char *parents = (char *)malloc ((size_t)(deep * 15) * sizeof (char));
  if (!parents)
    {
      free (buffer);
      return;
    }
  char *parents_ptr = parents;

  for (int i = 0; i < deep; i++)
    {
      if ((i > 0) && (i < deep))
        {
          *parents_ptr = ',';
          ++parents_ptr;
        }
      sprintf (parents_ptr, "%p", *deep_ptr);
      parents_ptr += 14;
      deep_ptr++;
    }

  flockfile (stderr);
  va_list args;
  va_start (args, fmt);

  if (fmt && fmt[0] != '\0') // Check if format string is not empty
    {
      fprintf (stderr,
               "< 📘 > th_id=%zu time=%zu |> file=%-25s line=%-4d "
               "deep=%-2d function=%-30s function_id=%-14p "
               "parents=<%s> |> position=init     |> ",
               pthread_self () % 1000,
               (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
               basename ((char *)file), line, deep, func, *(buffer + 2),
               parents);
      vfprintf (stderr, fmt, args);
    }

  fprintf (stderr, "\n");

  va_end (args);
  funlockfile (stderr);

  free (buffer);
  free (parents);
}

void
log_end (const char *file, int line, const char *func, const char *fmt, ...)
{
  struct timespec timespec;
  clock_gettime (CLOCK_MONOTONIC, &timespec);

  void **buffer = (void **)malloc (50 * sizeof (void *));
  if (!buffer)
    return;

  int deep = backtrace (buffer, 50);
  void **deep_ptr = buffer;

  char *parents = (char *)malloc ((size_t)(deep * 15) * sizeof (char));
  if (!parents)
    {
      free (buffer);
      return;
    }
  char *parents_ptr = parents;

  for (int i = 0; i < deep; i++)
    {
      if ((i > 0) && (i < deep))
        {
          *parents_ptr = ',';
          ++parents_ptr;
        }
      sprintf (parents_ptr, "%p", *deep_ptr);
      parents_ptr += 14;
      deep_ptr++;
    }

  flockfile (stderr);
  va_list args;
  va_start (args, fmt);

  if (fmt && fmt[0] != '\0') // Check if format string is not empty
    {
      fprintf (stderr,
               "< 📘 > th_id=%zu time=%zu |> file=%-25s line=%-4d "
               "deep=%-2d function=%-30s function_id=%-14p "
               "parents=<%s> |> position=end      |> ",
               pthread_self () % 1000,
               (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
               basename ((char *)file), line, deep, func, *(buffer + 2),
               parents);
      vfprintf (stderr, fmt, args);
    }

  fprintf (stderr, "\n");

  va_end (args);
  funlockfile (stderr);

  free (buffer);
  free (parents);
}

void
log_debug (const char *file, int line, const char *func, const char *fmt, ...)
{
  struct timespec timespec;
  clock_gettime (CLOCK_MONOTONIC, &timespec);

  void **buffer = (void **)malloc (50 * sizeof (void *));
  if (!buffer)
    return;

  int deep = backtrace (buffer, 50);
  void **deep_ptr = buffer;

  char *parents = (char *)malloc ((size_t)(deep * 15) * sizeof (char));
  if (!parents)
    {
      free (buffer);
      return;
    }
  char *parents_ptr = parents;

  for (int i = 0; i < deep; i++)
    {
      if ((i > 0) && (i < deep))
        {
          *parents_ptr = ',';
          ++parents_ptr;
        }
      sprintf (parents_ptr, "%p", *deep_ptr);
      parents_ptr += 14;
      deep_ptr++;
    }

  flockfile (stderr);
  va_list args;
  va_start (args, fmt);

  if (fmt && fmt[0] != '\0') // Check if format string is not empty
    {
      fprintf (stderr,
               "< 📘 > th_id=%zu time=%zu |> file=%-25s line=%-4d deep=%-2d "
               "function=%-30s function_id=%-14p parents=<%s> |> "
               "position=punctual |> ",
               pthread_self () % 1000,
               (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
               basename ((char *)file), line, deep, func, *(buffer + 2),
               parents);
      vfprintf (stderr, fmt, args);
    }

  fprintf (stderr, "\n");

  va_end (args);
  funlockfile (stderr);

  free (buffer);
  free (parents);
}

#endif // DEBUG >= 3
#endif // DEBUG >= 2
#endif // DEBUG >= 1
#endif // DEBUG >= 0

#endif // LOGGER_H

