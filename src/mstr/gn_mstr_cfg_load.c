#include <mstr/hdr/gn_mstr_cfg_load.h>

/*
 * TODO: Add description.
 */

bool
gn_mstr_cfg_load (const char * const path, gn_mstr_cfg_s * const mc)
{
  if (mc) {} // TODO: Remove.

  int ropen = open (path, O_CLOEXEC | O_RDONLY);
  if (ropen < 0) {
    fprintf (stderr, "Failed to open master configuration file \"%s\" (%s)\n", path, strerror (errno));
    return true;
  }

  size_t line_nr = 1; // Line we're at.
  size_t directive_line_nr = 1; // Line the directive was found at.

  const size_t read_buf_sz = 16;
  char read_buf[read_buf_sz];
  read_buf[0] = '\0';
  size_t read_buf_len = 0;

  const size_t directive_line_sz = 65536;
  char directive_line[directive_line_sz];
  directive_line[0] = '\0';
  size_t directive_line_len = 0;

  bool got_directive_line = false;
  bool load_lo = true;
  bool ret = true;

  while (load_lo) {
    // Append to read_buf. It may contain unused data from the previous read().
    const ssize_t rread = read (ropen, &read_buf[read_buf_len], read_buf_sz - 1 - read_buf_len);
    switch (rread) {
      case -1: {
        fprintf (stderr, "Failed to read master configuration file \"%s\" (%s)\n", path, strerror (errno));
        load_lo = false;

        if (errno == EBADF) ropen = -1;
        break;
      }
      case 0: {
        load_lo = false;
        ret = false;
        break;
      }
      default: {
        if (rread < -1) {
          fprintf (stderr, "Unexpected read() error. Code %li, errno %i (%s)\n", rread, errno, strerror (errno));
          load_lo = false;
          break;
        }

        // Append to read_buf. It may contain unused data from the previous read().
        read_buf_len += (size_t)rread;
        read_buf[read_buf_len] = '\0';

        if (!got_directive_line) {
          if (strchr (read_buf, ';') != NULL) {
            size_t read_buf_ix = 0;

            for (; read_buf[read_buf_ix] != ';'; read_buf_ix++) {
              if (read_buf[read_buf_ix] == '\n') {
                line_nr++;
                continue;
              }

              if (directive_line_len == 0) directive_line_nr = line_nr;
              directive_line[directive_line_len] = read_buf[read_buf_ix];
              directive_line_len++;
            }

            const size_t sem_ix = read_buf_ix; // Semicolon index.
            // Append the semicolon to the directive line.
            directive_line[directive_line_len] = read_buf[read_buf_ix];
            directive_line_len++;
            directive_line[directive_line_len] = '\0';

            // Move the remaining read_buf data to the beginning of read_buf.
            read_buf_ix++;
            for (size_t i = 0; read_buf_ix < read_buf_len; i++, read_buf_ix++) {
              // if (read_buf[read_buf_ix] == '\n') line_nr++;
              read_buf[i] = read_buf[read_buf_ix];
            }
            read_buf_len = read_buf_len - sem_ix - 1; // Update read_buf length.
            read_buf[read_buf_len] = '\0';

            got_directive_line = true;
          } else {
            for (size_t read_buf_ix = 0; read_buf[read_buf_ix] != '\0'; read_buf_ix++) {
              if (read_buf[read_buf_ix] == '\n') {
                line_nr++;
                continue;
              }

              if (directive_line_len == 0) directive_line_nr = line_nr;
              directive_line[directive_line_len] = read_buf[read_buf_ix];
              directive_line_len++;
            }
            directive_line[directive_line_len] = '\0';

            read_buf_len = 0;
          }
        }

        if (got_directive_line) {
          printf ("%s:%li: (%li) \"%s\"\n", path, directive_line_nr, directive_line_len, directive_line);
          directive_line[0] = '\0';
          directive_line_len = 0;
          got_directive_line = false;
        }
      }
    }
  }

  if (ropen != -1 && close (ropen) != 0) fprintf (stderr, "Failed to close master configuration file \"%s\" (%s)\n",
                                                  path, strerror (errno));

  return ret;
}
