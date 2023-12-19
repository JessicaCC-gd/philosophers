/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:29:20 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 17:43:24 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	convert_num(char *str, int i)
{
	long long int	num;

	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] || num > 2147483647)
		return (-1);
	return (num);
}

int	atoi_check(char *str)
{
	int	i;
	int	pluses;
	int	minuses;

	i = 0;
	minuses = 0;
	pluses = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+')
			pluses++;
		else
			minuses++;
		if (minuses > 0 || pluses > 1)
			return (-1);
		i++;
	}
	if (!str[i] || !(str[i] > 47 && str[i] < 58))
		return (-1);
	return (convert_num(str, i));
}

void	save_values(char **argv, t_table *table)
{
	table->n_phil = atoi_check(argv[1]);
	table->t_die = atoi_check(argv[2]);
	table->t_eat = atoi_check(argv[3]);
	table->t_sleep = atoi_check(argv[4]);
	if (argv[5])
		table->n_eat = atoi_check (argv[5]);
	table->dif = table->t_eat - table->t_sleep;
}

int	check_values(t_table *table, int argc)
{
	int	inv;

	inv = 0;
	if (table->n_phil < 1 || table->t_die < 0
		|| table->t_eat < 0 || table->t_sleep < 0)
		inv++;
	if (argc == 5)
		table->n_eat = -1;
	else
	 	if (table->n_eat < 1)
			inv++;
	return (inv);
}
