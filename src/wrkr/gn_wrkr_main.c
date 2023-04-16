#include <wrkr/hdr/gn_wrkr_main.h>

#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/un.h>

/*
 * TODO: Add description.
 */

uint8_t
gn_wrkr_main (const char * const ipc_addr_str)
{
  signal (SIGINT, SIG_IGN);
  signal (SIGPIPE, SIG_IGN);
  gn_lstnr_cfg_lst_s lc_lst;
  gn_lstnr_cfg_lst_ini (&lc_lst);

  int ipc_fd = socket (AF_UNIX, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, 0);

  struct sockaddr_un sun;
  memset (&sun, 0, sizeof (sun));
  sun.sun_family = AF_UNIX;
  strcpy (&sun.sun_path[1], ipc_addr_str);

  if (connect (ipc_fd, (struct sockaddr *)&sun, sizeof (sun)) == 0) printf ("Worker %i connected to master\n", getpid ());
  else return 1;

  gn_lstnrs_recv (ipc_fd, &lc_lst);

  // TODO: Receive and parse worker configuration.

  gn_wrkr_cfg_s wc;
  gn_wrkr_cfg_ini (&wc, &lc_lst);

  // TODO: Maybe use functions to validate.
  wc.conn_acpt_thrd_num = 4;
  wc.conn_mgmt_thrd_num = 1;
  wc.start_wout_conn_acpt_thrds = true;
  wc.start_wout_conn_mgmt_thrds = true;

  gn_start_conn_mgmt_thrds (&wc); // Start connection management threads.
  if (wc.conn_mgmt_thrd_conf_list.len == 0 && !wc.start_wout_conn_mgmt_thrds) {
    error_at_line (0, 0, __FILE__, __LINE__, "Can't start without connection management threads");
    goto lbl_err_no_cmts;
  }

  gn_start_conn_acpt_thrds (&wc); // Start connection acceptance threads.
  if (wc.conn_acpt_thrd_conf_list.len == 0 && !wc.start_wout_conn_acpt_thrds) {
    error_at_line (0, 0, __FILE__, __LINE__, "Can't start without connection acceptance threads");
    goto lbl_err_no_cats;
  }

  bool loop = true;
  while (loop) { // Main worker loop.
    struct pollfd pfd = {
      .fd = ipc_fd,
      .events = POLLIN | POLLRDHUP,
      .revents = 0
    };

    const int rpoll = poll (&pfd, 1, 0);
    switch (rpoll) {
      case 0: {
        break;
      }
      case -1: {
        error_at_line (0, errno, __FILE__, __LINE__, "Main loop poll() failed");
        break;
      }
      default: {
        if (pfd.revents & POLLRDHUP) {
          printf ("IPC closed, stopping worker %i\n", getpid ());
          loop = false;
        }
      }
    }

    sleep (1); // TODO: Remove.
  }

  /* Stop acceptance threads first because gn_stop_conn_mgmt_thrds() will empty the conn_mgmt_thrd_conf_list and
   * this list is used by connection acceptance threads. First stop the threads using the list, then empty it.
   */
  gn_stop_conn_acpt_thrds (&wc); // Stop connection acceptance threads.

  lbl_err_no_cats:
  gn_stop_conn_mgmt_thrds (&wc); // Stop connection management threads.

  lbl_err_no_cmts: ;
  gn_lstnr_cfg_s * lc = lc_lst.head;
  for (uint16_t i = 0; i < lc_lst.len; i++) {
    gn_lstnr_cfg_s * next_lc = lc->next;

    close (lc->fd);
    lc->fd = -1;

    free (lc);
    lc = next_lc;
  }

  return 0;
}
