
#include "../include/philo.h"

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->last_meal = get_time();
	pthread_create(&ph->monitor, NULL, &check_deaths, ph->config);
	pthread_detach(ph->monitor);
	if (ph->number % 2 == 0)
		ft_usleep(1);
	while (!ph->config->has_diedened && !did_everyone_eat_enough(ph->config))
	{
		print_thinking(ph);
		take_forks(ph);
		print_eating(ph);
		ph->last_meal = get_time();
		ft_usleep(ph->config->time_to_eat - 5);
		leave_forks(ph);
	}
	return (NULL);
}

void	one_philo(t_config *config)
{
	print_thinking(&config->philos[0]);
	ft_usleep(config->time_to_die);
	print_dead(&config->philos[0]);
}

void	start_simulation(t_config *config)
{
	int			i;

	i = 0;
	config->start_time = get_time();
	if (config->start_time == -1)
		return ;
	if (config->nb_philo == 1)
		return (one_philo(config));
	while (i < config->nb_philo)
	{
		pthread_create(&config->threads[i], NULL, &routine, &config->philos[i]);
		i++;
	}
	config->start_time = get_time();
	i = 0;
	while (i < config->nb_philo)
	{
		pthread_join(config->threads[i], NULL);
		i++;
	}
}

void	end_simulation(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philo)
	{
		pthread_mutex_destroy(&config->forks[i]);
		i++;
	}
	if (config->forks)
		free(config->forks);
	if (config->threads)
		free(config->threads);
	if (config->philos)
		free(config->philos);
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			error;

	error = 0;
	if (argc >= 5 || argc <= 6)
		if (!verif_argv(argv, argc))
			return (printerror());
	init_config(&config, argc, argv);
	if (error < 0)
		return (-6);
	start_simulation(&config);
	if (error < 0)
		return (-6);
	end_simulation(&config);
	if (error < 0)
		return (-6);
	return (0);
}
