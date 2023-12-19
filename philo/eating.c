/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:25:46 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 17:48:23 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	odd_philo(t_philo *philo)
{
	size_t	beg;

	beg = *(philo->beg);
	pthread_mutex_lock(philo->fork);
	philo->right = 1;
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->table->writer_bg);
	printf("%ld %d has taken a fork\n", get_time() - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	if (philo->table->n_phil == 1)
		return (1);
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->next->fork);
	philo->left = 1;
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->table->writer_bg);
	printf("%ld %d has taken a fork\n", get_time() - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	return (0);
}

int	even_philo(t_philo *philo)
{
	size_t	beg;

	beg = *(philo->beg);
	pthread_mutex_lock(philo->next->fork);
	philo->left = 1;
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->table->writer_bg);
	printf("%ld %d has taken a fork\n", get_time() - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->fork);
	philo->right = 1;
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(philo->table->writer_bg);
	printf("%ld %d has taken a fork\n", get_time() - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	return (0);
}

int	grab_forks(t_philo *philo)
{
	if (check_end(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		if (even_philo(philo))
			return (1);
	}
	else
	{
		if (philo->table->n_phil % 2 == 1 && philo->table->dif >= 0)
			usleep((philo->table->dif + 10) * 1000);
		if (odd_philo(philo))
			return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	size_t	beg;

	if (check_end(philo))
		return (1);
	beg = *(philo->beg);
	pthread_mutex_lock(philo->body_guard);
	pthread_mutex_lock(philo->table->writer_bg);
	philo->hunger_c = get_time();
	printf("%ld %d is eating\n", philo->hunger_c - beg, philo->id);
	pthread_mutex_unlock(philo->table->writer_bg);
	pthread_mutex_unlock(philo->body_guard);
	usleep(philo->table->t_eat * 1000);
	pthread_mutex_lock(philo->body_guard);
	philo->eaten += 1;
	pthread_mutex_unlock(philo->body_guard);
	pthread_mutex_unlock(philo->fork);
	philo->right = 0;
	pthread_mutex_unlock(philo->next->fork);
	philo->left = 0;
	return (0);
}
