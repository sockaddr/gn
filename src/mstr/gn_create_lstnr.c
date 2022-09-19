#include <mstr/hdr/gn_create_lstnr.h>

/*
 * TODO: Add description.
 */

uint8_t
gn_create_lstnr (gn_lstnr_cfg_lst_s * const lst, const char * const addr, const uint16_t port)
{
  if (port == 0) { // What sense would it make to use port 0 ?
    fprintf (stderr, "Invalid server port %i\n", port);
    return 1;
  }

  struct sockaddr_in sin;
  memset (&sin, 0, sizeof (sin));

  errno = 0;
  const int rinet_pton = inet_pton (AF_INET, addr, &sin.sin_addr);
  switch (rinet_pton) {
    case 1: { // Address is valid.
      sin.sin_family = AF_INET;
      sin.sin_port = htons (port);
      break;
    }
    case 0: {
      fprintf (stderr, "Invalid IPv4 address [%s]\n", addr);
      return 2;
    }
    default: {
      fprintf (stderr, "Unexpected inet_pton() error. Code %i, errno %i (%s)\n", rinet_pton, errno, strerror (errno));
      return 3;
    }
  }

  gn_lstnr_cfg_s * const cfg = malloc (sizeof (gn_lstnr_cfg_s));
  if (cfg != NULL) gn_lstnr_cfg_ini (cfg);
  else {
    fprintf (stderr, "Failed to allocate server socket configuration for [%s]:%i\n", addr, port);
    return 4;
  }

  uint8_t ret = 0;
  const int rsocket = socket (AF_INET, SOCK_CLOEXEC | SOCK_NONBLOCK | SOCK_STREAM, IPPROTO_TCP);
  if (rsocket < 0) {
    fprintf (stderr, "Failed to create server socket for [%s]:%i (%s)\n", addr, port, strerror (errno));
    ret = 5;
    goto lbl_end;
  }

  int reuseaddr = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof (int)) != 0) {
    fprintf (stderr, "Failed to set SO_REUSEADDR option (%s)\n", strerror (errno));
    ret = 6;
    goto lbl_end;
  }

  int reuseport = 1;
  if (setsockopt (rsocket, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof (int)) != 0) {
    fprintf (stderr, "Failed to set SO_REUSEPORT option (%s)\n", strerror (errno));
    ret = 7;
    goto lbl_end;
  }

  if (bind (rsocket, (struct sockaddr *)&sin, sizeof (sin)) != 0) {
    fprintf (stderr, "Failed to bind to [%s]:%i (%s)\n", addr, port, strerror (errno));
    ret = 8;
    goto lbl_end;
  }

  if (listen (rsocket, SOMAXCONN) != 0) { // TODO: Allow user to change SOMAXCONN.
    fprintf (stderr, "Failed to listen on [%s]:%i (%s)\n", addr, port, strerror (errno));
    ret = 9;
    goto lbl_end;
  }

  cfg->fd = rsocket;
  cfg->addr = (char *)addr;
  cfg->port = port;

  (void)! gn_lstnr_conf_list_push_back (lst, cfg); // TODO: Check error.
  return ret;

  lbl_end:
  if (rsocket > -1) close (rsocket);
  free (cfg);
  return ret;
}
