#ifndef GN_CONN_S_H
#define GN_CONN_S_H

#include <comn/hdr/gn_lstnr_cfg_s.h>

/*
 * TODO: Add description.
 */

 // Check gn_conn_ini() after modifying this struct.

typedef struct gn_conn_s gn_conn_s;

struct gn_conn_s
{
  int              fd;
  char *           saddr;
  uint16_t         sport;
  char *           daddr;
  gn_lstnr_cfg_s * lstnr_cfg; // For dport.
  gn_conn_s *      prev;
  gn_conn_s *      next;
};

#endif // GN_CONN_S_H
