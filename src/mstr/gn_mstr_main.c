#include <mstr/hdr/gn_mstr_main.h>

/*
 * TODO: Add description.
 */

void
gn_mstr_main (void)
{
  gn_mstr_cfg_s mc;
  gn_mstr_cfg_ini (&mc);

  uint8_t gn_self_path_err = 0; // TODO: Maybe do something with this variable.
  mc.self_path = gn_self_path (&gn_self_path_err);
  if (mc.self_path == NULL) return;

  mc.wrkrs_num = 2;

  // TODO: Load master config.

  gn_lstnr_conf_list_s lstnr_conf_list;
  gn_lstnr_conf_list_init (&lstnr_conf_list);
  gn_create_lstnr (&lstnr_conf_list, "0.0.0.0", 8080);
  gn_create_lstnr (&lstnr_conf_list, "192.168.2.2", 8081);

  gn_start_wrkrs (&mc, &lstnr_conf_list);

  while (true) { // Main master loop.
    sleep (1);
  }

  free (mc.self_path);
}
