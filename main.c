/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:51:10 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/17 14:02:49 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int args, char **argv)
{
	t_program program;

	if (args != 5 && args != 6)
		return (write(2, "Invalid argument numbers\n", 25));
	if (check_input(argv))
		return (1);
	if (!init_program(&program, argv))
		return (1);
	if (create_threads(&program))
	return (0);
}
