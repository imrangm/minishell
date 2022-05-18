/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:34:16 by nmadi             #+#    #+#             */
/*   Updated: 2022/05/18 13:37:21 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*join_paths(char *cwd, char *np)
{
	int		i;
	int		j;
	char	*a;

	a = (char *) malloc ((ft_strlen(cwd) + ft_strlen(np) + 2) * sizeof(char));
	i = 0;
	j = 0;
	if (a == NULL)
		return (NULL);
	while (cwd[i] != '\0')
	{
		a[i] = cwd[i];
		i++;
	}
	a[i] = '/';
	i++;
	while (np[j] != '\0')
		a[i++] = np[j++];
	a[i] = '\0';
	return (a);
}

int	b_cd(char *new_path)
{
	char	*cwd;
	char	*pwd;
	char	*joined;

	cwd = NULL;
	if (new_path[0] == '/' || new_path[0] == '.')
	{
		if (chdir(new_path) == -1)
		{
			//! Print error here
			//! Set last_exit_status to 1
			return (1);
		}
		//! Set last_exit_status to 0
		return (0);
	}
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (1);
	if (pwd[0] == '/' && !pwd[2])
		joined = ft_strjoin(pwd, new_path);
	else
		joined = join_paths(pwd, new_path);
	if (chdir(joined) == -1)
	{
		//! Print error here
		//! Set last_exit_status to 1
		free(joined);
		free(pwd);
		free(cwd);
		return (1);
	}
	free(joined);
	free(pwd);
	free(cwd);
	//! Set last_exit_status to 0
	return (0);
}
