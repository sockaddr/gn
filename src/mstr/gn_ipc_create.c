#include <mstr/hdr/gn_ipc_create.h>

/*
 * TODO: Add description.
 */

bool
gn_ipc_create (gn_mstr_cfg_s * const mc)
{
  mc->ipc_fd = socket (AF_UNIX, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, 0);
  if (mc->ipc_fd < 0) {
    fprintf (stderr, "Failed to create IPC socket (%s)\n", strerror (errno));
    return true;
  }

  if (bind (mc->ipc_fd, (struct sockaddr *)&mc->ipc_addr, sizeof (mc->ipc_addr)) == 0) return false; // Success

  fprintf (stderr, "Failed to bind IPC socket (%s)\n", strerror (errno));
  switch (errno) {
    // If we have a problem with the socket, return without trying to close it.
    case EBADF:
    case ENOTSOCK: {
      mc->ipc_fd = -1;
      return true;
    }
  }

  if (close (mc->ipc_fd) != 0) fprintf (stderr, "Failed to close IPC socket (%s)\n", strerror (errno));
  mc->ipc_fd = -1;

  return true;
}
