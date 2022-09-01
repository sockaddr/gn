#ifndef GN_WRKR_CONF_S_H
#define GN_WRKR_CONF_S_H

#include <stdint.h>

struct gn_wrkr_conf_s
{
  uint16_t conn_mgmt_thrd_num;
  uint8_t  conn_acpt_thrd_num;
};

typedef struct gn_wrkr_conf_s gn_wrkr_conf_s;

#endif // GN_WRKR_CONF_S_H
