/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:25:18 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/24 14:28:56 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_philo(t_program *program, char **argv, int i)
{
	program->philos = malloc(sizeof(t_philo) * program->nphilos);
	if (!program->philos)
		return (write(2, "Malloc bad\n", 11), 1);
	while (++i < program->nphilos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].num_philo = &program->nphilos;
		program->philos[i].eating = 0;
		program->philos[i].meal_eaten = 0;
		program->philos[i].start_time = get_time();
		program->philos[i].last_meal = get_time();
		program->philos[i].dead = &program->is_dead;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].time_to_die = ft_atoi(argv[2]);
		program->philos[i].time_to_eat = ft_atoi(argv[3]);
		program->philos[i].time_to_sleep = ft_atoi(argv[4]);
		pthread_mutex_init(&program->philos[i].lfork, NULL);
	}
	return (0);
}

int	init_program(t_program *program, char **argv)
{
	int	i;
	int	nf;

	nf = ft_atoi(argv[1]);
	program->nphilos = nf;
	program->is_dead = 0;
	i = -1;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->time_eat = -1;
	if (argv[5])
		program->time_eat = ft_atoi(argv[5]);
	if (fill_philo(program, argv, i))
		return (1);
	i = 0;
	program->philos[i].rfork = &program->philos[nf - 1].lfork;
	while (++i < program->nphilos)
		program->philos[i].rfork = &program->philos[i - 1].lfork;
	return (1);
}
