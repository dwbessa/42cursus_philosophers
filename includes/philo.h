/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:48:12 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/04 11:38:03 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define CYAN	"\x1b[36m"
# define RST	"\x1b[0m"
# define BLINK	"\033[5m"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_bool
{
	false = 0,
	true = 1,
}	t_bool;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	long		diner_counter;
	long		last_meal_time;
	t_bool		full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

struct s_table
{
	long	phi_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	t_bool	threads_ready;
	t_bool	end_simulation;
	t_fork	*forks;
	t_mtx	mutex;
	t_mtx	print_mtx;
	t_philo	*philos;
};

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DEAD
}	t_status;

void	error_exit(const char *error_msg);
void	parse_input(t_table *table, char **av);
int		data_init(t_table *table);
long	get_time(void);
void	*dinner(void *table);
long	clean(t_table *table);
void	print_status(t_philo *philo, t_status status);
int		dinner_start(t_table *table);
int		check_life(t_table *table);
void	eat(t_philo *philo);
void	nap(t_philo *philo);
void	think(t_philo *philo);
void	monitor_threads(t_table *table);
void	precise_usleep(long usec, t_table *table);
void	lone_philo(t_table *table);
t_bool	is_all_full(t_philo *philo);
t_bool	get_bool(t_table *table, t_bool *value);
void	set_bool(t_table *table, t_bool *dest, t_bool value);
void	synchro_philos(t_philo *philo);
void	wait_all_threads(t_table *table);
void	smart_usleep(t_table *t, long time);

#endif
