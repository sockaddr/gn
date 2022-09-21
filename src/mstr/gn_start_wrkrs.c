#include <mstr/hdr/gn_start_wrkrs.h>

/*
 * TODO: Add description.
 */

void
gn_start_wrkrs (gn_mstr_cfg_s * const mc)
{
  for (uint8_t i = 0; i < mc->wrkrs_num; i++) {
    if (gn_start_wrkr (mc)) continue;

    const int wrkr_fd = gn_wrkr_acpt (mc->ipc_fd);
    if (wrkr_fd > -1) {
      gn_lstnrs_send (wrkr_fd, &mc->lstnr_cfg_lst);
    }
  }
}
