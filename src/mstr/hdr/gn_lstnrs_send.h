#ifndef GN_LSTNRS_SEND_H
#define GN_LSTNRS_SEND_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>

#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <sys/socket.h>

void gn_lstnr_send (const int, const gn_lstnr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull));

#endif // GN_LSTNRS_SEND_H
