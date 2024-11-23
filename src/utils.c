/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:35:12 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/23 12:40:24 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IPCalc.h"

void		print_arr(uint8_t *arr)
{
	for (int i = 0; i < 3; i++){
		ft_putnbr(arr[i]);
		putchar('.');
	}
	ft_putnbr(arr[3]);
}

uint8_t		*char_arr_to_int_arr(char **ipC)
{
	uint8_t	*ipI;
	size_t	i = 0;

	if (!(ipI = malloc(sizeof(uint8_t) * 4)))
		return (NULL);
	while (ipC[i])
	{
		ipI[i] = (uint8_t)atoi(ipC[i]);
		free(ipC[i]);
		i++;
	}

	free(ipC);
	return (ipI);
}

void		show_results(net_struct NetDatas)
{
	puts("\n");
	fputs(ANSI_COLOR_GREEN "IP: ", stdout);
	print_arr(NetDatas.ip);
	fputs("\t\t\tMASK: ", stdout);
	print_arr(NetDatas.mask);
	fputs(ANSI_RESET, stdout);
	fputs("\n===================\n\n", stdout);
	fputs("Network address: ", stdout);
	print_arr(NetDatas.net_addr);
	fputs("\nBroadcast address: ", stdout);
	print_arr(NetDatas.broadcast_addr);
	NetDatas.net_addr[3]++;
	NetDatas.broadcast_addr[3]--;
	fputs("\nIP range: " ANSI_COLOR_MAGENTA, stdout);
	print_arr(NetDatas.net_addr);
	fputs(" --> ", stdout);
	print_arr(NetDatas.broadcast_addr);
	fputs(ANSI_RESET, stdout);
	printf("\nPossible addresses : %d\n", NetDatas.n_addr);
}