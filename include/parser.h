/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:59:25 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/14 10:17:14 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./utils.h"
# include "./tokenizer.h"

typedef enum
{
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
	char	*heredoc;
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

typedef	union
{
	t_ast_binary	*binary_node;
	t_cmd			*cmd;
}	t_ast_node_type;

typedef struct s_ast
{
	int 	node_type;
	void	*data;
}	t_ast;

AST 	*parser(TOKEN *tokens);
TOKEN	*peek(TOKEN *tokens);
void	consume(TOKEN **tokens);
void print_tree(AST *ast);

t_list	*execution_list(AST *ast);
void	print_exc_list(t_list *exec_list);
#endif