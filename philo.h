
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_philo;

typedef struct s_config
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start_time;
	int				has_diedened;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}					t_config;

typedef struct s_philo
{
	int				number;
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_config		*config;
	pthread_t		monitor;
}					t_philo;

// actions.c
void				take_forks(t_philo *ph);
void				go_to_sleep(t_philo *ph);
void				leave_forks(t_philo *ph);

// checks.c
int				did_everyone_eat_enough(t_config *config);
int					ft_atoi(const char *str);
int				verif_argv(char **argv, int argc);
void				*check_deaths(void *void_table);

// init.c
void				init_forks(t_config *config, int i);
void				init_philos(t_config *config, int i);
void				init_config(t_config *config, int ac, char **av);

// miscellaneous.c
long				get_time(void);
int					chrono(t_philo *ph);
int	printerror(void);
void				ft_usleep(int ms);

// status.c
void				print_eating(t_philo *ph);
void				print_dead(t_philo *ph);
void				print_thinking(t_philo *ph);
void				print_sleeping(t_philo *ph);
void				print_forks(t_philo *ph);

#endif
