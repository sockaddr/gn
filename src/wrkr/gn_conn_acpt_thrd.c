#include <wrkr/hdr/gn_conn_acpt_thrd.h>

#include <error.h> // TODO: Remove.

/*
 * TODO: Add description.
 */

void *
gn_conn_acpt_thrd (void * const p)
{
  if (p == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "gn_conn_acpt_thrd() parameter p is NULL"); // TODO: Remove.
    return NULL; // TODO: Log error. Maybe stop process.
  }

  gn_conn_acpt_thrd_conf_s * const conn_acpt_thrd_conf = p;
  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_RUNNING;

  // Don't free this list in this function.
  const gn_conn_mgmt_thrd_conf_list_s * const conn_mgmt_thrd_conf_list = conn_acpt_thrd_conf->conn_mgmt_thrd_conf_list;
  if (conn_mgmt_thrd_conf_list == NULL) {} // TODO: Remove.

  while (true) {

    if (conn_acpt_thrd_conf->stop) {
      if (conn_acpt_thrd_conf->state != CONN_ACPT_THRD_STOPPING) {
        conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPING;
        break;
      }
    }

    const struct timespec ts = {0, 1};
    const int rclock_nanosleep = clock_nanosleep (CLOCK_MONOTONIC, 0, &ts, NULL);
    switch (rclock_nanosleep) {
      // TODO.
    }
  }

  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPED;

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
