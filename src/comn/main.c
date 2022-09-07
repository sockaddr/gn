#include <comn/hdr/main.h>

int
main (const int argc, const char * const * const argv)
{
  bool worker = false; // If false the process will run as master, if true, as a worker.

  for (int argi = 1; argi < argc; argi++)
  {
    if (!strncmp (argv[argi], "--worker", strlen ("--worker"))) worker = true;
    else {
      error_at_line (0, 0, __FILE__, __LINE__, "Unexpected argument \"%s\"", argv[argi]);
      return 1;
    }
  }

  if (!worker) gn_mstr_main ();
  else gn_wrkr_main ();

  return 0; // TODO: Return a variable.
}
