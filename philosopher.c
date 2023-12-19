/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:56:56 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 15:54:06 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	size_t	beg;

	beg = *(philo->beg);
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->table->writer_bg);
	printf("%ld %d is sleeping\n", get_time() - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	if (check_end(philo))
		return (1);
	usleep(philo->table->t_sleep * 1000);
	return (0);
}

int	think(t_philo *philo)
{
	size_t	beg;

	beg = *(philo->beg);
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->table->writer_bg);
	printf("%ld %d is thinking\n", get_time() - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	return (0);
}

void	philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->body_guard);
	philo->hunger_c = get_time();
	while (1)
	{
		pthread_mutex_unlock(philo->body_guard);
		if (grab_forks(philo))
			return ;
		if (eat(philo))
			return ;
		if (sleeping(philo))
			return ;
		if (think(philo))
			return ;
		if (check_end(philo))
			return ;
		pthread_mutex_lock(philo->body_guard);
	}
	pthread_mutex_unlock(philo->body_guard);
	return ;
}
