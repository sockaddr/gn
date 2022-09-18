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

  bool worker = false; // If false the process will run as master, if true, as a worker.

  for (int argi = 1; argi < argc; argi++)
  {
    if (argv[argi] == NULL) {
      fprintf (stderr, "argv[%i] is NULL\n", argi);
      return 1;
    }
    else if (strncmp (argv[argi], "--worker", strlen ("--worker")) == 0) worker = true;
    else {
      fprintf (stderr, "Unexpected command line argument %i \"%s\"\n", argi, argv[argi]);
      return 1;
    }
  }

  if (!worker) gn_mstr_main ();
  else gn_wrkr_main ();

  return 0; // TODO: Return a variable.
}
