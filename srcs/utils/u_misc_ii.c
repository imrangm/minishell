/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/21 16:46:17 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_error(t_node *node, t_data *data)
{
	if (node->type == 1)
	{
		check_error(node->left, data);
		check_error(node->right, data);
	}
	else if (node->type == 2)
	{
		ft_putstr_fd(node->value, 2);
		ft_putchar_fd('\n', 2);
		data->last_exit_status = 1;
		data->error = 1;
		return (1);
	}
	return (0);
}

static void	u_read_pipe(char *temp)
{
	ft_free(temp);
	temp = ft_strdup("");
	write(1, "> ", 2);
}

char	*read_pipe(char *line)
{
	char	buf[2];
	char	*temp;

	set_signalset(2);
	temp = strdup("");
	write(1, "> ", 2);
	while (1)
	{
		read(STDIN_FILENO, buf, 1);
		buf[1] = '\0';
		temp = ft_strjoin_and_free(temp, buf);
		if (ft_strchr(temp, '\n'))
		{
			line = ft_strjoin_and_free(line, " ");
			line = ft_strjoin_and_free(line, temp);
			if (!ft_strchr(temp, '|'))
			{
				ft_free(temp);
				break ;
			}
			u_read_pipe(temp);
		}
	}
	return (trim_line(line));
}

void	free_and_exit(char **args, t_cmd *cmd, t_data *data)
{
	ft_free_2d(args);
	free_data(data);
	free_nodes(data->root);
	ft_free(cmd);
	exit(data->last_exit_status);
}
