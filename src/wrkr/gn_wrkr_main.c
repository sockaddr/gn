#include <wrkr/hdr/gn_wrkr_main.h>

// TODO: Remove code below START

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile bool sigint_rcvd = false;

void sigint_handler (int v) {
  if (v) {}
  sigint_rcvd = true;
}

// END REMOVE

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_wrkr_main (void)
{
  signal (SIGINT, sigint_handler); // TODO: Remove. This is just for testing a server stop.

  gn_conn_mgmt_thrd_conf_list_s conn_mgmt_thrd_conf_list;
  gn_conn_mgmt_thrd_conf_list_init (&conn_mgmt_thrd_conf_list);
  // Start connection management threads.
  gn_start_conn_mgmt_thrds (&conn_mgmt_thrd_conf_list);

  gn_conn_acpt_thrd_conf_list_s conn_acpt_thrd_conf_list;
  gn_conn_acpt_thrd_conf_list_init (&conn_acpt_thrd_conf_list);
  // Start connection acceptance threads.
  gn_start_conn_acpt_thrds (&conn_acpt_thrd_conf_list, &conn_mgmt_thrd_conf_list);


  while (true) { // Main worker loop.
    // TODO: Remove block below.
    if (sigint_rcvd) {
      printf ("Received SIGINT.\n");
      break;
    }

    sleep (1); // TODO: Remove.
  }

  /* Stop acceptance threads first because gn_stop_conn_mgmt_thrds() will empty the conn_mgmt_thrd_conf_list and this
   * list is used by connection acceptance threads. First stop the threads using the list, then empty it.
   */
  gn_stop_conn_acpt_thrds (&conn_acpt_thrd_conf_list); // Stop connection acceptance threads.
  gn_stop_conn_mgmt_thrds (&conn_mgmt_thrd_conf_list); // Stop connection management threads.
}
