/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:08 by mlapique          #+#    #+#             */
/*   Updated: 2024/08/12 16:30:33 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	end_simulation(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philo)
	{
		if (pthread_mutex_destroy(&config->forks[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(config->dead_rights) != 0)
		return (1);
	if (pthread_mutex_destroy(config->end_rights) != 0)
		return (1);
	if (pthread_mutex_destroy(config->meal_rights) != 0)
		return (1);
	if (pthread_mutex_destroy(config->print_rights) != 0)
		return (1);
	free(config->dead_rights);
	free(config->end_rights);
	free(config->meal_rights);
	free(config->print_rights);
	free(config->forks);
	free(config->threads);
	free(config->philos);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(ph->config->meal_rights);
	ph->last_meal = get_time();
	pthread_mutex_unlock(ph->config->meal_rights);
	while (get_wellbeing(ph) == 1)
	{
		if (print_thinking(ph) == 0)
			return (die(ph->config));
		if (take_forks(ph) == -1)
			return (die(ph->config));
		if (print_eating(ph) == 0)
		{
			if (leave_forks(ph) == -1)
				return (die(ph->config));
			return (0);
		}
		ft_usleep(ph->config->time_to_eat);
		if (leave_forks(ph) == -1)
			return (die(ph->config));
	}
	return (0);
}

int	one_philo(t_config *config)
{
	if (print_thinking(&config->philos[0]) == -1)
		return (1);
	if (ft_usleep(config->time_to_die) == -1)
		return (1);
	if (print_dead(&config->philos[0]) == -1)
		return (1);
	return (0);
}

int	start_simulation(t_config *config)
{
	int	i;

	i = -1;
	config->start_time = get_time();
	if (config->start_time == -1)
		return (1);
	if (config->nb_philo == 1)
	{
		one_philo(config);
		return (0);
	}
	while (++i < config->nb_philo)
		if (pthread_create(&config->threads[i], NULL, &routine,
				&config->philos[i]) != 0)
			return (1);
	if (pthread_create(&config->threads[i], NULL, &check_deaths, config) != 0)
		return (1);
	if (pthread_create(&config->threads[i + 1], NULL, &did_everyone_eat_enough,
			config) != 0)
		return (1);
	i = -1;
	while (++i < config->nb_philo + 2)
		if (pthread_join(config->threads[i], NULL) != 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc >= 5 && argc <= 6)
	{
		if (init_config(&config, argc, argv) < 0)
			return (printerror(), 1);
		if (start_simulation(&config) != 0)
		{
			write(1, "error\n", 6);
			return (1);
		}
		if (end_simulation(&config) != 0)
		{
			write(1, "error\n", 6);
			return (1);
		}
	}
	return (0);
}
