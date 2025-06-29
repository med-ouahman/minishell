/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:59:25 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 10:13:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./utils.h"
# include "./tokenizer.h"

# define READ 0
# define WRITE 1

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

typedef enum
{
	PIPE_ERROR = 12,
	REDIR_ERROR
}	t_error;

typedef struct s_ast t_ast;

# define AST t_ast

typedef struct
{
	int		type;
	char	*target;
}	t_redir;

typedef struct
{
	int	type;

	AST *left;
	AST *right;
}   t_ast_binary;

typedef struct
{
	int		is_buitlin;
	t_list	*args;
	t_list	*redirs;
}	t_cmd;

typedef struct s_ast
{
	int 	node_type;
	void	*data;
}	t_ast;

TOKEN	*peek(TOKEN *tokens);
void	consume(TOKEN **tokens);
void 	print_tree(AST *ast);
t_list	*create_pipeline(AST *ast);
void    print_redir(t_redir *redir);
char	*parse_heredoc(t_redir *redir);
void	print_exc_list(t_list *exec_list);
t_list	*get_redirs(TOKEN **tokens);
int		is_builtin(char *cmd);
int		last_exit_code(int new_value, int mode);
int		syntax_error(int claimer, TOKEN *token);
int is_redirection(int t);


/* Parsers */

AST 	*parser(TOKEN *tokens);
AST 	*parse_command(TOKEN **tokens);
AST		*parse_or_command(TOKEN **tokens);
AST		*parse_and_command(TOKEN **tokens);
AST		*parse_pipeline(TOKEN **tokens);
AST		*parse_atom(TOKEN **tokens);
int		error(int c, int mode);

#endif
