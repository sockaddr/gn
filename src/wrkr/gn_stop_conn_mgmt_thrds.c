#include <wrkr/hdr/gn_stop_conn_mgmt_thrds.h>

#include <error.h> // TODO: Remove.
#include <stdio.h> // TODO: Remove.

void
gn_stop_conn_mgmt_thrds (gn_conn_mgmt_thrd_conf_list_s * const list)
{
  gn_conn_mgmt_thrd_conf_s * conf = list->head;

  while (list->len > 0) {
    switch (conf->state) {
      // The thread reported that it's stopping, so we wait for the CONN_MGMT_THRD_STOPPED state.
      case CONN_MGMT_THRD_STOPPING: {
        break;
      }
      // The thread set this signal just before the function ended. We can remove the configuration from the list.
      case CONN_MGMT_THRD_STOPPED: {
        printf ("Stopped connection management thread (conf ptr %p)\n", conf); // TODO: Remove.
        // Remove the configuration structure at any position in the list.
        gn_conn_mgmt_thrd_conf_list_remove (list, conf);
        break;
      }
      // If the thread is running, send the stop signal if it wasn't already sent.
      case CONN_MGMT_THRD_RUNNING: {
        if (conf->stop) break; // The stop signal was already sent, don't send it again.

        printf ("Stopping connection management thread (conf ptr %p)...\n", conf); // TODO: Remove.
        conf->stop = true;
        break;
      }
      // For some reason (maybe RAM default, cosmic rays, etc) the state is invalid.
      default: {
        // TODO: Remove.
        error_at_line (0, 0, __FILE__, __LINE__, "Invalid connection management thread state %i", conf->state);
        // TODO: Log and/or display error. Maybe set state again.
      }
    }

    conf = conf->next;
    // TODO: Maybe call clock_nanosleep() to prevent 100% CPU usage.
  }
}