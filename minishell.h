/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:35:46 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 22:10:02 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

typedef enum e_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_tokens;

typedef struct s_proc
{
	int		fd[2];
	pid_t	pid;
	int		parsersize;
}	t_proc;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				is_quote;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_global
{
	t_lexer					*head;
	struct s_simple_cmds	*p_head;
	char					**env;
	char					**export;
	int						error;
}	t_global;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_global *, struct s_simple_cmds *);
	int						num_redirections;
	t_proc					prcs;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_globals
{
	int		error_num;
	int		sig;
}	t_globals;

extern t_globals	g_global;

void			ft_init_lexer(t_global *mini, char *line);
void			free_tokens(char **tokens);
void			ft_deallocate_lexer(t_global *mini);
void			ft_parser_lexpush_back(t_simple_cmds *temp, char *str);
void			ft_parser_lexlast_node(t_simple_cmds *temp, char *str);
void			ft_parser_lexfirst_node(t_simple_cmds *temp, char *str);
void			ft_init_parser(t_global *mini);
void			ft_init_matrix(t_global *mini);
void			ft_delete_node(int index, t_global *mini);
void			ft_skipinit(t_simple_cmds **new, int flag);
void			ft_parser_pushback(t_global *mini, t_lexer *lexer);
void			ft_parent(t_global *mini);
void			ft_expand(t_global *mini);
void			ft_deallocate_all(t_global *mini);
void			ft_init_builtin(t_global *mini);
void			ft_freearr(char ***str);
void			ft_executer(t_global *mini);
void			ft_multiple_command(t_global *mini);
void			ft_set_global(t_global *mini);
void			ft_set_pipes(t_global *mini, t_simple_cmds *temp, int i);
void			ft_wait_prcs(t_global *mini, int *status);
void			close_pipes(t_global *mini, int current);
void			ft_set_heredoc(t_lexer *redirection);
void			set_heredoc_for_multi(t_global *mini);
void			ft_set_pwd(t_global *mini, char *str);;
void			ft_handler(int sig);
void			ft_spik(char ***tokens, int *index, int *token_length,
					char **str);
char			*ft_addquotes(char *str);
void			ft_check_red(t_global *mini, int has_slash);
char			**ft_setenv(char **ev);
char			**ft_added(char **ev, char *str);
char			**ft_split_tok(char *str, char *del);
int				ft_check_tokens(t_global *mini);
int				ft_checkvalid(char *str);
int				ft_check_valid_identifier(char c);
int				ft_exporterror(char *c);
int				count_tokens(char *str, char *del);
char			**ft_setenvplus(char **ev);
int				ft_search_builtin(char *str);
int				ft_setdir(t_global *mini, char *str);
int				ft_printexport(char **str);
int				ft_is_valid(char c);
int				ft_checkvalid(char *str);
int				ft_check_error(t_global *mini);
int				ft_find_token(char *str);
int				ft_cd(t_global *mini, t_simple_cmds *parser);
int				ft_echo(t_global *mini, t_simple_cmds *parser);
int				ft_pwd(t_global *mini, struct s_simple_cmds *head);
int				ft_export(t_global *mini, t_simple_cmds *parser);
int				ft_unset(t_global *mini, t_simple_cmds *parser);
int				ft_env(t_global *mini, struct s_simple_cmds *head);
int				ft_exit(t_global *mini, struct s_simple_cmds *parser);
int				ft_strcmp(char *s1, char *s2);
int				ft_size_cmds(t_global *mini);
int				ft_search_slash(char *str);
int				ft_her(t_lexer *temp, char *file);
int				ft_open_pipes(t_global *mini);
int				ft_set_red(t_lexer *redirection);
int				ft_check_replace(t_simple_cmds *temp, t_global *mini);
int				ft_check_last(t_lexer *redirection);
int				ft_ifequalexists(char *str);
int				ft_replace_dollar(char **exp, int *j, char *str,
					t_global *mini);
int				ft_check_flag_status(char *str, int i, int *flag);
int				ft_ifvalid(char c);
int				is_delimiter(char c, char *del);
void			ft_expandmainly(char **exp, char *str, char **ev,
					t_global *mini);
int				ft_add_dollar(char *str, char **ev, t_global *mini);
int				ft_handle_qmark(char **exp, int *j, t_global *mini);
int				ft_check_flag_status(char *str, int i, int *flag);
int				ft_execute_single_commands(t_global *mini);
void			ft_stradd(char **exp, char *str, int j);
int				ft_allvalid(char c);
char			*ft_pathof(char *str, char **ev, t_global *mini);
void			ft_quicklyinitialize(int *i, int *flag, int *j);
char			**ft_split_tok(char *str, char *del);
void			ft_spik5(int *a, int *b);
void			ft_spik3(int *token_length, char **str);
void			ft_spik4(char ***tokens, int *index, int *token_length,
					char **str);
void			ft_spik2(char ***tokens, int *index, int *token_length,
					char **str);
void			ft_spik(char ***tokens, int *index, int *token_length,
					char **str);
void			free_tokens(char **tokens);
int				ft_parsersize(t_simple_cmds *parser);
void			ft_set_heredocs(t_simple_cmds *temp);
void			ft_clear_heredocs(t_simple_cmds *temp);
void			ft_set_lexer_index(t_simple_cmds *temp2);
void			ft_delete_lexer_node(int index, t_simple_cmds *temp2);
t_lexer			*ft_find_index(int i, t_lexer **lexer);
void			ft_printmatrix(char **str);
void			ft_clear_lexer(t_global *mini);
void			ft_parser_arrange(t_simple_cmds *parse);
int				ft_lexersize(t_lexer *lexer);
void			ft_parser_rearrange(t_global *mini);
void			ft_take_input_from_terminal(char *str, t_proc *child, int flag);
void			ft_take_input_from_file(t_global *mini, char *str,
					t_proc *child, int flag);
int				ft_greatgreat(t_global *mini, char *str);
int				ft_great(t_global *mini, char *str);
char			*ft_findinenv(t_global *mini, char *str);
void			ft_setinput(t_lexer **red, t_proc *child, int *flag,
					t_global *mini);
void			ft_setoutput(t_lexer **red, t_global *mini, int *flag,
					int *outfd);
char			*ft_set_path(t_global *mini, char **str);
char			*ft_path_arrange(char *path, char *str);
int				ft_execute_multiple_commands(t_global *mini);
int				ft_isparent(t_proc *childs, int parsersize);
t_simple_cmds	*ft_find_parser_index(int i, t_simple_cmds *parser);
void			ft_check_delete(t_global *mini, t_lexer *temp);
int				no_pwd(char **env);
void			ft_setmultiinput(t_lexer *red, t_proc *childs, int *flag,
					int i);
void			ft_take_multiinput_from_terminal(char *str, t_proc *child,
					int flag, int i);
void			ft_take_multiinput_from_file(char *str, t_proc *child, int flag,
					int i);
int				ft_pipecreation(t_global *mini, t_proc	**childs,
					int *parsersize);
void			ft_setprocesses(t_global *mini, t_simple_cmds **cmd,
					t_proc **childs, int *parsersize);
void			ft_closepipes(int parsersize, int outfd, int infd,
					t_proc **childs);
void			ft_waitmain(t_proc **childs, int parsersize, int *out);
void			ft_pipearrange(t_proc **childs, int *fds, t_global *mini,
					t_simple_cmds **cmd);
void			ft_setio(t_proc **childs, int parsersize, int *fds);
void			ft_execution(t_proc **childs, t_simple_cmds **cmd,
					int *fds, t_global *mini);
void			ft_closesinglepipes(t_proc *child, int *outfd);
void			ft_errorarranger(t_global *mini, int out);
int				ft_simpleif(t_global *mini);
int				ft_openpipe(t_proc *child, t_global *mini);
void			ft_singleexecution(t_proc *child, t_global *mini,
					t_simple_cmds *cmd);
void			setsingleio(t_proc *child, int *flag, t_global *mini,
					int *outfd);
void			ft_writeintoheredoc(int fdheredoc, char *line);
void			ft_setinputloop(int *flag, t_lexer **save2,
					t_lexer **save, t_proc *child);
void			ft_setoutputskip(int *flag, int *outfd, int *buffd);
void			ft_initskip1(t_lexer **save, t_lexer **save2,
					int *fflag, t_lexer *red);
void			ft_initskip0(t_lexer **save2);
void			ft_ifskip1(t_lexer **save, t_lexer **save2, int *fflag,
					int *flag);
void			ft_ifskip0(t_lexer *red, t_lexer **save);
t_lexer			*firstskip(t_lexer *red, t_lexer **save, int *fflag);
void			ft_smoothoperator(t_proc *child);
t_lexer			*smoothskip(t_lexer **red, t_lexer **save, int *flag);
void			ft_smoooooth(int	*buffd, int *outfd, int *flag);
void			signals_init(void);
void			suppress_output(void);
void			handle_sigint(int sig);
void			handle_sigquit(int sig);