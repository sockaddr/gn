#include <wrkr/hdr/gn_conn_acpt_thrd.h>

#include <wrkr/hdr/gn_conn_s.h>

#include <errno.h> // TODO: Remove.
#include <error.h> // TODO: Remove.
#include <stdio.h> // TODO: Remove.
#include <stdlib.h> // TODO: Remove.
#include <string.h> // TODO: Remove.
#include <unistd.h> // TODO: Remove.
#include <arpa/inet.h> // TODO: Remove.

/*
 * TODO: Add description.
 */

void *
gn_conn_acpt_thrd (void * const p)
{
  if (p == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "gn_conn_acpt_thrd() parameter p is NULL"); // TODO: Remove.
    return NULL; // TODO: Log error. Maybe stop process.
  }

  gn_conn_acpt_thrd_conf_s * const conn_acpt_thrd_conf = p;
  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_RUNNING;

  // Don't free this list in this function.
  const gn_conn_mgmt_thrd_conf_list_s * const conn_mgmt_thrd_conf_list = conn_acpt_thrd_conf->conn_mgmt_thrd_conf_list;
  if (conn_mgmt_thrd_conf_list == NULL) {} // TODO: Remove.

  const gn_lstnr_cfg_lst_s * const lstnr_cfg_lst = conn_acpt_thrd_conf->lstnr_conf_list;

  while (true) {
    gn_lstnr_cfg_s * lstnr_conf = lstnr_cfg_lst->head;
    for (uint16_t i = 0; i < lstnr_cfg_lst->len; lstnr_conf = lstnr_conf->next, i++) {
      struct sockaddr_in sin;
      size_t sizeof_sin = sizeof (sin);
      memset (&sin, 0, sizeof_sin);

      const int raccept4 = accept4 (lstnr_conf->fd, (struct sockaddr *)&sin, (socklen_t *)&sizeof_sin, SOCK_NONBLOCK);
      if (raccept4 < 0) {
        switch (errno) {
          case EAGAIN:
          case EINTR:
            break;
          default:
            error_at_line (0, errno, __FILE__, __LINE__, "Failed to accept connection on #%i [%s]:%i.",
                           lstnr_conf->fd, lstnr_conf->addr, lstnr_conf->port);
        }
        continue;
      }

      char saddr[INET_ADDRSTRLEN];
      memset (saddr, 0, sizeof (saddr));
      if (inet_ntop (AF_INET, &sin.sin_addr, saddr, INET_ADDRSTRLEN) == NULL) {
        error_at_line (0, errno, __FILE__, __LINE__, "inet_ntop() failed");
        goto lbl_close_raccept4;
      }
      const uint16_t sport = htons (sin.sin_port);

      struct sockaddr_in getsockname_sin;
      size_t sizeof_getsockname_sin = sizeof (getsockname_sin);
      memset (&getsockname_sin, 0, sizeof_getsockname_sin);
      if (getsockname (raccept4, (struct sockaddr *)&getsockname_sin, (socklen_t *)&sizeof_getsockname_sin) != 0) {
        error_at_line (0, errno, __FILE__, __LINE__, "getsockname() failed");
        goto lbl_close_raccept4;
      }

      char daddr[INET_ADDRSTRLEN];
      memset (daddr, 0, sizeof (daddr));
      if (inet_ntop (AF_INET, &getsockname_sin.sin_addr, daddr, INET_ADDRSTRLEN) == NULL) {
        error_at_line (0, errno, __FILE__, __LINE__, "inet_ntop() failed");
        goto lbl_close_raccept4;
      }

      error_at_line (0, 0, "", 0, "[%i] Connection from [%s]:%i to [%s] / [%s]:%i\n\n", getpid (), saddr, sport, lstnr_conf->addr, daddr, lstnr_conf->port);

      gn_conn_s * const conn = malloc (sizeof (gn_conn_s));
      if (conn != NULL) {
        gn_conn_ini (conn);
        conn->saddr = malloc (strlen (saddr) + 1);
        strcpy (conn->saddr, saddr);
        conn->sport = sport;
        conn->daddr = malloc (strlen (daddr) + 1);
        strcpy (conn->daddr, daddr);
        conn->fd = raccept4;
        conn->lstnr_cfg = lstnr_conf;
        if (!gn_pass_conn (conn_mgmt_thrd_conf_list, conn)) continue;

        error_at_line (0, 0, __FILE__, __LINE__, "Connection wasn't passed");
      } else error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection structure");

      if (conn != NULL) {
        free (conn->daddr);
        free (conn->saddr);
        free (conn);
      }

      lbl_close_raccept4:
      // TODO: Loop close() if allowed by user in configuration file. Default: don't loop.
      if (close (raccept4) != 0) {
        error_at_line (0, errno, __FILE__, __LINE__, "Failed to close client socket %i", raccept4);
      }
    }


    if (conn_acpt_thrd_conf->stop) {
      if (conn_acpt_thrd_conf->state != CONN_ACPT_THRD_STOPPING) {
        conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPING;
        break;
      }
    }

    const struct timespec ts = {0, 1};
    const int rclock_nanosleep = clock_nanosleep (CLOCK_MONOTONIC, 0, &ts, NULL);
    switch (rclock_nanosleep) {
      // TODO.
    }
  }

  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPED;

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
