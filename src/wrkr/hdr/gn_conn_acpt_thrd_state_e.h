#ifndef GN_CONN_ACPT_THRD_STATE_E_H
#define GN_CONN_ACPT_THRD_STATE_E_H

enum gn_conn_acpt_thrd_state_e {
  CONN_ACPT_THRD_RUNNING,
  CONN_ACPT_THRD_STOPPING,
  CONN_ACPT_THRD_STOPPED
};

typedef enum gn_conn_acpt_thrd_state_e gn_conn_acpt_thrd_state_e;

#endif // GN_CONN_ACPT_THRD_STATE_E_H
