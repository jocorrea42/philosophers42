/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:01:38 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/24 14:00:29 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	return (pthread_mutex_unlock(philo->dead_lock), 0);
}

int	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	return (pthread_mutex_unlock(philo->meal_lock), 0);
}

void	*philo_task(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_alive(philo))
	{
		eat(philo);
		dream(philo);
		think(*philo);
	}
	return (pointer);
}

int	create_threads(t_program *prog)
{
	int			i;
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &monitor, prog) != 0)
		destroy_all("Thread creation error", prog);
	i = -1;
	while (++i < prog->nphilos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, &philo_task,
				&prog->philos[i]) != 0)
			destroy_all("Thread creation error", prog);
	}
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", prog);
	i = -1;
	while (++i < prog->nphilos)
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", prog);
	return (0);
}
