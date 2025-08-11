shell="${1:-./minishell}"
valgrind --trace-children=yes --leak-check=no --track-fds=yes $shell