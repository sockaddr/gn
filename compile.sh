gcc \
-pipe -g -O3 \
-Wall -Werror -Wextra \
-o gn \
\
-Isrc \
\
src/main.c \
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
src/wrkr/gn_start_conn_acpt_thrds.c \
src/wrkr/gn_start_conn_mgmt_thrds.c \
src/wrkr/gn_stop_conn_acpt_thrds.c \
src/wrkr/gn_stop_conn_mgmt_thrds.c \
\
src/wrkr/gn_wrkr_main.c \
\
-lpthread
