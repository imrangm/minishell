/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pe_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:40:12 by nmadi             #+#    #+#             */
/*   Updated: 2022/07/08 13:39:15 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static char	*get_expanded(char *element)
// {
// 	int	i;
// 	int	q;

// 	i = 0;
// 	q = 0;
// 	while (element[i])
// 	{
// 		if (ft_isquote(element[i]) && !q)
// 			q = element[i];
// 		else if (q && element[i] == q)
// 			q = 0;
// 		else if (element[i] == '$' && (!q || q == DQUOTE))
// 		{
// 			if (element[i + 1]
// 				&& (ft_isalpha(element[i + 1])
// 				|| element[i + 1] == '_'
// 				|| element[i] == '?'))
// 			{

// 			}
// 		}
// 		i++;
// 	}
// }

// int	is_env(char *line, int *i, t_data *data)
// {
// 	int		oi;
// 	int		start;
// 	char	*env_var;

// 	start = 0;
// 	oi = *i;
// 	if (line[*i] == '$' && line[*i + 1] && !ft_isspace(line[*i + 1]))
// 	{
// 		start = *i + 1;
// 		while (line[*i] && !ft_isspace(line[*i]))
// 			(*i)++;
// 		env_var = ft_substr(line, start, (*i + 1) - start);
// 		printf("env_var = %s\n", env_var);
// 		if (env_exists(env_var, data))
// 			return (ft_strlen(get_env_value(env_var, data)));
// 		else
// 		{
// 			*i = oi;
// 			return (0);
// 		}
// 	}
// 	*i = oi;
// 	return (0);
// }

// int	get_expanded_line_size(char *line, t_data *data)
// {
// 	int	i;
// 	int	q;
// 	int	c;

// 	i = 0;
// 	q = 0;
// 	c = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]) && !q)
// 			q = line[i];
// 		else if (line[i] == q)
// 			q = 0;
// 		else if (!q)
// 		{
// 			if (is_env(line, &i, data))
// 		}
// 	}
// 	return (i);
// }

// char	*expand_line(char *line, t_data *data)
// {
// 	int		i;
// 	int		count;
// 	char	*expanded_line;

// 	i = 0;
// 	count = get_expanded_line_size(line, data);
// 	expanded_line = malloc(sizeof(char) * count + 1);
// 	while (line[i])
// 	{
// 		if (is_env(line, &i, data))
// 		{

// 		}
// 		else
// 			printf("2");
// 		i++;
// 	}
// 	expanded_line[i] = '\0';
// 	return (expanded_line);
// }