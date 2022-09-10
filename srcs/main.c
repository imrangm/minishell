/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:25:02 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/09 21:02:54 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	end_pipe(char **line)
{
	char	*tmp;

	tmp = ft_strtrim((*line), " ");
	if ((*line)[ft_strlen(tmp) - 1] == '|')
		line_update(line);
	ft_free(tmp);
}

char	*trim_line(char *line)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i])
		trimmed = ft_substr(line, i, (ft_strlen(line) - i) + 1);
	return (trimmed);
}

void	minishell(t_data *data)
{
	char	*line;

	while (isatty(STDIN_FILENO))
	{
		set_signalset(0);
		line = readline("$> ");
		if (!line)
		{
			free_data(data);
			break ;
		}
		if (check_space(line))
			continue ;
		if (line[0])
		{
			end_pipe(&line);
			add_history(line);
			data->line = trim_line(line);
			if (pc_valid(data->line, data))
				parse(data);
		}
		ft_free(data->line);
		ft_free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.last_exit_status = 0;
	init_envp(envp, &data);
	minishell(&data);
}
