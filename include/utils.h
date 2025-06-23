/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:05:01 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/29 14:39:39 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H


# include "../libft/libft.h"
# include <stdio.h>
# include "../include/garbage_collector.h"
# include "./null.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

int	    index_of(char *str_ptr[], char *key);
int	    panic(char *s, int code);
void	print_list(t_list *list);
size_t  get_lsize(t_list *var_list);
int     copy_list(char *buff, t_list *var_list, size_t size);

# endif
