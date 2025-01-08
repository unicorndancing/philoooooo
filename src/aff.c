/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:00 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/03 20:38:18 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_eating(t_philo *ph)
{
	pthread_mutex_lock(ph->config->meal_rights);
	ph->last_meal = get_time();
	pthread_mutex_unlock(ph->config->meal_rights);
	pthread_mutex_lock(ph->config->print_rights);
	if (get_wellbeing(ph) != 1)
	{
		pthread_mutex_unlock(ph->config->print_rights);
		return (0);
	}
	printf(PURPLE "%ld %d is eating\n" WHITE, get_time()
		- ph->config->start_time, ph->number);
	pthread_mutex_unlock(ph->config->print_rights);
	return (1);
}

int	print_dead(t_philo *ph)
{
	printf(CYANUS "%ld %d died\n" WHITE, get_time() - ph->config->start_time,
		ph->number);
	return (1);
}

int	print_thinking(t_philo *ph)
{
	pthread_mutex_lock(ph->config->print_rights);
	if (get_wellbeing(ph) != 1)
	{
		pthread_mutex_unlock(ph->config->print_rights);
		return (0);
	}
	printf(RED "%ld %d is thinking\n" WHITE, get_time()
		- ph->config->start_time, ph->number);
	pthread_mutex_unlock(ph->config->print_rights);
	return (1);
}

int	print_sleeping(t_philo *ph)
{
	pthread_mutex_lock(ph->config->print_rights);
	if (get_wellbeing(ph) != 1)
	{
		pthread_mutex_unlock(ph->config->print_rights);
		return (0);
	}
	printf(GREEN "%ld %d is sleeping\n" WHITE, get_time()
		- ph->config->start_time, ph->number);
	pthread_mutex_unlock(ph->config->print_rights);
	return (1);
}

int	print_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->config->print_rights);
	if (get_wellbeing(ph) != 1)
	{
		pthread_mutex_unlock(ph->config->print_rights);
		return (0);
	}
	printf(YELLOW "%ld %d has taken a fork\n" WHITE, get_time()
		- ph->config->start_time, ph->number);
	pthread_mutex_unlock(ph->config->print_rights);
	return (1);
}
