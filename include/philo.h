/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:47:07 by mlapique          #+#    #+#             */
/*   Updated: 2024/08/12 14:12:08 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BLACK "\033[0;30m" 
# define RED "\033[0;31m"
# define GREEN "\033[0;32m" 
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m" 
# define PURPLE "\033[0;35m"
# define CYANUS "\033[0;36m"
# define WHITE "\033[0;37m"

struct	s_philo;

typedef struct s_config
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start_time;
	int				has_diedened;
	int				is_over;
	pthread_mutex_t	*print_rights;
	pthread_mutex_t	*time;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead_rights;
	pthread_mutex_t	*meal_rights;
	pthread_mutex_t	*end_rights;
	struct s_philo	*philos;
}					t_config;

typedef struct s_philo
{
	int				number;
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*stop_mf;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_config		*config;
	pthread_t		monitor;
}					t_philo;

// actions.c
int					take_forks(t_philo *ph);
int					go_to_sleep(t_philo *ph);
int					leave_forks(t_philo *ph);

// verifsc
void				*did_everyone_eat_enough(void *void_config);
int					ft_atoi(const char *str);
int					verif_argv(char **argv, int argc);
void				*check_deaths(void *void_table);

// init.c
int					init_forks(t_config *config);
void				init_philos(t_config *config);
int					init_config(t_config *config, int argc, char **argv);

// littlethings.c
long int			get_time(void);
int					chrono(t_philo *ph);
int					printerror(void);
int					ft_usleep(int ms);

// aff.c
int					print_eating(t_philo *ph);
int					print_dead(t_philo *ph);
int					print_thinking(t_philo *ph);
int					print_sleeping(t_philo *ph);
int					print_forks(t_philo *ph);

// verif_mutexes 
long int			meal_time(t_philo *ph);
int					get_wellbeing(t_philo *ph);
int					end_simulation(t_config *config);
void				*die(t_config *config);

#endif