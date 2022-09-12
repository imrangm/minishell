/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 07:00:10 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/12 11:08:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	test_scan(char	*input)
{
	int		len;
	t_scan	*scan;
	int		i;

	len = ft_strlen(input);
	printf("------------------------\n");
	printf("%d Chars\n", len);
	scan = scan_input(input);
	i = 0;
	while (i < len)
	{
		printf("%d- C: %c T: %d\n", i, scan->chars[i]->c, scan->chars[i]->t);
		i++;
	}
	free_chars(scan->chars, scan->len);
	ft_free(scan);
}

void	test_tokenize(t_scan *source)
{
	t_token	**tokens;
	int		i;
	int		count;

	i = 0;
	count = count_tokens(source);
	printf("------------------------\n");
	printf("%d Tokens\n", count);
	printf("------------------------\n");
	tokens = tokenize(source, 0);
	while (i < count)
	{
		printf("%d: [%s]\tQ: %d\n", tokens[i]->type, tokens[i]->value,
			tokens[i]->quote);
		i++;
	}
	free_tokens(tokens);
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
