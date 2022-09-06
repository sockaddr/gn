#include <wrkr/hdr/gn_conn_acpt_thrd.h>

#include <wrkr/hdr/gn_conn_s.h>

#include <errno.h> // TODO: Remove.
#include <error.h> // TODO: Remove.
#include <stdio.h> // TODO: Remove.
#include <stdlib.h> // TODO: Remove.
#include <string.h> // TODO: Remove.
#include <unistd.h> // TODO: Remove.
#include <arpa/inet.h> // TODO: Remove.

void
gn_lstnr_conf_init (gn_lstnr_conf_s * const conf)
{
  conf->fd = -1;
  conf->addr = NULL;
  conf->port = 0;
  conf->prev = NULL;
  conf->next = NULL;
}

struct gn_lstnr_conf_list_s
{
  gn_lstnr_conf_s * head;
  gn_lstnr_conf_s * tail;
  uint16_t          len;
};

typedef struct gn_lstnr_conf_list_s gn_lstnr_conf_list_s;

void
gn_lstnr_conf_list_init (gn_lstnr_conf_list_s * const list)
{
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}

bool
gn_lstnr_conf_list_push_back (gn_lstnr_conf_list_s * const list,
                              gn_lstnr_conf_s * const      conf)
{
  switch (list->len) {
    case UINT16_MAX: {
      return true;
    }
    case 0: {
      list->head = list->tail = conf->prev = conf->next = conf;
      break;
    }
    default: {
      list->tail->next = conf;
      conf->prev = list->tail;
      list->head->prev = conf;
      conf->next = list->head;
      list->tail = conf;
    }
  }

  list->len++;
  return false;
}

void
gn_create_lstnr (gn_lstnr_conf_list_s * const list, const char * const addr, const uint16_t port)
{
  gn_lstnr_conf_s * const conf = malloc (sizeof (gn_lstnr_conf_s));
  if (conf == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate listener configuration for [%s]:%i", addr, port);
    return;
  }

  gn_lstnr_conf_init (conf);
  conf->addr = (char *)addr;
  conf->port = port;

  const int rsocket = socket (AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
  if (rsocket < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to create server socket for [%s]:%i.", addr, port);
    goto end;
  }

  struct sockaddr_in sin;
  memset (&sin, 0, sizeof (sin));
  sin.sin_addr.s_addr = inet_addr (conf->addr);
  sin.sin_family = AF_INET;
  sin.sin_port = htons (conf->port);

  int reuseaddr = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof (int)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to set SO_REUSEADDR option");
    goto end;
  }

  int reuseport = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof (int)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to set SO_REUSEPORT option");
    goto end;
  }

  if (bind (rsocket, (struct sockaddr *)&sin, sizeof (sin)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to bind to [%s]:%i", conf->addr, conf->port);
    goto end;
  }

  if (listen (rsocket, SOMAXCONN) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to listen on [%s]:%i", conf->addr, conf->port);
    goto end;
  }

  conf->fd = rsocket;
  gn_lstnr_conf_list_push_back (list, conf);
  return;

  end:
  free (conf);
}

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

  gn_lstnr_conf_list_s lstnr_conf_list;
  gn_lstnr_conf_list_init (&lstnr_conf_list);

  gn_create_lstnr (&lstnr_conf_list, "0.0.0.0", 8080);
  gn_create_lstnr (&lstnr_conf_list, "192.168.2.2", 8081);

  while (true) {
    gn_lstnr_conf_s * lstnr_conf = lstnr_conf_list.head;
    for (uint16_t i = 0; i < lstnr_conf_list.len; lstnr_conf = lstnr_conf->next, i++) {
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
        goto close_raccept4;
      }
      const uint16_t sport = htons (sin.sin_port);

      struct sockaddr_in getsockname_sin;
      size_t sizeof_getsockname_sin = sizeof (getsockname_sin);
      memset (&getsockname_sin, 0, sizeof_getsockname_sin);
      if (getsockname (raccept4, (struct sockaddr *)&getsockname_sin, (socklen_t *)&sizeof_getsockname_sin) != 0) {
        error_at_line (0, errno, __FILE__, __LINE__, "getsockname() failed");
        goto close_raccept4;
      }

      char daddr[INET_ADDRSTRLEN];
      memset (daddr, 0, sizeof (daddr));
      if (inet_ntop (AF_INET, &getsockname_sin.sin_addr, daddr, INET_ADDRSTRLEN) == NULL) {
        error_at_line (0, errno, __FILE__, __LINE__, "inet_ntop() failed");
        goto close_raccept4;
      }

      printf ("[%i] Connection from [%s]:%i to [%s] / [%s]:%i\n\n", getpid (), saddr, sport, lstnr_conf->addr, daddr, lstnr_conf->port);

      gn_conn_s * const conn = malloc (sizeof (gn_conn_s));
      if (conn != NULL) {
        gn_conn_init (conn);
        conn->saddr = malloc (strlen (saddr) + 1);
        strcpy (conn->saddr, saddr);
        conn->sport = sport;
        conn->daddr = malloc (strlen (daddr) + 1);
        strcpy (conn->daddr, daddr);
        conn->fd = raccept4;
        conn->lstnr_conf = lstnr_conf;
        if (!gn_pass_conn (conn_mgmt_thrd_conf_list, conn)) continue;

        error_at_line (0, 0, __FILE__, __LINE__, "Connection wasn't passed");
      } else error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate connection structure");

      if (conn != NULL) {
        free (conn->daddr);
        free (conn->saddr);
        free (conn);
      }

      close_raccept4:
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

  // Test code start.
  gn_lstnr_conf_s * lstnr_conf = lstnr_conf_list.head;
  for (uint16_t i = 0; i < lstnr_conf_list.len; i++) {
    gn_lstnr_conf_s * next_lstnr_conf = lstnr_conf->next;

    close (lstnr_conf->fd);
    lstnr_conf->fd = -1;

    free (lstnr_conf);
    lstnr_conf = next_lstnr_conf;
  }
  // Test code end.

  conn_acpt_thrd_conf->state = CONN_ACPT_THRD_STOPPED;

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
