#include <mstr/hdr/gn_mstr_cfg_load.h>

/*
 * TODO: Add description.
 */

bool
gn_mstr_cfg_load (const char * const path, gn_mstr_cfg_s * const mc)
{
  if (mc) {} // TODO: Remove.

  int fd = open (path, O_CLOEXEC | O_RDONLY);
  if (fd < 0) {
    fprintf (stderr, "Failed to open master configuration file \"%s\" (%s)\n", path, strerror (errno));
    return true;
  }

  size_t ln_nr = 1; // Line we're at.
  size_t drcv_ln_nr = 1; // Line the directive was found at.

  char buf[READ_BUF_SZ];
  memset (buf, 0, READ_BUF_SZ);
  size_t buf_len = 0;

  char drcv_ln[DRCV_LN_SZ];
  memset (drcv_ln, 0, DRCV_LN_SZ);
  size_t drcv_ln_len = 0;

  bool got_ln = false;
  bool loop = true;
  bool ret = true;

  while (loop) {
    // Append to read buffer. It may contain unused data from the previous read().
    errno = 0;
    const ssize_t rread = read (fd, &buf[buf_len], READ_BUF_SZ - 1 - buf_len);
    switch (rread) {
      case -1: {
        fprintf (stderr, "Failed to read master configuration file \"%s\" (%s)\n", path, strerror (errno));
        loop = false;

        if (errno == EBADF) fd = -1;
        break;
      }
      case 0: {
        loop = false;
        ret = false;
        break;
      }
      default: {
        if (rread < -1) {
          fprintf (stderr, "Unexpected read() error while loading master configuration file \"%s\". "
                           "Code %li, errno %i (%s)\n", path, rread, errno, strerror (errno));
          loop = false;
          break;
        }

        // Append to read buffer. It may contain unused data from the previous read().
        buf_len += (size_t)rread;
        buf[buf_len] = '\0';

        if (!got_ln) { // If we don't have a directive line...
          if (strchr (buf, ';') != NULL) { // and we have a line delimiter in the read buffer...
            // Append to the directive line buffer.
            size_t buf_i = 0;
            for (; buf[buf_i] != ';'; buf_i++) {
              // Don't append leading new-line characters.
              if (buf[buf_i] == '\n') {
                ln_nr++;
                continue;
              }

              // Here, we skipped new-lines, now we're at the line where the directive starts.
              if (drcv_ln_len == 0) {
                drcv_ln_nr = ln_nr; // Set the directive line number.
                if (buf[buf_i] == ' ' || buf[buf_i] == '\t') continue; // Don't append leading whitespace.
              }

              if (drcv_ln_len == DRCV_LN_SZ - 2) {
                fprintf (stderr, "Directive line buffer too small (%i bytes)\n", DRCV_LN_SZ);
                loop = false;
                goto lbl_end;
              }

              // Now append.
              drcv_ln[drcv_ln_len] = buf[buf_i];
              drcv_ln_len++;
            }

            const size_t sem_i = buf_i; // Semicolon index.
            // Append the semicolon to the directive line.
            drcv_ln[drcv_ln_len] = buf[buf_i];
            drcv_ln_len++;
            drcv_ln[drcv_ln_len] = '\0';

            // Move the remaining read_buf data to the beginning of read_buf.
            buf_i++;
            for (size_t buf_i_s = 0; buf_i < buf_len; buf_i_s++, buf_i++) buf[buf_i_s] = buf[buf_i];
            buf_len = buf_len - sem_i - 1; // Update read_buf length.
            buf[buf_len] = '\0';

            got_ln = true;
          } else { // and we don't have a line delimiter in the read buffer...
            for (size_t buf_i = 0; buf[buf_i] != '\0'; buf_i++) {
              // Don't append leading new-line characters.
              if (buf[buf_i] == '\n') {
                ln_nr++;
                continue;
              }

              if (drcv_ln_len == 0) {
                drcv_ln_nr = ln_nr; // Set the directive line number.
                if (buf[buf_i] == ' ' || buf[buf_i] == '\t') continue; // Don't append leading whitespace.
              }

              if (drcv_ln_len == DRCV_LN_SZ - 2) {
                fprintf (stderr, "Directive line buffer too small (%i bytes)\n", DRCV_LN_SZ);
                loop = false;
                goto lbl_end;
              }

              // Now append.
              drcv_ln[drcv_ln_len] = buf[buf_i];
              drcv_ln_len++;
            }

            drcv_ln[drcv_ln_len] = '\0';

            buf_len = 0;
          }
        }

        if (got_ln) {
          printf ("%s:%li: (%li) \"%s\"\n", path, drcv_ln_nr, drcv_ln_len, drcv_ln);

          const size_t directive_name_sz = 64;
          char directive_name[directive_name_sz];
          size_t directive_name_len = 0;

          size_t directive_line_ix = 0;
          while (directive_line_ix < drcv_ln_len) {
            if (drcv_ln[directive_line_ix] == ' ' || drcv_ln[directive_line_ix] == '\t' || drcv_ln[directive_line_ix] == ';') {
              directive_name[directive_name_len] = '\0';
              break;
            }
            if (directive_name_len == directive_name_sz - 2) {
              fprintf (stderr, "Directive name too long (%s)\n", drcv_ln);
              return true; // TODO: ropen not closed.
            }
            directive_name[directive_name_len] = drcv_ln[directive_line_ix];
            directive_line_ix++;
            directive_name_len++;
          }

          printf ("directive_name (%li) \"%s\"\n", directive_name_len, directive_name);
          if (directive_name_len == 1) {
            fprintf (stderr, "Empty directive in \"%s\" line %li\n", path, drcv_ln_nr);
            loop = false;
            ret = true;
            break;
          }

          const size_t directive_value_sz = 65536;
          char directive_value[directive_value_sz];
          size_t directive_value_len = 0;

          for (; directive_line_ix < drcv_ln_len; directive_line_ix++) {
            if (drcv_ln[directive_line_ix] == ';') {
              directive_value[directive_value_len] = '\0';
              break;
            }

            if (directive_value_len == 0) {
              if (drcv_ln[directive_line_ix] == ' ' || drcv_ln[directive_line_ix] == '\t') continue;
            }

            directive_value[directive_value_len] = drcv_ln[directive_line_ix];
            directive_value_len++;
          }

          printf ("directive_value (%li) \"%s\"\n", directive_value_len, directive_value);

          if (!strcmp (directive_name, "workers")) {

          } else if (!strcmp (directive_name, "connection_acceptance_threads")) {

          } else if (!strcmp (directive_name, "connection_management_threads")) {

          } else if (!strcmp (directive_name, "allow_start_without_connection_acceptance_threads")) {

          } else if (!strcmp (directive_name, "allow_start_without_connection_management_threads")) {

          } else {
            fprintf (stderr, "Unknow directive \"%s\" in \"%s\" line %li\n", directive_name, path, drcv_ln_nr);
            loop = false;
            ret = true;
          }

          drcv_ln[0] = '\0';
          drcv_ln_len = 0;
          got_ln = false;
        }
      }
    }
  }

  lbl_end:
  if (fd != -1 && close (fd) != 0) fprintf (stderr, "Failed to close master configuration file \"%s\" (%s)\n", path,
                                            strerror (errno));

  return ret;
}
