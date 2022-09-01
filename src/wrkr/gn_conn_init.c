#include <wrkr/hdr/gn_conn_init.h>

void
gn_conn_init (gn_conn_s * const conn)
{
  conn->fd = -1;
  conn->saddr = NULL;
  conn->sport = 0;
  conn->daddr = NULL;
  conn->lstnr_conf = NULL;
  conn->prev = NULL;
  conn->next = NULL;
}
