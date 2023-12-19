/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:38:42 by jecarval          #+#    #+#             */
/*   Updated: 2023/11/29 17:44:17 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	size_t			hunger_c;
	int				eaten;
	int				right;
	int				left;
	size_t			*beg;
	pthread_mutex_t	*body_guard;
	pthread_mutex_t	*fork;
	pthread_t		thread_id;
	struct s_philo	*previous;
	struct s_philo	*next;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				n_phil;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				dif;
	size_t			s_time;
	int				reaped_souls;
	int				all_full;
	pthread_mutex_t	*writer_bg;
	pthread_mutex_t	*body_guard;
	struct s_philo	*philo_1;
}	t_table;

void	save_values(char **argv, t_table *table);
int		check_values(t_table *table, int argc);

void	philosopher_birth(t_table *table);

void	philosopher(t_philo *philo);
int		eat(t_philo *philo);
int		grab_forks(t_philo *philo);
int		check_end(t_philo *philo);

size_t	get_time(void);

void	clean_table(t_table *table);
void	join_threads(t_table *table);

void	writer(size_t time, int id, char c, t_table *table);

void	*grim_reaper(t_table *table);

#endif
