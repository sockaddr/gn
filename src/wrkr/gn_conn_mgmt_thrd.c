#include <stdio.h> // TODO: Remove.

void *
gn_conn_mgmt_thrd (void * const p)
{
  printf ("Thread started\n");

  // To silence compiler error "unused parameter p"
  if (p) {} // TODO: Remove.

  return NULL;
}
