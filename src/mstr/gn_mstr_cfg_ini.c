#include <mstr/hdr/gn_mstr_cfg_ini.h>

/*
 * TODO: Add description.
 */

void
gn_mstr_cfg_ini (gn_mstr_cfg_s * const mc)
{
  gn_lstnr_cfg_lst_ini (&mc->lstnr_cfg_lst);
  mc->self_path = NULL;
  mc->wrkrs_num = 1;
}
