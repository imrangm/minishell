/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:43:58 by nmadi             #+#    #+#             */
/*   Updated: 2022/09/09 18:23:27 by imustafa         ###   ########.fr       */
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

void	signal_handler_iii(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	write(1, "> ", 2);
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
	else if (sigmode == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &signal_handler_iii);
	}
}
