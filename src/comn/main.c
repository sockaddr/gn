#include <comn/hdr/main.h>

int
main (const int argc, const char * const * const argv)
{
  if (argc < 0) {
    fprintf (stderr, "Negative number of command line arguments (%i)\n", argc);
    return 1;
  }
  if (argc > 50) { // TODO: Maybe lower this number.
    fprintf (stderr, "Number of command line arguments is too high (%i)\n", argc);
    return 1;
  }
  if (argv[0] == NULL) {
    fprintf (stderr, "argv[0] is NULL\n");
    return 1;
  }

  const char * ipc_addr_str = NULL; // "Address" of the Unix socket for master/worker IPC.

  for (int argi = 1; argi < argc; argi++)
  {
    if (argv[argi] == NULL) {
      fprintf (stderr, "argv[%i] is NULL\n", argi);
      return 1;
    }
    else if (strncmp (argv[argi], "--ipc-addr", strlen ("--ipc-addr")) == 0) {
      if (ipc_addr_str != NULL) {
        fprintf (stderr, "Command line argument \"--ipc-addr\" already set\n");
        return 1;
      }
      if (++argi == argc) {
        fprintf (stderr, "Missing value for command line argument %i \"--ipc-addr\"\n", argi);
        return 1;
      }

      ipc_addr_str = argv[argi];
    }
    else {
      fprintf (stderr, "Unexpected command line argument %i \"%s\"\n", argi, argv[argi]);
      return 1;
    }
  }

  int ret = 0;
  // If ipc_addr_str is set it means we must start as worker. --ipc-addr argument doesn't make sense for master process.
  if (ipc_addr_str == NULL) ret = gn_mstr_main ();
  else gn_wrkr_main (ipc_addr_str); // TODO: Place return value in 'ret' and maybe move ipc_addr_str to gn_wrkr_cfg_s.

  return ret;
}
