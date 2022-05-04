/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/04 20:17:26 by imustafa         ###   ########.fr       */
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

void	sym_check(char *line, t_redirs *rd)
{
	if (rd->heredoc)
		here_ops(line, rd);
	else if (rd->infile || rd->outfile || rd->append)
		file(line, rd);
}

void	process(char *line, t_redirs *rd)
{
	char 	**out;
	char	**redir;
	int		i;
	int		fd;

	out = ft_split(line, ' ');
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
				redir = chars_split(out[i], ">>");
				rd->append = redir[1];
			}
			// printf("%s\n", rd->append);
		}
		else if (ft_strnstr(out[i], ">", ft_strlen(out[i])))
		{
			if (!ft_strncmp(out[i], ">", 1))
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
				rd->outfile = redir[1];
			}
			// printf("%s\n", rd->outfile);
		}
		i++;
	}
}

char	*cmd_copy(char *input)
{
	int		i;
	char	*copy;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '<' || input[i] == '>')
			break;
		i++;
	}
	copy = ft_substr(input, 0, i);
	return (copy);
}

void	split_pipe(char *line)
{
	char	**cmd;
	t_pipe	**p;
	int		i;
	int		c;

	i = 0;
	
	c = count_pipes(line) + 1;
	p = malloc(sizeof(t_pipe *) * c);
	i = 0;
	cmd = ft_split(line, '|');
	while (cmd[i])
	{
		cmd[i] = ft_strtrim(cmd[i], " ");
		p[i] = malloc(sizeof(t_pipe));
		process(cmd[i], &p[i]->rd);
		p[i]->fcmd = cmd_copy(cmd[i]);
		// printf("%d: %s\n", i, p[i]->fcmd);
		i++;
	}
	pipes(line, p);
}

void	split_rd(char *line)
{
	t_redirs	*rd;
	char		*cmd;

	rd = malloc(sizeof(t_redirs));
	line = ft_strtrim(line, " ");
	cmd = cmd_copy("line");
	process(line, rd);
	sym_check(cmd, rd);
}