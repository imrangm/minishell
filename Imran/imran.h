/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imran.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imran <imran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:32:39 by imran             #+#    #+#             */
/*   Updated: 2022/04/10 11:58:12 by imran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMRAN_H
# define IMRAN_H

# include "../central.h"
# include "libft/libft.h"
# include <stdio.h>
# include <string.h>

char	*find_exec(char *prg, char	**paths);
char	*cmd_path(char	*cmd);
void	ft_free_arg(char **arr);
void	execute(char *line);

#endif