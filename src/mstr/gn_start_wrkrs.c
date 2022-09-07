void
gn_start_wrkrs (char * const self_path)
{
  for (uint8_t i = 0; i < 2; i++) {
    gn_start_wrkr (self_path);
  }
}
