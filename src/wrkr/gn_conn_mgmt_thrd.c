#include <wrkr/hdr/gn_conn_mgmt_thrd.h>

#include <stdio.h> // TODO: Remove.
#include <unistd.h> // TODO: Remove.

void *
gn_conn_mgmt_thrd (void * const p)
{
  if (p == NULL) return NULL; // TODO: Log error.

  gn_conn_mgmt_thrd_conf_s * const conn_mgmt_thrd_conf = p;
  conn_mgmt_thrd_conf->state = CONN_MGMT_THRD_RUNNING;

  while (true) {
    sleep (1); // TODO: Remove.
    if (conn_mgmt_thrd_conf->stop) {
      if (conn_mgmt_thrd_conf->state != CONN_MGMT_THRD_STOPPING) {
        conn_mgmt_thrd_conf->state = CONN_MGMT_THRD_STOPPING;
        break;
      }
    }
  }

  printf ("CMT %p stopped\n", conn_mgmt_thrd_conf);
  conn_mgmt_thrd_conf->state = CONN_MGMT_THRD_STOPPED;

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
