/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_includes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:13:53 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/22 00:17:41 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_INCLUDES_H
# define ALL_INCLUDES_H

//? printf, readline, rl_*, & add_history, strerror, perror
#include <stdio.h>

//? printf, readline, rl_*, & add_history
#include <readline/readline.h>
#include <readline/history.h>

//? malloc, free, exit, getenv
#include <stdlib.h>

//? write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
#include <unistd.h>

//? open
#include <fcntl.h>

//? wait, waitpid, wait3, wait4
#include <sys/wait.h>

//? wait3, wait4
#include <sys/time.h>
#include <sys/resource.h>

//? signal, sigaction, sigemptyset, sigaddset, kill
#include <signal.h>

//? stat, lstat, fstat
#include <sys/stat.h>

//? readdir, opendir, closedir
#include <dirent.h>
#include <sys/types.h>

//? ioctl
#include <sys/ioctl.h>

//? tcsetattr, tcgetattr
#include <termios.h>

//? tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <curses.h>
#include <term.h>

#endif