#include "logger.h"

#if DEBUG >= 0

#include <execinfo.h>
#include <libgen.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void log_critical(const char *file, int line, const char *func, const char *fmt,
                  ...) {
  struct timespec timespec;
  clock_gettime(CLOCK_MONOTONIC, &timespec);

  // Obtener el backtrace
  void *buffer[50];
  int depth = backtrace(buffer, 50);

  // Convertir el backtrace a una cadena de direcciones
  char *addresses = malloc(depth * 20); // 20 caracteres por dirección
  if (!addresses) {
    return;
  }
  addresses[0] = '\0';
  for (int i = 0; i < depth; i++) {
    char addr[20];
    snprintf(addr, sizeof(addr), "%p%s", buffer[i], (i < depth - 1) ? "," : "");
    strcat(addresses, addr);
  }

  flockfile(stderr);
  va_list args;
  va_start(args, fmt);

  fprintf(stderr,
          "< 💣 > th_id=%zu time=%zu |> file=%s line=%d depth=%d "
          "function=%s function_id=%p parents=<%s> |> position=punctual |> ",
          pthread_self() % 1000,
          (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
          basename((char *)file), line, depth, func, (void *)func, addresses);

  if (fmt && fmt[0] != '\0') {
    vfprintf(stderr, fmt, args);
  }

  fprintf(stderr, "\n");

  va_end(args);
  funlockfile(stderr);

  free(addresses);
}

#if DEBUG >= 1

void log_error(const char *file, int line, const char *func, const char *fmt,
               ...) {
  struct timespec timespec;
  clock_gettime(CLOCK_MONOTONIC, &timespec);

  void *buffer[50];
  int depth = backtrace(buffer, 50);

  char *addresses = malloc(depth * 20);
  if (!addresses) {
    return;
  }
  addresses[0] = '\0';
  for (int i = 0; i < depth; i++) {
    char addr[20];
    snprintf(addr, sizeof(addr), "%p%s", buffer[i], (i < depth - 1) ? "," : "");
    strcat(addresses, addr);
  }

  flockfile(stderr);
  va_list args;
  va_start(args, fmt);

  fprintf(stderr,
          "< ⏰ > th_id=%zu time=%zu |> file=%s line=%d depth=%d "
          "function=%s function_id=%p parents=<%s> |> position=punctual |> ",
          pthread_self() % 1000,
          (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
          basename((char *)file), line, depth, func, (void *)func, addresses);

  if (fmt && fmt[0] != '\0') {
    vfprintf(stderr, fmt, args);
  }

  fprintf(stderr, "\n");

  va_end(args);
  funlockfile(stderr);

  free(addresses);
}

#if DEBUG >= 2

void log_warn(const char *file, int line, const char *func, const char *fmt,
              ...) {
  struct timespec timespec;
  clock_gettime(CLOCK_MONOTONIC, &timespec);

  void *buffer[50];
  int depth = backtrace(buffer, 50);

  char *addresses = malloc(depth * 20);
  if (!addresses) {
    return;
  }
  addresses[0] = '\0';
  for (int i = 0; i < depth; i++) {
    char addr[20];
    snprintf(addr, sizeof(addr), "%p%s", buffer[i], (i < depth - 1) ? "," : "");
    strcat(addresses, addr);
  }

  flockfile(stderr);
  va_list args;
  va_start(args, fmt);

  fprintf(stderr,
          "< ❗ > th_id=%zu time=%zu |> file=%s line=%d depth=%d "
          "function=%s function_id=%p parents=<%s> |> position=punctual |> ",
          pthread_self() % 1000,
          (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
          basename((char *)file), line, depth, func, (void *)func, addresses);

  if (fmt && fmt[0] != '\0') {
    vfprintf(stderr, fmt, args);
  }

  fprintf(stderr, "\n");

  va_end(args);
  funlockfile(stderr);

  free(addresses);
}

#if DEBUG >= 3

void log_init(const char *file, int line, const char *func, const char *fmt,
              ...) {
  struct timespec timespec;
  clock_gettime(CLOCK_MONOTONIC, &timespec);

  void *buffer[50];
  int depth = backtrace(buffer, 50);

  char *addresses = malloc(depth * 20);
  if (!addresses) {
    return;
  }
  addresses[0] = '\0';
  for (int i = 0; i < depth; i++) {
    char addr[20];
    snprintf(addr, sizeof(addr), "%p%s", buffer[i], (i < depth - 1) ? "," : "");
    strcat(addresses, addr);
  }

  flockfile(stderr);
  va_list args;
  va_start(args, fmt);

  fprintf(stderr,
          "< 📘 > th_id=%zu time=%zu |> file=%s line=%d depth=%d "
          "function=%s function_id=%p parents=<%s> |> position=init     |> ",
          pthread_self() % 1000,
          (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
          basename((char *)file), line, depth, func, (void *)func, addresses);

  if (fmt && fmt[0] != '\0') {
    vfprintf(stderr, fmt, args);
  }

  fprintf(stderr, "\n");

  va_end(args);
  funlockfile(stderr);

  free(addresses);
}

void log_end(const char *file, int line, const char *func, const char *fmt,
             ...) {
  struct timespec timespec;
  clock_gettime(CLOCK_MONOTONIC, &timespec);

  void *buffer[50];
  int depth = backtrace(buffer, 50);

  char *addresses = malloc(depth * 20);
  if (!addresses) {
    return;
  }
  addresses[0] = '\0';
  for (int i = 0; i < depth; i++) {
    char addr[20];
    snprintf(addr, sizeof(addr), "%p%s", buffer[i], (i < depth - 1) ? "," : "");
    strcat(addresses, addr);
  }

  flockfile(stderr);
  va_list args;
  va_start(args, fmt);

  fprintf(stderr,
          "< 📘 > th_id=%zu time=%zu |> file=%s line=%d depth=%d "
          "function=%s function_id=%p parents=<%s> |> position=end      |> ",
          pthread_self() % 1000,
          (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
          basename((char *)file), line, depth, func, (void *)func, addresses);

  if (fmt && fmt[0] != '\0') {
    vfprintf(stderr, fmt, args);
  }

  fprintf(stderr, "\n");

  va_end(args);
  funlockfile(stderr);

  free(addresses);
}

void log_debug(const char *file, int line, const char *func, const char *fmt,
               ...) {
  struct timespec timespec;
  clock_gettime(CLOCK_MONOTONIC, &timespec);

  void *buffer[50];
  int depth = backtrace(buffer, 50);

  char *addresses = malloc(depth * 20);
  if (!addresses) {
    return;
  }
  addresses[0] = '\0';
  for (int i = 0; i < depth; i++) {
    char addr[20];
    snprintf(addr, sizeof(addr), "%p%s", buffer[i], (i < depth - 1) ? "," : "");
    strcat(addresses, addr);
  }

  flockfile(stderr);
  va_list args;
  va_start(args, fmt);

  fprintf(stderr,
          "< 📘 > th_id=%zu time=%zu |> file=%s line=%d depth=%d "
          "function=%s function_id=%p parents=<%s> |> position=punctual |> ",
          pthread_self() % 1000,
          (size_t)(timespec.tv_sec * 1000000) + (timespec.tv_nsec / 1000),
          basename((char *)file), line, depth, func, (void *)func, addresses);

  if (fmt && fmt[0] != '\0') {
    vfprintf(stderr, fmt, args);
  }

  fprintf(stderr, "\n");

  va_end(args);
  funlockfile(stderr);

  free(addresses);
}

#endif // DEBUG >= 3
#endif // DEBUG >= 2
#endif // DEBUG >= 1
#endif // DEBUG >= 0
