/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftFn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:45:57 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/23 12:00:32 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IPCalc.h"

#define MIN_INT (-2147483647 -1)

void	ft_putnbr(int n)
{
	char *ret = ft_itoa(n);
	fputs(ret, stdout);
	free(ret);
}

static	int		ft_count_words(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static	char	*ft_word(const char *str, char c, int *i)
{
	char	*s;
	int		k;

	if (!(s = (char *)malloc(sizeof(s) * (strlen((char *)str)))))
		return (NULL);
	k = 0;
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

char			**ft_split(const char *str, char c)
{
	int		i;
	int		j;
	int		wrd;
	char	**s;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	wrd = ft_count_words(str, c);
	if (!(s = (char **)malloc(sizeof(s) * (wrd + 2))))
		return (NULL);
	while (str[i] == c && str[i])
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, c, &i);
		j++;
	}
	s[j] = NULL;
	return (s);
}

char    *ft_itoa(int n)
{
    char    *tmp;
    char    *ret;
    int     i = 0, y = 0;
    
    if (n == MIN_INT)
    {
        ret = (char *)malloc(12);
        ret = strcpy(ret, "-2147483648");
        ret[11] = 0;
        return (ret);
    }

    if (n == 0)
    {
        ret = (char *)malloc(2);
        ret[0] = '0';
        ret[1] = 0;
        return (ret);
    }
 
    tmp = (char *)malloc(12);
    bzero(tmp, 11);
    if (n < 0)
        tmp[i++] = '-';
    if (n == 0)
        tmp[i] = '0';
    n = abs(n);
    while (n)
    {
        tmp[++i] = 48 + (n % 10);
        n /= 10;
    }

    ret = (char *)malloc(i + 1);
    (tmp[0] == '-') ? (ret[y++] = '-') : y;
    while (tmp[i])
        ret[y++] = tmp[i--];
        
    ret[y] = 0;
    free(tmp);
    return (ret);
}