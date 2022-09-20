/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/20 11:41:50 by imustafa         ###   ########.fr       */
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
			ft_free(temp);
			temp = ft_strdup("");
			write(1, "> ", 2);
		}
	}
	return (trim_line(line));
}
