/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:02:43 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/04 12:24:44 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	define_forks(t_fork **first_fork, t_fork **second_fork, t_philo *philo)
{
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

void	eat(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	define_forks(&first_fork, &second_fork, philo);
	pthread_mutex_lock(&first_fork->fork);
	print_status(philo, FORK);
	pthread_mutex_lock(&second_fork->fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	pthread_mutex_lock(&philo->table->mutex);
	philo->diner_counter++;
	pthread_mutex_unlock(&philo->table->mutex);
	if (philo->diner_counter == philo->table->nbr_limit_meals)
		philo->full = true;
	pthread_mutex_lock(&philo->table->mutex);
	philo->last_meal_time = get_time() - philo->table->start_simulation;
	pthread_mutex_unlock(&philo->table->mutex);
	smart_usleep(philo->table, (philo->table->time_to_eat));
	pthread_mutex_unlock(&first_fork->fork);
	pthread_mutex_unlock(&second_fork->fork);
}

void	nap(t_philo *philo)
{
	print_status(philo, SLEEP);
	smart_usleep(philo->table, philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK);
}
