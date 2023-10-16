/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:14:49 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/16 14:10:08 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
//# include <limits.h>

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_INFILE,
	ERROR_OUTFILE,
	ERROR_FILES_FD,
	ERROR_PIPE,
	ERROR_PID_1,
	ERROR_PID_2,
	ERROR_CMD_NOT_EXISTS,
	ERROR_SPLIT_EXTRACTING_CMD = 20, // be free!
}	t_error;

/**
 * @brief Esta estructura servirá para cuando tengamos
 * 				un número indefinido de comandos (varios pipes) * 
 */
typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_and_argmts;
	char	*path_cmd;
	int		pid;
}				t_cmd;

typedef	struct s_env_lst
{
	char				*nm;
	char				*val;
	struct s_env_lst	*nx;
}						t_env_lst;

typedef struct	s_msh
{
	t_error		error;
	t_env_lst	*env_lst;
}				t_msh;

t_msh	g_data;

/* ***************************************************************** */
/* *********************    PIPEX  FUNCTIONS   ********************* */
/* ***************************************************************** */

//void	ft_errors(int error, t_minishell *d);
//void	ft_init_data(t_minishell *d, char **argv, char **envp);
//int	ft_forks(t_minishell *d, char **envp);
//void	ft_free_all(t_minishell *d);

/* ***************************************************************** */
/* *****************     ENVIRONMENT  FUNCTIONS    ***************** */
/* ***************************************************************** */

void	ft_duplic_envp(char **envp);
t_env_lst	*ft_env_lst_new(char **tmp_env);
void	ft_env_lstadd_back(t_env_lst *new);
void	ft_env_lstadd_front(t_env_lst *new);
void	ft_env_lstdelone(char *del_env_nm);
void	ft_env_lstclear(void);
void	ft_env_lst_print(void);

/* ***************************************************************** */
/* ********************     UTILS  FUNCTIONS     ******************* */
/* ***************************************************************** */

void	ft_free_null(char *str);


#endif
