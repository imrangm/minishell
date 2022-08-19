/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_misc_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:32:49 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/19 16:07:42 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd_oldpwd(char *old_pwd, int rv, t_data *data)
{
	char	*pwd;

	if (rv)
		return ;
	pwd = getcwd(NULL, 0);
	ft_free(data->pwd);
	ft_free(data->old_pwd);
	data->pwd = ft_strdup(pwd);
	data->old_pwd = ft_strdup(old_pwd);
	modify_env(ft_strdup("PWD"), data->pwd, data);
	modify_env(ft_strdup("OLDPWD"), data->old_pwd, data);
	ft_free(pwd);
}

char	*line_update(void)
{
	char	buf[2];
	char	*line;
	char	*final;

	line = ft_strdup("");
	final = line;
	write(1, "> ", 2);
	while (1)
	{
		read(0, buf, 1);
		buf[1] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(line, '\n'))
		{
			if (!ft_strchr(line, '|'))
				break ;
			write(1, "> ", 2);
			final = ft_strjoin_and_free(final, ft_strtrim(line, "\n"));
			free(line);
			line = strdup("");
		}
	}
	final = ft_strjoin_and_free(final, ft_strtrim(line, "\n"));
	free(line);
	return (final);
}
