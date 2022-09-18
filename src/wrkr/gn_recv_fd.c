#include <wrkr/hdr/gn_recv_fd.h>

int
gn_recv_fd (int sock)
{
    struct msghdr msg;
    memset (&msg, 0, sizeof (msg));

    char buf[256];
    struct iovec iov = {
      .iov_base = buf,
      .iov_len = sizeof (buf)
    };

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    char c_buf[256];
    msg.msg_control = c_buf;
    msg.msg_controllen = sizeof (c_buf);

    if (recvmsg (sock, &msg, 0) < 0) {
      error_at_line (0, errno, __FILE__, __LINE__, "recvmsg() failed");
      return -1;
    }

    struct cmsghdr * const cmsg = CMSG_FIRSTHDR (&msg);
    unsigned char * const dat = CMSG_DATA (cmsg);

    int fd = *((int*) dat);
    return fd;
}
