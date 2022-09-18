#include <mstr/hdr/gn_start_wrkr.h>

/*
 * TODO: Add description.
 */

void
gn_start_wrkr (char * const self_path, gn_lstnr_conf_list_s * const lstnr_conf_list)
{
  // Create socket pair to send configuration and sockets to worker process.
  int sp[2] = {-1, -1}; // TODO: Store them in worker proc entry.
  const int rsocketpair = socketpair (AF_UNIX, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, 0, sp);
  if (rsocketpair != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "socketpair() failed");
    return;
  }

  const pid_t rfork = fork ();
  switch (rfork) {
    case 0: { // Child
      char * const argv[3] = {self_path, "--worker", NULL};
      execv (self_path, argv);
      error_at_line (0, errno, __FILE__, __LINE__, "execv() failed");
      exit (1);
    }
    case -1: {
      error_at_line (0, errno, __FILE__, __LINE__, "fork() failed");
      break;
    }
    default: { // Parent
      return;
    }
  }

  close (sp[0]);
  close (sp[1]);
}
