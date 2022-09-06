#include <wrkr/hdr/gn_start_conn_acpt_thrds.h>

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_start_conn_acpt_thrds (gn_wrkr_conf_s * const wc)
{
  /* Number of connection acceptance threads to start. Something larger than uint8_t might be too much.
   * We'll have to test it.
   */

  for (uint8_t i = 0; i < wc->conn_acpt_thrd_num; i++) {
    // If list if full, it's useless to try to allocate/push/start anything.
    if (wc->conn_acpt_thrd_conf_list.len == UINT8_MAX) {
      error_at_line (0, 0, __FILE__, __LINE__, "Connection acceptance threads list is full\n");
      return;
    }

    gn_conn_acpt_thrd_conf_s * tc = malloc (sizeof (gn_conn_acpt_thrd_conf_s));
    if (tc == NULL) {
      // TODO: Maybe log to file and/or display.
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection acceptance thread configuration structure");
      continue;
    }

    gn_conn_acpt_thrd_conf_init (tc, &wc->conn_mgmt_thrd_conf_list);

    if (!gn_start_conn_acpt_thrd (wc ,tc)) continue;

    // TODO: Free tc members.
    free (tc);
    tc = NULL;
  }
}
