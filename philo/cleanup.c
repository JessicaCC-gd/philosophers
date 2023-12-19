/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:42:11 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 16:33:46 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_philo	*clean_leftovers(t_philo *philo)
{
	t_philo	*tmp;

	pthread_mutex_destroy(philo->fork);
	free(philo->fork);
	free (philo->body_guard);
	tmp = philo;
	philo = philo->next;
	free(tmp);
	return (philo);
}

void	clean_table(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = table->philo_1;
	i = 0;
	while (i++ < table->n_phil && philo)
	{
		if (philo->right == 1)
		{
			pthread_mutex_unlock(philo->fork);
			philo->right = 0;
		}
		if (philo->left == 1)
		{
			pthread_mutex_unlock(philo->next->fork);
			philo->left = 0;
		}
		philo = clean_leftovers(philo);
	}
	free(table->body_guard);
}

void	join_threads(t_table *table)
{
	t_philo	*phi;
	int		i;

	phi = table->philo_1;
	i = 0;
	while (i++ < table->n_phil)
	{
		pthread_join(phi->thread_id, NULL);
		phi = phi->next;
	}
}
