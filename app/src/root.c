/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neryss </var/spool/mail/neryss>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:16:57 by neryss            #+#    #+#             */
/*   Updated: 2026/06/12 16:18:21 by neryss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "root.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	check_root(void)
{
	if (getuid() != 0)
	{
		printf("You must be root!\n");
		exit(1);
	}
}
