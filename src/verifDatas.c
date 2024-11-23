/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifDatas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:32:05 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/23 12:38:56 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IPCalc.h"

int		verify_ip(uint8_t *ip)
{
	for (int i = 0; i < 4; i++){
		if (ip[i] < 0 || ip[i] > 255){
			puts(ANSI_COLOR_RED "Wrong IP value.\n");
			return (1);
		}
	}

	return (0);
}

// all bits in mask must be consecutive 0's or 1's
int		verify_mask(uint8_t *mask)
{
	size_t	i = 0;
	char	nb_flag = 0; //null-bit flag
	
	while (i < 4)
	{
		if (mask[i] > 0 && nb_flag){
			puts(ANSI_COLOR_RED "Wrong mask value.\n");
			return (1);
		}
		if (mask[i] != 0xFF)
		{
			for (int y = 7; y >= 0; y--)
			{
				if ((mask[i] & 1 << y) && nb_flag){
					puts(ANSI_COLOR_RED "Wrong mask value.\n");
					return (1);
				}
				if (!(mask[i] & 1 << y))
					nb_flag = 1;
			}
		}
		i++;
	}
	
	return (0);
}

int		verify_args(char **argv)
{
	if (!strchr(argv[0], '.')){
		puts(ANSI_COLOR_RED "Wrong IP format: 000.000.000.000");
		return (1);
	}

	if (!strchr(argv[1], '.') && !strchr(argv[1], '/')){
		puts(ANSI_COLOR_RED "Wrong mask format: /00 or 000.000.000.000");
		return (1);
	}

	for (int i = 0; argv[0][i]; i++){
		if (!isdigit(argv[0][i]) && argv[0][i] != '.'){
			puts(ANSI_COLOR_RED "Wrong IP format: 000.000.000.000");
			return (1);
		}
	}
	
	for (int i = 0; argv[1][i]; i++){
		if (!isdigit(argv[1][i]) && argv[1][i] != '/' && argv[1][i] != '.'){
			puts(ANSI_COLOR_RED "Wrong IP format: 000.000.000.000");
			return (1);
		}
	}
	
	return (0);
}