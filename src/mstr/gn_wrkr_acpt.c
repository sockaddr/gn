#include <mstr/hdr/gn_wrkr_acpt.h>

/*
 * TODO: Add description.
 */

int
gn_wrkr_acpt (const int ipc_fd)
{
  struct pollfd pfd = {
    .fd = ipc_fd,
    .events = POLLIN,
    .revents = 0
  };

  errno = 0;
  const int rpoll = poll (&pfd, 1, 3000);
  switch (rpoll) {
    case 0: {
      fprintf (stderr, "Timeout waiting for connection from worker\n");
      return -1;
    }
    case -1: {
      fprintf (stderr, "Failed to wait for connection from worker (%s)\n", strerror (errno));
      return -1;
    }
    default: {
      if (rpoll == 1) break;

      fprintf (stderr, "Unexpected poll() return value. Value %i, errno %i (%s)\n", rpoll, errno, strerror (errno));
      return -1;
    }
  }

  const int raccept4 = accept4 (ipc_fd, NULL, 0, SOCK_CLOEXEC | SOCK_NONBLOCK);
  if (raccept4 > -1) return raccept4; // TODO: Maybe goto before poll() if errno is EAGAIN/EINTR/etc.

  fprintf (stderr, "Failed to accept connection from worker (%s)\n", strerror (errno));
  return -1;
}
