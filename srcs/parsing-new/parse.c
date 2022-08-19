/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:23:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/08/19 18:34:17 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
create constructs to combine parts of tokens 
together to process them later

parser also would check for syntax and throw
error if there is a problem with it

Once you go through a token you are supposed to 
eat or consume it, in my case, i just move on to 
the next token.

I have to weigh benefits of linked list and implement 
if needed. Currently, there is no backtracking and
and no removal hence double pointer array 
is sufficient
*/

int	has_more_tokens(t_token **toks)
{
	return (toks[0]->iter + 1 < toks[0]->count);
}

t_token	look_ahead(t_token **toks)
{
	t_token	ret;
	int		i;

	ret.value = 0;
	ret.type = 0;
	if (!has_more_tokens(toks))
		return (ret);
	if (!toks[0]->cur)
		return (*toks[0]);
	i = toks[0]->iter;
	ret = *toks[i + 1];
	return (ret);
}

void	next_token(t_token **toks)
{
	if (toks[0]->cur && has_more_tokens(toks))
	{
		toks[0]->iter++;
	}
	if (!toks[0]->iter && has_more_tokens(toks))
	{
		toks[0]->iter = 0;
		toks[0]->cur = 1;
	}
}

/*
This part will process tokens to make synctactical analysis based
on the grammer of shell or how the input needs to be processed
*/
t_node	*parse(t_token **toks)
{
		return (parse_pipeline(toks));
}

/*
GRAMMAR
-------
(BONUS)
commandline : conditional
conditional : conditional "&&" pipeline
			| conditional "||" pipeline
-----------
commandline : pipeline ;
pipeline	: command 
			| pipeline "|" command -> command "|" command "|" command...;
			(to avoid left recursion)
*/

t_node	*parse_pipeline(t_token **toks)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	left = parse_command(toks);
	if (!has_more_tokens(toks) || look_ahead(toks).type != PIPE)
		return (left);
	if (look_ahead(toks).type == PIPE)
	{
		next_token(toks); // eat or consume pipe character
		if (look_ahead(toks).type != WORD)
		{
			right = error_node(ft_strjoin("unexpected token near: ",
				toks[toks[0]->iter]->value));
			return (right);
		}
		right = parse_pipeline(toks);
		return(pair_node(left, right, "PIPELINE"));
	}
	next_token(toks); // eat or consume pipe character
	if (look_ahead(toks).type != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
			toks[toks[0]->iter]->value));
		return (right);
	}
	right = parse_command(toks);
	return (pair_node(left, right, "PIPELINE"));
}
/*
NOTE: left recursion is not supported by RDP
command	: [word or redirection]...
command : word 
		| redirection 
		| command word -> word word word (use while loop instead of recursion)
		| command redirection -> redirection* (use while loop instead of recursion)
		;
command : [redirection*] arguments [redirection*] where redirection on either side
are optional {FINAL}
*/

t_node	*parse_command(t_token **toks)
{
	t_node	*left;
	t_node	*right;

	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	while (has_more_tokens(toks) && look_ahead(toks).type != PIPE)
	{
		if (look_ahead(toks).type == WORD
			|| look_ahead(toks).type == SQUOTE
			|| look_ahead(toks).type == DQUOTE)
		{
			next_token(toks);
			if (left->value)
			{
				toks[toks[0]->iter]->value = ft_strjoin(left->value,
				ft_strjoin(" ", toks[toks[0]->iter]->value));
			}
			left = parse_arguments(toks);
		}
		if (look_ahead(toks).type == REDIR)
		{
			next_token(toks);
			//check if infile exists, create outfile
			//run heredoc and throw syntax error
			//afterwords if any
			if (right->value)
			{
				process_redirection(right->left_node->value,
				right->value);
			}
			right = parse_redirection(toks);
		}
	}
	if (!left->id)
		left = node(toks);
	if (!right->id)
	{
		left->id = ft_strdup("COMMAND");
		return (left);
	}
	return (pair_node(left, right, "COMMAND"));
}

t_node	*parse_arguments(t_token **toks)
{
	t_node	*args;
	t_node	*left;
	t_node	*right;
	t_token	*temp;
	int		expansion_mode;

	args = node(toks);
	expansion_mode = 0;
	temp = toks[toks[0]->iter];
	if ((temp->type == WORD || temp->type == DQUOTE)
		&& ft_strchr(temp->value, '$'))
	{
		expansion_mode = 1;
	}
	if (expansion_mode)
	{
		args->id = ft_strdup("RAW");
		left = args;
		right = add_expansion(args);
		return (pair_node(left, right, "ARGS"));
	}
	args->id = ft_strdup("ARGS");
	return (args);
}

/*
redirection : redirectionop filename ;
redirection : ">" | ">>" | "<" | "<<"
*/

t_node	*parse_redirection(t_token **toks)
{
	t_node	*left;
	t_node	*right;
	// int		in;
	// int		out;

	//in redirs - <
	//need to add checks when expected token
	//is not found and throw an error
	left = malloc(sizeof(t_node));
	right = malloc(sizeof(t_node));
	left = node(toks);
	left->id = ft_strdup("OP");
	if (look_ahead(toks).type != WORD)
	{
		right = error_node(ft_strjoin("unexpected token near: ",
			toks[toks[0]->iter]->value));
		return (pair_node(left, right, "REDIR"));
	}
	next_token(toks);
	right = node(toks);
	right->id = ft_strdup("FILE");
	return (pair_node(left, right, "REDIR"));
}

void	test_parse(t_token **toks)
{
	t_node	*ret;

	ret = parse(toks);
		printf("------------------------\n");
	printf("AST\n");
	visit(ret, 0);
}
