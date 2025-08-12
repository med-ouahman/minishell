#!/bin/bash

track_fds="yes"
trace_children="yes"
track_origins="yes"
dir=$HOME"/Desktop/minishell"

valgrind --leak-check=full --track-origins=yes --trace-children=yes --show-leak-kinds=all --track-fds=$track_fds --suppressions=$dir/r.supp $dir/minishell