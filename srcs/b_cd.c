/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:09 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/30 19:57:28 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	if (new_path[0] == '/' || new_path[0] == '.')
	{
		chdir(new_path);
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		return (0);
	}
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (1);
	joined = join_paths(pwd, new_path);
	chdir(joined);
	printf("%s\n", joined);
	free(joined);
	free(pwd);
	free(cwd);
	return (0);
}
