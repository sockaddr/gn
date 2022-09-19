#ifndef GN_LSTNR_CFG_LST_S_H
#define GN_LSTNR_CFG_LST_S_H

#include <comn/hdr/gn_lstnr_conf_s.h>

/*
 * TODO: Add description.
 */

// Check gn_lstnr_cfg_lst_ini() after modifying this struct.

struct gn_lstnr_cfg_lst_s
{
  gn_lstnr_conf_s * head;
  gn_lstnr_conf_s * tail;
  uint16_t          len;
};

typedef struct gn_lstnr_cfg_lst_s gn_lstnr_cfg_lst_s;

#endif // GN_LSTNR_CFG_LST_S_H
