/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:02:43 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 19:14:37 by dbessa           ###   ########.fr       */
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
