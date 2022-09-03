#ifndef GN_NEW_CONN_LIST_S_H
#define GN_NEW_CONN_LIST_S_H

#include <wrkr/hdr/gn_conn_s.h>

#include <stdatomic.h>
#include <stddef.h>

typedef struct gn_new_conn_list_s gn_new_conn_list_s;

/*
 * TODO: Add description.
 */

struct gn_new_conn_list_s
{
  atomic_uintptr_t     lock;
  gn_conn_s *          head;
  gn_conn_s *          tail;
  uint8_t              len;
  gn_new_conn_list_s * prev;
  gn_new_conn_list_s * next;
};

#endif // GN_NEW_CONN_LIST_S_H
