/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:21:28 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/12 14:57:07 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_env_var_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		i++;
	else
	{
		free(str);
		return (0);
	}
	if (ft_isalpha(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			free(str);
			return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

int	ft_2d_arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**expand_envs(char **str, char **envp)
{
	int		i;
	int		str_size;
	char	**expanded_str;
	char	*dollarless_var_name;

	i = 0;
	str_size = ft_2d_arr_len(str);
	expanded_str = (char **) malloc(sizeof(char *) * (str_size + 1));
	dollarless_var_name = NULL;
	while (i < str_size)
	{
		if (is_env_var_syntax(str[i]))
		{
			dollarless_var_name = ft_substr(str[i], 1, ft_strlen(str[i]));
			if (env_exists(dollarless_var_name, envp))
				expanded_str[i] = get_env_value(dollarless_var_name, envp);
			free(dollarless_var_name);
		}
		else if (i < str_size)
			expanded_str[i] = ft_strdup(str[i]);
		i++;
	}
	expanded_str[i] = 0;
	return (expanded_str);
}
