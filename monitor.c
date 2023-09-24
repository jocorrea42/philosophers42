/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:54:38 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/24 13:56:16 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	is_dead(t_program *prog)
{
	int	i;

	i = -1;
	while (++i < prog->nphilos)
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

int	is_ate(t_program *prog)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	if (prog->time_eat == -1)
		return (0);
	while (++i < prog->nphilos)
	{
		pthread_mutex_lock(&prog->meal_lock);
		if (prog->philos[i].meal_eaten >= prog->time_eat)
			finished_eating++;
		pthread_mutex_unlock(&prog->meal_lock);
	}
	if (finished_eating == prog->nphilos)
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
		if (is_dead(prog) == 1 || is_ate(prog) == 1)
			break ;
	return (ptr);
}
