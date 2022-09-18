#ifndef GN_MSTR_CFG_S_H
#define GN_MSTR_CFG_S_H

#include <stdint.h>

/*
 * TODO: Add description.
 */

struct gn_mstr_cfg_s
{
  char *  self_path; // Absolute path to the program.
  uint8_t wrkrs_num; // Number of worker processes to start.
};

typedef struct gn_mstr_cfg_s gn_mstr_cfg_s;

#endif // GN_MSTR_CFG_S_H
