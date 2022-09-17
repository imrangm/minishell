/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:06:37 by imustafa          #+#    #+#             */
/*   Updated: 2022/09/17 15:51:43 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* CONSTRUCTOR FUNCTIONS */

t_execcmd	*exe_cmd(char *fcmd)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = SCMD;
	cmd->fcmd = fcmd;
	return (cmd);
}

t_redircmd	*redir_cmd(char *fcmd, t_redirs *rd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = RCMD;
	cmd->fcmd = fcmd;
	cmd->rd = *rd;
	return (cmd);
}

t_pipecmd	*pipe_cmd(t_pipe **p, int nchild)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PCMD;
	cmd->pipes = p;
	cmd->nchild = nchild;
	return (cmd);
}

/* DESTRUCTOR FUNCTION */

void	free_command(t_cmd *cmd)
{
	t_execcmd	*exec;
	t_redircmd	*redir;
	t_pipecmd	*pipe;

	if (cmd->type == SCMD)
	{
		exec = (t_execcmd *) cmd;
		ft_free(exec->fcmd);
		ft_free(exec);
	}
	if (cmd->type == RCMD)
	{
		redir = (t_redircmd *) cmd;
		ft_free(redir->fcmd);
		ft_free(redir);
	}
	if (cmd->type == PCMD)
	{
		pipe = (t_pipecmd *) cmd;
		ft_free(pipe);
	}
}

/* EXECUTOR FUNCTION */

void	execute(t_cmd *cmd, t_data *data)
{
	t_execcmd	*exec;
	t_redircmd	*redir;
	t_pipecmd	*pipe;

	if (cmd->type == SCMD)
	{
		exec = (t_execcmd *) cmd;
		scmd(exec->fcmd, data);
	}
	if (cmd->type == RCMD)
	{
		redir = (t_redircmd *) cmd;
		redirs(redir->fcmd, &redir->rd, data);
	}
	if (cmd->type == PCMD)
	{
		pipe = (t_pipecmd *) cmd;
		pipes(pipe->pipes);
	}
	ft_free(cmd);
}
