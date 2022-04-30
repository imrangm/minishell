/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:25:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/30 19:31:33 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_pwd(void)
{
	char	*cwd;
	char	*pwd;

	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	if (pwd)
		free(pwd);
	if (cwd)
		free(cwd);
	return (0);
}
