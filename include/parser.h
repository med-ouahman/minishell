/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:35:59 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/12 22:28:10 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./utils.h"
# include "./tokenizer.h"
# include "./signal_handler.h"
# include <sys/types.h>
# include <dirent.h>

typedef enum
{
	NOT,
	CD,
	ECHO,
	EXIT,
	PWD,
	ENV,
	EXPORT,
	UNSET
}	t_builtins;

typedef struct s_ast t_ast;

# define AST t_ast

typedef struct
{
	int		type;
	char	*target;
	int		heredoc_fd;
}	t_redir;

typedef struct
{
	AST *left;
	AST *right;
}   t_ast_binary;

typedef struct
{
	AST		*ast_node;
	t_list	*redirs;
}	t_subshell;

typedef struct
{
	int		is_buitlin;
	TOKEN	*args; /* list of strings, could also be an array of strings */
	t_list	*redirs; /* list of t_redir type */
}	t_cmd;

typedef struct s_ast
{
	int		node_type;
	void	*data;
}	t_ast;

void	print_file_error(char *filename, char *err_msg);
void	print_file_error2(char *filename, char *_path, char *__err_msg);

TOKEN	*peek(TOKEN *tokens);
TOKEN	*consume(TOKEN **tokens);

void	add_token_back(TOKEN **args, TOKEN *token);
void 	print_tree(AST *ast);
void    print_redir(t_redir *redir);
void	print_exc_list(t_list *exec_list);
t_list	*create_pipeline(AST *ast);

t_list	*get_redirs(TOKEN **tokens);
int		is_builtin(char *cmd);
int		last_exit_code(int new_value, int mode);
int		syntax_error(int claimer, TOKEN *token);
int		is_redirection(int t);



/* Parsers */

int		parse_heredoc(char *_delim, int __expand);
t_list 	*parser(TOKEN *tokens);
t_list 	*parse_command(TOKEN **tokens);
t_list	*parse_pipeline(TOKEN **tokens);
int		error(int c, int mode);
size_t	token_list_size(TOKEN *list);

/*	wildcard */

t_list	*wildcard(char *pattern);
int		is_wildcard(TOKEN *token);

char	**build_argument_list(TOKEN *tokens);

#endif
