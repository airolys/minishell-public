/* ************************************************************************** */
/**//**//*   *//**//*   By: *//*	*//*   Created:   by *//*   Updated:   by */
/*							acharra											  */
/*								dkermia										  */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <linux/limits.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define MAGENTA "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define END "\001\033[0m\002"

typedef enum e_type
{
	ASSIGNEMENT_WORD	= (1 << 0),
	WORD = (1 << 1),
	AND_IF = (1 << 2),
	PIPE = (1 << 3),
	OR_IF = (1 << 4),
	LESS = (1 << 5),
	DLESS = (1 << 6),
	GREAT = (1 << 7),
	DGREAT = (1 << 8),
	LPARENT = (1 << 9),
	RPARENT = (1 << 10),
	CMD = (1 << 11),
	ROOT = (1 << 12),
	SEPARATOR = (PIPE | AND_IF | OR_IF),
	REDIRECT = (LESS | DLESS | GREAT | DGREAT),
	PARENT = (LPARENT | RPARENT),
	WORDS = (ASSIGNEMENT_WORD | WORD | CMD),
	OPERATOR = (SEPARATOR | REDIRECT | PARENT),
	ALL = (OPERATOR | WORDS),
}	t_token_type;

enum e_sigtype
{
	FORK,
	UNFORK
};

typedef struct s_token
{
	int				type;
	char			*txt;
	struct s_token	*next;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_tokens
{
	t_token	*first;
	t_token	*last;
	int		amount;
}	t_tokens;

typedef struct s_data
{
	char				*user_input;
	t_tokens			*tokens;
	t_token				*tree;
	int					status;
	int					stop;
	char				**args;
	int					argc;
	char				**env;
	struct termios		*term;
	int					last_pid;
}	t_data;

char				*quote_remove(char *str);

//		main.c

void				free_list(t_token *tmp);
void				free_for_all(t_data *data);
void				stop_signals(void);
void				start_signals(int fork);
void				handle_sigint(void);
void				handlerfork(int signum);
void				sig_handler(int signum);

//		main_utils.c

int					init_data(t_data *data, char **env);
int					shell_level(t_data *data, int offset);

//		signals.c

void				handle_ctrcinread(int signum);

//		parse_heredoc.c

t_token				*get_heredoc(t_data *data, char *str, int *len);

//		parsing_utils.c

t_token				*make_token(char *str, int len, int type);
void				add_token_last(t_tokens *list, t_token *toadd);
void				*ft_strcpy(void	*dest, const void *src, size_t n);
t_tokens			*create_tokens(void);

//		parsing.c

int					parse_input(t_data *userdata);
t_token				*tokenize_word(char *str, int *len);

//		syntax.c

int					syntax_check(t_tokens *t);

//		tree.c

void				build_tree(t_data *data);

//		tree_utils.c

void				print_tree_rec(t_token *root, int level);
void				show_token_tree(t_token *root, int depth, char *str);
void				free_tree(t_token *t);

//		actions.c

void				exect_tree(t_data *data, t_token *root);

//		all_star.c

int					ft_isspace(char c);
void				star(t_data *data);

//		exec_utils.c

void				free_args(t_data *data);
void				exec(t_data *data, char *path);
int					exec_builtin(t_data *data, char *cmd);
int					ft_strnchr(char *str, char c);

//		builtins

void				builtin_error(t_data *data, char *error);

void				ft_cd(t_data *data);

void				ft_echo(t_data *data);

void				ft_env(t_data *data);

int					ft_atoi(char *str);
void				ft_exit(t_data *data);

void				print_env(char **tab);
void				ft_export(t_data *data);

void				ft_pwd(t_data *data);

int					rm_env(t_data *data, char *key);
void				ft_unset(t_data *data);

//		env_utils.c

void				clear_tab(char **tab);
char				**dup_tab(char **tab, char *add);
int					ft_tabsize(char **tab);
char				*ft_strjoin(char *s1, char *s2);
int					is_keychar(char c);

//		env_func.c

int					compare_key(char *key, char *line);
int					ft_strncmp(char *s1, char *s2, int n);
int					add_env(t_data *data, char *line);
char				*get_value(t_data *data, char *key);
char				*get_env(t_data *data, char *key);

//		ft_itoa.c

char				*ft_itoa(int n);

//		ft_split.c

char				**ft_split(char const *s, char c);

//		expansion.c

char				*expand(char *src, t_data *data);

//		handle_cmd.c

char				*search_name(t_data *data, char *name);
void				handle_cmd(t_data *data, t_token *t);

//		handle_less.c

void				handle_less(t_data *data, t_token *t);
void				handle_dless(t_data *data, t_token *t);
void				handle_great(t_data *data, t_token *t);
void				handle_dgreat(t_data *data, t_token *t);

//		handle_pipe.c

void				handle_pipe(t_data *data, t_token *t);

//		handle_orand.c

void				handle_or_if(t_data *data, t_token *t);
void				handle_and_if(t_data *data, t_token *t);

//		handle_word.c

void				add_to_args(t_data *data, char *new_arg);
void				handle_word(t_data *data, t_token *t);

//		utils.c

char				*ft_strdup(char *str);
char				*ft_strchr(char *str, char c);
int					ft_strlen(const char *str);
int					ft_strlcpy(char *dest, const char *src, const int len);
char				*ft_strcmp(char *s1, char *s2);

#endif
