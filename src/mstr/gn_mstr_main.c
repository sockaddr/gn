#include <mstr/hdr/gn_mstr_main.h>

// Test code, start
#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>

volatile bool sigint_rcvd = false;

void
sigint_handler (const int s)
{
  printf ("Master received signal %i\n", s);
  sigint_rcvd = true;
}
// Test code, end

/*
 * TODO: Add description.
 */

uint8_t
gn_mstr_main (void)
{
  // TODO: Remove. This is just for testing a server stop.
  if (signal (SIGINT, sigint_handler) == SIG_ERR) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to register SIGINT handler");
  }

  gn_mstr_cfg_s mc;
  gn_mstr_cfg_ini (&mc);

  uint8_t gn_self_path_err = 0; // TODO: Maybe do something with this variable.
  mc.self_path = gn_self_path (&gn_self_path_err);
  if (mc.self_path == NULL) return 1;

  struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
  const int rclock_gettime = clock_gettime (CLOCK_REALTIME, &ts);
  if (rclock_gettime != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "clock_gettime() failed");
    return 1; // TODO: mc.self_path not freed.
  }

  // Generate Unix socket name. sun_path[0] must be '\0'.
  snprintf (mc.wrkr_io_addr.sun_path, sizeof (mc.wrkr_io_addr.sun_path), "A%lx%lx", ts.tv_sec, ts.tv_nsec); // TODO: Check error.
  mc.wrkr_io_addr.sun_path[0] = '\0';

  // Create Unix socket for master/worker IO.
  mc.wrkr_io_fd = socket (AF_UNIX, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, 0);
  if (mc.wrkr_io_fd < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "sun socket() failed");
    return 1; // TODO: mc.self_path not freed.
  }

  if (bind (mc.wrkr_io_fd, (struct sockaddr *)&mc.wrkr_io_addr, sizeof (mc.wrkr_io_addr)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "sun bind() failed");
    return 1; // TODO: mc.self_path not freed.
  }

  // TODO: Maybe call listen() at the last time after other checks/etc are done.

  if (listen (mc.wrkr_io_fd, 32) != 0) { // Chose random value 32...
    error_at_line (0, errno, __FILE__, __LINE__, "sun listen() failed");
    return 1; // TODO: mc.self_path not freed.
  }

  // TODO: Load master config.
  mc.wrkrs_num = 2;

  // Test code, start
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "0.0.0.0", 8080);
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "192.168.2.2", 8081);
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "127.0.0.1", 8082);
  // Test code, end

  gn_start_wrkrs (&mc); // TODO: Maybe use returned value.

  while (true) { // Main master loop.
    // TODO: Remove block below.
    if (sigint_rcvd) {
      printf ("Master received SIGINT.\n");
      break;
    }

    sleep (1); // TODO: Remove.
  }

  while (mc.lstnr_cfg_lst.len > 0) {
    gn_lstnr_cfg_s * const lc = mc.lstnr_cfg_lst.head;
    (void)! gn_lstnr_cfg_lst_pop (&mc.lstnr_cfg_lst);
    close (lc->fd);
    free (lc);
  }

  free (mc.self_path);
  return 0;
}
