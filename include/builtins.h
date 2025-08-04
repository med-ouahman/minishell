/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:35:31 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 14:44:13 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./parser.h"

/* builtins */

int		cd(char **args);
int		echo(char **args);
int		exit_(char **args);
int		pwd(void);
int		unset(char **args);
int		env(void);
int		export(char **args);

/* buitlin utilities */

int		check_valid_variable(char *str);
void	dup_env(void);
t_uint	size_env(void);
void	swap_ptrs(char **p1, char **p2);
t_uint	key_size(char *s1);
int		export_add(char **argv);

#endif