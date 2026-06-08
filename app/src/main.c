#include "params.h"
#include "parser.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  t_params params;

  parse_args(argc, argv, &params);
	print_flags(&params);
  return (0);
}
