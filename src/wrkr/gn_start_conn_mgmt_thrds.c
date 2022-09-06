#include <wrkr/hdr/gn_start_conn_mgmt_thrds.h>

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_start_conn_mgmt_thrds (gn_wrkr_conf_s * const wc)
{
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

    if (!gn_start_conn_mgmt_thrd (wc, tc)) continue;

    // TODO: Free conn_mgmt_thrd_conf members.
    // TODO: &conn_mgmt_thrd_conf->new_conn_list_list not emptied.
    free (tc);
    tc = NULL;
  }
}
