#include "params.h"
#include "parser.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  t_params params;

  parse_args(argc, argv, &params);
  return (0);
}
