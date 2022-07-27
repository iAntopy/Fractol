/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:32:20 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/26 20:38:25 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct	s_pkg
{
	int		status;
	char	str[100];
}	t_pkg;

int	children_high_on_adventure(t_pkg pkg, int incoming[2], int outgoing[2]) 
{
	int	call_count;
	
	close(incoming[1]);
	close(outgoing[0]);
	call_count = 0;
	printf("pkg : status %d, str %s, arr :", pkg.status, pkg.str);
	while (1)
	{
		printf("Child process : Call Count : %d\n", call_count);
		printf("Child process reading from incoming read pipe\n");
		read(incoming[0], &pkg, sizeof(t_pkg));
		printf("Child read successfully with status : %d\n", pkg.status);
		if (pkg.status == 0)
		{
			printf("Child received close order\n");
			break ;
		}
		printf("Child received str : %s\n", pkg.str);
		strcpy(pkg.str, "Message received and sent back\n");
		printf("Child writing to outgoing write pipe\n");
		write(outgoing[1], &pkg, sizeof(t_pkg));
		call_count++;
	}
	printf("CHILD CLOSING \n");
	exit(0);
}

// provide list of int fd pointers
void	close_fd_ptr_list(int nb_fds, ...)
{
	int		i;
	int		*fd_ptr;
	va_list	ap;

	va_start(ap, nb_fds);
	i = -1;
	while (++i < nb_fds)
	{
		fd_ptr = va_arg(ap, int *);
		close(*fd_ptr);
		*fd_ptr = -1;
	}
	va_end(ap);
}

void	tickle_childs_berries(t_pkg *pkg, int main_to_child[2], int child_to_main[2], char *msg)
{
	strcpy(pkg->str, msg);
	printf("main str : %s\n", pkg->str);
	pkg->status = 1;
	printf("Main writing to main_to_child write pipe\n");
	write(main_to_child[1], pkg, sizeof(t_pkg));
	printf("Main written to pipe successfully\n");
	printf("Main reading from child_to_main pipe\n");
	read(child_to_main[0], pkg, sizeof(t_pkg));
	printf("Main received pkg from child : %s\n", pkg->str);
	printf("Tickling over\n");
}

int	main()
{
	int		fork_id;
	t_pkg	pkg;
	int		main_to_child[2];
	int		child_to_main[2];

	pkg.status = 1;
	
	if (pipe(main_to_child) < 0)
		return (-1);
	if (pipe(child_to_main) < 0)
		return (-1);

	fork_id = fork();
	if (fork_id == 0)
		children_high_on_adventure(pkg, main_to_child, child_to_main);
	else
	{
		close_fd_ptr_list(2, main_to_child, child_to_main + 1);
		tickle_childs_berries(&pkg, main_to_child, child_to_main, "This is ass\n");
		tickle_childs_berries(&pkg, main_to_child, child_to_main, "No really I mean some filthy ass shit\n");
		tickle_childs_berries(&pkg, main_to_child, child_to_main, "No I will not calm down good sir\n");
	}
	return (0);
}
