#include <mstr/hdr/gn_start_wrkr.h>

void
gn_start_wrkr (char * const self_path, gn_lstnr_conf_list_s * const lstnr_conf_list)
{
  const pid_t rfork = fork ();
  switch (rfork) {
    case 0: { // Child
      char * const argv[3] = {self_path, "--worker", NULL};
      execv (self_path, argv);
      break;
    }
    case -1: {
      break;
    }
    default: { // Parent
    }
  }
}
