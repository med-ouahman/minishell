/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:07:02 by mouahman          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/03 16:34:30 by mouahman         ###   ########.fr       */
=======
/*   Updated: 2025/07/03 16:53:49 by aid-bray         ###   ########.fr       */
>>>>>>> 191da425410b72e73f73348b77e5aea2e344120c
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "./utils.h"
# include "./parser.h"

int cd(t_cmd *cmd);
int export(t_cmd *cmd);
int pwd(t_cmd *cmd);
int env(t_cmd *cmd);
int unset(t_cmd *cmd);
int echo(t_cmd *cmd);
int exit_(t_cmd *cmd);

#endif
