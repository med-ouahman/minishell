/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:18:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 12:25:18 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "./utils.h"

# define ALLOC 1
# define FREE 2
# define FREE_U 3

void	garbage_collector(void *ptr, int option);
void	*my_alloc(size_t size);

#endif
