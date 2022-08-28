#include <wrkr/hdr/gn_start_conn_mgmt_thrds.h>

void
gn_start_conn_mgmt_thrds (gn_conn_mgmt_thrd_conf_list_s * const list)
{
  if (list == 0) return; // TODO: Remove.
  /* Number of connection management threads to start. size_t would be too large.
     uint8_t might be too small for servers handling large amounts of connections.
   */
  const uint16_t conn_mgmt_thrd_num = 4; // TODO: Set this from config file. Maybe rename.

  for (uint16_t i = 0; i < conn_mgmt_thrd_num; i++) {
    pthread_t thrd_id;
    const int rpthread_create = pthread_create (&thrd_id, NULL, gn_conn_mgmt_thrd, NULL);
    switch (rpthread_create) {
    }
  }
}
