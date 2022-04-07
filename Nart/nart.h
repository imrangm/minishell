/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:53:43 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/07 18:17:16 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NART_H
# define NART_H
# include "../central.h"
# include "libft/libft.h"

void	minishell(void);
void	interpret(char *str);
char	**parse(char *str);

#endif