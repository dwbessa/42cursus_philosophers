/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:29:51 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 22:38:56 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_all_full(t_philo *philo)
{
	int		i;
	t_bool	ret;

	i = -1;
	ret = false;
	while (++i < philo->table->phi_nbr)
	{
		if (philo[i].full == true)
			ret = true;
		else
			return (false);
	}
	return (ret);
}

int	check_life(t_table *table)
{
	long	now;
	t_philo	*philo;

	philo = table->philos;
	pthread_mutex_lock(&table->mutex);
	now = get_time() - table->start_simulation - philo->last_meal_time;
	pthread_mutex_unlock(&table->mutex);
	if (now > table->time_to_die)
	{
		pthread_mutex_lock(&table->mutex);
		table->end_simulation = true;
		pthread_mutex_unlock(&table->mutex);
		if (!is_all_full(table->philos))
			print_status(philo, DEAD);
		return (-1);
	}
	return (0);
}

void	*dinner(void *arg)
{
	t_table	*tab;
	t_philo	*phi;

	phi = (t_philo *)arg;
	tab = phi->table;
	wait_all_threads(tab);
	synchro_philos(phi);
	pthread_mutex_lock(&tab->mutex);
	while (!tab->end_simulation && !phi->full && !is_all_full(phi))
	{
		pthread_mutex_unlock(&tab->mutex);
		eat(phi);
		nap(phi);
		think(phi);
		pthread_mutex_lock(&tab->mutex);
	}
	pthread_mutex_unlock(&tab->mutex);
	return (0);
}

void	*mr_lonely(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->table->mutex);
	while (philo->table->end_simulation)
		usleep(300);
	pthread_mutex_unlock(&philo->table->mutex);
	return (NULL);
}

void	lone_philo(t_table *table)
{
	t_philo	*philo;

	philo = table->philos;
	pthread_create(&philo[0].thread_id, NULL, mr_lonely, &philo[0]);
	monitor_threads(table);
}
