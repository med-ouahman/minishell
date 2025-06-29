/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:52:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/28 10:29:27 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../include/utils.h"

typedef enum e_types
{
	WORD = 1,
	OPERATOR,
	PIPE,
	REDIN,
	REDOUT,
	REDOUTAPP,
	HEREDOC,
	AND,
	OR,
	OPENPAR,
	CLOSEPAR,
	SUBSHELL,
	ATOM,
	CMD,
	WILDCARD,
}	t_types;

typedef struct	s_token	t_token;

# define TOKEN t_token

typedef struct s_token
{
	char	*line;
	char	*token;
	int		split;
	int		type;
	int		quote;
	int		start;
	int		end;
	int		p_quote;
	TOKEN	*join_with;
	TOKEN	*next;
}	TOKEN;

typedef struct	s_info
{
	int	type;
	int	quote;
	int	start;
	int	end;
}	t_info;

TOKEN	*tokenizer(char *line);
int		is_space(int c);
int		is_quote(int c);
int		is_sep_char(int c);
int 	is_sep(char *line, int *i);

int 	expand(TOKEN *token, int code);
t_list	*get_var_list(char *str, int code);
char	*expand_var_list(t_list *var_list);
int		is_starting(int c);
int		is_subsequent(int c);
int		invalid_var_char(int c);

void	print_token_list(TOKEN *list);
int		join_tokens(TOKEN **tokens);

char	**word_split(TOKEN *tokens, char *charset);
TOKEN	*get_prev_node(TOKEN *token_l, TOKEN *node);

#endif
