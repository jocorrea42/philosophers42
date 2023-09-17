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

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sig;
	unsigned long long	res;

	i = 0;
	res = 0;
	sig = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		if (res > __LONG_LONG_MAX__ && sig == 1)
			return (0);
		if (res > __LONG_LONG_MAX__ && sig == -1)
			return (-1);
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * sig);
}

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	check_input(char **argv)
{
	if (!is_num(argv[1]) || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (!is_num(argv[2]) || ft_atoi(argv[2]) <= 0 )
		return (write(2, "Invalid time to die\n", 21), 1);
	if (!is_num(argv[3]) || ft_atoi(argv[3]) <= 0 )
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (!is_num(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (!is_num(argv[5]) || ft_atoi(argv[5]) < 0))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	init_program(t_program *program, char **argv)
{
	int i;

	program->num_philos = ft_atoi(argv[1]);
	program->is_dead = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
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
		program->philos[i].dead = &program->is_dead;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].time_to_die = ft_atoi(argv[2]);
		program->philos[i].time_to_eat = ft_atoi(argv[3]);
		program->philos[i].time_to_sleep = ft_atoi(argv[4]);
		program->philos[i].num_time_eat = -1;
		pthread_mutex_init(&program->philos[i].l_fork, NULL);
		if (i == 0)
			program->philos[i].r_fork = &program->philos[program->num_philos - 1].l_fork;
		else
			program->philos[i].r_fork = &program->philos[i - 1].l_fork;
		if (argv[5])
			program->philos[i].num_time_eat = ft_atoi(argv[5]);
	}
	return (1);
}
