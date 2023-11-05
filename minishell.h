/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:14:49 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/05 18:17:04 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NC	"\e[0m"
# define R 	"\e[31m"
# define G 	"\e[32m"
# define Y 	"\e[33m"
# define B 	"\e[34m"
# define V 	"\e[35m"
//# include <limits.h>

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_INFILE,
	ERROR_OUTFILE,
	ERROR_FILES_FD,
	ERROR_PIPE,
	ERROR_PID,
	ERROR_CMD_NOT_EXISTS,
	ERROR_SPLIT_EXTRACTING_CMD = 20, // be free!
	END = 99, // to execute command [exit] or exit caused by an error
}	t_error;

typedef struct	s_cmd_lst
{
	char				**args;	 // cmd[0] + argmts of the command
	char				*path_cmd;   // absolute direction & command
	char				*env_path;   // path (from $PATH) & command
//	char				**cmd_flags; // posible flags of the command
	int					pid;
	int					fd_in;
	int					ft_out;
	struct s_cmd_lst	*nx;
}			t_cmd_lst;

typedef	struct s_env_lst
{
	char				*nm;
	char				*val;
	int					equal;
	struct s_env_lst	*nx;
}						t_env_lst;

typedef struct	s_msh
{
	t_error		error;
	t_env_lst	*env_lst;
	t_cmd_lst	*cmd_lst;
	int			fd;
}				t_msh;

/* ***************************************************************** */
/* *********************    PIPEX  FUNCTIONS   ********************* */
/* ***************************************************************** */

//void	ft_errors(int error, t_minishell *d);
//void	ft_init_data(t_minishell *d, char **argv, char **envp);
//int	ft_forks(t_minishell *d, char **envp);
//void	ft_free_all(t_minishell *d);

/* ***************************************************************** */
/* *****************     ENVIRONMENT  FUNCTIONS    ***************** */
/* ********     will be used by [env], [export], [unset]    ******** */
/* ***************************************************************** */

void		ft_duplic_envp(t_msh *data, char **envp);
void		ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new);
void		ft_free_envlst_node(t_env_lst *del_node);
t_env_lst	*ft_env_lst_new(char **tmp_env, int equal);
void		ft_env_join_val(t_env_lst *t_nd, t_env_lst *new);
void		ft_env_modify_or_add_node(t_msh *data, t_env_lst *new);
void		ft_env_lstadd_back(t_msh *data, t_env_lst *new);
void		ft_msh_lstadd_front(t_msh *data, void *new, int type);
void		ft_env_lstclear(t_env_lst *del_lst);
void		ft_env_lstdelone(t_msh *data, char *del_env_nm);
void		ft_env_lst_print(t_msh *data);
void		ft_export_lst_print(t_msh *data);
t_env_lst	*ft_index_built_lst(t_msh *data);
t_env_lst	*ft_index_new_nd(t_env_lst *nd);
void		*ft_index_lstadd_back(t_env_lst *index, t_env_lst *nd);
t_env_lst	*ft_index_lstadd_front(t_env_lst *index, t_env_lst *nd);
void		ft_index_lstadd_mid(t_env_lst *prev, t_env_lst *nd);
char		**ft_find_env_paths(t_msh *data);


/* ***************************************************************** */
/* ******************     BUILTINS  FUNCTIONS      ***************** */
/* ***************************************************************** */

void	ft_builtin_exec(t_msh *data, char *cmd);
void	ft_builtin_exec_exit(t_msh *data);
void	ft_builtin_exec_env(t_msh *data);
void	ft_builtin_exec_export(t_msh *data);
void	ft_builtin_exec_unset(t_msh *data);
void	ft_builtin_exec_cd(t_msh *data);

/* ***************************************************************** */
/* ***************     LEXER & PARSER  FUNCTIONS      ************** */
/* ***************************************************************** */

void	ft_init_msh_struct(t_msh *data);
void	ft_simple_lexer(t_msh *data, char *pipeline);
void	ft_simple_parser(t_msh *data);
int		ft_env_forbidden_chars(char *name);

/* ***************************************************************** */
/* ****************     EXTERNAL CMDS  FUNCTIONS     *************** */
/* ***************************************************************** */

void	ft_find_cmd_path(t_cmd_lst *cmd, char **paths);
int		ft_exec_external_cmd(t_msh *data);

/* ***************************************************************** */
/* ********************     UTILS  FUNCTIONS     ******************* */
/* ***************************************************************** */

void	ft_error_status(t_msh *data, int error);
void	ft_free_null(char *str);
char	*ft_join_free(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_str_equal(char *s1, char *s2);
char	**ft_2rows_split(char *str, char c);
int		ft_matrix_len(char **str);


#endif
