#include <mstr/hdr/gn_ipc_create.h>

void
gn_ipc_create (gn_mstr_cfg_s * const mc)
{
  mc->ipc_fd = socket (AF_UNIX, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, 0);
  if (mc->ipc_fd < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to create IPC socket");
    return;
  }

  if (bind (mc->ipc_fd, (struct sockaddr *)&mc->ipc_addr, sizeof (mc->ipc_addr)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to bind IPC socket");
    goto lbl_end;
  }

  // TODO: Maybe call listen() at the last time after other checks/etc are done.

  if (listen (mc->ipc_fd, 32) != 0) { // Chose random value 32...
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to listen on IPC socket");
    goto lbl_end;
  }

  return;

  lbl_end:
  close (mc->ipc_fd);
  mc->ipc_fd = -1;
  return;
}
