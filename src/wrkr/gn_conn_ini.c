#include <wrkr/hdr/gn_conn_ini.h>

/*
 * TODO: Add description.
 */

void
gn_conn_ini (gn_conn_s * const conn)
{
  conn->fd = -1;
  conn->saddr = NULL;
  conn->sport = 0;
  conn->daddr = NULL;
  conn->lstnr_cfg = NULL;
  conn->prev = NULL;
  conn->next = NULL;
}
