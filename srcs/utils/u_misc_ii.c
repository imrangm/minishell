/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/16 16:39:49 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd_oldpwd(char *old_pwd, int rv, t_data *data)
{
	char	*pwd;

	if (rv)
		return ;
	pwd = getcwd(NULL, 0);
	safe_free(data->pwd);
	safe_free(data->old_pwd);
	data->pwd = ft_strdup(pwd);
	data->old_pwd = ft_strdup(old_pwd);
	modify_env(ft_strdup("PWD"), data->pwd, data);
	modify_env(ft_strdup("OLDPWD"), data->old_pwd, data);
	safe_free(pwd);
}
