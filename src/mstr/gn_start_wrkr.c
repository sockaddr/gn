#include <mstr/hdr/gn_start_wrkr.h>

/*
 * TODO: Add description.
 */

bool
gn_start_wrkr (const gn_mstr_cfg_s * const mc)
{
  errno = 0;
  const pid_t rfork = fork ();

  switch (rfork) {
    case 0: { // Child
      char * const argv[4] = {mc->self_path, "--ipc-addr", (char *)&mc->ipc_addr.sun_path[1], NULL};
      const int rexecv = execv (mc->self_path, argv);
      if (rexecv == -1) fprintf (stderr, "Failed to execute worker process (%s)\n", strerror (errno));
      else fprintf (stderr, "Unexpected execv() error. Code %i, errno %i (%s)\n", rexecv, errno, strerror (errno));
      exit (1);
    }
    case -1: {
      fprintf (stderr, "Failed to fork worker process (%s)\n", strerror (errno));
      return true;
    }
    default: { // Parent
      if (rfork > 0) return false; // Success

      fprintf (stderr, "Unexpected fork() error. Code %i, errno %i (%s)\n", rfork, errno, strerror (errno));
      return true;
    }
  }
}

/*
sleep (1);
int raccept4 = accept4 (mc->ipc_fd, NULL, 0, SOCK_NONBLOCK);
if (raccept4 < 0) {
  error_at_line (0, errno, __FILE__, __LINE__, "accept4() failed");
  break;
}
// Send server socket info one by one.
gn_lstnr_cfg_s * lstnr_conf = mc->lstnr_cfg_lst.head;
for (uint8_t i = 0; i < mc->lstnr_cfg_lst.len; lstnr_conf = lstnr_conf->next, i++) {
  printf ("Sending #%i [%s]:%i\n", lstnr_conf->fd, lstnr_conf->addr, lstnr_conf->port);

  const size_t send_buf_sz = 128;
  char send_buf[send_buf_sz];
  memset (send_buf, 0, send_buf_sz);
  const int rsnprintf = snprintf (send_buf, send_buf_sz, "[%s]:%i\n", lstnr_conf->addr, lstnr_conf->port);

  // Check if error occured.
  if (rsnprintf < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "snprintf() error %i", rsnprintf);
    goto lbl_prnt_end;
  }
  // Check if output was truncated.
  if ((size_t)rsnprintf >= send_buf_sz) {
    error_at_line (0, 0, __FILE__, __LINE__, "snprintf() output truncated");
    goto lbl_prnt_end;
  }

  const ssize_t rsend = send (raccept4, send_buf, strlen (send_buf), SOCK_NONBLOCK);
  if (rsend < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "send() failed");
  }

  struct pollfd pfd = {
    .fd = raccept4,
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
      ssize_t rrecv = recv (raccept4, recv_buf, recv_buf_sz - 1, SOCK_NONBLOCK);
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
          gn_send_fd (raccept4, lstnr_conf->fd);
        }
      }
    }
  }
}

const ssize_t rsend = send (raccept4, "/", 1, SOCK_NONBLOCK);
if (rsend < 0) {
  error_at_line (0, errno, __FILE__, __LINE__, "send() failed");
}

lbl_prnt_end:
return;
*/
