/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:27:32 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/20 14:03:52 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_readline(char *lim)
{
	char	*text;

	text = read_line(lim);
	free(text);
}

int	check_io(char *prev, char *current)
{
	return ((prev[0] == GREAT && current[0] == LESS)
		|| (prev[0] == LESS && current[0] == GREAT));
}

char	op_type(char *op)
{
	int	len;

	len = ft_strlen(op);
	if (len == 2 && op[0] == LESS)
		return (DLESS);
	else if (len == 2 && op[0] == GREAT)
		return (DGREAT);
	else if (len == 1 && op[0] == LESS)
		return (LESS);
	else if (len == 1 && op[0] == GREAT)
		return (GREAT);
	return (0);
}

void	free_redirs(t_redircmd *redir)
{
	t_data	*data;

	data = redir->data;
	ft_free(redir);
	free_data(data);
	free_nodes(data->root);
	exit(data->last_exit_status);
}
