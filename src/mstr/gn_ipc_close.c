#include <mstr/hdr/gn_ipc_close.h>

/*
 * TODO: Add description.
 */

void
gn_ipc_close (int * const ipc_fd)
{
  const int rclose = close (*ipc_fd);
  *ipc_fd = -1;
  if (rclose == 0) return;

  fprintf (stderr, "Failed to close IPC socket (%s)\n", strerror (errno));
}
