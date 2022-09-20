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

bool
gn_gen_ipc_path (struct sockaddr_un * const ipc_addr)
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

/*
 * TODO: Add description.
 */

uint8_t
gn_mstr_main (void)
{
  // Test code, start
  if (signal (SIGINT, sigint_handler) == SIG_ERR) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to register SIGINT handler");
  }
  // Test code, end

  gn_mstr_cfg_s mc;
  gn_mstr_cfg_ini (&mc);

  uint8_t gn_self_path_err = 0; // TODO: Maybe do something with this variable.
  mc.self_path = gn_self_path (&gn_self_path_err);
  if (mc.self_path == NULL) return 1;

  int ret = 0;

  if (gn_gen_ipc_path (&mc.ipc_addr)) {
    ret = 1;
    goto lbl_err_ipc_path;
  }

  gn_ipc_create (&mc);

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

  lbl_err_ipc_path:
  free (mc.self_path);

  return ret;
}
