#ifndef GN_LSTNR_CONF_LIST_S_H
#define GN_LSTNR_CONF_LIST_S_H

#include <comn/hdr/gn_lstnr_conf_s.h>

struct gn_lstnr_conf_list_s
{
  gn_lstnr_conf_s * head;
  gn_lstnr_conf_s * tail;
  uint16_t          len;
};

typedef struct gn_lstnr_conf_list_s gn_lstnr_conf_list_s;

#endif // GN_LSTNR_CONF_LIST_S_H
