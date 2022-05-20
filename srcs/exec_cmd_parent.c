/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/20 19:56:35 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_parent_function(char **args)
{
	if (!cmp_str(args[0], "export") && args[1])
		return (1);
	else if (!cmp_str(args[0], "unset"))
		return (1);
	else if (!cmp_str(args[0], "exit"))
		return (1);
	else if (!cmp_str(args[0], "cd"))
		return (1);
	return (0);
}

char	**exec_cmd_parent(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!cmp_str(args[0], "export"))
		b_export(args, data);
	else if (!cmp_str(args[0], "unset"))
		b_unset(args, data);
	else if (!cmp_str(args[0], "exit"))
		b_exit(args, data);
	else if (!cmp_str(args[0], "cd") && args[1])
		b_cd(args, data);
	return (data->envp);
}
