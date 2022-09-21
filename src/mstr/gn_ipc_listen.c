#include <mstr/hdr/gn_ipc_listen.h>

/*
 * TODO: Add description.
 */

bool
gn_ipc_listen (int * const ipc_fd)
{
  if (listen (*ipc_fd, 32) == 0) return false; // TODO: Maybe choose another backlog value.

  fprintf (stderr, "Failed to listen on IPC socket (%s)\n", strerror (errno));
  switch (errno) {
    // If we have a problem with the socket, invalidate it to avoid closing another file descriptor.
    case EBADF:
    case ENOTSOCK: {
      *ipc_fd = -1;
      return true;
    }
  }

  return true;
}
