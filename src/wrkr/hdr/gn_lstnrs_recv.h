#ifndef GN_LSTNRS_RECV_H
#define GN_LSTNRS_RECV_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>

#include <errno.h>
#include <error.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

void gn_lstnr_cfg_ini (gn_lstnr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_lstnr_cfg_lst_pshb (gn_lstnr_cfg_lst_s * const, gn_lstnr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__((warn_unused_result));

int gn_recv_fd (int);

#endif // GN_LSTNRS_RECV_H
