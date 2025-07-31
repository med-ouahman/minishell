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

# include "../libft/libft.h"
# include "./utils.h"
# include "./parser.h"

/* builtins */

int		cd(char **args);
int		export(char **args);
int		pwd(void);
int		env(void);
int		unset(char **args);
int		echo(char **args);
int		exit_(char **args);

/* buitlin utilities */

void	destroy_env(char ***env);
int		dup_env(char ***env);
long	size_env(char **env);
int		export_add(char **vars);
void	swap_ptrs(void **p1, void **p2);
t_uint	key_size(char *s1);

#endif
