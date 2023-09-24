/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:01:38 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/17 16:21:21 by jocorrea         ###   ########.fr       */
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

void	*philo_task(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_sleep(1);
	while (!is_alive(philo))
	{
		eat(philo);
		dream(philo);
		think(*philo);
	}
	return (pointer);
}


int	philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	return (pthread_mutex_unlock(philo->meal_lock), 0);
}

int	check_if_dead(t_program *prog)
{
	int	i;

	i = -1;
	while (++i < prog->num_philos)
	{
		if (philosopher_dead(&prog->philos[i]))
		{
			print_message("died", &prog->philos[i]);
			pthread_mutex_lock(&prog->dead_lock);
			prog->is_dead = 1;
			pthread_mutex_unlock(&prog->dead_lock);
			return (1);
		}
	}
	return (0);
}

int	check_if_all_ate(t_program *prog)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	if (prog->num_time_eat == -1)
		return (0);
	while (++i < prog->num_philos)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (prog->philos[i].meal_eaten >= prog->num_time_eat)
			finished_eating++;
		pthread_mutex_unlock(&prog->meal_lock);
	}
	if (finished_eating == prog->num_philos)
	{
		pthread_mutex_lock(&prog->dead_lock);
		prog->is_dead = 1;
		pthread_mutex_unlock(&prog->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_program	*prog;

	prog = (t_program *)ptr;
	while (1)
		if (check_if_dead(prog) == 1 || check_if_all_ate(prog) == 1)
			break ;	
	return (ptr);
}

int	create_threads(t_program *prog)
{
	int	i;
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &monitor, prog) != 0)
		destroy_all("Thread creation error", prog);
	i = -1;
	while (++i < prog->num_philos)
		if (pthread_create(&prog->philos[i].thread, NULL, &philo_task,
				&prog->philos[i]) != 0)
			destroy_all("Thread creation error", prog);
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", prog);
	i = -1;
	while (++i < prog->num_philos)
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", prog);
	return (0);
}
