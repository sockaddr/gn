void
gn_start_conn_mgmt_thrds (void)
{
}

void
gn_wrkr_main (void)
{
  gn_start_conn_mgmt_thrds ();
}

int
main (const int argc, const char * const * const argv)
{
  gn_wrkr_main ();
  return 0;
}
