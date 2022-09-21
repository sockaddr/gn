#include <mstr/hdr/gn_lstnrs_send.h>

void
gn_lstnrs_send (const int ipc_fd, const gn_lstnr_cfg_lst_s * const lc_lst)
{
  // Send server socket info one by one.
  gn_lstnr_cfg_s * lc = lc_lst->head;
  for (uint8_t i = 0; i < lc_lst->len; lc = lc->next, i++)
  {
    printf ("Sending #%i [%s]:%i\n", lc->fd, lc->addr, lc->port); // TODO: Remove.
    gn_lstnr_send (ipc_fd, lc);
  }

  const ssize_t rsend = send (ipc_fd, "/", 1, SOCK_NONBLOCK);
  if (rsend < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "send() failed");
  }
}
