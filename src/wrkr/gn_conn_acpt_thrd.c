#include <wrkr/hdr/gn_conn_acpt_thrd.h>

#include <stdio.h> // TODO: Remove.
#include <unistd.h> // TODO: Remove.

void *
gn_conn_acpt_thrd (void * const p)
{
  if (p == NULL) return NULL; // TODO: Log error.

  gn_conn_acpt_thrd_conf_s * const conn_acpt_thrd_conf = p;
  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_RUNNING;

  while (true) {
    sleep (1); // TODO: Remove.
    if (conn_acpt_thrd_conf->stop) {
      if (conn_acpt_thrd_conf->state != CONN_ACPT_THRD_STOPPING) {
        conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPING;
        break;
      }
    }
  }

  printf ("CAT %p stopped\n", conn_acpt_thrd_conf);
  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPED;

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
