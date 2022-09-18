#include <mstr/hdr/gn_create_lstnr.h>

void
gn_create_lstnr (gn_lstnr_cfg_lst_s * const list, const char * const addr, const uint16_t port)
{
  gn_lstnr_conf_s * const conf = malloc (sizeof (gn_lstnr_conf_s));
  if (conf == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "Failed to allocate listener configuration for [%s]:%i", addr, port);
    return;
  }

  gn_lstnr_conf_init (conf);
  conf->addr = (char *)addr;
  conf->port = port;

  const int rsocket = socket (AF_INET, SOCK_CLOEXEC | SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
  if (rsocket < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to create server socket for [%s]:%i.", addr, port);
    goto lbl_end;
  }

  struct sockaddr_in sin;
  memset (&sin, 0, sizeof (sin));
  sin.sin_addr.s_addr = inet_addr (conf->addr);
  sin.sin_family = AF_INET;
  sin.sin_port = htons (conf->port);

  int reuseaddr = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof (int)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to set SO_REUSEADDR option");
    goto lbl_end;
  }

  int reuseport = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof (int)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to set SO_REUSEPORT option");
    goto lbl_end;
  }

  if (bind (rsocket, (struct sockaddr *)&sin, sizeof (sin)) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to bind to [%s]:%i", conf->addr, conf->port);
    goto lbl_end;
  }

  if (listen (rsocket, SOMAXCONN) != 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "Failed to listen on [%s]:%i", conf->addr, conf->port);
    goto lbl_end;
  }

  conf->fd = rsocket;
  (void)! gn_lstnr_conf_list_push_back (list, conf);
  return;

  lbl_end:
  free (conf);
}
