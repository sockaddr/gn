#include <mstr/hdr/gn_ipc_path_gen.h>

bool
gn_ipc_path_gen (struct sockaddr_un * const ipc_addr)
{
  struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
  const int rclock_gettime = clock_gettime (CLOCK_REALTIME, &ts);
  if (rclock_gettime != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "clock_gettime() failed");
    return true;
  }

  // Generate Unix socket name. sun_path[0] must be '\0'.
  snprintf (ipc_addr->sun_path, sizeof (ipc_addr->sun_path), "A%lx%lx", ts.tv_sec, ts.tv_nsec); // TODO: Check error.
  ipc_addr->sun_path[0] = '\0';
  return false;
}
