#include <wrkr/hdr/gn_conn_mgmt_thrd.h>

#include <error.h> // TODO: Remove.

/*
 * TODO: Add description.
 */

void *
gn_conn_mgmt_thrd (void * const p)
{
  if (p == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "gn_conn_mgmt_thrd() parameter 'p' is NULL"); // TODO: Remove.
    return NULL; // TODO: Log error. Maybe stop process.
  }

  gn_conn_mgmt_thrd_conf_s * const conn_mgmt_thrd_conf = p;
  conn_mgmt_thrd_conf->state = CONN_MGMT_THRD_RUNNING;

  gn_conn_list_s conn_list;
  gn_conn_list_init (&conn_list);

  while (true) {
    gn_conn_s * conn = conn_list.head;
    while (conn != NULL) {
      conn = conn->next;
    }

    // TODO: Don't accept connections if thread stop requested.
    gn_get_new_conns (&conn_mgmt_thrd_conf->new_conn_list_list, &conn_list);

    if (conn_mgmt_thrd_conf->stop) {
      if (conn_mgmt_thrd_conf->state != CONN_MGMT_THRD_STOPPING) {
        conn_mgmt_thrd_conf->state = CONN_MGMT_THRD_STOPPING;
        break;
      }
    }

    const struct timespec ts = {0, 1};
    const int rclock_nanosleep = clock_nanosleep (CLOCK_MONOTONIC, 0, &ts, NULL);
    switch (rclock_nanosleep) {
      // TODO.
    }
  }

  conn_mgmt_thrd_conf->state = CONN_MGMT_THRD_STOPPED;

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
