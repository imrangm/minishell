/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/05/08 21:24:58 by imustafa         ###   ########.fr       */
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

int	check_syntax(char *file)
{
	file = ft_strtrim(file, " ");
	if (ft_strncmp(file, ">", 1) == 0 || ft_strncmp(file, "<", 1) == 0)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (1);
	}
	return (0);
}

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

void	check_redir(char *input)
{
	char	**ln1;
	char	**ln2;
	int		i;

	ln1 = ft_split(input, ' ');
	i = 0;
	while (ln1[i])
	{
		ln1[i] = ft_strtrim(ln1[i], " ");
		printf("%d: %s\n", i, ln1[i]);
		i++;
	}
	input = rm_redir(input);
	// input = ft_strtrim(input, " ");
	// printf("input: %s\n", input);
	ln2 = ft_split(input, ' ');
	i = 0;
	while (ln2[i] != NULL)
	{
		ln2[i] = ft_strtrim(ln2[i], " ");
		printf("%d: %s\n", i, ln2[i]);
		i++;
	}
}

void	process(char *line, t_redirs *rd)
{
	char	**out;
	char	**redir;
	int		i;
	int		j;
	int		len;
	int		fd;

	// check_redir(ln);
	out = ft_split(line, ' ');
	i = 0;
	while (out[i] != NULL)
		i++;
	len = ft_strlen(out[i - 1]);
	if (out[i - 1][len - 1] == '>' || out[i - 1][len - 1] == '<')
	{
		ft_putstr_fd("syntax error", 2);
		exit(2);
	}
	i = 0;
	while (out[i] != NULL)
	{
		out[i] = ft_strtrim(out[i], " ");
		printf("out(%d): %s\n", i, out[i]);
		if (ft_strnstr(out[i], "<<", ft_strlen(out[i])))
		{
			if (ft_strlen(out[i]) == 2)
			{
				// check_syntax(out[i + 1]);
				rd->heredoc = out[i + 1];
			}
			else if (count_redir(out[i]) == 2)
			{
				out[i] = ft_strtrim(out[i], "<");
				printf("2: %s\n", out[i]);
				rd->heredoc = out[i];
			}
			else
			{
				redir = ft_split_chars(out[i], "<<");
				// check_syntax(redir[1]);
				rd->heredoc = redir[1];
			}
			printf("h: %s\n", rd->heredoc);
			rd->lastin = 'h';
		}
		else if (ft_strnstr(out[i], "<", ft_strlen(out[i])))
		{
			if (ft_strlen(out[i]) == 1)
			{
				// check_syntax(out[i + 1]);
				printf("1: %s\n", out[i + 1]);
				rd->infile = out[i + 1];
			}
			else if (count_redir(out[i]) == 1)
			{
				out[i] = ft_strtrim(out[i], "<");
				printf("2: %s\n", out[i]);
				rd->infile = out[i];
			}
			else
			{
				redir = ft_split(out[i], '<');
				// check_syntax(redir[1]);
				j = 0;
				while (redir[j])
				{
					printf("3: %s\n", redir[j]);
					j++;
				}	
				rd->infile = redir[j - 1];
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
				out[i] = ft_strtrim(out[i], ">");
				printf("2: %s\n", out[i]);
				rd->append = out[i];
			}
			else
			{
				out[i] = ft_strtrim(out[i], ">");
				redir = ft_split_chars(out[i], ">>");
				j = 0;
				while (redir[j])
				{
					fd = open(redir[j], O_CREAT | O_TRUNC, 0644);
					close(fd);
					j++;
				}	
				rd->append = redir[j - 1];
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
				// if (!check_syntax(out[i + 1]))
				// 	break ;
				rd->outfile = out[i + 1];
				printf("1: %s\n", out[i + 1]);
			}
			else if (count_redir(out[i]) == 1)
			{
				out[i] = ft_strtrim(out[i], ">");
				printf("2: %s\n", out[i]);
				rd->outfile = out[i];
			}
			else
			{
				out[i] = ft_strtrim(out[i], ">");
				redir = ft_split(out[i], '>');
				j = 0;
				while (redir[j])
				{
					fd = open(redir[j], O_CREAT | O_TRUNC, 0644);
					printf("3: %s\n", redir[j]);
					close(fd);
					j++;
				}
				rd->outfile = redir[j - 1];
			}
			printf("o: %s\n", rd->outfile);
			rd->lastout = 'o';
		}
		i++;
	}
	// set_sym(out, rd);
	printf("lastin: %c\n", rd->lastin);
	printf("lastout: %c\n", rd->lastout);
}
