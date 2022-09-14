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

  mstr_conf.wrkrs_num = 1;

  // TODO: Load master config.

  gn_start_wrkrs (&mstr_conf);

  while (true) { // Main master loop.
    sleep (1);
  }

  free (mstr_conf.self_path);
}
