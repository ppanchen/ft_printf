/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 12:42:58 by ppanchen          #+#    #+#             */
/*   Updated: 2017/01/18 12:43:01 by ppanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_catcher(char *str, t_format **f)
{
	int i;

	i = -1;
	while (++i < 5)
		(*f)->flags[i] = 0;
	i = -1;
	while (FLAGS[++i])
	{
		if (FLAGS[i] == '0')
			continue ;
		if (ft_strchr(str, FLAGS[i]) != 0)
			(*f)->flags[i] = 1;
	}
	i = 0;
	while (!(str[i] >= '1' && str[i] <= '9') && str[i] != 0)
		i++;
	str = ft_strsub(str, 0, i);
	if (ft_strchr(str, '0') != 0)
		(*f)->flags[3] = 1;
}

void		num_type_catcher(char *str, t_format **f)
{
	char	**arr;
	int		i;

	i = -1;
	arr = ft_strsplit(NUM_TYPES, ' ');
	(*f)->num_type = "";
	while (arr[++i])
		if (ft_strstr(str, arr[i]) != 0)
			(*f)->num_type = ft_strjoin((*f)->num_type, arr[i]);
	free(arr);
}

void		digit_catcher(char *str, t_format **f)
{
	int		i;
	char	*d;

	i = 0;
	if ((d = ft_strchr(str, '.')) == 0)
	{
		while (!(str[i] >= '1' && str[i] <= '9') && str[i] != 0)
			i++;
		(*f)->before_dot = ft_atoi(str + i);
		(*f)->after_dot = -1;
	}
	else
	{
		str = ft_strsub(str, 0, d - str);
		while (!(str[i] >= '1' && str[i] <= '9') && str[i] != 0)
			i++;
		(*f)->before_dot = ft_atoi(str + i);
		d++;
		(*f)->after_dot = d ? ft_atoi(d) : 0;
	}
}

char		*ft_fill_struct(char *c, char *str, va_list *ap)
{
	t_format	*f;
	char		*retstr;

	f = (t_format *)malloc(sizeof(t_format) * 1);
	f->spec = *c;
	if (c)
		str = ft_strsub(str, 0, c - str);
	flag_catcher(str, &f);
	num_type_catcher(str, &f);
	digit_catcher(str, &f);
	retstr = paste_arg(f, ap);
	free(f);
	return (retstr);
}

char		*ft_checker(char *str, va_list *ap)
{
	int			i;
	char		*c;
	char		*retstr;
	char 		*tmp;

	i = 0;
	while (str[++i])
	{
		if (ft_strchr(FLAGS, str[i]) != 0 || str[i] == '.' ||
				ft_isdigit(str[i]) != 0 || ft_strchr(NUM_TYPES, str[i]) != 0)
		{
			c = 0;
			break ;
		}
		c = ft_strchr(TYPES, str[i]);
		if (c != 0)
			break ;
	}
	if (c == NULL && (i = 1))
		while (str[i] && (ft_strchr(FLAGS, str[i]) != 0 || str[i] == '.' ||
				ft_isdigit(str[i]) != 0 || ft_strchr(NUM_TYPES, str[i]) != 0))
			i++;
	c = str + i;
	retstr = ft_fill_struct(c++, str, ap);
	tmp = retstr;
	retstr = ft_strjoin(retstr, c);
	ft_strdel(&tmp);
	return (retstr);
}
