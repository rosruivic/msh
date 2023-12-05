/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:14:49 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/05 19:13:05 by roruiz-v         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/ttydefaults.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include <limits.h>
//# include <readline/rlstdc.h> 	 // da error
//# include <readline/rltypedefs.h>  // da error

# define NC	"\e[0m"
# define R 	"\e[31m"
# define G 	"\e[32m"
# define Y 	"\e[33m"
# define B 	"\e[34m"
# define V 	"\e[35m"

# define RD 0		// pipe read extreme
# define WR 1		// pipe write extreme

# define SIR 1		// redir struct 'type' = Simple Input Redir (<)
# define DIR 2		// redir struct 'type' = Double Input Redir (<<)
# define SOR 3		// redir struct 'type' = Simple Output Redir (>)
# define DOR 4		// redir struct 'type' = Double Output Redir (>>)

typedef struct	s_sgn
{
	int	listen; // for signals (could be a STRUCT only for signal issues) 
	int	chld_pid; // for signals (could be a STRUCT only for signal issues)
}		t_sgn;

extern t_sgn	g_sgn;

typedef enum e_error
{
	NO_ERROR,
	ERROR_SIGACTION_FAILURE,
	ERROR_ARGMTS,
	ERROR_INFILE,
	ERROR_OUTFILE,
	ERROR_FILES_FD,
	ERROR_PIPE_CREATION,
	ERROR_PIPE_EXECUTION,
	ERROR_PID,
	ERROR_NO_PATHS,
	ERROR_CMD_NOT_EXISTS,
	ERROR_CHDIR_FAILURE,
	ERROR_CHDIR_OLDPWD_NOT_SET,
	ERROR_CHDIR_HOME_NOT_SET,
	ERROR_TOO_MANY_ARGUMENTS,
	ERROR_NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_START_NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_SPLIT_EXTRACTING_CMD, 			// be free!
	END = 99,
}	t_error;

/**
 * @brief  We need to determinate what kind of redir is (SIR, DIR, SOR, DOR)
 * 			and, if it's the case, the infile or outfile to be open
 *  	In case of '<<', file = NULL;
 */
typedef struct	s_rd
{
	int			type;
	char		*end_key;
	char		*heredoc;
	char		*file;
	struct s_rd	*nx;	
}				t_rd;

/**
 * @brief   Each node can be a command or a redirection node,
 * 	the difference between both types is the data contained within.
 *  
 *  BEWARE OF THIS !!! parser only fills 'type', 'c_args' & 'c_abs_path'
 * 
 * 	> c_args[0]   -> contains the cmd as the usu writes
 *                     (WITH or WITHOUT absolute path)
 * 	> c_args[...] -> contains the arguments and flags of the command
 *  > c_abs_path  -> contains a copy of c_args[0] (WITH or WITHOUT abs_path)
 *  > c_env_path  -> contains a copy of c_abs_path if it has an abs_path,
 *        OR a correct access path from $PATH when c_args[0] don't have abs_path
 *	> pid         -> to execute an external cmd (not a builtin)
 *	> fd[2]       -> to be used when there were a pipe
 *  > orgn        -> pointer to main data struct
 */
typedef struct	s_cmd_lst
{
	t_rd				*rds;
	char				**c_args;
	char				*c_abs_path;
	char				*c_env_path;
	int					pid;
	int					pipe_val;
	int					fd_in;
	int					fd[2];
	struct s_msh		*orgn;
	struct s_cmd_lst	*nx;
}						t_cmd_lst;

typedef	struct s_env_lst
{
	char				*nm;
	char				*val;
	int					equal;
	struct s_env_lst	*nx;
}						t_env_lst;

typedef struct	s_msh
{
	struct sigaction	sig;
	t_error				error;
	t_env_lst			*env_lst;
	t_cmd_lst			*cmd_lst;
	char				*pipeline;
	int					pid;		// para ejecutar cuando haya pipes
	int					fd;			// now it's used by many parts of msh
	int					org_stdin;	// to keep the original STDIN
	int					org_stdout; // to keep the original STDOUT
	int					exit_code;
}						t_msh;

/* ***************************************************************** */
/* ******************      SIGNAL  FUNCTIONS       ***************** */
/* ***************************************************************** */

void	ft_handler(int sig, siginfo_t *info, void *context);
void	ft_ctrl_d(t_msh *data);

/* ***************************************************************** */
/* *****************     ENVIRONMENT  FUNCTIONS    ***************** */
/* ********     will be used by [env], [export], [unset]    ******** */
/* ***************************************************************** */

void		ft_duplic_envp(t_msh *data, char **envp);
void		ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new);
t_env_lst	*ft_env_lst_new(char **tmp_env, int equal);
void		ft_env_join_val(t_env_lst *t_nd, t_env_lst *new);
void		ft_env_modify_or_add_node(t_msh *data, t_env_lst *new);
void		ft_env_lstadd_back(t_msh *data, t_env_lst *new);
void		ft_msh_lstadd_front(t_msh *data, void *new, int type);
void		ft_env_lstclear(t_env_lst *del_lst);
void		ft_env_lstdelone(t_msh *data, char *del_env_nm);
void		ft_env_lst_print(t_msh *data);
void		ft_export_lst_print(t_msh *data);
void		ft_free_envlst_node(t_env_lst *del_node);
t_env_lst	*ft_index_built_lst(t_msh *data);
t_env_lst	*ft_index_new_nd(t_env_lst *nd);
void		*ft_index_lstadd_back(t_env_lst *index, t_env_lst *nd);
t_env_lst	*ft_index_lstadd_front(t_env_lst *index, t_env_lst *nd);
void		ft_index_lstadd_mid(t_env_lst *prev, t_env_lst *nd);
char		**ft_find_env_paths(t_msh *data);
int			ft_env_lst_count_nds(t_env_lst *env_lst);

/* ***************************************************************** */
/* ***************     LEXER & PARSER  FUNCTIONS      ************** */
/* ***************************************************************** */

void	ft_init_msh_struct(t_msh *data);
void	ft_simple_lexer(t_msh *data);
void	ft_simple_parser(t_msh *data);
int		ft_env_forbidden_chars(char *name);

/* ***************************************************************** */
/* ******************     CMD LIST  FUNCTIONS      ***************** */
/* ***************************************************************** */

void	ft_cmd_lstclear(t_msh *data);

/* ***************************************************************** */
/* ***************        EXECUTOR  FUNCTIONS         ************** */
/* ***************************************************************** */

void	ft_executor(t_msh *data);
void	ft_redir_heredoc(t_msh *data, t_cmd_lst *cmd_nd);
void	ft_redir_infile(t_msh *data, t_cmd_lst *cmd_nd);

/* ***************************************************************** */
/* ******************     BUILTINS  FUNCTIONS      ***************** */
/* ***************************************************************** */

//void	ft_builtin_executor(t_msh *data, char *cmd);
void	ft_builtin_executor(t_msh *data, char *cmd, t_cmd_lst *cmd_nd);
void	ft_builtin_exec_echo(t_msh *data);
void	ft_builtin_exec_exit(t_msh *data);
void	ft_builtin_exec_env(t_msh *data);
void	ft_builtin_exec_export(t_msh *data);
void	ft_builtin_exec_pwd(t_msh *data);
void	ft_builtin_exec_unset(t_msh *data);
void	ft_builtin_exec_cd(t_msh *data);
void	ft_builtin_exec_cd_down(t_msh *data);
void	ft_builtin_exec_cd_without_args(t_msh *data, int exit_code);
void	ft_builtin_exec_cd_oldpwd(t_msh *data);
void	ft_env_change_val(t_msh *data, char *nm_dst, char *new_val);
char	*ft_env_obtain_val(t_msh *data, char *env_nm);


/* ***************************************************************** */
/* ****************     EXTERNAL CMDS  FUNCTIONS     *************** */
/* ***************************************************************** */

void	ft_find_cmd_path(t_cmd_lst *cmd, char **paths);
int		ft_exec_external_cmd(t_msh *data);

/* ***************************************************************** */
/* ********************     ERROR  FUNCTIONS     ******************* */
/* ***************************************************************** */

void	ft_error_start(char *argv_1, int error);
void	ft_error_status(t_msh *data, int error);
void	ft_error_signal(int error);
void	ft_error_cd(t_msh *data, int error);
void	ft_error_pipes_forks(t_msh *data, int error);

/* ***************************************************************** */
/* ********************     UTILS  FUNCTIONS     ******************* */
/* ***************************************************************** */

void	ft_free_null_void_return(char **str);
char	*ft_free_null_no_void_return(char *str);
char	*ft_join_free(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_str_equal(char *s1, char *s2);
char	**ft_2rows_split(char *str, char c);
int		ft_matrix_len(char **str);
int		ft_is_str_digits(char *str);


#endif
