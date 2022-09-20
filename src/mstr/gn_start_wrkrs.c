#include <mstr/hdr/gn_start_wrkrs.h>

/*
 * TODO: Add description.
 */

void
gn_start_wrkrs (gn_mstr_cfg_s * const mc)
{
  for (uint8_t i = 0; i < mc->wrkrs_num; i++) {
    (void)! gn_start_wrkr (mc);
  }
}
