#ifndef GN_MSTR_CFG_S_H
#define GN_MSTR_CFG_S_H

#include <comn/hdr/gn_lstnr_cfg_lst_s.h>

#include <sys/un.h>

/*
 * TODO: Add description.
 */

// Check gn_mstr_cfg_ini() after modifying this struct.

struct gn_mstr_cfg_s
{
  gn_lstnr_cfg_lst_s lstnr_cfg_lst; // List of server sockets info.
  char *             self_path;     // Absolute path to the program.
  struct sockaddr_un wrkr_io_addr;  // Address for master/worker IO.
  int                wrkr_io_fd;    // Socket for master/worker IO.
  uint8_t            wrkrs_num;     // Number of worker processes to start.
};

typedef struct gn_mstr_cfg_s gn_mstr_cfg_s;

#endif // GN_MSTR_CFG_S_H
