#ifndef GN_START_WRKR_H
#define GN_START_WRKR_H

#include <mstr/hdr/gn_mstr_cfg_s.h>

#include <errno.h>
#include <error.h>
#include <poll.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

void gn_send_fd (const int, int);

#endif // GN_START_WRKR_H
