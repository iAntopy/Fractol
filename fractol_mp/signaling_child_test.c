/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling_child_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 00:17:01 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/02 15:14:33 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

typedef struct	s_shared_memory
{
	char	str[100];
}	t_shmem;

void	__crash_exit(void)
{
	printf("Child process exiting\n");
	exit(0);
}

void	child_labor_activated(t_shmem *shmem)
{
	printf("Child labor activated !\n");
	printf("shared memory pointer is : %p\n", shmem);
}

void	__proc_job(t_shmem *shmem)
{
	int		sig;
	sigset_t	sigset;

	printf("signal set init and adding SIGTERM in set\n");
	sigemptyset(&sigset);
	printf("sigemptyset initialized\n");

	while (1)
	{
		sigaddset(&sigset, SIGTERM);
		sigaddset(&sigset, SIGUSR1);
		printf("waiting for signal\n");
		sigwait(&sigset, &sig);
		if (sig == SIGTERM)
			__crash_exit();
		else if (sig == SIGUSR1)
			child_labor_activated(shmem);
		printf("received signal %d\n", sig);
	}
	exit(0);
}

int	test_signals(t_shmem *sm, int child_pid)
{
	sleep(1);
	printf(" o--- Parent sending child labor signal 1\n");
	kill(child_pid, SIGUSR1);
	sleep(1);
	printf(" o--- Parent sending child labor signal 2\n");
	kill(child_pid, SIGUSR1);
	sleep(2);
	printf(" o--- Parent sending stop signal\n");
	kill(child_pid, SIGTERM);
	return (0);
}

int	main(void)
{
	int	pid;
	t_shmem	*shmem;

	shmem = NULL;
//	shmem = (t_shmem *)mmap(NULL, sizeof(t_shmem) + (sizeof(t_shmem) % sysconf(_SC_PAGE_SIZE)),
//		PROT_READ | PROT_WRITE,	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	pid = fork();
	if (pid < 0)		// FORK FAILED
		exit(1);
	else if (pid == 0)	// CHILD
	{
		printf("A message from child process\n");
		__proc_job(shmem);
	}
	else			// PARENT
	{
		printf("A message from parent process\n");
		test_signals(shmem, pid);
	}
	wait(NULL);
	return (0);
}

