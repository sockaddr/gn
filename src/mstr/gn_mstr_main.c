#include <mstr/hdr/gn_mstr_main.h>

/*
 * TODO: Add description.
 */

uint8_t
gn_mstr_main (void)
{
  gn_mstr_cfg_s mc;
  gn_mstr_cfg_ini (&mc);

  uint8_t gn_self_path_err = 0; // TODO: Maybe do something with this variable.
  mc.self_path = gn_self_path (&gn_self_path_err);
  if (mc.self_path == NULL) return 1;

  // TODO: Load master config.
  mc.wrkrs_num = 2;

  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "0.0.0.0", 8080);
  (void)! gn_create_lstnr (&mc.lstnr_cfg_lst, "192.168.2.2", 8081);

  gn_start_wrkrs (&mc);

  while (true) { // Main master loop.
    sleep (1);
  }

  free (mc.self_path);
  return 0;
}
