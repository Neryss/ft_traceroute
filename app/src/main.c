/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss <ckurt@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:55:42 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 20:21:59 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "parser.h"
#include "traceroute.h"
#include "root.h"
#include "dns.h"
#include <stdint.h>
#include <unistd.h>
#include "../libft/libft.h"

int main(int argc, char **argv)
{
	t_params		params;
	t_traceroute	traceroute;

	ft_bzero(&params, sizeof(t_params));
	ft_bzero(&traceroute, sizeof(t_traceroute));
	traceroute.port = 33434;
	check_root();
	parse_args(argc, argv, &params);
	print_flags(&params);
	dns_lookup(&params);
	if (params.rdns)
		reverse_dns_lookup(&params);
	init_traceroute(&traceroute, &params);
	traceroute.dest_str = params.host;
	while (!traceroute.dest_reached)
	{
		send_probe(&traceroute);
		recv_icmp(&traceroute);
		increment_port(&traceroute);
		traceroute.ttl++;
		sleep(1);
	}
	return (0);
}
