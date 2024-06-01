/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:59:37 by dbessa            #+#    #+#             */
/*   Updated: 2024/06/01 13:44:24 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_table	table;
	t_bool	dinner;

	i = -1;
	dinner = true;
	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		while (dinner && !table.end_simulation)
		{
			i = -1;
			while (++i < table.phi_nbr)
			{
				if (check_life(table.philos[i], &table))
				{
					dinner = false;
					return (0);
				}
			}
			usleep(1000);
		}
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit(BLINK"🚨 Wrong number of arguments\n" RST
			GREEN"Correct is ./philo 5 800 200 200 [5]\n" RST);
	}
}
