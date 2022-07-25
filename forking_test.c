/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:32:20 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/24 14:01:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef struct	s_pkg
{
	int	arr[10];
	int	status;
	char	str[10];
}	t_pkg;

int	children_high_on_adventure(t_pkg *pkg, int wr_pipe)
{
	int	i;

	printf("pkg : status %d, str %s, arr :", pkg->status, pkg->str);
	i = -1;
	while (++i < 10)
	{
		printf("%d, ", pkg->arr[i]);
		pkg->arr[i] = i;

	}
	printf("\n");
	pkg->status = 99;
	write(wr_pipe, pkg, sizeof(t_pkg));
	exit(0);
}

int	main()
{
	int	fork_id;
	t_pkg	pkg;
	int	status;
	int	i;
	int	pp[2];

	pkg.status = 1;
	memcpy(pkg.str, "allo", 5);
	i = -1;
	while (++i < 10)
		pkg.arr[i] = i * 100;
		
	if (pipe(pp) < 0)
		return (-1);
	fork_id = fork();
	if (fork_id == 0)
		children_high_on_adventure(&pkg, pp[1]);
	else
	{
//		waitpid(fork_id, &status, 0);
		read(pp[0], &pkg, sizeof(t_pkg));
		printf("\n\npkg : status %d, str %s, arr :", pkg.status, pkg.str);
		i = -1;
		while (++i < 10)
			printf("%d, ", pkg.arr[i]);
	}
	return (0);
}
