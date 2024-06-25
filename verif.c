
#include "../include/philo.h"

int	did_everyone_eat_enough(t_config *config)
{
	int	i;

	i = 0;
	if (config->nb_eat == -1)
		return (0);
	while (i < config->nb_philo)
	{
		if (config->philos[i].eat_count < config->nb_eat)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	result;

	i = 0;
	negative = 1;
	result = 0;
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

int	verif_argv(char **argv, int argc)
{
	char	*str;
	int	i;
	int j;

	j = 1;
	i = 0;
	while (j < argc)
	{
		str = argv[j];
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '-')
			return (0);
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		if (str[i] == '\0')
			break ;
		else
			return (0);
		j++;
		i = 0;
	}
	return (1);
}

void	*check_deaths(void *void_config)
{
	int		i;
	t_config	*config;

	i = 0;
	config = (t_config *)void_config;
	while (1)
	{
		if (did_everyone_eat_enough(config))
			break ;
		if (get_time() - config->philos[i].last_meal > config->time_to_die
			&& config->philos[i].last_meal != -1
			&& (config->philos[i].eat_count < config->nb_eat
				|| config->nb_eat == -1))
		{
			print_dead(&config->philos[i]);
			config->has_diedened = 1;
			exit(55);
		}
		i = (i + 1) % config->nb_philo;
	}
	return (0);
}
