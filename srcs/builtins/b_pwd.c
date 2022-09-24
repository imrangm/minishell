/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:25:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/24 16:10:59 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	b_pwd(t_data *data)
{
	char	*cwd;
	char	*pwd;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	data->last_exit_status = 0;
	if (!pwd)
	{
		pwd = get_env_value("PWD", data);
		if (!pwd)
			pwd = get_env_value("OLDPWD", data);
		printf("%s\n", pwd);
		ft_free(pwd);
		return (0);
	}
	printf("%s\n", pwd);
	ft_free(pwd);
	ft_free(cwd);
	return (0);
}
