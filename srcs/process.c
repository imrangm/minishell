/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/07 21:27:59 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sym(char **line, char *sym)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if (ft_strncmp(line[i], sym, ft_strlen(line[i])) == 0)
			return (i);
		i++;
	}
	return (0);
}

void set_sym(char **out, t_redirs *rd)
{
	if (find_sym(out, "<<") > find_sym(out, "<"))
		rd->lastin = 'h';
	else
		rd->lastin = 'i';
	if (find_sym(out, ">>") > find_sym(out, ">"))
		rd->lastout = 'a';
	else
		rd->lastout = 'o';
}

int	redir_check(char *input)
{
	int	i;
	
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' || input[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

void	process(char *line, t_redirs *rd)
{
	char	**out;
	char	**redir;
	int		i;
	int		j;
	int		fd;

	out = ft_split(line, ' ');
	i = 0;
	while (out[i] != NULL)
	{
		out[i] = ft_strtrim(out[i], " ");
		// if (redir_check(out[i]) && redir_check(out[i + 1]))
		// {
		// 	ft_putstr_fd("minishell: syntax error\n", 2);
		// 	break ;
		// }
		if (ft_strnstr(out[i], "<<", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], "<<", 2))
				rd->heredoc = out[i + 1];
			else
			{
				redir = ft_split_chars(out[i], "<<");
				rd->heredoc = redir[1];
			}
		}
		else if (ft_strnstr(out[i], "<<", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], "<", 1))
				rd->infile = out[i + 1];
			else
			{
				redir = ft_split(out[i], '<');
				rd->infile = redir[1];
			}
		}
		else if (ft_strnstr(out[i], ">>", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], ">>", 2))
			{
				if (rd->append)
				{
					fd = open(rd->append, O_CREAT, 0644);
					close(fd);
				}
				rd->append = out[i + 1];
			}
			else
			{
				redir = ft_split_chars(out[i], ">>");
				rd->append = redir[1];
			}
		}
		else if (ft_strchr(out[i], '>'))
		{
			if (ft_strncmp(out[i], ">", 1) == 0)
			{
				if (rd->outfile)
				{
					fd = open(rd->outfile, O_CREAT, 0644);
					close(fd);
				}
				rd->outfile = out[i + 1];
			}
			else
			{
				redir = ft_split(out[i], '>');
				j = 1;
				while (redir[j])
				{
					fd = open(redir[j], O_CREAT, 0644);
					close(fd);
					rd->outfile = redir[j];
					j++;
				}
			}
		}
		i++;
	}
	set_sym(out, rd);
}
