#include <mstr/hdr/gn_send_fd.h>

void
gn_send_fd (const int sock, int fd)
{
  struct msghdr msg = { 0 };
  char buf[CMSG_SPACE (sizeof (fd))];
  memset (buf, '\0', sizeof (buf));
  struct iovec iov = {
    .iov_base = "A",
    .iov_len = 1
  };

  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_control = buf;
  msg.msg_controllen = sizeof (buf);

  struct cmsghdr * const cmsg = CMSG_FIRSTHDR (&msg);
  cmsg->cmsg_len = CMSG_LEN (sizeof (fd));
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = SCM_RIGHTS;


  *((int *) CMSG_DATA (cmsg)) = fd;

  msg.msg_controllen = CMSG_SPACE (sizeof (fd));

  if (sendmsg (sock, &msg, 0) < 0) printf ("sendmsg() failed");
}
