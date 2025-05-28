/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:07:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/15 10:12:59 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	env(int option);
int export(char *key, char *value);
int exit_(void);
int change_dir(char *path);
int echo(char *args[], char *options[]);
int unset(char *key);
int pwd(void);

#endif
