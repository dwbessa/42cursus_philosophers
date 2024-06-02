/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:29:17 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 20:49:34 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	clean(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = -1;
	philo = table->philos;
	fork = table->forks;
	while (++i < table->phi_nbr)
	{
		pthread_mutex_destroy(&fork[i].fork);
	}
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->mutex);
	free(philo);
	free(fork);
	return (table->phi_nbr);
}
