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

# include "../include/utils.h"

typedef struct s_token	t_token;
typedef enum e_types
{
	NONE,
	WHITESPACE,
	PIPE,
	REDIN,
	REDOUT,
	REDOUTAPP,
	HEREDOC,
	AND,
	OR,
	OPENPAR,
	CLOSEPAR,
	DOLLAR,
	CMD,
	ARG,
}	t_types;

typedef enum e_cat
{
	OPERATOR,
	WORD,
}	t_cat;

typedef struct s_token
{
	char	*line;
	char	*token;
	int		split;
	t_token	*join_with;
	int		type;
	int		quote;
	int		start;
	int		end;
	int		p_quote;
}	t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}	t_token_list;

typedef struct s_parse_tree
{
	t_token		        *token;
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
}   t_parse_tree;

# define LIST t_token_list
# define TOKEN t_token
# define TREE t_parse_tree

LIST	*tokenize(char *line);
int		is_space(int c);
int		is_quote(int c);
int		is_sep_char(int c);
int 	is_sep(char *line, int *i);

int 	expand(LIST *token_list);
t_list	*get_var_list(char *str);
char	*expand_var_list(t_list *var_list);
int		is_starting(int c);
int		is_subsequent(int c);
int		invalid_var_char(int c);

int		clear_tree(t_parse_tree *tree);
void	print_token_list(LIST *list);
int		join_tokens(LIST *token_l);

int		word_split(LIST **tokens, char *charset);
LIST	*get_prev_node(LIST *token_l, LIST *node);
#endif