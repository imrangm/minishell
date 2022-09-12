/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:02:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/12 11:03:22 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_token(t_token *tokens)
{
	tokens->type = 0;
	tokens->value = NULL;
	tokens->iter = 0;
	tokens->cur = 0;
	tokens->count = 0;
	tokens->quote = 0;
	tokens->space = 0;
}
