gcc \
-pipe -g -O3 \
-Wall -Werror -Wextra \
-o gn \
\
-Isrc \
\
-D_GNU_SOURCE \
\
src/comn/main.c \
src/comn/gn_lstnr_cfg_ini.c \
src/comn/gn_lstnr_cfg_lst_ini.c \
src/comn/gn_lstnr_cfg_lst_pop.c \
src/comn/gn_lstnr_cfg_lst_pshb.c \
\
src/mstr/gn_ipc_close.c \
src/mstr/gn_ipc_create.c \
src/mstr/gn_ipc_listen.c \
src/mstr/gn_ipc_path_gen.c \
\
src/mstr/gn_create_lstnr.c \
src/mstr/gn_lstnr_send.c \
src/mstr/gn_lstnrs_send.c \
src/mstr/gn_mstr_cfg_ini.c \
src/mstr/gn_mstr_cfg_load.c \
src/mstr/gn_mstr_main.c \
src/mstr/gn_self_path.c \
src/mstr/gn_send_fd.c \
src/mstr/gn_start_wrkr.c \
src/mstr/gn_start_wrkrs.c \
src/mstr/gn_wrkr_acpt.c \
\
src/wrkr/gn_conn_acpt_thrd.c \
src/wrkr/gn_conn_acpt_thrd_conf_init.c \
src/wrkr/gn_conn_acpt_thrd_conf_list_init.c \
src/wrkr/gn_conn_acpt_thrd_conf_list_push_back.c \
src/wrkr/gn_conn_acpt_thrd_conf_list_remove.c \
\
src/wrkr/gn_conn_mgmt_thrd.c \
src/wrkr/gn_conn_mgmt_thrd_conf_init.c \
src/wrkr/gn_conn_mgmt_thrd_conf_list_init.c \
src/wrkr/gn_conn_mgmt_thrd_conf_list_push_back.c \
src/wrkr/gn_conn_mgmt_thrd_conf_list_remove.c \
\
src/wrkr/gn_conn_ini.c \
src/wrkr/gn_conn_list_init.c \
src/wrkr/gn_conn_list_push_back.c \
\
src/wrkr/gn_new_conn_list_init.c \
src/wrkr/gn_new_conn_list_pop.c \
src/wrkr/gn_new_conn_list_push_back.c \
src/wrkr/gn_new_conn_list_list_init.c \
src/wrkr/gn_new_conn_list_list_push_back.c \
\
src/wrkr/gn_get_new_conns.c \
src/wrkr/gn_lstnrs_recv.c \
src/wrkr/gn_pass_conn.c \
src/wrkr/gn_recv_fd.c \
\
src/wrkr/gn_start_conn_acpt_thrd.c \
src/wrkr/gn_start_conn_acpt_thrds.c \
src/wrkr/gn_start_conn_mgmt_thrd.c \
src/wrkr/gn_start_conn_mgmt_thrds.c \
src/wrkr/gn_stop_conn_acpt_thrds.c \
src/wrkr/gn_stop_conn_mgmt_thrds.c \
\
src/wrkr/gn_wrkr_cfg_ini.c \
src/wrkr/gn_wrkr_main.c \
\
-lpthread
