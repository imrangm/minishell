/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 18:01:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd_child(char **args, t_data *data)
{
	if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
	{
		b_echo(args, data);
		kill(getpid(), 9);
	}
	else if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
	{
		b_pwd();
		kill(getpid(), 9);
	}
	else if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
	{
		b_env(data->envp);
		kill(getpid(), 9);
	}
	else if (execve(cmd_path(args[0], data), args, data->envp) == -1)
		return (-1);
	//! Add an if-statement here that checks if the first command
	//! is the minishell exec so that I increment SHLVL then pass the envp to the execve
	// else if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
	// 	printf("Entered export from the wrong place.\n");
	// else if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
	// 	printf("Entered unset from the wrong place.\n");
	// else if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
	// 	printf("Entered env from the wrong place.\n");
	return (0);
}