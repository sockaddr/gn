#include <wrkr/hdr/gn_start_conn_mgmt_thrds.h>

#include <stdio.h> // TODO: Remove.

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_start_conn_mgmt_thrds (gn_wrkr_conf_s * const wc)
{
  /* Number of connection management threads to start. size_t would be too large.
     uint8_t might be too small for servers handling large amounts of connections.
   */

  for (uint16_t i = 0; i < wc->conn_mgmt_thrd_num; i++) {
    // If list if full, it's useless to try to allocate/push/start anything.
    if (wc->conn_mgmt_thrd_conf_list.len == UINT16_MAX) {
      error_at_line (0, 0, __FILE__, __LINE__, "Connection management threads list is full\n");
      return;
    }

    gn_conn_mgmt_thrd_conf_s * tc = malloc (sizeof (gn_conn_mgmt_thrd_conf_s));
    if (tc == NULL) {
      // TODO: Maybe log to file and/or display.
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection management thread configuration structure");
      continue;
    }

    gn_conn_mgmt_thrd_conf_init (tc);

    // TODO. Test block to add 4 new-connection lists.
    for (uint8_t j = 0; j < 4; j++) {
      gn_new_conn_list_s * const new_conn_list = malloc (sizeof (gn_new_conn_list_s));
      if (new_conn_list != NULL) {
        gn_new_conn_list_init (new_conn_list);
        gn_new_conn_list_list_push_back (&tc->new_conn_list_list, new_conn_list);
      }
    }

    printf ("Starting connection management thread (conf ptr %p)... ", tc); // TODO: Remove.
    const int rcreate = pthread_create (&tc->thrd_id, NULL, gn_conn_mgmt_thrd, tc);
    switch (rcreate) {
      case 0: {
        const int rdetach = pthread_detach (tc->thrd_id);
        (void)! gn_conn_mgmt_thrd_conf_list_push_back (&wc->conn_mgmt_thrd_conf_list, tc);
        tc = NULL; // Set to NULL to avoid freeing a struct that's going to be used.
        printf ("done\n"); // TODO: Remove.
        if (rdetach != 0) error_at_line (0, rdetach, __FILE__, __LINE__, "pthread_detach() failed");
        break;
      }
      default: {
        printf ("failed\n"); // TODO: Remove.
        // TODO: Maybe log to file and/or display.
        error_at_line (0, rcreate, __FILE__, __LINE__, "Failed to start connection management thread");
      }
    }

    if (tc == NULL) continue;
    // TODO: Free conn_mgmt_thrd_conf members.
    // TODO: &conn_mgmt_thrd_conf->new_conn_list_list not emptied.
    free (tc);
    tc = NULL;
  }
}
