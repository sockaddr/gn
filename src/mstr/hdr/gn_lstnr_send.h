#ifndef GN_LSTNR_SEND_H
#define GN_LSTNR_SEND_H

#include <comn/hdr/gn_lstnr_cfg_s.h>

#include <errno.h>
#include <error.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

void gn_send_fd (const int, int);

#endif // GN_LSTNR_SEND_H
