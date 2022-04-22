/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:43:58 by nmadi             #+#    #+#             */
/*   Updated: 2022/04/22 17:40:06 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signals(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (set_in_minishell_var(-1) == 1)
		rl_redisplay();
}

int	set_in_minishell_var(int is_true)
{
	static int in_minishell;

	if (is_true != -1)
		in_minishell = is_true;
	return (in_minishell);
}
