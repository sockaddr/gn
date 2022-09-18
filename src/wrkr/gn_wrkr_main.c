#include <wrkr/hdr/gn_wrkr_main.h>

// TODO: Remove code below, start.

#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile bool sigint_rcvd = false;

void
sigint_handler (const int s)
{
  printf ("Signal %i\n", s);
  sigint_rcvd = true;
}

// Remove code above, end.

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_wrkr_main (void)
{
  // TODO: Remove. This is just for testing a server stop.
  if (signal (SIGINT, sigint_handler) == SIG_ERR) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to register SIGINT handler");
  }

  bool recv_loop = true;
  while (recv_loop) {

    const size_t recv_buf_sz = 128;
    char recv_buf[recv_buf_sz];
    const ssize_t rrecv = recv (STDIN_FILENO, recv_buf, recv_buf_sz - 1, SOCK_NONBLOCK);
    switch (rrecv) {
      case 0: {
        error_at_line (0, 0, __FILE__, __LINE__, "Master disconnected");
        recv_loop = false;
        break;
      }
      case -1: {
        error_at_line (0, errno, __FILE__, __LINE__, "Worker recv() failed");
        recv_loop = false;
        break;
      }
      default: {
        const size_t recv_buf_len = (size_t)rrecv;
        recv_buf[recv_buf_len] = '\0';
        if (recv_buf[0] == '/') {
          recv_loop = false;
          break;
        }

        // Not an error.
        error_at_line (0, 0, "", 0, "%i rcvd from master (%li) \"%s\"\n", getpid (), recv_buf_len, recv_buf);
      }
    }
  }

  // TODO: Receive and parse worker configuration.

  gn_wrkr_conf_s wrkr_conf;
  (void)! gn_wrkr_conf_init (&wrkr_conf);

  // TODO: Maybe use functions to validate.
  wrkr_conf.conn_acpt_thrd_num = 4;
  wrkr_conf.conn_mgmt_thrd_num = 2;
  wrkr_conf.start_wout_conn_acpt_thrds = true;
  wrkr_conf.start_wout_conn_mgmt_thrds = true;

  gn_start_conn_mgmt_thrds (&wrkr_conf); // Start connection management threads.
  if (wrkr_conf.conn_mgmt_thrd_conf_list.len == 0 && !wrkr_conf.start_wout_conn_mgmt_thrds) {
    error_at_line (0, 0, __FILE__, __LINE__, "Can't start without connection management threads");
    goto lbl_err_no_cmts;
  }

  gn_start_conn_acpt_thrds (&wrkr_conf); // Start connection acceptance threads.
  if (wrkr_conf.conn_acpt_thrd_conf_list.len == 0 && !wrkr_conf.start_wout_conn_acpt_thrds) {
    error_at_line (0, 0, __FILE__, __LINE__, "Can't start without connection acceptance threads");
    goto lbl_err_no_cats;
  }

  while (true) { // Main worker loop.
    // TODO: Remove block below.
    if (sigint_rcvd) {
      printf ("Received SIGINT.\n");
      break;
    }

    sleep (1); // TODO: Remove.
  }

  /* Stop acceptance threads first because gn_stop_conn_mgmt_thrds() will empty the conn_mgmt_thrd_conf_list and
   * this list is used by connection acceptance threads. First stop the threads using the list, then empty it.
   */
  gn_stop_conn_acpt_thrds (&wrkr_conf); // Stop connection acceptance threads.

  lbl_err_no_cats:
  gn_stop_conn_mgmt_thrds (&wrkr_conf); // Stop connection management threads.

  lbl_err_no_cmts: ; // TODO: Remove semicolon.
}
