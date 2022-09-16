/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:19:06 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/15 18:20:25 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_tok(t_exp *exp, t_token *token)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*final;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(token->value)
		+ ft_strlen(exp->value) - (exp->end - exp->start);
	final = malloc(sizeof(char) * len);
	while (i < (size_t) exp->start)
	{
		final[i] = token->value[i];
		i++;
	}
	while (j < ft_strlen(exp->value))
		final[i++] = exp->value[j++];
	k = exp->end + 1;
	while (k < ft_strlen(token->value))
		final[i++] = token->value[k++];
	final[i] = '\0';
	ft_free(token->value);
	token->value = final;
}

void	expander(t_token *tok, t_exp *exp, t_data *data)
{
	char	*param;
	char	*value;

	param = exp->param;
	value = NULL;
	if (ft_strncmp(param, "?", 1) == 0)
	{
		value = ft_itoa(data->last_exit_status);
		data->last_exit_status = 0;
	}
	else
	{
		value = get_env_value(param, data);
		if (!value)
			value = ft_strdup("");
	}
	exp->value = value;
	update_tok(exp, tok);
}
