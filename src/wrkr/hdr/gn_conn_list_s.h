#ifndef GN_CONN_LIST_S_H
#define GN_CONN_LIST_S_H

#include <wrkr/hdr/gn_conn_s.h>

#include <stddef.h>

struct gn_conn_list_s
{
  gn_conn_s * head;
  gn_conn_s * tail;
  size_t      len;
};

typedef struct gn_conn_list_s gn_conn_list_s;

#endif // GN_CONN_LIST_S_H
