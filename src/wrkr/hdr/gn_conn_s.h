#ifndef GN_CONN_S_H
#define GN_CONN_S_H

#include <wrkr/hdr/gn_lstnr_conf_s.h>

typedef struct gn_conn_s gn_conn_s;

struct gn_conn_s
{
  int               fd;
  char *            saddr;
  uint16_t          sport;
  char *            daddr;
  gn_lstnr_conf_s * lstnr_conf; // For dport.
  gn_conn_s *       prev;
  gn_conn_s *       next;
};

#endif // GN_CONN_S_H
