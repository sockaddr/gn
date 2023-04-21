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
    const ssize_t rread = read (fd, &buf[buf_len], READ_BUF_SZ - 1 - buf_len);
    switch (rread) {
      case -1: {
        switch (errno) {
          // Don't stop reading if one of these errors occur.
          case EINTR:
          case EIO: {
            break;
          }
          default: {
            // Stop reading and invalidate fd if any other error occurs.
            fprintf (stderr, "Failed to read master configuration file \"%s\" (%s)\n", path, strerror (errno));
            fd = -1;
            loop = false;
          }
        }
        break;
      }
      case 0: {
        if (buf_len == 0) {
          loop = false;
          ret = false;
          break;
        }
        __attribute__((fallthrough));
      }
      default: {
        // Append to read buffer. It may contain unused data from the previous read().
        buf_len += (size_t)rread;
        buf[buf_len] = '\0';

        if (!got_ln) { // If we don't have a directive line...
          if (strchr (buf, ';') != NULL) { // and we have a line delimiter in the read buffer...
            // Append to the directive line buffer.
            size_t buf_i = 0;
            for (; buf[buf_i] != ';'; buf_i++) {
              if (buf[buf_i] == ' ' || buf[buf_i] == '\t') {
                if (drcv_ln_len == 0) continue;
              }
              if (buf[buf_i] == '\n') {
                ln_nr++;
                if (drcv_ln_len == 0) continue;
              }

              if (drcv_ln_len == DRCV_LN_SZ - 2) {
                fprintf (stderr, "Directive line buffer too small (%i bytes)\n", DRCV_LN_SZ);
                loop = false;
                goto lbl_end;
              }

              if (drcv_ln_len == 0) drcv_ln_nr = ln_nr;

              // Now append.
              drcv_ln[drcv_ln_len] = buf[buf_i];
              drcv_ln_len++;
            }

            if (drcv_ln_len == 0) drcv_ln_nr = ln_nr; // Correct the directive line number if empty directive found.

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
              if (buf[buf_i] == ' ' || buf[buf_i] == '\t') {
                if (drcv_ln_len == 0) continue;
              }
              if (buf[buf_i] == '\n') {
                ln_nr++;
                if (drcv_ln_len == 0) continue;
              }

              if (drcv_ln_len == 0) drcv_ln_nr = ln_nr; // Set the directive line number.

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

          char drcv_name[DRCV_NAME_SZ];
          memset (drcv_name, 0, DRCV_NAME_SZ);
          size_t drcv_name_len = 0;

          size_t drcv_ln_i = 0;
          for (; drcv_ln_i < drcv_ln_len; drcv_ln_i++) {
            if (drcv_ln[drcv_ln_i] == ' ' || drcv_ln[drcv_ln_i] == '\t' || drcv_ln[drcv_ln_i] == '\n' || drcv_ln[drcv_ln_i] == ';') {
              drcv_name[drcv_name_len] = '\0';
              break;
            }

            if (drcv_name_len == DRCV_NAME_SZ - 2) {
              fprintf (stderr, "Directive name too long \"%s\" (maximum %i bytes)\n", drcv_ln, DRCV_NAME_SZ - 2);
              loop = false;
              goto lbl_end;
            }

            drcv_name[drcv_name_len] = drcv_ln[drcv_ln_i];
            drcv_name_len++;
          }

          printf ("drcv_name (%li) \"%s\"\n", drcv_name_len, drcv_name);
          if (drcv_name_len == 0) {
            fprintf (stderr, "Empty directive in \"%s\" line %li\n", path, drcv_ln_nr);
            loop = false;
            ret = true;
            break;
          }

          char drcv_val[DRCV_VAL_SZ];
          memset (drcv_val, 0, DRCV_VAL_SZ);
          size_t drcv_val_len = 0;

          for (; drcv_ln_i < drcv_ln_len; drcv_ln_i++) {
            if (drcv_ln[drcv_ln_i] == ';') {
              drcv_val[drcv_val_len] = '\0';
              break;
            }

            if (drcv_val_len == 0) {
              if (drcv_ln[drcv_ln_i] == ' ' || drcv_ln[drcv_ln_i] == '\t' || drcv_ln[drcv_ln_i] == '\n') continue;
            }

            if (drcv_val_len == DRCV_VAL_SZ - 1) {
              fprintf (stderr, "Directive value too long \"%s\" (maximum %i bytes)\n", drcv_ln, DRCV_VAL_SZ - 1);
              loop = false;
              goto lbl_end;
            }

            drcv_val[drcv_val_len] = drcv_ln[drcv_ln_i];
            drcv_val_len++;
          }

          if (drcv_val_len > 0) {
            for (size_t drcv_val_i = drcv_val_len - 1; drcv_val_i > 0; drcv_val_i--) {
              if (drcv_val[drcv_val_i] == ' ' || drcv_val[drcv_val_i] == '\t' || drcv_val[drcv_val_i] == '\n') {
                drcv_val_len--;
                continue;
              }
              drcv_val[drcv_val_len] = '\0';
              break;
            }
          }

          printf ("drcv_val (%li) \"%s\"\n", drcv_val_len, drcv_val);

          if (!strcmp (drcv_name, "workers")) {

          } else if (!strcmp (drcv_name, "connection_acceptance_threads")) {

          } else if (!strcmp (drcv_name, "connection_management_threads")) {

          } else if (!strcmp (drcv_name, "allow_start_without_connection_acceptance_threads")) {

          } else if (!strcmp (drcv_name, "allow_start_without_connection_management_threads")) {

          } else {
            fprintf (stderr, "Unknow directive \"%s\" in \"%s\" line %li\n", drcv_name, path, drcv_ln_nr);
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
