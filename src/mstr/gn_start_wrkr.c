#include <mstr/hdr/gn_start_wrkr.h>

/*
 * TODO: Add description.
 */

bool
gn_start_wrkr (const gn_mstr_cfg_s * const mc)
{
  errno = 0;
  const pid_t rfork = fork ();

  switch (rfork) {
    case 0: { // Child
      char * const argv[4] = {mc->self_path, "--ipc-addr", (char *)&mc->ipc_addr.sun_path[1], NULL};
      const int rexecv = execv (mc->self_path, argv);
      if (rexecv == -1) fprintf (stderr, "Failed to execute worker process (%s)\n", strerror (errno));
      else fprintf (stderr, "Unexpected execv() error. Code %i, errno %i (%s)\n", rexecv, errno, strerror (errno));
      exit (1);
    }
    case -1: {
      fprintf (stderr, "Failed to fork worker process (%s)\n", strerror (errno));
      return true;
    }
    default: { // Parent
      if (rfork > 0) return false; // Success

      fprintf (stderr, "Unexpected fork() error. Code %i, errno %i (%s)\n", rfork, errno, strerror (errno));
      return true;
    }
  }
}
