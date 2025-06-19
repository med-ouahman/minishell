/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:52:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/18 11:53:18 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../include/utils.h"

typedef enum e_types
{
	NONE,
	WORD,
	OPERATOR,
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


typedef struct	s_tl	t_tokenl;
typedef struct	s_token	t_token;

# define LIST	t_tokenl
# define TOKEN t_token

typedef struct s_token
{
	char	*line;
	char	*token;
	int		split;
	TOKEN	*join_with;
	int		type;
	int		quote;
	int		start;
	int		end;
	int		p_quote;
}	TOKEN;

typedef struct s_tl
{
	t_token		*token;
	struct s_tl	*next;
}	LIST;


typedef struct	s_info
{
	int	type;
	int	quote;
	int	start;
	int	end;
}	t_info;

LIST	*tokenizer(char *line);
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

void	print_token_list(LIST *list);
int		join_tokens(LIST **tokens);

int		word_split(LIST **tokens, char *charset);
LIST	*get_prev_node(LIST *token_l, LIST *node);

#endif
