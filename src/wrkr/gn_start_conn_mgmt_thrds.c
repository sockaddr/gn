#include <wrkr/hdr/gn_start_conn_mgmt_thrds.h>

#include <stdio.h> // TODO: Remove.

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_start_conn_mgmt_thrds (gn_wrkr_conf_s * const wrkr_conf)
{
  /* Number of connection management threads to start. size_t would be too large.
     uint8_t might be too small for servers handling large amounts of connections.
   */

  for (uint16_t i = 0; i < wrkr_conf->conn_mgmt_thrd_num; i++) {
    // If list if full, it's useless to try to allocate/push/start anything.
    if (wrkr_conf->conn_mgmt_thrd_conf_list.len == UINT16_MAX) {
      error_at_line (0, 0, __FILE__, __LINE__, "Connection management threads list is full\n");
      return;
    }

    gn_conn_mgmt_thrd_conf_s * conn_mgmt_thrd_conf = malloc (sizeof (gn_conn_mgmt_thrd_conf_s));
    if (conn_mgmt_thrd_conf == NULL) {
      // TODO: Maybe log to file and/or display.
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection management thread configuration structure");
      continue;
    }

    gn_conn_mgmt_thrd_conf_init (conn_mgmt_thrd_conf);

    // TODO. Test block to add 4 new-connection lists.
    for (uint8_t j = 0; j < 4; j++) {
      gn_new_conn_list_s * const new_conn_list = malloc (sizeof (gn_new_conn_list_s));
      if (new_conn_list != NULL) {
        gn_new_conn_list_init (new_conn_list);
        gn_new_conn_list_list_push_back (&conn_mgmt_thrd_conf->new_conn_list_list, new_conn_list);
      }
    }

    printf ("Starting connection management thread (conf ptr %p)... ", conn_mgmt_thrd_conf); // TODO: Remove.
    const int rpthread_create = pthread_create (&conn_mgmt_thrd_conf->thrd_id, NULL, gn_conn_mgmt_thrd, conn_mgmt_thrd_conf);
    switch (rpthread_create) {
      case 0: {
        const int rpthread_detach = pthread_detach (conn_mgmt_thrd_conf->thrd_id);
        (void)! gn_conn_mgmt_thrd_conf_list_push_back (&wrkr_conf->conn_mgmt_thrd_conf_list, conn_mgmt_thrd_conf);
        conn_mgmt_thrd_conf = NULL; // Set to NULL to avoid freeing a struct that's going to be used.
        printf ("done\n"); // TODO: Remove.
        if (rpthread_detach != 0) error_at_line (0, rpthread_detach, __FILE__, __LINE__, "pthread_detach() failed");
        break;
      }
      default: {
        printf ("failed\n"); // TODO: Remove.
        // TODO: Maybe log to file and/or display.
        error_at_line (0, rpthread_create, __FILE__, __LINE__, "Failed to start connection management thread");
      }
    }

    if (conn_mgmt_thrd_conf == NULL) continue;
    // TODO: Free conn_mgmt_thrd_conf members.
    // TODO: &conn_mgmt_thrd_conf->new_conn_list_list not emptied.
    free (conn_mgmt_thrd_conf);
    conn_mgmt_thrd_conf = NULL;
  }
}
