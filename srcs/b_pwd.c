/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:25:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/20 13:23:15 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_pwd(t_data *data)
{
	char	*cwd;
	char	*pwd;

	cwd = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
	{
		data->last_exit_status = 1;
		return (1);
	}
	printf("%s\n", pwd);
	if (pwd) //! Double-check if necessary
		free(pwd);
	if (cwd) //! Double-check if necessary
		free(cwd);
	return (0);
}
