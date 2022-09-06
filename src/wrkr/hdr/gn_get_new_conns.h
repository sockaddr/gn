 #ifndef GN_GET_NEW_CONNS_H
 #define GN_GET_NEW_CONNS_H

#include <wrkr/hdr/gn_new_conn_list_list_s.h>
#include <wrkr/hdr/gn_conn_list_s.h>

bool gn_conn_list_push_back (gn_conn_list_s * const, gn_conn_s * const)
  __attribute__((hot)) __attribute__((nonnull));

void gn_new_conn_list_pop (gn_new_conn_list_s * const)
  __attribute__((hot)) __attribute__((nonnull));

#endif // GN_GET_NEW_CONNS_H
