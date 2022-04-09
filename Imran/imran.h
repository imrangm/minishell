/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imran.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:39 by imran             #+#    #+#             */
/*   Updated: 2022/04/09 19:38:23 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMRAN_H
# define IMRAN_H

# include "../central.h"
# include <stdio.h>
# include <string.h>

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
void	execute(char *line);

#endif