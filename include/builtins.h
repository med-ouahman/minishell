/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:35:31 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/11 06:05:34 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./utils.h"

/* builtins */

int		cd(char **args);
int		echo(char **args);
int		exit_(char **args);
int		pwd(char *oldpwd);
int		unset(char **args);
int		env(char **args);
int		export(char **args);

/* buitlin utilities */
void	add_var(char *new_var);
void	change_var(char *new_var);
int		check_valid_variable(char *str);
void	dup_env(void);
t_uint	size_env(void);
void	swap_ptrs(char **p1, char **p2);
t_uint	key_size(char *s1);
int		export_add(char **argv);

#endif