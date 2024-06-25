
#include "../include/philo.h"

void	print_eating(t_philo *ph)
{
	printf("%ld %d is eating\n", get_time()
		- ph->config->start_time, ph->number);
}

void	print_dead(t_philo *ph)
{
	printf("%ld %d died\n", get_time() - ph->config->start_time,
		ph->number);
}

void	print_thinking(t_philo *ph)
{
	printf("%ld %d is thinking\n", get_time()
		- ph->config->start_time, ph->number);
}

void	print_sleeping(t_philo *ph)
{
	printf("%ld %d is sleeping\n", get_time()
		- ph->config->start_time, ph->number);
}

void	print_forks(t_philo *ph)
{
	printf("%ld %d has taken a fork\n", get_time()
		- ph->config->start_time, ph->number);
}
