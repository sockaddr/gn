#include <mstr/hdr/gn_mstr_main.h>

/*
 * TODO: Add description.
 */

void
gn_mstr_main (void)
{
  gn_mstr_conf_s mstr_conf;
  gn_mstr_conf_init (&mstr_conf);

  mstr_conf.self_path = gn_self_path (NULL);
  if (mstr_conf.self_path == NULL) return;

  mstr_conf.wrkrs_num = 2;

  // TODO: Load master config.

  gn_lstnr_conf_list_s lstnr_conf_list;
  gn_lstnr_conf_list_init (&lstnr_conf_list);
  gn_create_lstnr (&lstnr_conf_list, "0.0.0.0", 8080);
  gn_create_lstnr (&lstnr_conf_list, "192.168.2.2", 8081);

  gn_start_wrkrs (&mstr_conf, &lstnr_conf_list);

  while (true) { // Main master loop.
    sleep (1);
  }

  free (mstr_conf.self_path);
}
