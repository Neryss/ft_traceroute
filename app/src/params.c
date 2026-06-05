/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:18:20 by neryss            #+#    #+#             */
/*   Updated: 2026/06/05 18:19:04 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include <stdio.h>
#include <stdlib.h>

void	init_flags(t_params *params)
{
	params->hop_start = 1;
	params->interval = 0.0f;
	params->packet_size = 32;
	params->probes_per_hop = 3;
	params->ttl = 30;
}

void	print_flags(t_params *params)
{
	printf("Hop start = %d\ninterval = %f\npacket size = %d\nprobes/hop = %d\nttl = %d\n",
		params->hop_start, params->interval, params->packet_size, params->probes_per_hop, params->ttl);
}

void    print_help_menu(void)
{
    printf("Usage:\n");
    printf("\tft_traceroute [OPTION...] HOST [ packetlen ]\n");
    printf("Default options:\n");
    printf("--help\t\t\tRead this help and exit\n");
    printf("Bonus options :\n");
    printf("-m, --m\t\t\tttl max (default = 30)\n");
    printf("-f, --f\t\t\tStart from the N hop (instead from 1)\n");
    printf("-q, --q\t\t\tSet the number of probes per each hop. Default is 3\n");
    printf("-rdns, --rdns\t\tResolve IP addresses to their domain names\n");
    printf("-z, --z\t\t\tMinimal time interval between probes (default 0).\n");
    printf("\t\t\tIf the value is more than 10, then it specifies a\n");
    printf("\t\t\tnumber in milliseconds, else it is a number of\n");
    printf("\t\t\tseconds (float point values allowed too)\n\n");
    printf("Arguments:\n");
    printf("host\t\t\tThe host to traceroute to\n");
    printf("packetlen\t\tThe full packet length (default is the length of an IP\n");
    printf("\t\t\theader plus 40). Can be ignored or increased to a minimal\n");
    printf("\t\t\tallowed value\n");
    exit(0);
}
