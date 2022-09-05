#include <wrkr/hdr/gn_pass_conn.h>

/*
 * TODO: Add description.
 */

bool
gn_pass_conn (const gn_conn_mgmt_thrd_conf_list_s * const conn_mgmt_thrd_conf_list, gn_conn_s * const conn)
{
  gn_conn_mgmt_thrd_conf_s * conn_mgmt_thrd_conf = conn_mgmt_thrd_conf_list->head;

  for (uint16_t i = 0; i < conn_mgmt_thrd_conf_list->len; conn_mgmt_thrd_conf = conn_mgmt_thrd_conf->next, i++)
  {
    const gn_new_conn_list_list_s * const new_conn_list_list = &conn_mgmt_thrd_conf->new_conn_list_list;
    gn_new_conn_list_s * new_conn_list = new_conn_list_list->head;

    for (uint8_t j = 0; j < new_conn_list_list->len; new_conn_list = new_conn_list->next, j++)
    {
      uintptr_t exp = (uintptr_t)NULL;
      if (!atomic_compare_exchange_strong_explicit (&new_conn_list->lock, &exp, (uintptr_t)&exp, memory_order_relaxed, memory_order_relaxed)) continue;
      gn_new_conn_list_push_back (new_conn_list, conn); // TODO: Check if list is full.
      atomic_store_explicit (&new_conn_list->lock, (uintptr_t)NULL, memory_order_relaxed);
      return false; // Connection was passed.
    }
  }

  return true; // Connection wasn't passed.
}
