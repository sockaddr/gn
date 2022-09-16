#ifndef GN_MSTR_MAIN_H
#define GN_MSTR_MAIN_H

#include <comn/hdr/gn_lstnr_conf_list_s.h>
#include <mstr/hdr/gn_mstr_conf_s.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void   gn_create_lstnr (gn_lstnr_conf_list_s * const, const char * const, const uint16_t);
void   gn_lstnr_conf_list_init (gn_lstnr_conf_list_s * const);
void   gn_mstr_conf_init (gn_mstr_conf_s * const);
char * gn_self_path (uint8_t * const);
void   gn_start_wrkrs (gn_mstr_conf_s * const);

#endif // GN_MSTR_MAIN_H
