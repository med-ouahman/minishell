#!/bin/bash

track_fds="yes"
trace_children="yes"
track_origins="yes"
dir=$HOME"/Desktop/minishell"

valgrind --leak-check=no --track-origins=yes --trace-children=yes --track-fds=$track_fds --suppressions=./r.supp bash