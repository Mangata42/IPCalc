/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeMem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:12:18 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/25 11:55:40 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IPCalc.h"

void	freeArgs(char **argv)
{
	if (argv){
		for (int i = 0; i < 3; i++){
			if (argv[i])
				free(argv[i]);
		}
		
		free(argv);
	}
}

void	freeStruct(net_struct *NetDatas)
{
	if (NetDatas)
	{
		if (NetDatas->ip)
			free(NetDatas->ip);
		if (NetDatas->mask)
			free(NetDatas->mask);
		if (NetDatas->mask_bin)
			free(NetDatas->mask_bin);
		if (NetDatas->net_addr)
			free(NetDatas->net_addr);
		if (NetDatas->broadcast_addr)
			free(NetDatas->broadcast_addr);
	}
}