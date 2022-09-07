#include <mstr/hdr/gn_mstr_main.h>

void
gn_mstr_main (void)
{
  char * const self_path = gn_self_path (NULL);
  if (self_path == NULL) return;

  gn_start_wrkrs (self_path);

  while (true) { // Main master loop.
    sleep (1);
  }

  free (self_path);
}
