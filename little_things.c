
#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	printerror(void)
{
	printf("write that you dumdum: ./philo \
	\n[number_of_philosophers]\
	\n[time_to_liven't]\
	\n[time_to_spagetthis]\
	\n[time_to_snorlaxing]\
	\n[number_of_time_each_philosophers_must_spagetthis], this one is optional,\
	they just gonna suffer for an eternity without it\n");
	return(-1);
}

void	ft_usleep(int ms)
{
	/*if (*/!usleep(ms * 10 * 10 * 10 * 10 / 10);//)
		//error = -1;
}
