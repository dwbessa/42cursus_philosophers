/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:01:23 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/04 12:29:02 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_diff(long past, long pres)
{
	return ((pres - past) * 1000);
}

void	smart_usleep(t_table *t, long time)
{
	long	past;

	past = (get_time() - t->start_simulation);
	while (!get_bool(t, &t->end_simulation))
	{
		if (time_diff(past, (get_time() - t->start_simulation)) >= time)
			break ;
		usleep(1000);
	}
}

void	error_exit(const char *error_msg)
{
	printf(RED"%s\n"RST, error_msg);
	exit(EXIT_FAILURE);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, t_status status)
{
	long	now;

	pthread_mutex_lock(&philo->table->print_mtx);
	now = get_time() - philo->table->start_simulation;
	if (status == DEAD)
		printf(RED"%ld\t%d died\n"RST, now, philo->id);
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->end_simulation)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		pthread_mutex_unlock(&philo->table->print_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mutex);
	if (status == SLEEP)
		printf("%ld\t%d is sleeping\n", now, philo->id);
	if (status == FORK)
		printf("%ld\t%d has taken a fork\n", now, philo->id);
	if (status == EAT)
		printf(GREEN"%ld\t%d is eating\n"RST, now, philo->id);
	if (status == THINK)
		printf("%ld\t%d is thinking\n", now, philo->id);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
