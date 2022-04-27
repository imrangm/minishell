/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/04/27 17:08:29 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Using readline library to create shell command-line
** and executing the commands through user input
*/
void pipe_init(t_pipe *p)
{
	p->fcmd = NULL;
	p->prev = NULL;
	p->next = NULL;
}

void print_struct(t_redirs *rd)
{
	if (rd->infile)
		printf("%s", rd->infile);
	if (rd->outfile)
		printf("%s", rd->outfile);
	if (rd->append)
		printf("%s", rd->append);
	if (rd->heredoc)
		printf("%s", rd->heredoc);
}

void process(char *line, t_pipe *p)
{
	char 	**out;
	int		i;

	out = ft_split(line, ' ');
	p->fcmd = ft_strtrim(out[0], " ");
	i = 0;
	while(out[i])
	{
		out[i] = ft_strtrim(out[i], " ");
		if (ft_strncmp(out[i], "<", 1))
		{
			p->rd.infile = out[i + 1];
		}
		else if (ft_strncmp(out[i], ">", 1))
		{
			p->rd.outfile = out[i + 1];
		}
		else if (ft_strncmp(out[i], ">>", 2))
		{
			p->rd.append = out[i + 1];
		}
		else if (ft_strncmp(out[i], "<<", 2))
		{
			p->rd.heredoc = out[i + 1];
		}
		i++;
	}
}


int	main(void)
{
	char	*line;
	t_pipe	*p;

	in_minishell_var(1);
	while (isatty(STDIN_FILENO))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signals);
		line = readline("$> ");
		if (!line)
			break ;
		if (line[0])
		{
			add_history(line);
			// if (preliminary_check(line))
			// {
			// 	if (ft_strchr(line, '|'))
			// 		pipes(line);
			// 	else if (ft_strnstr(line, "<<", ft_strlen(line)))
			// 		here_ops(line);
			// 	else if (ft_strnstr(line, ">>", ft_strlen(line)))
			// 		append(line);
			// 	else if (ft_strchr(line, '<') || ft_strchr(line, '>'))
			// 		file(line);
			// 	else
			// 		execute(line);
			// }
			p = malloc (sizeof(p));
			pipe_init(p);
			process(line, p);
			print_struct(&p->rd);
		}
		in_minishell_var(1);
		free(line);
	}
}
