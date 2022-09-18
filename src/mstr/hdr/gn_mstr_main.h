#ifndef GN_MSTR_MAIN_H
#define GN_MSTR_MAIN_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>
#include <mstr/hdr/gn_mstr_cfg_s.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void   gn_create_lstnr (gn_lstnr_cfg_lst_s * const, const char * const, const uint16_t);
void   gn_start_wrkrs (gn_mstr_cfg_s * const, gn_lstnr_cfg_lst_s * const);

void   gn_lstnr_cfg_lst_ini (gn_lstnr_cfg_lst_s * const)
  __attribute__((cold)) __attribute__((nonnull));

void   gn_mstr_cfg_ini (gn_mstr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

char * gn_self_path (uint8_t * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_MSTR_MAIN_H
