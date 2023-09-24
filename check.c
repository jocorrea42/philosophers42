/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:25:18 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/17 16:03:47 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	init_program(t_program *program, char **argv)
{
	int i;

	program->num_philos = ft_atoi(argv[1]);
	program->is_dead = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->num_time_eat = -1;
	if (argv[5])
			program->num_time_eat = ft_atoi(argv[5]);
	i = -1;
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (write(2, "Malloc bad\n", 11), 0);
	while (++i < program->num_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].num_philo = &program->num_philos;
		program->philos[i].eating = 0;
		program->philos[i].meal_eaten = 0;
		program->philos[i].start_time = get_current_time();
		program->philos[i].last_meal = get_current_time();
		program->philos[i].dead = &program->is_dead;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].time_to_die = ft_atoi(argv[2]);
		program->philos[i].time_to_eat = ft_atoi(argv[3]);
		program->philos[i].time_to_sleep = ft_atoi(argv[4]);
	}
	i = -1;
	while (++i < program->num_philos)
		if (i == 0)
			program->philos[i].r_fork = &program->philos[program->num_philos - 1].l_fork;
		else
			program->philos[i].r_fork = &program->philos[i - 1].l_fork;
	return (1);
}
