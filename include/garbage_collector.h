/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:18:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 11:08:30 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "./utils.h"

typedef enum
{
    COLLECT,
    CHECK,
    FREE,
    DESTROY
}   t_gbc_options;

void	garbage_collector(void *ptr, int option);
void	*my_alloc(size_t size);

#endif
