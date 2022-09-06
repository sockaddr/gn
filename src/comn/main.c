#include <comn/hdr/main.h>

// Test code start. TODO: Fix.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
gn_self_path (char ** self_path)
{
  char proc_path[1024];
  sprintf (proc_path, "/proc/%i/exe", getpid ());
  char self_path_tmp[4096];
  memset (self_path_tmp, 0, sizeof (self_path_tmp));
  ssize_t rreadlink = readlink (proc_path, self_path_tmp, sizeof (self_path_tmp));
  *self_path = malloc ((size_t)rreadlink + 1);
  strcpy (*self_path, self_path_tmp);
}

void
gn_mstr_main (void)
{
  char * self_path = NULL;
  gn_self_path (&self_path);
  printf ("Self path: '%s'\n", self_path);

  for (uint8_t i = 0; i < 2; i++) {
    const pid_t rfork = fork ();
    switch (rfork) {
      case 0: { // Child
        char * argv[3] = {self_path, "--worker", NULL};
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
