/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:18 by mlapique          #+#    #+#             */
/*   Updated: 2024/08/12 16:28:46 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_wellbeing(t_philo *ph)
{
	int	is_ok;

	is_ok = -1;
	pthread_mutex_lock(ph->config->end_rights);
	pthread_mutex_lock(ph->config->dead_rights);
	if (ph->config->has_diedened != 1 && ph->config->is_over != 1)
		is_ok = 1;
	pthread_mutex_unlock(ph->config->dead_rights);
	pthread_mutex_unlock(ph->config->end_rights);
	return (is_ok);
}

void	*die(t_config *config)
{
	pthread_mutex_lock(config->end_rights);
	config->is_over = 1;
	pthread_mutex_unlock(config->end_rights);
	return (NULL);
}
