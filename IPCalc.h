/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../IPCalc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:59:16 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/23 11:58:43 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IPCALC_H
# define IPCALC_H

# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_RESET   		"\x1b[0m"
# define ANSI_BOLD			"\x1b[1m"
# define ANSI_TERM_CLEAR	"\033[2J\033[H"

typedef struct 
{
	uint8_t			*ip;
	uint8_t			*mask;
	unsigned int	mask_cidr;
	uint8_t			*net_addr;			//network address
	uint8_t			*broadcast_addr;
	int				n_addr; 			//possible addresses
} 						net_struct;

// verifDatas.c
int					verify_ip(uint8_t *ip);
int					verify_mask(uint8_t *mask);
int					verify_args(char **argv);
//

// utils.c
void				print_arr(uint8_t *arr);
uint8_t				*char_arr_to_int_arr(char **ipC);
void				show_results(net_struct NetDatas);

// freeMem.c
void				freeArgs(char **argv);
void				freeStruct(net_struct *NetDatas);
//

// libftFn.c
void				ft_putnbr(int n);
char				**ft_split(const char *str, char c);
char				*ft_itoa(int n);

#endif