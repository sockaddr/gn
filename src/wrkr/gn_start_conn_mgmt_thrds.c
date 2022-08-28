#include <wrkr/hdr/gn_start_conn_mgmt_thrds.h>

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_start_conn_mgmt_thrds (gn_conn_mgmt_thrd_conf_list_s * const list)
{
  if (list == 0) return; // TODO: Remove.

  /* Number of connection management threads to start. size_t would be too large.
     uint8_t might be too small for servers handling large amounts of connections.
   */
  const uint16_t conn_mgmt_thrd_num = 4; // TODO: Set this from config file. Maybe rename.

  for (uint16_t i = 0; i < conn_mgmt_thrd_num; i++) {
    gn_conn_mgmt_thrd_conf_s * conn_mgmt_thrd_conf = malloc (sizeof (gn_conn_mgmt_thrd_conf_s));
    if (conn_mgmt_thrd_conf == NULL) {
      // TODO: Maybe log to file and/or display.
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection management thread configuration structure");
      continue;
    }

    printf ("Starting connection management thread (conf ptr %p)... ", conn_mgmt_thrd_conf); // TODO: Remove.
    const int rpthread_create = pthread_create (&conn_mgmt_thrd_conf->thrd_id, NULL, gn_conn_mgmt_thrd, conn_mgmt_thrd_conf);
    switch (rpthread_create) {
      case 0: {
        conn_mgmt_thrd_conf = NULL; // Set to NULL to avoid freeing a struct that's going to be used.
        printf ("done\n"); // TODO: Remove.
        break;
      }
      default: {
        printf ("failed\n"); // TODO: Remove.
        // TODO: Maybe log to file and/or display.
        error_at_line (0, rpthread_create, __FILE__, __LINE__, "Failed to start thread connection management thread");
      }
    }

    if (conn_mgmt_thrd_conf == NULL) continue;
    free (conn_mgmt_thrd_conf);
    conn_mgmt_thrd_conf = NULL;
  }
}
