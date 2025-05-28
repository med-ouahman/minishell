/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:05:01 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/27 17:46:32 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include <stdio.h>

int	    index_of(char *str_ptr[], char *key);
int	    panic(char *s, int code);
void	print_list(t_list *list);
size_t  get_lsize(t_list *var_list);
int     copy_list(char *buff, t_list *var_list, size_t size);

# endif
