/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:41:40 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/03 11:44:08 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILCARD_H
# define WILCARD_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>

static int	is_match(char *from, char *srch);
t_list		*wilcard(int ac, char **srch);

#endif
