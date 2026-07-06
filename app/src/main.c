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
#include <sys/time.h>
#include "../libft/libft.h"

static double	get_time_seconds(void)
{
	struct	timeval	t;

	gettimeofday(&t, 0);
	return (t.tv_sec + t.tv_usec / 1e9);
}

int main(int argc, char **argv)
{
	t_params		params;
	t_traceroute	traceroute;
	double			current_time;
	double			last_time;

	current_time = 0.0;
	last_time = 0.0;
	ft_bzero(&params, sizeof(t_params));
	ft_bzero(&traceroute, sizeof(t_traceroute));
	traceroute.port = 33434;
	check_root();
	init_flags(&params);
	parse_args(argc, argv, &params);
	print_flags(&params);
	dns_lookup(&params);
	if (params.rdns)
		reverse_dns_lookup(&params);
	init_traceroute(&traceroute, &params);
	traceroute.dest_str = params.host;
	while (!traceroute.dest_reached && traceroute.ttl < params.ttl)
	{
		current_time = get_time_seconds();
		if (current_time - last_time >= params.interval || last_time == 0)
		{
			last_time = current_time;
			printf("%*d ", 2, traceroute.ttl);
			for (int i = 0; i < params.probes_per_hop; i++)
			{
				send_probe(&traceroute);
				recv_icmp(&traceroute);
				increment_port(&traceroute);
			}
			printf("\n");
			traceroute.ttl++;
		}
	}
	return (0);
}
