#include <comn/hdr/main.h>

int
main (const int argc, const char * const * const argv)
{
  // To silence compiler error "unused parameter argc/argv"
  if (argc < 0 && argv) {} // TODO: Remove.

  gn_wrkr_main ();

  return 0; // TODO: Return a variable.
}
