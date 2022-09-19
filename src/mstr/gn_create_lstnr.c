#include <mstr/hdr/gn_create_lstnr.h>

/*
 * TODO: Add description.
 */

uint8_t
gn_create_lstnr (gn_lstnr_cfg_lst_s * const lst, const char * const addr, const uint16_t port)
{
  gn_lstnr_cfg_s * const cfg = malloc (sizeof (gn_lstnr_cfg_s));
  if (cfg == NULL) {
    fprintf (stderr, "Failed to allocate listener configuration for [%s]:%i\n", addr, port);
    return 1;
  }

  gn_lstnr_cfg_ini (cfg);
  cfg->addr = (char *)addr;
  cfg->port = port;

  uint8_t ret = 0;
  const int rsocket = socket (AF_INET, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, IPPROTO_TCP);
  if (rsocket < 0) {
    fprintf (stderr, "Failed to create server socket for [%s]:%i (%s)\n", addr, port, strerror (errno));
    ret = 2;
    goto lbl_end;
  }

  struct sockaddr_in sin;
  memset (&sin, 0, sizeof (sin));
  sin.sin_addr.s_addr = inet_addr (cfg->addr); // TODO: Check cfg->addr is valid.
  sin.sin_family = AF_INET;
  sin.sin_port = htons (cfg->port); // TODO: Check cfg->port is valid.

  int reuseaddr = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof (int)) != 0) {
    fprintf (stderr, "Failed to set SO_REUSEADDR option (%s)\n", strerror (errno));
    ret = 3;
    goto lbl_end;
  }

  int reuseport = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof (int)) != 0) {
    fprintf (stderr, "Failed to set SO_REUSEPORT option (%s)\n", strerror (errno));
    ret = 4;
    goto lbl_end;
  }

  if (bind (rsocket, (struct sockaddr *)&sin, sizeof (sin)) != 0) {
    fprintf (stderr, "Failed to bind to [%s]:%i (%s)\n", cfg->addr, cfg->port, strerror (errno));
    ret = 5;
    goto lbl_end;
  }

  if (listen (rsocket, SOMAXCONN) != 0) { // TODO: Allow user to change SOMAXCONN.
    fprintf (stderr, "Failed to listen on [%s]:%i (%s)\n", cfg->addr, cfg->port, strerror (errno));
    ret = 6;
    goto lbl_end;
  }

  cfg->fd = rsocket;
  (void)! gn_lstnr_conf_list_push_back (lst, cfg); // TODO: Check error.
  return ret;

  lbl_end:
  if (rsocket > -1) close (rsocket);
  free (cfg);
  return ret;
}
