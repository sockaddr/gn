#ifndef GN_NEW_CONN_LIST_LIST_S_H
#define GN_NEW_CONN_LIST_LIST_S_H

#include <wrkr/hdr/gn_new_conn_list_s.h>

/*
 * TODO: Add description.
 */

struct gn_new_conn_list_list_s
{
  gn_new_conn_list_s * head;
  gn_new_conn_list_s * tail;
  uint8_t              len;
};

typedef struct gn_new_conn_list_list_s gn_new_conn_list_list_s;

#endif // GN_NEW_CONN_LIST_LIST_S_H
