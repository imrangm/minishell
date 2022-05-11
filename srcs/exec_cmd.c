/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/11 16:22:13 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(char **args, t_data *data)
{
	if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
		exit(0);
	else if (!ft_strncmp(args[0], "echo", ft_strlen(args[0])))
		b_echo(args);
	else if (!ft_strncmp(args[0], "cd", ft_strlen(args[0])))
		b_cd(args[1]);
	else if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
		b_pwd();
	else if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
		add_env(args[1], args[2], data->envp); //? export
	else if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
		unset_env(args[1], data->envp); //? unset
	else if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
		b_env(data->envp); //? env
	else if (execve(cmd_path(args[0], data), args, data->envp) == -1)
		return (-1);
	return (0);
}