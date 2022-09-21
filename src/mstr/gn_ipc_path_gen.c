#include <mstr/hdr/gn_ipc_path_gen.h>

/*
 * gn_ipc_path_gen() - Generate path for master/worker IPC.
 * @ipc_addr: sockaddr_un structure to store the generated path.
 *
 * This function gets the system time and transforms the number of seconds and nanoseconds from integers to hex strings.
 * These strings are concatenated to form the Unix socket "path". This path isn't on the filesystem, that's why the
 * first byte is '\0'.
 *
 * The 'A' character in the snprintf() string is there because GCC cannot compile if the string starts with '\0' and Gn
 * is compiled with the -Werror switch. GCC will say "warning: embedded ‘\0’ in format [-Wformat-contains-nul]".
 * After the path is generated 'A' is replaced by '\0'.
 *
 * Return: This function returns false on success or true if clock_gettime() or snprintf() fails.
 */

bool
gn_ipc_path_gen (struct sockaddr_un * const ipc_addr)
{
  struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
  const int rclock_gettime = clock_gettime (CLOCK_REALTIME, &ts);
  if (rclock_gettime != 0) {
    fprintf (stderr, "clock_gettime() failed (%s)\n", strerror (errno));
    return true;
  }

  // Generate Unix socket name. sun_path[0] must be '\0'.
  const int rsnprintf = snprintf (ipc_addr->sun_path, sizeof (ipc_addr->sun_path), "A%lx%lx", ts.tv_sec, ts.tv_nsec);
  if (rsnprintf < 0) {
    fprintf (stderr, "snprintf(ipc_addr->sun_path) error %i\n", rsnprintf);
    return true;
  }

  if ((size_t)rsnprintf >= sizeof (ipc_addr->sun_path)) {
    fprintf (stderr, "snprintf(ipc_addr->sun_path) buffer too small (%i bytes needed)\n", rsnprintf);
    return true;
  }

  ipc_addr->sun_path[0] = '\0';
  return false;
}
