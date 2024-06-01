/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:29:51 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 13:33:55 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->right_fork->fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->diner_counter++;
	if (philo->diner_counter == philo->table->nbr_limit_meals)
		philo->full = true;
	philo->last_meal_time = get_time() - philo->table->start_simulation;
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	nap(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK);
}

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

int	check_life(t_philo philo, t_table *table)
{
	long	now;

	now = get_time() - table->start_simulation;
	if (now - philo.last_meal_time > table->time_to_die)
	{
		table->end_simulation = true;
		if (!is_all_full(table->philos))
			print_status(&philo, DEAD);
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
	while (!tab->end_simulation && !phi->full && !is_all_full(phi))
	{
		eat(phi);
		nap(phi);
		think(phi);
	}
	return (0);
}

int	dinner_start(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = table->philos;
	while (i < table->phi_nbr)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (-1);
		i++;
	}
	return (0);
}
