gcc \
-pipe -g -O3 \
-Wall -Werror -Wextra \
-o gn \
\
-Isrc \
\
src/main.c \
src/wrkr/gn_conn_mgmt_thrd.c \
src/wrkr/gn_start_conn_mgmt_thrds.c \
src/wrkr/gn_wrkr_main.c \
\
-lpthread
