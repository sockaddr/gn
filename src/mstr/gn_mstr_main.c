#include <mstr/hdr/gn_mstr_main.h>

// Test code, start
#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>

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

  if (gn_mstr_cfg_load ("./etc/gn/gn.cfg", &mc)) {
    ret = 1;
    goto lbl_err_cfg_load;
  }

  if (gn_ipc_path_gen (&mc.ipc_addr)) {
    ret = 1;
    goto lbl_err_ipc_path;
  }

  if (gn_ipc_create (&mc)) {
    ret = 1;
    goto lbl_err_ipc_create;
  }

  // TODO: Load master config.
  mc.wrkrs_num = 1;

  // Test code, start
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "0.0.0.0", 8080);
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "192.168.2.2", 8081);
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "127.0.0.1", 8082);
  // Test code, end

  if (gn_ipc_listen (&mc.ipc_fd)) {
    ret = 1;
    goto lbl_err_ipc_listen;
  }

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

  lbl_err_ipc_listen:
  gn_ipc_close (&mc.ipc_fd);

  lbl_err_ipc_create:
  lbl_err_ipc_path:
  lbl_err_cfg_load:
  free (mc.self_path);

  return ret;
}
