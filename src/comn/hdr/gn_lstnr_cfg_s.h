#ifndef GN_LSTNR_CFG_S_H
#define GN_LSTNR_CFG_S_H

#include <stdint.h>

/*
 * TODO: Add description.
 */

// Check gn_lstnr_cfg_ini() after modifying this struct.

typedef struct gn_lstnr_cfg_s gn_lstnr_cfg_s;

struct gn_lstnr_cfg_s
{
  int              fd;
  char *           addr;
  uint16_t         port;
  gn_lstnr_cfg_s * prev;
  gn_lstnr_cfg_s * next;
};

#endif // GN_LSTNR_CFG_S_H
