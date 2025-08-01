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

int		export(char **args);

/* buitlin utilities */

void	dup_env(char ***env);
int	    check_valid_variable(char *str);
int	    size_env(char **env);
void	destroy_env(char ***env);


#endif
