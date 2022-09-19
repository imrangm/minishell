/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:06:37 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/19 13:48:30 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_execcmd	*exec_cmd(char *fcmd, t_data *data)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = SCMD;
	cmd->fcmd = fcmd;
	cmd->data = data;
	return (cmd);
}

t_redircmd	*redir_cmd(char *fcmd, t_redirs *rd, t_data *data)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = RCMD;
	cmd->fcmd = fcmd;
	cmd->rd = *rd;
	cmd->data = data;
	return (cmd);
}

t_pipecmd	*pipe_cmd(t_pipe **p, int nchild, t_data *data)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PCMD;
	cmd->p = p;
	cmd->nchild = nchild;
	cmd->data = data;
	return (cmd);
}

void	execute(t_cmd *cmd)
{
	if (cmd->type == SCMD)
	{
		scmd((t_execcmd *) cmd);
	}
	if (cmd->type == RCMD)
	{
		redirs((t_redircmd *) cmd);
	}
	if (cmd->type == PCMD)
	{
		pipes((t_pipecmd *) cmd);
	}
	ft_free(cmd);
}
