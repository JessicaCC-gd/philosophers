/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:21:52 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 14:20:09 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_full(t_table *table)
{
	t_philo	*philo;
	int		i;
	int		ate;

	philo = table->philo_1;
	i = 0;
	ate = 0;
	while (i++ < table->n_phil)
	{
		pthread_mutex_lock(philo->body_guard);
		if (philo->eaten >= table->n_eat && table->n_eat > 0)
			ate++;
		pthread_mutex_unlock(philo->body_guard);
		philo = philo->next;
	}
	return (ate);
}

void	reaping(t_table *table, t_philo *philo, size_t time)
{
	pthread_mutex_lock(table->body_guard);
	table->reaped_souls += 1;
	pthread_mutex_unlock(table->body_guard);
	pthread_mutex_lock(table->writer_bg);
	printf("%ld %d died\n", time - table->s_time, philo->id);
	pthread_mutex_unlock(table->writer_bg);
}

void	all_full(t_table *table)
{
	pthread_mutex_lock(table->body_guard);
	table->all_full = 1;
	pthread_mutex_unlock(table->body_guard);
}

t_philo	*next_philo(t_philo *philo)
{
	pthread_mutex_unlock(philo->body_guard);
	return (philo->next);
}

void	*grim_reaper(t_table *table)
{
	t_philo	*philo;
	size_t	time;
	int		full;

	philo = table->philo_1;
	while (1)
	{
		full = check_all_full(table);
		time = get_time();
		pthread_mutex_lock(philo->body_guard);
		if (full == table->n_phil 
			|| time - philo->hunger_c > (size_t)table->t_die)
		{
			if (full != table->n_phil)
				reaping(table, philo, time);
			else
				all_full(table);
			pthread_mutex_unlock(philo->body_guard);
			return (NULL);
		}
		else
			philo = next_philo(philo);
	}
	return (NULL);
}
