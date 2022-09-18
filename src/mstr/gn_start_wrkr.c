#include <mstr/hdr/gn_start_wrkr.h>

/*
 * TODO: Add description.
 */

void
gn_start_wrkr (char * const self_path, gn_lstnr_conf_list_s * const lstnr_conf_list)
{
  // Create socket pair to send configuration and sockets to worker process.
  int sp[2] = {-1, -1}; // TODO: Store them in worker proc entry.
  const int rsocketpair = socketpair (AF_UNIX, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, 0, sp);
  if (rsocketpair != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "socketpair() failed");
    return;
  }

  const pid_t rfork = fork ();
  switch (rfork) {
    case 0: { // Child
      if (dup2 (sp[0], STDIN_FILENO) == -1) {
        error_at_line (0, errno, __FILE__, __LINE__, "dup2() failed");
        goto chld_end;
      }
      if (dup2 (sp[0], STDOUT_FILENO) == -1) {
        error_at_line (0, errno, __FILE__, __LINE__, "dup2() failed");
        goto chld_end;
      }

      char * const argv[3] = {self_path, "--worker", NULL};
      execv (self_path, argv);
      error_at_line (0, errno, __FILE__, __LINE__, "execv() failed");

      chld_end:
      exit (1);
    }
    case -1: {
      error_at_line (0, errno, __FILE__, __LINE__, "fork() failed");
      break;
    }
    default: { // Parent
      // Send server socket info one by one.
      gn_lstnr_conf_s * lstnr_conf = lstnr_conf_list->head;
      for (uint8_t i = 0; i < lstnr_conf_list->len; lstnr_conf = lstnr_conf->next, i++) {
        printf ("Sending #%i [%s]:%i\n", lstnr_conf->fd, lstnr_conf->addr, lstnr_conf->port);

        const size_t send_buf_sz = 128;
        char send_buf[send_buf_sz];
        memset (send_buf, 0, send_buf_sz);
        const int rsnprintf = snprintf (send_buf, send_buf_sz, "[%s]:%i\n", lstnr_conf->addr, lstnr_conf->port);

        // Check if error occured.
        if (rsnprintf < 0) {
          error_at_line (0, errno, __FILE__, __LINE__, "snprintf() error %i", rsnprintf);
          goto prnt_end;
        }
        // Check if output was truncated.
        if ((size_t)rsnprintf >= send_buf_sz) {
          error_at_line (0, 0, __FILE__, __LINE__, "snprintf() output truncated");
          goto prnt_end;
        }

        const ssize_t rsend = send (sp[1], send_buf, strlen (send_buf), SOCK_NONBLOCK);
        if (rsend < 0) {
          error_at_line (0, errno, __FILE__, __LINE__, "send() failed");
        }

        struct pollfd pfd = {
          .fd = sp[1],
          .events = POLLIN | POLLRDHUP,
          .revents = 0
        };

        const int rpoll = poll (&pfd, 1, 3000);
        switch (rpoll) {
          case 0: {
            error_at_line (0, 0, __FILE__, __LINE__, "Worker didn't send data");
            break;
          }
          case -1: {
            error_at_line (0, errno, __FILE__, __LINE__, "Master poll() failed");
            break;
          }
          default: {
            const size_t recv_buf_sz = 128;
            char recv_buf[recv_buf_sz];
            ssize_t rrecv = recv (sp[1], recv_buf, recv_buf_sz - 1, SOCK_NONBLOCK);
            switch (rrecv) {
              case 0: {
                error_at_line (0, 0, __FILE__, __LINE__, "Worker disconnected");
                break;
              }
              case -1: {
                error_at_line (0, errno, __FILE__, __LINE__, "Master recv() failed");
                break;
              }
              default: {
                const size_t recv_buf_len = (size_t)rrecv;
                recv_buf[recv_buf_len] = '\0';
                printf ("Received from worker #%i (%li) \"%s\"\n", rfork, recv_buf_len, recv_buf);
                gn_send_fd (sp[1], lstnr_conf->fd);
              }
            }
          }
        }
      }

      const ssize_t rsend = send (sp[1], "/", 1, SOCK_NONBLOCK);
      if (rsend < 0) {
        error_at_line (0, errno, __FILE__, __LINE__, "send() failed");
      }

      prnt_end:
      return;
    }
  }

  close (sp[0]);
  close (sp[1]);
}
