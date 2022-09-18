#include <mstr/hdr/gn_self_path.h>

/*
 * TODO: Add description.
 */

char *
gn_self_path (uint8_t * const err)
{
  *err = 0;

  char proc_path[PROC_PATH_SZ];
  memset (proc_path, 0, PROC_PATH_SZ);

  const int rsnprintf = snprintf (proc_path, PROC_PATH_SZ, "/proc/%i/exe", getpid ());
  if (rsnprintf < 0) {
    fprintf (stderr, "snprintf(proc_path) error %i\n", rsnprintf);
    *err = 1;
    goto lbl_end;
  }

  if ((size_t)rsnprintf >= PROC_PATH_SZ) {
    fprintf (stderr, "snprintf(proc_path) buffer too small (%i bytes needed)\n", rsnprintf);
    *err = 2;
    goto lbl_end;
  }

  // Get the path 'proc_path' points to.
  char self_path_tmp[SELF_PATH_SZ];
  memset (self_path_tmp, 0, SELF_PATH_SZ);
  const ssize_t rreadlink = readlink (proc_path, self_path_tmp, SELF_PATH_SZ);
  if (rreadlink < 0) {
    fprintf (stderr, "readlink() error %i (%s)\n", errno, strerror (errno));
    *err = 3;
    goto lbl_end;
  }

  if (rreadlink == SELF_PATH_SZ) {
    fprintf (stderr, "readlink() target buffer too small (%li bytes)\n", rreadlink);
    *err = 4;
    goto lbl_end;
  }

  const size_t self_path_tmp_len = (size_t)rreadlink;
  self_path_tmp[self_path_tmp_len] = '\0';

  // Allocate a buffer with the right size.
  const size_t self_path_sz = self_path_tmp_len + 1;
  char * const self_path = malloc (self_path_sz);
  if (self_path == NULL) {
    fprintf (stderr, "self_path malloc(%li) failed\n", self_path_sz);
    *err = 5;
    goto lbl_end;
  }

  strncpy (self_path, self_path_tmp, self_path_sz); // TODO: Use strlcpy()
  return self_path;

  lbl_end:
  return NULL;
}
