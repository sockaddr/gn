#include <wrkr/hdr/gn_wrkr_main.h>

// TODO: Remove code below START

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile bool sigint_rcvd = false; // TODO: Remove.

void sigint_handler (int v) { // TODO: Remove.
  if (v) {}
  sigint_rcvd = true;
}

// END REMOVE

void // TODO: Maybe return a value.
gn_wrkr_main (void)
{
  signal (SIGINT, sigint_handler); // TODO: Remove. This is just for testing a server stop.

  gn_conn_mgmt_thrd_conf_list_s conn_mgmt_thrd_conf_list;
  gn_conn_mgmt_thrd_conf_list_init (&conn_mgmt_thrd_conf_list);

  gn_start_conn_mgmt_thrds (&conn_mgmt_thrd_conf_list); // Start connection management threads.

  while (true) { // Main worker loop.
    // TODO: Remove block below.
    if (sigint_rcvd) {
      printf ("Received SIGINT.\n");
      break;
    }

    sleep (1);
  }

  gn_stop_conn_mgmt_thrds (&conn_mgmt_thrd_conf_list); // Stop connection management threads.
}
