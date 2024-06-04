/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:29:51 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/04 12:05:45 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_start(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = table->philos;
	set_bool(table, &table->threads_ready, true);
	if (table->nbr_limit_meals == 0)
		return (0);
	else if (table->phi_nbr == 1)
	{
		lone_philo(table);
		return (0);
	}
	monitor_threads(table);
	while (++i < table->phi_nbr)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (-1);
	}
	return (0);
}

void	set_bool(t_table *table, t_bool *dest, t_bool value)
{
	pthread_mutex_lock(&table->mutex);
	*dest = value;
	pthread_mutex_unlock(&table->mutex);
}

t_bool	get_bool(t_table *table, t_bool *value)
{
	t_bool	ret;

	pthread_mutex_lock(&table->mutex);
	ret = *value;
	pthread_mutex_unlock(&table->mutex);
	return (ret);
}

void	wait_all_threads(t_table *table)
{
	while (get_bool(table, &table->threads_ready))
		;
}

void	synchro_philos(t_philo *philo)
{
	if (philo->table->phi_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			smart_usleep(philo->table, 3e4);
	}
	else
	{
		if (philo->id % 2)
			think(philo);
	}
}
