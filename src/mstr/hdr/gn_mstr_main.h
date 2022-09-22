#ifndef GN_MSTR_MAIN_H
#define GN_MSTR_MAIN_H

#include <mstr/hdr/gn_mstr_cfg_s.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void gn_start_wrkrs (gn_mstr_cfg_s * const);

uint8_t gn_create_lstnr (gn_lstnr_cfg_lst_s * const, const char * const, const uint16_t)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

void gn_ipc_close (int * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_ipc_create (gn_mstr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

bool gn_ipc_listen (int * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

bool gn_ipc_path_gen (struct sockaddr_un * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

bool gn_lstnr_cfg_lst_pop (gn_lstnr_cfg_lst_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

void gn_mstr_cfg_ini (gn_mstr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_mstr_cfg_load (const char * const, gn_mstr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

char * gn_self_path (uint8_t * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

#endif // GN_MSTR_MAIN_H
