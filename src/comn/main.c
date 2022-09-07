#include <comn/hdr/main.h>

// Test code start. TODO: Fix.

#include <errno.h>
#include <error.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PROC_PATH_SZ 32
#define SELF_PATH_SZ 65536

char *
gn_self_path (uint8_t * const err)
{
  char proc_path[PROC_PATH_SZ];
  memset (proc_path, 0, PROC_PATH_SZ);

  const int rsnprintf = snprintf (proc_path, PROC_PATH_SZ, "/proc/%i/exe", getpid ());
  if (rsnprintf < 0) {
    error_at_line (0, 0, __FILE__, __LINE__, "snprintf() returned %i", rsnprintf);
    if (err != NULL) *err = 1;
    goto end;
  }

  if ((size_t)rsnprintf >= PROC_PATH_SZ) {
    error_at_line (0, 0, __FILE__, __LINE__, "snprintf() returned %i", rsnprintf);
    if (err != NULL) *err = 2;
    goto end;
  }


  char self_path_tmp[SELF_PATH_SZ];
  memset (self_path_tmp, 0, SELF_PATH_SZ);
  ssize_t rreadlink = readlink (proc_path, self_path_tmp, SELF_PATH_SZ);
  if (rreadlink < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "readlink() returned %li", rreadlink);
    if (err != NULL) *err = 3;
    goto end;
  }
  printf ("rreadlink() returned %li\n", rreadlink);
  if (rreadlink == SELF_PATH_SZ) {
    error_at_line (0, 0, __FILE__, __LINE__, "readlink() returned %li", rreadlink);
    if (err != NULL) *err = 4;
    goto end;
  }

  const size_t self_path_tmp_len = (size_t)rreadlink;
  self_path_tmp[self_path_tmp_len] = '\0';

  const size_t self_path_sz = self_path_tmp_len + 1;
  char * const self_path = malloc (self_path_sz);
  if (self_path == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "malloc(%li) failed", self_path_sz);
    if (err != NULL) *err = 5;
    goto end;
  }

  strncpy (self_path, self_path_tmp, self_path_sz);
  return self_path;

  end: ;
  return NULL;
}

void
gn_start_wrkr (char * const self_path)
{
  const pid_t rfork = fork ();
  switch (rfork) {
    case 0: { // Child
      char * const argv[3] = {self_path, "--worker", NULL};
      execv (self_path, argv);
      break;
    }
    case -1: {
      break;
    }
    default: { // Parent
    }
  }
}

void
gn_start_wrkrs (char * const self_path)
{
  for (uint8_t i = 0; i < 2; i++) {
    gn_start_wrkr (self_path);
  }
}

void
gn_mstr_main (void)
{
  char * const self_path = gn_self_path (NULL);
  printf ("Self path: '%s'\n", self_path);
  gn_start_wrkrs (self_path);

  while (true) { // Main master loop.
    sleep (1);
  }

  free (self_path);
}

// Test code end.

int
main (const int argc, const char * const * const argv)
{
  // To silence compiler error "unused parameter argc/argv"
  if (argc < 0 && argv) {} // TODO: Remove.

  if (argc == 2 && strcmp (argv[1], "--worker") == 0) gn_wrkr_main ();
  else gn_mstr_main ();

  return 0; // TODO: Return a variable.
}
