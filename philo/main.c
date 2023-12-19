/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:43:01 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 17:44:24 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	check_end(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->table->body_guard);
	if (philo->table->reaped_souls > 0 || philo->table->all_full)
		flag = 1;
	pthread_mutex_unlock(philo->table->body_guard);
	if (flag)
	{
		if (philo->right == 1)
		{
			pthread_mutex_unlock(philo->fork);
			philo->right = 0;
		}
		if (philo->left)
		{
			pthread_mutex_unlock(philo->next->fork);
			philo->left = 0;
		}
	}
	return (flag);
}

void	run_sim(t_table *table)
{
	t_philo		*phi;
	pthread_t	reaper;
	int			i;

	phi = table->philo_1;
	i = 0;
	table->s_time = get_time();
	while (i++ < table->n_phil)
	{
		pthread_create(&phi->thread_id, NULL, (void *)philosopher, phi);
		phi = phi->next;
	}
	pthread_create(&reaper, NULL, (void *)grim_reaper, table);
	pthread_join(reaper, NULL);
	join_threads(table);
	clean_table(table);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		inv_args;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid Argument(s)\n");
		return (0);
	}
	table = (t_table){0};
	save_values(argv, &table);
	inv_args = check_values(&table, argc);
	if (inv_args)
	{
		printf("Invalid Argument(s)\n");
		return (0);
	}
	table.body_guard = malloc(sizeof(pthread_mutex_t));
	table.writer_bg = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table.body_guard, NULL);
	pthread_mutex_init(table.writer_bg, NULL);
	philosopher_birth(&table);
	run_sim(&table);
	free(table.writer_bg);
	return (0);
}
