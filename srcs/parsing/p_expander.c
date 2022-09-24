/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:19:06 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:10:29 by nmadi            ###   ########.fr       */
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

static void	quotes_error_exit(t_toklist *toks, t_exp *exp, t_data *data)
{
	free_expansion(exp);
	free_tokens(toks->first);
	ft_free(toks);
	data->last_exit_status = 1;
	ft_putendl_fd("Error: Quotes within env variables are not allowed.", 2);
}

int	expander(t_toklist *toks, t_token *tok, t_exp *exp, t_data *data)
{
	char	*value;

	value = NULL;
	if (ft_strncmp(exp->param, "?", 1) == 0)
		value = ft_itoa(data->last_exit_status);
	else
	{
		value = get_env_value(exp->param, data);
		if (!value)
			value = ft_strdup("");
	}
	exp->value = value;
	if (!ft_strchr(value, '\"') && !ft_strchr(value, '\''))
		update_tok(exp, tok);
	else
	{
		quotes_error_exit(toks, exp, data);
		ft_free(value);
		return (1);
	}
	free_expansion_all(exp);
	return (0);
}

int	check_exp(char *str)
{
	char	*tmp;

	if (!ft_strchr(str, '$'))
		return (0);
	tmp = ft_strchr(str, '$');
	if (tmp[1] && (ft_isspace(tmp[1]) || ft_isquote(tmp[1])
			|| ft_isdigit(tmp[1]) || tmp[1] == '(' || tmp[1] == '{'))
		return (0);
	return (1);
}
