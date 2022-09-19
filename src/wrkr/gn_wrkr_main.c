#include <wrkr/hdr/gn_wrkr_main.h>

#include <errno.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>

/*
 * TODO: Add description.
 */

void // TODO: Maybe return a value.
gn_wrkr_main (void)
{
  signal (SIGINT, SIG_IGN);
  signal (SIGPIPE, SIG_IGN);
  gn_lstnr_cfg_lst_s lstnr_conf_list;
  gn_lstnr_cfg_lst_ini (&lstnr_conf_list);

  bool recv_loop = true;
  while (recv_loop) {

    gn_lstnr_cfg_s * const lstnr_cfg = malloc (sizeof (gn_lstnr_cfg_s));
    if (lstnr_cfg == NULL) {
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate gn_lstnr_cfg_s");
      return;
    }
    gn_lstnr_cfg_ini (lstnr_cfg);

    char * const addr = malloc (128);
    if (addr == NULL) {
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate server socket address buffer");
      free (lstnr_cfg);
      return;
    }

    struct pollfd pfd = {
      .fd = STDIN_FILENO,
      .events = POLLIN | POLLRDHUP,
      .revents = 0
    };

    const int rpoll = poll (&pfd, 1, 3000);
    switch (rpoll) {
      case 0: {
        error_at_line (0, 0, __FILE__, __LINE__, "Master didn't send data");
        break;
      }
      case -1: {
        error_at_line (0, errno, __FILE__, __LINE__, "Worker poll() failed");
        break;
      }
      default: {
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

            const ssize_t rsend = send (STDOUT_FILENO, recv_buf, recv_buf_len, SOCK_NONBLOCK);
            if (rsend < 0) {
              error_at_line (0, errno, __FILE__, __LINE__, "Worker send() failed");
            }

            const int rpoll = poll (&pfd, 1, 3000);
            switch (rpoll) {
              case 0: {
                error_at_line (0, 0, __FILE__, __LINE__, "Master didn't send data");
                break;
              }
              case -1: {
                error_at_line (0, errno, __FILE__, __LINE__, "Worker poll() failed");
                break;
              }
              default: {
                int fd = gn_recv_fd (STDIN_FILENO);
                error_at_line (0, 0, "", 0, "Worker #%i received #%i %s", getpid (), fd, recv_buf);

                // Get address
                size_t i = 1, addr_len = 0;
                for (; addr_len < 128 && recv_buf[i] != ']'; i++, addr_len++) {
                  addr[addr_len] = recv_buf[i];
                }
                addr[addr_len] = '\0';

                // Get port
                for (; recv_buf[i] != ':'; i++);
                i++;

                char port[6];
                size_t port_len = 0;
                for (; port_len < 5 && recv_buf[i] != '\n'; i++, port_len++) {
                  port[port_len] = recv_buf[i];
                }
                port[port_len] = '\0';

                lstnr_cfg->addr = addr;
                lstnr_cfg->port = atoi (port);
                lstnr_cfg->fd = fd;
                (void)! gn_lstnr_cfg_lst_pshb (&lstnr_conf_list, lstnr_cfg); // TODO: Check error.

                error_at_line (0, 0, "", 0, "fd = %i, addr (%li) = \"%s\", port = %i\n", lstnr_cfg->fd ,
                                                                                         strlen (lstnr_cfg->addr),
                                                                                         lstnr_cfg->addr,
                                                                                         lstnr_cfg->port);
              }
            }
          }
        }
      }
    }
  }

  // TODO: Receive and parse worker configuration.

  gn_wrkr_conf_s wrkr_conf;
  (void)! gn_wrkr_conf_init (&wrkr_conf, &lstnr_conf_list);

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

  bool loop = true;
  while (loop) { // Main worker loop.
    struct pollfd pfd[2];
    pfd[0] = (struct pollfd){
      .fd = STDIN_FILENO,
      .events = POLLIN | POLLRDHUP,
      .revents = 0
    };
    pfd[1] = (struct pollfd){
      .fd = STDOUT_FILENO,
      .events = POLLOUT | POLLRDHUP,
      .revents = 0
    };

    const int rpoll = poll (pfd, 2, 0);
    switch (rpoll) {
      case 0: {
        break;
      }
      case -1: {
        error_at_line (0, errno, __FILE__, __LINE__, "Main loop poll() failed");
        break;
      }
      default: {
        for (uint8_t pfd_i = 0; pfd_i < 2; pfd_i++) {
          if (pfd[pfd_i].revents & POLLRDHUP) {
            if (pfd_i == 0) error_at_line (0, 0, "", 0, "STDIN closed");
            else error_at_line (0, 0, "", 0, "STDOUT closed");
            error_at_line (0, 0, "", 0, "Stopping worker %i", getpid ());
            loop = false;
          }
        }
      }
    }

    sleep (1); // TODO: Remove.
  }

  /* Stop acceptance threads first because gn_stop_conn_mgmt_thrds() will empty the conn_mgmt_thrd_conf_list and
   * this list is used by connection acceptance threads. First stop the threads using the list, then empty it.
   */
  gn_stop_conn_acpt_thrds (&wrkr_conf); // Stop connection acceptance threads.

  lbl_err_no_cats:
  gn_stop_conn_mgmt_thrds (&wrkr_conf); // Stop connection management threads.

  lbl_err_no_cmts: ;
  gn_lstnr_cfg_s * lstnr_cfg = lstnr_conf_list.head;
  for (uint16_t i = 0; i < lstnr_conf_list.len; i++) {
    gn_lstnr_cfg_s * next_lstnr_cfg = lstnr_cfg->next;

    close (lstnr_cfg->fd);
    lstnr_cfg->fd = -1;

    free (lstnr_cfg);
    lstnr_cfg = next_lstnr_cfg;
  }
}
