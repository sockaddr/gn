#include <wrkr/hdr/gn_lstnrs_recv.h>

void
gn_lstnrs_recv (const int ipc_fd, gn_lstnr_cfg_lst_s * const lc_lst)
{
  bool recv_loop = true;
  while (recv_loop) {

    gn_lstnr_cfg_s * lc = malloc (sizeof (gn_lstnr_cfg_s));
    if (lc == NULL) {
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate gn_lstnr_cfg_s");
      return;
    }
    gn_lstnr_cfg_ini (lc);

    char * const addr = malloc (128);
    if (addr == NULL) {
      error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate server socket address buffer");
      free (lc);
      return;
    }

    struct pollfd pfd = {
      .fd = ipc_fd,
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

        const ssize_t rrecv = recv (ipc_fd, recv_buf, recv_buf_sz - 1, SOCK_NONBLOCK);
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
            printf ("%i rcvd from master (%li) \"%s\"\n", getpid (), recv_buf_len, recv_buf);

            const ssize_t rsend = send (ipc_fd, recv_buf, recv_buf_len, SOCK_NONBLOCK);
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
                int fd = gn_recv_fd (ipc_fd);
                printf ("Worker #%i received #%i %s\n", getpid (), fd, recv_buf);

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

                lc->addr = addr;
                lc->port = atoi (port);
                lc->fd = fd;
                (void)! gn_lstnr_cfg_lst_pshb (lc_lst, lc); // TODO: Check error.

                printf ("fd = %i, addr (%li) = \"%s\", port = %i\n", lc->fd , strlen (lc->addr), lc->addr, lc->port);
                lc = NULL;
              }
            }
          }
        }
      }
    }

    if (lc != NULL) {
      if (lc->fd > -1) close (lc->fd);
      free (addr);
      free (lc);
    }
  }
}
