#!/bin/bash

track_fds="yes"
trace_children="yes"
track_origins="yes"
dir=$HOME"/Desktop/minishell"

arg=$1

if [ -z $arg ]
then
    arg="leak"
fi

if [ $arg = "fds" ]
then
    valgrind --leak-check=no --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=$dir/r.supp $dir/minishell
else
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=$dir/r.supp $dir/minishell
fi