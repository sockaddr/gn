#include <wrkr/hdr/gn_get_new_conns.h>

/*
 * TODO: Add description.
 */

void
gn_get_new_conns (gn_new_conn_list_list_s * const ncll, gn_conn_list_s * const list)
{
  gn_new_conn_list_s * new_conn_list = ncll->head;

  for (uint8_t i = 0; i < ncll->len; new_conn_list = new_conn_list->next, i++)
  {
    uintptr_t exp = (uintptr_t)NULL;
    if (!atomic_compare_exchange_strong_explicit (&new_conn_list->lock, &exp, (uintptr_t)&exp, memory_order_relaxed, memory_order_relaxed)) continue;

    while (new_conn_list->len > 0) {
      gn_conn_s * new_conn = new_conn_list->head;
      gn_new_conn_list_pop (new_conn_list);
      gn_conn_list_push_back (list, new_conn);
    }

    atomic_store_explicit (&new_conn_list->lock, (uintptr_t)NULL, memory_order_relaxed);
  }
  if (list->tail != NULL) list->tail->next = NULL;
}
