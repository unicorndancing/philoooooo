/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:10 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/04 16:59:39 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	everyone_has_eaten(t_config *config)
{
	pthread_mutex_lock(config->print_rights);
	pthread_mutex_lock(config->end_rights);
	printf("everybody ate\n");
	config->is_over = 1;
	pthread_mutex_unlock(config->end_rights);
	pthread_mutex_unlock(config->print_rights);
	return (0);
}

void	*did_everyone_eat_enough(void *void_config)
{
	int			i;
	t_config	*config;

	config = void_config;
	i = 0;
	if (config->nb_eat == -1)
		return (0);
	while (1 && get_wellbeing(config->philos) == 1)
	{	
		ft_usleep(1);
		pthread_mutex_lock(config->meal_rights);
		if (config->philos[i].eat_count < config->nb_eat)
			i = 0;
		pthread_mutex_unlock(config->meal_rights);
		if (i == config->nb_philo - 1)
		{
			everyone_has_eaten(config);
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	result;

	i = 0;
	negative = 1;
	result = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		negative *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * negative);
}

int	in_death(t_config *config, int i)
{
	pthread_mutex_lock(config->print_rights);
	pthread_mutex_lock(config->dead_rights);
	print_dead(&config->philos[i]);
	config->has_diedened = 1;
	pthread_mutex_unlock(config->print_rights);
	pthread_mutex_unlock(config->dead_rights);
	pthread_mutex_unlock(config->meal_rights);
	return (0);
}

void	*check_deaths(void *void_config)
{
	int			i;
	t_config	*config;

	i = 0;
	config = (t_config *)void_config;
	while (1 && get_wellbeing(config->philos) == 1)
	{
		ft_usleep(1);
		pthread_mutex_lock(config->meal_rights);
		if (config->philos[i].last_meal != -1 && get_time()
			- config->philos[i].last_meal > config->time_to_die
			&& (config->philos[i].eat_count < config->nb_eat
				|| config->nb_eat == -1))
		{
			in_death(config, i);
			return (0);
		}
		pthread_mutex_unlock(config->meal_rights);
		i = (i + 1) % config->nb_philo;
	}
	return (0);
}
