#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h> // TODO: Remove.

void *
gn_conn_mgmt_thrd (void * const p)
{
  printf ("Thread started\n");

  // To silence compiler error "unused parameter p"
  if (p) {} // TODO: Remove.

  return NULL;
}

void
gn_start_conn_mgmt_thrds (conn_mgmt_thrd_conf_list * const list)
{
  /* Number of connection management threads to start. size_t would be too large.
     uint8_t might be too small for servers handling large amounts of connections.
   */
  const uint16_t conn_mgmt_thrd_num = 4; // TODO: Set this from config file. Maybe rename.

  for (uint16_t i = 0; i < conn_mgmt_thrd_num; i++) {
    pthread_t thrd_id;
    const int rpthread_create = pthread_create (&thrd_id, NULL, gn_conn_mgmt_thrd, NULL);
    switch (rpthread_create) {
    }
  }
}

struct gn_conn_mgmt_thrd_conf_s {
  pthread_t thrd_id;
};

typedef struct gn_conn_mgmt_thrd_conf_s gn_conn_mgmt_thrd_conf_s;

struct gn_conn_mgmt_thrd_conf_list_s
{
  gn_conn_mgmt_thrd_conf_s * head;
  gn_conn_mgmt_thrd_conf_s * tail;
  uint16_t                   len;
};

typedef struct gn_conn_mgmt_thrd_conf_list_s gn_conn_mgmt_thrd_conf_list_s;

void
gn_wrkr_main (void)
{
  gn_conn_mgmt_thrd_conf_list_s conn_mgmt_thrd_conf_list;
  // Start connection management threads.
  gn_start_conn_mgmt_thrds (&conn_mgmt_thrd_conf_list);
}

int
main (const int argc, const char * const * const argv)
{
  // To silence compiler error "unused parameter argc/argv"
  if (argc < 0 && argv) {} // TODO: Remove.

  gn_wrkr_main ();

  return 0;
}
