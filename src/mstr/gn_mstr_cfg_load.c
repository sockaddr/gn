#include <mstr/hdr/gn_mstr_cfg_load.h>

void
gn_mstr_cfg_load ()
{
  const int ropen = open ("./etc/gn/gn.cfg", O_RDONLY);
  if (ropen > -1) {
    size_t line_nr = 1;
    size_t directive_line_nr = 0;
    const size_t read_buf_sz = 16;
    char read_buf[read_buf_sz];
    read_buf[0] = '\0';
    size_t read_buf_len = 0;

    bool got_directive_line = false;
    const size_t directive_line_sz = 65536;
    char directive_line[directive_line_sz];
    directive_line[0] = '\0';
    size_t directive_line_len = 0;

    bool load_lo = true;
    while (load_lo) {
      const ssize_t rread = read (ropen, &read_buf[read_buf_len], read_buf_sz - 1 - read_buf_len);
      switch (rread) {
        case -1: {
          // TODO. (EINTR, etc)
          break;
        }
        case 0: {
          load_lo = false;
          break;
        }
        default: {
          if (rread < -1) {
            error_at_line (0, errno, __FILE__, __LINE__, "Unexpected read() return value %li", rread);
            load_lo = false;
          }

          read_buf_len += (size_t)rread;
          read_buf[read_buf_len] = '\0';
          /*printf ("read_buf_len: %li\n", read_buf_len);
          printf ("read_buf: \"%s\"\n\n", read_buf);*/

          if (!got_directive_line) {
            if (strchr (read_buf, ';')) {
              size_t read_buf_ix = 0;

              while (read_buf[read_buf_ix] != ';') {
                if (read_buf[read_buf_ix] == '\n') {
                  line_nr++;
                } else {
                  if (directive_line_len == 0) directive_line_nr = line_nr;
                  directive_line[directive_line_len] = read_buf[read_buf_ix];
                  directive_line_len++;
                }

                read_buf_ix++;
              }
              const size_t sem_ix = read_buf_ix;
              directive_line[directive_line_len] = read_buf[read_buf_ix];
              directive_line_len++;
              directive_line[directive_line_len] = '\0';

              read_buf_ix++;
              size_t i = 0;
              while (read_buf_ix < read_buf_len) {
                // if (read_buf[read_buf_ix] == '\n') line_nr++;
                read_buf[i] = read_buf[read_buf_ix];
                i++;
                read_buf_ix++;
              }
              read_buf_len = read_buf_len - sem_ix - 1;
              read_buf[read_buf_len] = '\0';

              got_directive_line = true;
            } else {
              size_t read_buf_ix = 0;

              while (read_buf[read_buf_ix] != '\0') {
                if (read_buf[read_buf_ix] == '\n') {
                  line_nr++;
                } else {
                  if (directive_line_len == 0) directive_line_nr = line_nr;
                  directive_line[directive_line_len] = read_buf[read_buf_ix];
                  directive_line_len++;
                }

                read_buf_ix++;
              }
              directive_line[directive_line_len] = '\0';

              read_buf_len = 0;
            }
          }

          if (got_directive_line) {
            printf ("directive_line (%li) %li:\"%s\"\n", directive_line_len, directive_line_nr, directive_line);
            directive_line[0] = '\0';
            directive_line_len = 0;
            got_directive_line = false;
          }
          break;
        }
      }
    }
    if (close (ropen) != 0) error_at_line (0, errno, __FILE__, __LINE__, "close() failed");
  } else error_at_line (0, errno, __FILE__, __LINE__, "open() failed");
}
