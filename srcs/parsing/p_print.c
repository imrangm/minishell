/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmadi <nmadi@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 07:00:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/24 16:10:39 by nmadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_chars(t_charlist	*scan)
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

void	print_tokens(t_token *token)
{
	int	i;

	i = 1;
	printf("------------------------\n");
	printf("%d Tokens\n", count_tokens(token));
	printf("------------------------\n");
	while (token)
	{
		printf("%d: (%d) [%s]\n", i, token->type, token->value);
		token = token->next;
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
		printf("%s: %s\n", node->id, node->value);
	}
	if (node->type == 1)
	{
		printf("%s:\n", node->id);
		print_ast(node->left, spaces + 3);
		print_ast(node->right, spaces + 3);
	}
	if (node->type == 2)
		printf("%s: %s\n", node->id, node->value);
}
