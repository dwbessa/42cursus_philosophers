/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:59:37 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 22:36:16 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	pthread_mutex_init(&table.print_mtx, NULL);
	pthread_mutex_init(&table.mutex, NULL);
	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit(BLINK"🚨 Wrong number of arguments\n" RST
			GREEN"Correct is ./philo 5 800 200 200 [5]\n" RST);
	return (0);
}

void	monitor_threads(t_table *table)
{
	int		i;
	t_bool	dinner;

	dinner = true;
	while (dinner && !table->end_simulation)
	{
		i = -1;
		while (++i < table->phi_nbr)
		{
			if (check_life(table))
			{
				dinner = false;
				pthread_mutex_lock(&table->mutex);
				table->end_simulation = true;
				pthread_mutex_unlock(&table->mutex);
				break ;
			}
		}
		usleep(1000);
	}
}
