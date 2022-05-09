/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/09 16:42:49 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redir(char *input)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			c++;
		i++;
	}
	return (c);
}

/*
** work in progress
*/ 

// void	assign_sym(char *sym, t_redirs *rd)
// {
// 	if (sym == "<<")
// 		rd->lastin = 'h';
// 	else if (sym == "<")
// 		rd->lastin = 'i';
// 	if (sym == ">>")
// 		rd->lastout = 'a';
// 	else if (sym == "<")
// 		rd->lastout = 'o';
// }

// void	assign(char **out, t_redirs *rd, char *sym, int *i)
// {
// 	char	**redir;

// 	if (ft_strnstr(out[*i], sym, ft_strlen(out[*i])))
// 	{
// 		if (ft_strlen(out[*i]) == ft_strlen(sym))
// 		{
// 			// check_syntax(out[i + 1]);
// 			rd->heredoc = out[*i + 1];
// 		}
// 		else if (count_redir(out[*i]) == 2)
// 		{
// 			out[*i] = ft_strtrim(out[*i], "<>");
// 			printf("2: %s\n", out[*i]);
// 			rd->heredoc = out[*i];
// 		}
// 		else
// 		{
// 			redir = ft_split_chars(out[*i], sym);
// 			// check_syntax(redir[1]);
// 			rd->heredoc = redir[1];
// 		}

// 		assign_sym(sym, rd);
// 		// printf("s: %s\n", rd->heredoc);
// 	}
// }

void	check(char **out, t_redirs *rd)
{
	int		i;
	int		j;
	char	**redir;
	int		fd;

	i = 0;
	rd->lastin = 0;
	rd->lastout = 0;
	while (out[i] != NULL)
	{
		out[i] = ft_strtrim(out[i], " ");
		printf("out(%d): %s\n", i, out[i]);
		if (ft_strnstr(out[i], "<<", ft_strlen(out[i])))
		{
			if (ft_strlen(out[i]) == 2)
			{
				rd->heredoc = out[i + 1];
			}
			else if (count_redir(out[i]) == 2)
			{
				out[i] = ft_strtrim(out[i], "<>");
				printf("2: %s\n", out[i]);
				rd->heredoc = out[i];
			}
			else
			{
				redir = ft_split(out[i], '<');
				j = 0;
				while (redir[j + 1])
				{
					printf("rd: %s\n", redir[j]);
					read_line(redir[j]);
					j++;
				}
				rd->heredoc = redir[j];
			}
			printf("h: %s\n", rd->heredoc);
			rd->lastin = 'h';
		}
		else if (ft_strnstr(out[i], "<", ft_strlen(out[i])))
		{
			if (ft_strlen(out[i]) == 1)
			{
				printf("1: %s\n", out[i + 1]);
				rd->infile = out[i + 1];
			}
			else if (count_redir(out[i]) == 1)
			{
				out[i] = ft_strtrim(out[i], "<>");
				printf("2: %s\n", out[i]);
				rd->infile = out[i];
			}
			else
			{
				redir = ft_split(out[i], '<');
				j = 0;
				while (redir[j + 1])
				{
					printf("3: %s\n", redir[j]);
					j++;
				}	
				rd->infile = redir[j];
			}
			printf("i: %s\n", rd->infile);
			rd->lastin = 'i';
		}
		else if (ft_strnstr(out[i], ">>", ft_strlen(out[i])))
		{
			if (rd->append)
			{
				fd = open(rd->append, O_CREAT | O_TRUNC, 0644);
				close(fd);
			}
			if (ft_strlen(out[i]) == 2)
			{
				printf("1: %s\n", out[i]);
				rd->append = out[i + 1];
			}
			else if (count_redir(out[i]) == 2)
			{
				out[i] = ft_strtrim(out[i], "<>");
				printf("2: %s\n", out[i]);
				rd->append = out[i];
			}
			else
			{
				out[i] = ft_strtrim(out[i], "<>");
				redir = ft_split(out[i], '>');
				j = 0;
				while (redir[j + 1])
				{
					fd = open(redir[j], O_CREAT | O_TRUNC, 0644);
					close(fd);
					j++;
				}	
				rd->append = redir[j];
			}
			printf("a: %s\n", rd->append);
			rd->lastout = 'a';
		}
		else if (ft_strnstr(out[i], ">", ft_strlen(out[i])))
		{
			if (rd->outfile)
			{
				fd = open(rd->outfile, O_CREAT | O_TRUNC, 0644);
				close(fd);
			}
			if (ft_strlen(out[i]) == 1)
			{
				rd->outfile = out[i + 1];
				printf("1: %s\n", out[i + 1]);
			}
			else if (count_redir(out[i]) == 1)
			{
				out[i] = ft_strtrim(out[i], "<>");
				printf("2: %s\n", out[i]);
				rd->outfile = out[i];
			}
			else
			{
				out[i] = ft_strtrim(out[i], "<>");
				redir = ft_split(out[i], '>');
				j = 0;
				while (redir[j + 1])
				{
					fd = open(redir[j], O_CREAT | O_TRUNC, 0644);
					printf("3: %s\n", redir[j]);
					close(fd);
					j++;
				}
				rd->outfile = redir[j];
			}
			printf("o: %s\n", rd->outfile);
			rd->lastout = 'o';
		}
		i++;
	}
}

void	process(char *line, t_redirs *rd)
{
	char	**out;

	out = ft_split(line, ' ');
	check(out, rd);
	printf("lastin: %c\n", rd->lastin);
	printf("lastout: %c\n", rd->lastout);
}
