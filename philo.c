/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:59:37 by dbessa            #+#    #+#             */
/*   Updated: 2024/05/23 21:14:20 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5)
	{
		//✅ correct input
		//1) errors checking
		parse_input(&table, av);

		//2) creating the thing
		data_init(&table);
		
		//3) the dinner
		dinner_start(&table);

		//4) No leaks
		clean(&table);
	}
	else
	{
		error_exit("🚨 Wrong number of arguments\n"
			GREEN"Correct is ./philo 5 800 200 200 [5]"RST);
	}
}

