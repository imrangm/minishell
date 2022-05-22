/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:25:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/22 15:34:54 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_pwd(t_data *data)
{
	char	*cwd;
	char	*pwd;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	printf("pwd = %p\ncwd = %p\n", &pwd, &cwd);
	data->last_exit_status = 0;
	if (!pwd)
	{
		pwd = get_env_value("PWD", data->envp);
		if (!pwd)
			pwd = get_env_value("OLDPWD", data->envp);
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	free(cwd);
	return (0);
}
