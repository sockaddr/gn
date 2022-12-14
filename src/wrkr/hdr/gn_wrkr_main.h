#ifndef GN_WRKR_MAIN_H
#define GN_WRKR_MAIN_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>
#include <wrkr/hdr/gn_wrkr_cfg_s.h>

#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void gn_lstnr_cfg_lst_ini (gn_lstnr_cfg_lst_s * const)
  __attribute__((cold)) __attribute__((nonnull));

void gn_lstnrs_recv (const int, gn_lstnr_cfg_lst_s * const)
  __attribute__((cold)) __attribute__((nonnull));

void gn_start_conn_acpt_thrds (gn_wrkr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));
void gn_start_conn_mgmt_thrds (gn_wrkr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

void gn_stop_conn_acpt_thrds (gn_wrkr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));
void gn_stop_conn_mgmt_thrds (gn_wrkr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_wrkr_cfg_ini (gn_wrkr_cfg_s * const, gn_lstnr_cfg_lst_s * const)
  __attribute__((cold)) __attribute__((nonnull));

#endif // GN_WRKR_MAIN_H
