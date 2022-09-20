#include <wrkr/hdr/gn_start_conn_mgmt_thrd.h>

#include <error.h> // TODO: Remove.
#include <stdio.h> // TODO: Remove.

/*
 * TODO: Add description.
 */

bool
gn_start_conn_mgmt_thrd (gn_wrkr_cfg_s * const wc, gn_conn_mgmt_thrd_conf_s * const tc)
{
  printf ("Starting connection management thread (conf ptr %p)... ", tc); // TODO: Remove.

  const int rcreate = pthread_create (&tc->thrd_id, NULL, gn_conn_mgmt_thrd, tc);
  if (rcreate != 0) {
    printf ("failed\n"); // TODO: Remove.
    // TODO: Maybe log to file and/or display.
    error_at_line (0, rcreate, __FILE__, __LINE__, "Failed to start connection management thread");
    return true;
  }

  const int rdetach = pthread_detach (tc->thrd_id);
  (void)! gn_conn_mgmt_thrd_conf_list_push_back (&wc->conn_mgmt_thrd_conf_list, tc);
  printf ("done\n"); // TODO: Remove.
  if (rdetach != 0) error_at_line (0, rdetach, __FILE__, __LINE__, "pthread_detach() failed");

  return false;
}
