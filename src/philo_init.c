/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:29:00 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 17:35:37 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_table *table)
{
	int		i;
	t_philo	*sopher;

	sopher = table->philos;
	sopher = malloc(sizeof(t_philo) * table->phi_nbr);
	table->forks = malloc(sizeof(t_fork) * table->phi_nbr);
	if (!sopher || !table->forks)
		return (-1);
	i = 0;
	while (i < table->phi_nbr)
	{
		sopher[i].id = i + 1;
		sopher[i].diner_counter = 0;
		sopher[i].full = false;
		sopher[i].last_meal_time = 0;
		sopher[i].left_fork = table->forks + i;
		sopher[i].right_fork = table->forks + ((i + 1) % table->phi_nbr);
		sopher[i].thread_id = 0;
		sopher[i].table = table;
		i++;
	}
	table->philos = sopher;
	return (0);
}

static int	init_forks(t_table *table)
{
	int		i;
	t_fork	*fork_list;

	fork_list = table->forks;
	i = 0;
	while (i < table->phi_nbr)
	{
		if (pthread_mutex_init(&fork_list[i].fork, NULL))
			return (-1);
		fork_list->fork_id = i + 1;
		i++;
	}
	table->forks = fork_list;
	return (0);
}

static int	init_threads(t_table *table)
{
	int		i;
	t_philo	*sopher;

	i = -1;
	sopher = table->philos;
	table->start_simulation = get_time();
	while (++i < table->phi_nbr)
	{
		if (pthread_create(&sopher[i].thread_id, NULL, dinner, &sopher[i]))
			return (-1);
	}
	table->philos = sopher;
	return (0);
}

int	data_init(t_table *table)
{
	if (init_philos(table))
		return (-1);
	if (init_forks(table))
		return (-1);
	if (init_threads(table))
		return (-1);
	return (0);
}

	// int	i = 0;
	// while (i < table->phi_nbr)
	// {
	// 	printf("philo: %d\nid:%d\ndiner_counter:%ld\nfull:%d\nlast_meal_time:%
	//		ld\nthread_id:%ld\ntable phi:\t%p\ntable:\t%p\n\n", i+1,
	// 		sopher[i].id, sopher[i].diner_counter, sopher[i].full, 
	//		sopher[i].last_meal_time, sopher[i].thread_id, sopher[i].table,
	//		table);
	// 	i++;
	// }
	// printf("time_to_die\t%ld\n", table->time_to_die);
	// printf("time_to_eat\t%ld\n", table->time_to_eat);
	// printf("time_to_sleep\t%ld\n", table->time_to_sleep);
	// printf("nbr_limit_meals\t%ld\n", table->nbr_limit_meals);
	// printf("start_simulation\t%ld\n", table->start_simulation);
	// printf("end_simulation\t%d\n", table->end_simulation);