/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:19:31 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/10 02:49:32 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* Proprietary get_env()
*/
char	*get_env_value(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], ft_strlen(str))
			&& envp[i][ft_strlen(str)] == '=')
			return(ft_substr(ft_strchr(envp[i], '='), 1, ft_strlen(ft_strchr(envp[i], '='))));
		i++;
	}
	return (NULL);
}

/*
* Returns 1 if env exists; otherwise returns 0.
*/
int	env_exists(char *var_name, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name))
			&& envp[i][ft_strlen(var_name)] == '=')
			return(1);
		i++;
	}
	return (0);
}

// char	*append_env(char *var_name, char *value, char **envp)
// {
// 	;
// }

// char	*modify_env(char *value, char **envp)
// {
// 	;
// }

//! For testing purposes
// int	main(int argc, char **argv, char **envp)
// {
// 	printf("%s\n", get_env_value("USERR", envp));
// 	printf("%d\n", env_exists("USERR", envp));
// }
