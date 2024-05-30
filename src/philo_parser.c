/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbessa <dbessa@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:01:23 by dbessa            #+#    #+#             */
/*   Updated: 2024/05/30 15:27:18 by dbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	handle_overflow(long res, char nptr, long sign)
{
	if (res > LONG_MAX / 10 || (res == LONG_MAX / 10 && nptr - '0' > \
		LONG_MAX % 10))
	{
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	return (0);
}

static long	ft_atol(const char *nptr)
{
	int		i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || (nptr[i] == ' '))
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i + 1] == '-' || nptr[i +1] == '+')
			return (0);
		else if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (handle_overflow(res, nptr[i], sign) != 0)
			return (handle_overflow(res, nptr[i], sign));
		res = (res * 10) + (nptr[i++] - '0');
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

void	validate_input(char **av)
{
	int	j;
	int	check;

	check = 1;
	while (av[check] != NULL)
	{
		j = 0;
		while (av[check][j] != '\0')
		{
			if (!ft_isdigit(av[check][j]))
			{
				printf("%s\n", av[check]);
				error_exit("🚨 Only digits are acceptable\n"
					GREEN"Correct is ./philo 5 800 200 200 [5]\n" RST);
			}
			j++;
		}
		check++;
	}
}

void	parse_input(t_table *table, char **av)
{
	struct timeval	time;

	validate_input(av);
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->nbr_limit_meals = -1;
	if (av[5] != NULL)
		table->nbr_limit_meals = ft_atol(av[5]);
	gettimeofday(&time, NULL);
	table->start_simulation = time.tv_usec;
}
