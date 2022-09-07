#include <mstr/hdr/gn_self_path.h>

char *
gn_self_path (uint8_t * const err)
{
  char proc_path[PROC_PATH_SZ];
  memset (proc_path, 0, PROC_PATH_SZ);

  const int rsnprintf = snprintf (proc_path, PROC_PATH_SZ, "/proc/%i/exe", getpid ());
  if (rsnprintf < 0) {
    error_at_line (0, 0, __FILE__, __LINE__, "snprintf() returned %i", rsnprintf);
    if (err != NULL) *err = 1;
    goto end;
  }

  if ((size_t)rsnprintf >= PROC_PATH_SZ) {
    error_at_line (0, 0, __FILE__, __LINE__, "snprintf() returned %i", rsnprintf);
    if (err != NULL) *err = 2;
    goto end;
  }


  char self_path_tmp[SELF_PATH_SZ];
  memset (self_path_tmp, 0, SELF_PATH_SZ);
  ssize_t rreadlink = readlink (proc_path, self_path_tmp, SELF_PATH_SZ);
  if (rreadlink < 0) {
    error_at_line (0, errno, __FILE__, __LINE__, "readlink() returned %li", rreadlink);
    if (err != NULL) *err = 3;
    goto end;
  }
  printf ("rreadlink() returned %li\n", rreadlink);
  if (rreadlink == SELF_PATH_SZ) {
    error_at_line (0, 0, __FILE__, __LINE__, "readlink() returned %li", rreadlink);
    if (err != NULL) *err = 4;
    goto end;
  }

  const size_t self_path_tmp_len = (size_t)rreadlink;
  self_path_tmp[self_path_tmp_len] = '\0';

  const size_t self_path_sz = self_path_tmp_len + 1;
  char * const self_path = malloc (self_path_sz);
  if (self_path == NULL) {
    error_at_line (0, 0, __FILE__, __LINE__, "malloc(%li) failed", self_path_sz);
    if (err != NULL) *err = 5;
    goto end;
  }

  strncpy (self_path, self_path_tmp, self_path_sz);
  return self_path;

  end: ;
  return NULL;
}
