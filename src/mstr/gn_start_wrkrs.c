#include <mstr/hdr/gn_start_wrkrs.h>

void
gn_start_wrkrs (gn_mstr_conf_s * const mstr_conf, gn_lstnr_conf_list_s * const lstnr_conf_list)
{
  for (uint8_t i = 0; i < mstr_conf->wrkrs_num; i++) {
    (void)! gn_start_wrkr (mstr_conf->self_path, lstnr_conf_list);
  }
}
