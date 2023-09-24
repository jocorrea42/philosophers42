/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:25:27 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/24 13:56:07 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!is_alive(philo))
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	think(t_philo philo)
{
	print_message("is thinking", &philo);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print_message("has taken a r_fork", philo);
	if (*philo->num_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->rfork);
	}
	pthread_mutex_lock(&philo->lfork);
	print_message("has taken a l_fork", philo);
	print_message("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}
