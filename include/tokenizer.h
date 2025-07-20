/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:52:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 16:44:37 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../include/utils.h"

# define IFS " \t\n"

/*

In bash the value of IFS (Internal Field Separators) is unset
which means that it defaults to <space>, <tab> and <newline> characters.

*/

typedef enum e_types
{
	WORD = 1,
	OP,
	PIPE,
	REDIN,
	REDOUT,
	REDOUTAPP,
	HEREDOC,
	CMD,
}	t_types;

typedef struct	s_token	t_token;

# define TOKEN t_token

typedef struct s_token
{
	char	*token;
	int		split;
	int		type;
	int		quote;
	int		start;
	int		end;
	int		p_quote;
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

t_list	*expander(char *token);
char	find_next_quote(char *s);
t_list	*expand(TOKEN *token);
t_list	*get_var_list(char *str);
char	*expand_var_list(t_list *var_list);
int		is_starting(int c);
int		is_subsequent(int c);
int	is_splittable(char *token);
int	has_spaces(char *s);
int	index_of_quote(char *token, int qt, int first);
int		invalid_var_char(int c);

void	print_token_list(TOKEN *list);
int		join_tokens(TOKEN **tokens);
int		quote_removal(t_list *tokens);
void	remove_quotes_from_token(char *_token);
t_list	*word_split(TOKEN *tokens);
TOKEN	*get_prev_node(TOKEN *token_l, TOKEN *node);
int	access_exit_code(int new_val, int mode);
void	add_exit_code(t_list **var_list, int code);
#endif
