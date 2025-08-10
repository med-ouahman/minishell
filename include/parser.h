/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:22:48 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/07 05:01:17 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./utils.h"
# include <dirent.h>
# include <wait.h>
# include <fcntl.h>
# include "./signal_handler.h"

typedef enum s_enum_types
{
	WORD = 1,
	PIPE,
	RED_OUT,
	RED_INP,
	RED_APPOUT,
	RED_HERDOC,
	AMBIGUES,
	S_QUOTE,
	D_QUOTE,
	NO_QUOTE,
	SPLIT,
	JOIN
}	t_enum_types;

typedef struct s_info
{
	int		type;
	size_t	start;
	size_t	end;
	char	is_squote;
	char	is_dquote;
}	t_info;

typedef struct s_token
{
	char			*str;
	int				type;
	int				join;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int		type;
	char	*file;
	int		heredoc_fd;
}	t_redir;

typedef struct s_cmd
{
	int		is_builtin;
	t_list	*args;
	t_list	*redir;
}	t_cmd;

/* tool functions */

int		is_quote(char c);
int		is_space(char c);
int		is_operator(char *input, size_t*i, int flag);
int		is_redirection(t_token *token);

/* tokenizing */

t_token	*get_tokens(char *input);
int		add_token(t_token **tokens, char *input, t_info info);
void	read_token_token(char *input, t_info *info, size_t*i);
void	split_token_dquote(t_token **side_tokens, char *input);

/* parser */

t_list	*parser(char *input);
void	free_list_token(t_token *token);
int		check_valid_input(t_token *token);
t_list	*set_cmd(t_token *token);

/* expansion and quote removal */

int		expand(t_list *cmd);
void	split_after_expand(t_token *tokens);
void	check_join_split(t_token *token);
t_token	*split_token(char *str);
size_t	check_for_expand(char *input, size_t i);
void	join_var_expanded(t_token *tokens);
void	rm_quote(char *str);
void	expand_token_dqoute(t_token *token);
void	expand_token_var(t_token *token);
t_token	*new_tokens_expanded(t_token *token);
t_list	*join_tokens_args(t_list **arg, t_token *tokens);
void	join_tokens_redir(t_redir *redir, t_token *tokens);
t_token	*prepar_args(t_list	**arg, t_token *tokens);
int		check_last_token_unexpanded(t_token *tokens);
int		check_valid_variable(char *str);

/* heredoc */

int		close_heredocs(t_list *redirs);
t_list	*parser(char *input);
void	free_list_token(t_token *token);
void	read_heredoc(char *delmiter, int fd);
int		parser_heredoc(t_list *redirs, char *delim);
char	*ft_join(char *str1, int free1, char *str2, int free2);
char	*parser_line(char *input, int _expand);

#endif
