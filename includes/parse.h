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

#ifndef PARSE_H
# define PARSE_H

# include "../includes/utils.h"

typedef enum e_types
{
	NONE,
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
	int		type;
	int		quote;
	int		start;
	int		end;
	int		join_with;
	int		p_quote;
}	t_token;

typedef struct s_parse_tree
{
	t_token		        *token;
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
}   t_parse_tree;

t_parse_tree	*parser(char *line);
void			print_tree(t_parse_tree *tree, int dir);
int	is_space(int c);
int	is_quote(int c);
int	is_sep_char(int c);
int is_sep(char *line, int *i);

#endif