/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:17:23 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/24 21:25:29 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_msh *data)
{
	char		*input_line;
	int			exit_code;
	t_cmd_lst	*tmp;
	int			fd;

	fd = 0;
	input_line = NULL;
	exit_code = 0;
	tmp = data->cmd_lst;
	tmp->rds->heredoc = NULL;
	pipe(tmp->fd); // esta tubería contendrá la info obtenida
	tmp->pid = fork();
	if (tmp->pid < 0)
		ft_error_pipes_forks(data, ERROR_PID);
	else if (tmp->pid == 0)
	{ // hace el heredoc
		close(tmp->fd[RD]);
		dup2(tmp->fd[WR], STDOUT_FILENO);
		close(tmp->fd[WR]);
		input_line = readline("> ");
		while (input_line && ft_strcmp(input_line, tmp->rds->end_key) != 0)
		{
			tmp->rds->heredoc = ft_join_free(tmp->rds->heredoc, input_line);
			ft_free_null_void_return(&input_line);
			input_line = readline("> ");
		}
		ft_free_null_void_return(&input_line);
		printf("DEBUG FT_HEREDOC) %s\n", tmp->rds->heredoc);
	}
	else // FATHER recibiendo lo que ha hecho el hijo
	{
		close(tmp->fd[WR]);
		dup2(tmp->fd[RD], STDIN_FILENO); // aquí se acumula el resultado
		close(tmp->fd[RD]);
		wait(&exit_code);
		fd = open(STDIN_FILENO, O_RDONLY);
		tmp->rds->heredoc = get_next_line(STDIN_FILENO);
		printf("DEBUG: heredoc = %s\n", tmp->rds->heredoc);
	}
	return (WEXITSTATUS(exit_code));
}
