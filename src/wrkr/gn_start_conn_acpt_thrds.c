#include <wrkr/hdr/gn_start_conn_acpt_thrds.h>

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_start_conn_acpt_thrds (gn_conn_acpt_thrd_conf_list_s * const list)
{
  /* Number of connection acceptance threads to start. Something larger than uint8_t might be too much.
   * We'll have to test it.
   */
  const uint8_t conn_acpt_thrd_num = 4; // TODO: Set this from config file. Maybe rename.

  for (uint8_t i = 0; i < conn_acpt_thrd_num; i++) {
    // If list if full, it's useless to try to allocate/push/start anything.
    if (list->len == UINT8_MAX) {
      error_at_line (0, 0, __FILE__, __LINE__, "Connection acceptance threads list is full\n");
      return;
    }

    gn_conn_acpt_thrd_conf_s * conn_acpt_thrd_conf = malloc (sizeof (gn_conn_acpt_thrd_conf_s));
    if (conn_acpt_thrd_conf == NULL) {
      // TODO: Maybe log to file and/or display.
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection acceptance thread configuration structure");
      continue;
    }

    gn_conn_acpt_thrd_conf_init (conn_acpt_thrd_conf);
    printf ("Starting connection acceptance thread (conf ptr %p)... ", conn_acpt_thrd_conf); // TODO: Remove.
    const int rpthread_create = pthread_create (&conn_acpt_thrd_conf->thrd_id, NULL, gn_conn_acpt_thrd, conn_acpt_thrd_conf);
    switch (rpthread_create) {
      case 0: {
        (void)! gn_conn_acpt_thrd_conf_list_push_back (list, conn_acpt_thrd_conf);
        conn_acpt_thrd_conf = NULL; // Set to NULL to avoid freeing a struct that's going to be used.
        printf ("done\n"); // TODO: Remove.
        break;
      }
      default: {
        printf ("failed\n"); // TODO: Remove.
        // TODO: Maybe log to file and/or display.
        error_at_line (0, rpthread_create, __FILE__, __LINE__, "Failed to start connection acceptance thread");
      }
    }

    if (conn_acpt_thrd_conf == NULL) continue;
    // TODO: Free conn_acpt_thrd_conf members.
    free (conn_acpt_thrd_conf);
    conn_acpt_thrd_conf = NULL;
  }
}
