/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IPCalc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:39:48 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/24 13:17:47 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IPCalc.h"

uint8_t			*get_mask(char *mask_arg)
{
	uint8_t		*mask_arr;
	int			maskN_bits;
	int			div, rem;
	
	if (strchr(mask_arg, '.')){
		mask_arr = char_arr_to_int_arr(ft_split(mask_arg, '.'));
		if (!mask_arr)
			return (NULL);
	}
	else
	{
		if (!(mask_arr = calloc(4, sizeof(uint8_t))))
			return (NULL);
		maskN_bits = atoi(strchr(mask_arg, '/') + 1);
		div = maskN_bits / 8;
		rem = maskN_bits % 8;

		for(int i = 0; i < div; i++)
			mask_arr[i] = 0xFF;
		mask_arr[div] = (~0 << (8 - rem)); // remaining bits
	}
	return (mask_arr);
}

unsigned int	get_mask_cidr(uint8_t *mask)
{
	unsigned int nbits = 0; // null-bits count

	for (int i = 0; i < 4; i++)
	{
		if (mask[i] != 0xFF){
			for (int y = 7; y >= 0; y--){
				if (!(mask[i] & 1 << y))
					nbits++;
			}
		}
	}
	return (32 - nbits);
}

// IP & MASK
int				compute_network_addr(net_struct *NetDatas)
{
	if (!(NetDatas->net_addr = calloc(4, sizeof(uint8_t))))
		return (1);
	for (int i = 0; i < 4; i++)
		NetDatas->net_addr[i] = NetDatas->ip[i] & NetDatas->mask[i];
		
	return (0);
}

// IP | (bits not set in MASK)
int				compute_broadcast_addr(net_struct *NetDatas)
{
	if (!(NetDatas->broadcast_addr = calloc(4, sizeof(uint8_t))))
		return(1);
	for (int i = 0; i < 4; i++)
		NetDatas->broadcast_addr[i] = NetDatas->ip[i] | ~NetDatas->mask[i];
	
	return (0);
}

// 2^null_bits - 2 (network and broadcast) or 2^(32 - bits) - 2
int				compute_usable_addr(uint8_t *mask)
{
	int 	null_bits = 0;
	int		usable_addr = 1;
	size_t	i = 0;

	while (i < 4)
	{
		for (int y = 0; y < 8; y++){
			if (!(mask[i] >> y & 1))
				null_bits++;
		}
		i++;
	}

	for (int z = 0; z < null_bits; z++) // exponent 2
		usable_addr *= 2;

	return (usable_addr - 2); 
}

void			initDataStruct(net_struct *NetDatas)
{
	NetDatas->ip = 0;
	NetDatas->mask = 0;
	NetDatas->mask_cidr = 0;
	NetDatas->net_addr = 0;
	NetDatas->broadcast_addr = 0;
	NetDatas->n_addr = 0;
}

void			askContinue(char *keepOn)
{
	int c;

	puts(ANSI_COLOR_CYAN "\nContinue? y/n");
	fputs("> ", stdout);
	while (getchar() != '\n');
	c = getchar();
	(c == 'y' || c == 'Y') ? (*keepOn = 1) : (*keepOn = 0);
	fputs(ANSI_RESET, stdout);
}

int				main()
{
	char		**argv;
	net_struct	NetDatas;
	char		keepOn = 1;

		
	printf(ANSI_TERM_CLEAR);
	while (keepOn)
	{
		if (!(argv = malloc(sizeof(char *) * 3)))
			return (1);
		argv[0] = malloc(sizeof(char) * 17);
		argv[1] = malloc(sizeof(char) * 17);
		argv[2] = NULL;

		initDataStruct(&NetDatas);
		fputs("IP: ", stdout);
		scanf("%s", argv[0]);
		fputs("MASK: ", stdout);
		scanf("%s", argv[1]);
		if (verify_args(argv) == 1){
			freeArgs(argv);
			askContinue(&keepOn);
			continue;
		}
			
		NetDatas.ip = char_arr_to_int_arr(ft_split(argv[0], '.'));
		NetDatas.mask = get_mask(argv[1]);
		if(!NetDatas.ip || !NetDatas.mask){
			freeArgs(argv);
			freeStruct(&NetDatas);
			return (1);
		}
		
		if (verify_ip(NetDatas.ip) || verify_mask(NetDatas.mask)){
			freeArgs(argv);
			freeStruct(&NetDatas);
			return (1);
		}

		if (compute_network_addr(&NetDatas) || compute_broadcast_addr(&NetDatas)){
			freeArgs(argv);
			freeStruct(&NetDatas);
			return (1);
		}
		
		NetDatas.mask_cidr = get_mask_cidr(NetDatas.mask);
		NetDatas.n_addr = compute_usable_addr(NetDatas.mask);
		fputs(ANSI_RESET, stdout);
		show_results(NetDatas);
		freeArgs(argv);
		freeStruct(&NetDatas);
		askContinue(&keepOn);
	}
	
	return (0);
}