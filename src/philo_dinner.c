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
	if (tab->phi_nbr % 2 != 0 && phi->id == tab->phi_nbr)
		usleep(200000);
	if (phi->id % 2 == 0)
		usleep(150000);
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

int	dinner_start(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = table->philos;
	monitor_threads(table);
	while (i < table->phi_nbr)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (-1);
		i++;
	}
	return (0);
}
