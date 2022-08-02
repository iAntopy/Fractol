

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("page size : %d\n", sysconf(_SC_PAGE_SIZE));
	return (0);
}
