#include "error_exit.h"

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>

# define ERROR_PRINT "ft_traceroute: %sTry \'./ft_traceroute --help\'"

void	error_exit(int code, const char *msg, ...)
{
	va_list	args;
	int		len;
	char	*fmt_msg;

	va_start(args, msg);
	len = vsnprintf(NULL, 0, msg, args);
	va_end(args);
	if (len < 0)
		exit (1);
	fmt_msg = malloc(sizeof(char) * (len + 1));
	if (!fmt_msg)
		exit (1);
	va_start(args, msg);
	vsnprintf(fmt_msg, len + 1, msg, args);
	va_end(args);
	printf(ERROR_PRINT, fmt_msg);
	free(fmt_msg);
	exit(code);
}
