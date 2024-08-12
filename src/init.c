/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:03 by mlapique          #+#    #+#             */
/*   Updated: 2024/07/14 17:16:26 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(t_config *config)
{
	int	i;

	i = 0;
	config->forks = malloc(sizeof(pthread_mutex_t) * config->nb_philo);
	if (config->forks == NULL)
		return (-1);
	while (i < config->nb_philo)
	{
		if (pthread_mutex_init(&config->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	init_philos(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philo)
	{
		config->philos[i].number = i + 1;
		config->philos[i].config = config;
		config->philos[i].eat_count = 0;
		config->philos[i].last_meal = -1;
		config->philos[i].left_fork = &config->forks[i];
		config->philos[i].right_fork = \
		&config->forks[(i + 1) % config->nb_philo];
		i++;
	}
}

int	init_config2(t_config *config)
{
	config->dead_rights = malloc(sizeof(pthread_mutex_t));
	config->meal_rights = malloc(sizeof(pthread_mutex_t));
	config->print_rights = malloc(sizeof(pthread_mutex_t));
	config->end_rights = malloc(sizeof(pthread_mutex_t));
	if (!config->dead_rights || !config->meal_rights || \
	!config->print_rights || !config->end_rights)
		return (-1);
	config->threads = malloc(sizeof(pthread_t) * (config->nb_philo + 2));
	if (config->threads == NULL)
		return (-1);
	config->philos = malloc(sizeof(t_philo) * config->nb_philo);
	if (pthread_mutex_init(config->print_rights, NULL) != 0 || \
	pthread_mutex_init(config->dead_rights, NULL) != 0 || \
	pthread_mutex_init(config->meal_rights, NULL) != 0 || \
	pthread_mutex_init(config->end_rights, NULL) != 0)
		return (-1);
	if (init_forks(config) == -1)
		return (free(config->threads), \
		free(config->philos), free(config->print_rights), -6);
	init_philos(config);
	return (0);
}

int	init_config(t_config *config, int argc, char **argv)
{
	config->nb_philo = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->has_diedened = 0;
	config->is_over = -1;
	if (argc > 6)
		return (-6);
	if (argc == 6)
		config->nb_eat = ft_atoi(argv[5]);
	else
		config->nb_eat = -1;
	if (config->nb_philo < 1 || config->time_to_die < 20 \
	|| config->time_to_eat < 20 || config->time_to_sleep < 20 \
	|| config->nb_philo > 210)
		return (-6);
	return (init_config2(config));
}
