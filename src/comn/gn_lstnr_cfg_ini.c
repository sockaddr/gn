#include <comn/hdr/gn_lstnr_cfg_ini.h>

/*
 * TODO: Add description.
 */

void
gn_lstnr_cfg_ini (gn_lstnr_cfg_s * const cfg)
{
  cfg->fd = -1;
  cfg->addr = NULL;
  cfg->port = 0;
  cfg->prev = NULL;
  cfg->next = NULL;
}
