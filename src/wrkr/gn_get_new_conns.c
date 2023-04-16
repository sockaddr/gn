#include <wrkr/hdr/gn_get_new_conns.h>

/*
 * TODO: Add description.
 */

void
gn_get_new_conns (gn_new_conn_list_list_s * const ncll, gn_conn_list_s * const list)
{
  // Take the first (list of new connections) from the (list of new connections lists).
  gn_new_conn_list_s * new_conn_list = ncll->head;

  // Go through each (new connections list) in the (list of new connections lists).
  for (uint8_t i = 0; i < ncll->len; new_conn_list = new_conn_list->next, i++)
  {
    // Try to lock the new connections list.
    uintptr_t exp = (uintptr_t)NULL;
    if (!atomic_compare_exchange_strong_explicit (&new_conn_list->lock, &exp, (uintptr_t)&exp, memory_order_relaxed, memory_order_relaxed)) {
      continue; // Can't lock it. Try the next list.
    }

    // If we're here it means we locked the list.
    while (new_conn_list->len > 0) // Empty the new connections list.
    {
      gn_conn_s * new_conn = new_conn_list->head; // Take the first connection in the list.
      gn_new_conn_list_pop (new_conn_list); // Remove the first connection from the list.
      gn_conn_list_push_back (list, new_conn); // Add the connection to the thread's connections list.
    }

    atomic_store_explicit (&new_conn_list->lock, (uintptr_t)NULL, memory_order_relaxed); // Unlock the list.
  }

  // Makes the thread's doubly-linked list NULL-ended.
  // if (list->tail != NULL) list->tail->next = NULL;
}
