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
src/wrkr/gn_conn_init.c \
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
src/wrkr/gn_pass_conn.c \
\
src/wrkr/gn_start_conn_acpt_thrd.c \
src/wrkr/gn_start_conn_acpt_thrds.c \
src/wrkr/gn_start_conn_mgmt_thrd.c \
src/wrkr/gn_start_conn_mgmt_thrds.c \
src/wrkr/gn_stop_conn_acpt_thrds.c \
src/wrkr/gn_stop_conn_mgmt_thrds.c \
\
src/wrkr/gn_wrkr_conf_init.c \
\
src/wrkr/gn_wrkr_main.c \
\
-lpthread
