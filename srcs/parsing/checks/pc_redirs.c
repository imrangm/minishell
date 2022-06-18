/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:40:44 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/18 18:57:38 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

static int	handle_single(char *str, int i)
{
	if ((str[i] == '>' && (str[i + 1] == '<' || str[i + 1] == '|'))
		|| (str[i] == '<' && (str[i + 1] == '>' || str[i + 1] == '|'))
		|| (str[i] == '>' && (str[i + 1] == '>' || str[i + 1] == '|'))
		|| (str[i] == '<' && (str[i + 1] == '<' || str[i + 1] == '|'))
		|| (str[i] == '>' && (str[i + 1] == '<' || str[i + 1] == '|'))
		|| (str[i] == '|' && (str[i + 1] == '>' || str[i + 1] == '<'))
		|| (str[i] == '|' && str [i + 1] == '|'))
	{
		ft_putstr_fd("Error: Invalid syntax.\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_double(char *str, int i)
{
	if (((str[i] == '>' && str[i + 1] == '>' && (str[i + 2] == '|'
					|| str[i + 2] == '<' || str[i + 2] == '>')))
		|| (str[i] == '>' && str[i + 1] == '>'
			&& (str[i + 2] == '|' || str[i + 2] == '<'
				|| str[i + 2] == '>')))
	{
		ft_putstr_fd("Error: Invalid syntax.\n", 2);
		return (1);
	}
	return (0);
}

int	pc_redirs(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (i < j)
	{
		if (i + 1 < j)
		{
			if (handle_single(str, i))
				return (1);
		}
		if (i + 2 < j)
		{
			if (handle_double(str, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	pc_redir(char *line)
{
	int		i;
	char	**out;

	i = 0;
	out = split_rd(line);
	while (out[i + 1])
	{
		if ((ft_strchr(out[i], '<') || (ft_strchr(out[i], '>')))
			&& (check_space(out[i + 1]) || ft_strchr(out[i + 1], '|')))
		{
			free_2d(out);
			return (error("Error: Invalid redirection syntax\n"));
		}
		if (ft_countoccurance(out[i], '>', '<') > 2)
		{
			free_2d(out);
			return (error("Error: Invalid redirection syntax\n"));
		}
		i++;
	}
	free_2d(out);
	return (0);
}
