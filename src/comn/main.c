#include <comn/hdr/main.h>

int
main (const int argc, const char * const * const argv)
{
  if (argc < 0) {
    fprintf (stderr, "Negative number of command line arguments (%i)\n", argc);
    return 1;
  }
  if (argc > 50) {
    fprintf (stderr, "Number of command line arguments is too high (%i)\n", argc);
    return 1;
  }
  if (argv[0] == NULL) {
    fprintf (stderr, "argv[0] is NULL\n");
    return 1;
  }

  const char * ipc_addr = NULL;
  bool worker = false; // If false the process will run as master, if true, as a worker.

  for (int argi = 1; argi < argc; argi++)
  {
    if (argv[argi] == NULL) {
      fprintf (stderr, "argv[%i] is NULL\n", argi);
      return 1;
    }
    else if (strncmp (argv[argi], "--ipc-addr", strlen ("--ipc_addr")) == 0) {
      if (++argi >= argc) {
        fprintf (stderr, "Missing value for command line argument %i \"--ipc-addr\"\n", argi);
        return 1;
      }

      ipc_addr = argv[argi];
      fprintf (stdout, "IPC addr: '%s'\n", ipc_addr);
    }
    else if (strncmp (argv[argi], "--worker", strlen ("--worker")) == 0) worker = true;
    else {
      fprintf (stderr, "Unexpected command line argument %i \"%s\"\n", argi, argv[argi]);
      return 1;
    }
  }

  int ret = 0;
  if (!worker) ret = gn_mstr_main ();
  else gn_wrkr_main (ipc_addr); // TODO: Place return value in 'ret'

  return ret;
}
