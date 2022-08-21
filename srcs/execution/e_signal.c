/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:43:58 by nmadi             #+#    #+#             */
/*   Updated: 2022/08/21 16:32:40 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_ii(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

//* Default Minishell loop signal set is 0.
void	set_signalset(int sigmode)
{
	if (sigmode == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &signal_handler);
	}
	else if (sigmode == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, &signal_handler_ii);
	}
}
