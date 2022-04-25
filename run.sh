#!/bin/bash

valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline ./minishell