/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:01:23 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 16:52:46 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error_msg)
{
	printf(RED "%s\n" RST, error_msg);
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

	now = get_time() - philo->table->start_simulation;
	if (status == DEAD)
		printf(RED"%ld %d died\n"RST, now, philo->id);
	if (philo->table->end_simulation)
		return ;
	if (status == SLEEP)
		printf("%ld %d is sleeping\n", now, philo->id);
	if (status == FORK)
		printf("%ld %d has taken a fork\n", now, philo->id);
	if (status == EAT)
		printf("%ld %d is eating\n", now, philo->id);
	if (status == THINK)
		printf("%ld %d is thinking\n", now, philo->id);
}
