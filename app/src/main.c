/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss <ckurt@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:55:42 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 16:51:47 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "parser.h"
#include "traceroute.h"
#include "socket.h"
#include "root.h"
#include "dns.h"
#include <unistd.h>
#include "../libft/libft.h"

int main(int argc, char **argv)
{
	t_params		params;
	t_traceroute	traceroute;

	ft_bzero(&params, sizeof(t_params));
	ft_bzero(&traceroute, sizeof(t_traceroute));
	check_root();
	parse_args(argc, argv, &params);
	print_flags(&params);
	dns_lookup(&params);
	if (params.rdns)
		reverse_dns_lookup(&params);
	init_sockets(&traceroute);
	return (0);
}
