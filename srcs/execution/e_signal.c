/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:43:58 by nmadi             #+#    #+#             */
/*   Updated: 2022/06/14 20:41:53 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signals_main(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals_else(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_signalset(int sigmode)
{
	if (sigmode == 0) // Default Minishell loop signal set.
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signals_main);
	}
	else if (sigmode == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, &handle_signals_else);
	}
}