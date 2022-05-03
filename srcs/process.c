/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/03 20:13:35 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sym(char **line, char *sym)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if (ft_strnstr(line[i], sym, ft_strlen(line[i])))
			return (i);
		i++;
	}
	return (0);
}

void	sym_check(t_pipe *p)
{
	if (preliminary_check(p->fcmd))
	{
		// if (ft_strchr(fcmd, '|'))
		// 	pipes(line);
		if (p->rd.heredoc)
			here_ops(p);
		else if (p->rd.infile || p->rd.outfile)
			file(p);
		else if (p->rd.append)
			append(p);
		else
			execute(p->fcmd);
	}
}

void	process(char *fcmd, t_redirs *rd)
{
	char 	**out;
	char	**redir;
	int		i;

	out = ft_split(fcmd, ' ');
	i = 0;
	while (out[i] != NULL)
	{
		out[i] = ft_strtrim(out[i], " ");
		if (ft_strnstr(out[i], "<<", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], "<<", 2))
				rd->heredoc = out[i + 1];
			else
			{
				redir = chars_split(out[i], "<<");
				rd->heredoc = redir[1];
			}
			// printf("%s\n", rd->heredoc);
		}
		else if (ft_strchr(out[i], '<'))
		{
			if (!ft_strncmp(out[i], "<", 1))
				rd->infile = out[i + 1];
			else
			{
				redir = ft_split(out[i], '<');
				rd->infile = redir[1];
			}
			// printf("%s\n", rd->infile);
		}
		else if (ft_strnstr(out[i], ">>", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], ">>", 2))
				rd->append = out[i + 1];
			else
			{
				redir = chars_split(out[i], ">>");
				rd->append = redir[1];
			}
			// printf("%s\n", rd->append);
		}
		else if (ft_strnstr(out[i], ">", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], ">", 1))
				rd->outfile = out[i + 1];
			else
			{
				redir = ft_split(out[i], '>');
				rd->outfile = redir[1];
			}
			// printf("%s\n", rd->outfile);
		}
		i++;
	}
}

void	split_pipe(char *line)
{
	char	**cmd;
	char	*fcmd;
	t_pipe	**p;
	int		i;
	int		c;

	i = 0;
	if (ft_strchr(line, '|') || ft_strchr(line, '<') || ft_strchr(line, '>'))
	{
		c = count_pipes(line) + 1;
		p = malloc(sizeof(t_pipe *) * c);
		i = 0;
		cmd = ft_split(line, '|');
		while (cmd[i])
		{
			fcmd = ft_strtrim(cmd[i], " ");
			p[i] = malloc(sizeof(t_pipe));
			p[i]->fcmd = fcmd;
			// printf("%d: %s\n", i, p[i]->fcmd);
			process(fcmd, &p[i]->rd);
			sym_check(p[i]);
			i++;	
		}
	}
	else
	{
		//only one pipe structure with following struct as null
		execute(line);
	}
}