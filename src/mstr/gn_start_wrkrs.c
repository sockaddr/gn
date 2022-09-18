#include <mstr/hdr/gn_start_wrkrs.h>

void
gn_start_wrkrs (gn_mstr_cfg_s * const mc)
{
  for (uint8_t i = 0; i < mc->wrkrs_num; i++) {
    (void)! gn_start_wrkr (mc);
  }
}
