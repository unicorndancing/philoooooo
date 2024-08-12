/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:18:05 by mlapique          #+#    #+#             */
/*   Updated: 2024/07/14 17:16:16 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	printerror(void)
{
	printf("write that you please: ./philo\
	\n[number_of_philosophers] not more than 200 please\
	\n[time_to_die] not under 10 please\
	\n[time_to_spageteat] not under 10 please\
	\n[time_to_sleep] not under 10 please\
	\n[number_of_time_each_philosophers_must_spageteat], this one is optional,\
	they just gonna suffer for an eternity without it\n");
	return (-1);
}

int	ft_usleep(int ms)
{
	long int	start_time;
	long int	time;

	start_time = get_time();
	while (1)
	{
		usleep(1);
		time = get_time();
		if (time == -1)
			return (-1);
		if (time - start_time >= ms)
			return (0);
	}
	return (0);
}
