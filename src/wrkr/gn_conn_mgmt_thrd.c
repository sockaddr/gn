#include <wrkr/hdr/gn_conn_mgmt_thrd.h>

#include <unistd.h> // TODO: Remove.

void *
gn_conn_mgmt_thrd (void * const p)
{
  if (p == NULL) return NULL; // TODO: Log error.

  while (true) {
    sleep (1); // TODO: Remove.
  }

  return NULL; // TODO: Maybe return something else or store exit code in conf struct.
}
