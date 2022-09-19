#ifndef GN_CREATE_LSTNR_H
#define GN_CREATE_LSTNR_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void gn_lstnr_cfg_ini (gn_lstnr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_lstnr_cfg_lst_pshb (gn_lstnr_cfg_lst_s * const, gn_lstnr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_CREATE_LSTNR_H
