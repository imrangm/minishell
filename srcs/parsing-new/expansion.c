/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:17 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/21 13:55:05 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//process the raw node and change id to final
void	expander(t_node	*cmd, t_data *data)
{
	char		*param;
	char		*final;
	int			start;
	int			end;
	int			len;
	size_t		i;
	size_t		j;

	if (ft_strncmp(cmd->right_node->right_node->value, "?", 1) == 0)
		param = ft_itoa(data->last_exit_status);
	else
		param = get_env_value(cmd->right_node->right_node->value, data);
	start = cmd->right_node->left_node->left_node->val;
	end = cmd->right_node->left_node->right_node->val;
	len = ft_strlen(param) + ft_strlen(cmd->left_node->value) - (end - start);
	printf("values start:%d, end:%d, len:%d\n", start, end, len);
	printf("param: %s\n", param);
	final = malloc(sizeof(char) * len);
	i = 0;
	while (i < (size_t) start)
	{
		final[i] = cmd->left_node->value[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(param))
	{
		final[i] = param[j];
		i++;
		j++;
	}
	j = end + 1;
	while (j < ft_strlen(cmd->left_node->value))
	{
		final[i] = cmd->left_node->value[j];
		i++;
		j++;
	}
	final[i] = '\0';
	printf("final: %s\n", final);
	cmd->left_node->value = final;
	cmd->left_node->id = ft_strdup("FINAL");
}
