#ifndef GN_MSTR_CFG_S_H
#define GN_MSTR_CFG_S_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>

#include <sys/un.h>

/*
 * TODO: Add description.
 */

// Check gn_mstr_cfg_ini() after modifying this struct.

typedef struct
{
  struct sockaddr_un ipc_addr;      // Address for master/worker IPC.
  int                ipc_fd;        // Socket for master/worker IPC.
  gn_lstnr_cfg_lst_s lstnr_cfg_lst; // List of server sockets info.
  char *             self_path;     // Absolute path to the program.
  uint8_t            wrkrs_num;     // Number of worker processes to start.
} gn_mstr_cfg_s;

#endif // GN_MSTR_CFG_S_H
