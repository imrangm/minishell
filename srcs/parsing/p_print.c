/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 07:00:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/13 14:42:15 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_chars(t_scan	*scan)
{
	int			len;
	int			i;

	len = scan->len;
	printf("------------------------\n");
	printf("%d Chars\n", len);
	i = 0;
	while (i < len)
	{
		printf("%d- C: %c T: %d\n", i, scan->chars[i]->c, scan->chars[i]->t);
		i++;
	}
}

void	print_tokens(t_token **tokens)
{
	int		i;

	i = 0;
	printf("------------------------\n");
	printf("%d Tokens\n", tokens[0]->count);
	printf("------------------------\n");
	while (i < tokens[0]->count)
	{
		printf("%d: [%s]\n", tokens[i]->type, tokens[i]->value);
		i++;
	}
}

static void	indent(size_t spaces)
{
	size_t	i;

	i = 0;
	while (i < spaces)
	{
		printf(" ");
		i++;
	}
}

void	print_ast(t_node *node, size_t spaces)
{
	indent(spaces);
	if (node->type == 0)
	{
		if (ft_strncmp(node->id, "START", 5) == 0
			|| ft_strncmp(node->id, "END", 3) == 0)
			printf("%s: %d\n", node->id, node->val);
		else
			printf("%s: %s\n", node->id, node->value);
	}
	if (node->type == 1)
	{
		if (ft_strncmp(node->id, "PARAM", 5) == 0)
			printf("%s: %s\n", node->id, node->value);
		else
			printf("%s:\n", node->id);
		print_ast(node->left_node, spaces + 3);
		print_ast(node->right_node, spaces + 3);
	}
	if (node->type == 2)
		printf("%s: %s\n", node->id, node->value);
}
