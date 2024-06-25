
#include "../include/philo.h"

void	init_forks(t_config *config, int i)
{
	while (i < config->nb_philo)
	{
		pthread_mutex_init(&config->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_config *config, int i)
{
	while (i < config->nb_philo)
	{
		config->philos[i].number = i + 1;
		config->philos[i].config = config;
		config->philos[i].eat_count = 0;
		config->philos[i].last_meal = -1;
		config->philos[i].left_fork = &config->forks[i];
		config->philos[i].right_fork = &config->forks[(i + 1) % config->nb_philo];
		i++;
	}
}

void	init_config(t_config *config, int argc, char **argv)
{
	int	i;

	i = 0;
	config->nb_philo = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->has_diedened = 0;
	if (argc == 6)
		config->nb_eat = ft_atoi(argv[5]);
	else
		config->nb_eat = -1;
	config->threads = malloc(sizeof(pthread_t) * config->nb_philo);
	config->forks = malloc(sizeof(pthread_mutex_t) * config->nb_philo);
	config->philos = malloc(sizeof(t_philo) * config->nb_philo);
	init_philos(config, i);
	i = 0;
	init_forks(config, i);
}
