track_fds="yes"
trace_children="yes"
track_origins="yes"
shell="./minishell"
leak= #--leak-check=full --track-origins=yes --trace-children=yes --show-leak-kinds=all
valgrind $leak --track-fds=$track_fds --suppressions=r.supp $shell
