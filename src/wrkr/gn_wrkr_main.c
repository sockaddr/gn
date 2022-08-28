#include <wrkr/hdr/gn_wrkr_main.h>

void
gn_wrkr_main (void)
{
  gn_conn_mgmt_thrd_conf_list_s conn_mgmt_thrd_conf_list;
  // Start connection management threads.
  gn_start_conn_mgmt_thrds (&conn_mgmt_thrd_conf_list);
}
