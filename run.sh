valgrind --leak-check=full --track-origins=yes --trace-children=yes --show-leak-kinds=all --suppressions=r.supp ./minishell
# valgrind --track-fds=yes --trace-children=yes ./minishell