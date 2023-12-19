/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midwife.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:33:56 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 16:16:55 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_birth(t_table *table, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->fork, NULL);
	philo->body_guard = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->body_guard, NULL);
	philo->id = i;
	philo->eaten = 0;
	philo->hunger_c = 0;
	philo->right = 0;
	philo->left = 0;
	philo->beg = &table->s_time;
	philo->next = NULL;
	philo->previous = NULL;
	philo->table = table;
	return (philo);
}

void	philosopher_birth(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philo_1 = new_birth(table, 1);
	philo = table->philo_1;
	i = 2;
	if (table->n_phil > 1)
	{
		while (i <= table->n_phil)
		{
			philo->next = new_birth(table, i++);
			philo->next->previous = philo;
			philo = philo->next;
		}
		table->philo_1->previous = philo;
		philo->next = table->philo_1;
	}
	else
		philo->next = philo;
}
