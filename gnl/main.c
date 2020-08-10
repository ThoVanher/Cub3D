#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd;
	char *line;
	int ret ;

	line = 0;
	if (argc == 0)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		write(1, "open() failed\n", 14);
	while ((ret = get_next_line (fd, &line)) == 1)
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		write(1, "close() failed\n", 15);
	return (0);
}
