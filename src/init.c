/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:03 by mlapique          #+#    #+#             */
/*   Updated: 2024/08/13 14:41:48 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_config *config)
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
	if (pthread_mutex_init(config->dead_rights, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(config->end_rights, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(config->print_rights, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(config->meal_rights, NULL) != 0)
		return (-1);
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

int	init_config3(t_config *config)
{
	config->dead_rights = malloc(sizeof(pthread_mutex_t));
	if (!config->dead_rights)
		return (-1);
	config->meal_rights = malloc(sizeof(pthread_mutex_t));
	if (!config->meal_rights)
		return (free(config->dead_rights), -1);
	config->print_rights = malloc(sizeof(pthread_mutex_t));
	if (!config->print_rights)
		return (free(config->dead_rights), free(config->meal_rights), -1);
	config->end_rights = malloc(sizeof(pthread_mutex_t));
	if (!config->end_rights)
		return (free(config->dead_rights), free(config->meal_rights), \
		free(config->print_rights), -1);
	config->threads = malloc(sizeof(pthread_t) * (config->nb_philo + 2));
	if (config->threads == NULL)
		return (free(config->dead_rights), free(config->meal_rights), \
		free(config->end_rights), free(config->print_rights), -1);
	config->philos = malloc(sizeof(t_philo) * config->nb_philo);
	if (config->philos == NULL)
		return (free(config->dead_rights), free(config->meal_rights), \
		free(config->end_rights), free(config->print_rights), \
		free(config->threads), -1);
	return (0);
}

int	init_config2(t_config *config)
{
	if (init_config3(config) != 0)
		return (-1);
	if (init_mutex(config) == -1)
		return (free(config->dead_rights), free(config->meal_rights), \
		free(config->end_rights), free(config->print_rights), \
		free(config->threads), free(config->philos), -1);
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
	if (config->nb_philo < 1 || config->time_to_die < 10 \
	|| config->time_to_eat < 10 || config->time_to_sleep < 10 \
	|| config->nb_philo > 210)
		return (-6);
	return (init_config2(config));
}
