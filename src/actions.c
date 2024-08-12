/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:17:57 by mlapique          #+#    #+#             */
/*   Updated: 2024/08/12 16:33:40 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_forks(t_philo *ph)
{
	if (ph->number % 2 == 0)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		if (print_forks(ph) == -1)
			return (-1);
		if (print_forks(ph) == -1)
			return (-1);
	}
	else
	{
		ft_usleep(5);
		pthread_mutex_lock(ph->right_fork);
		pthread_mutex_lock(ph->left_fork);
		if (print_forks(ph) == -1)
			return (-1);
		if (print_forks(ph) == -1)
			return (-1);
	}
	return (0);
}

int	go_to_sleep(t_philo *ph)
{
	if (print_sleeping(ph) == -1)
		return (-1);
	if (ft_usleep(ph->config->time_to_sleep) == -1)
		return (-1);
	pthread_mutex_lock(ph->config->meal_rights);
	ph->eat_count++;
	pthread_mutex_unlock(ph->config->meal_rights);
	return (0);
}

int	leave_forks(t_philo *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	if (go_to_sleep(ph) == -1)
		return (-1);
	return (0);
}
