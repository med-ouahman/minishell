/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:18:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/28 16:19:46 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# define P_MAX 1000
# include <stdlib.h>

int		garbage_collector(void *ptr, int option);
void	*my_alloc(size_t size);

#endif
