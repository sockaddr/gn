#include <mstr/hdr/gn_lstnr_send.h>

void
gn_lstnr_send (const int ipc_fd, const gn_lstnr_cfg_s * const lc)
{
  const size_t send_buf_sz = 128;
  char send_buf[send_buf_sz];
  memset (send_buf, 0, send_buf_sz);
  const int rsnprintf = snprintf (send_buf, send_buf_sz, "[%s]:%i\n", lc->addr, lc->port);

  // Check if error occured.
  if (rsnprintf < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "snprintf() error %i", rsnprintf);
    goto lbl_end;
  }
  // Check if output was truncated.
  if ((size_t)rsnprintf >= send_buf_sz) {
    error_at_line (0, 0, __FILE__, __LINE__, "snprintf() output truncated");
    goto lbl_end;
  }

  const ssize_t rsend = send (ipc_fd, send_buf, strlen (send_buf), SOCK_NONBLOCK);
  if (rsend < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "send() failed");
  }

  struct pollfd pfd = {
    .fd = ipc_fd,
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
      ssize_t rrecv = recv (ipc_fd, recv_buf, recv_buf_sz - 1, SOCK_NONBLOCK);
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
          printf ("Received from worker #%i (%li) \"%s\"\n", -1 /* rfork */, recv_buf_len, recv_buf);
          gn_send_fd (ipc_fd, lc->fd);
        }
      }
    }
  }

  lbl_end: ;
}
