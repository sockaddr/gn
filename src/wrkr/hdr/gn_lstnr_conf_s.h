#ifndef GN_LSTNR_CONF_S_H
#define GN_LSTNR_CONF_S_H

typedef struct gn_lstnr_conf_s gn_lstnr_conf_s;

struct gn_lstnr_conf_s
{
  int               fd;
  char *            addr;
  uint16_t          port;
  gn_lstnr_conf_s * prev;
  gn_lstnr_conf_s * next;
};

#endif // GN_LSTNR_CONF_S_H
