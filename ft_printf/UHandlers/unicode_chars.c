/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 17:10:55 by ppanchen          #+#    #+#             */
/*   Updated: 2017/02/02 17:10:57 by ppanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

wchar_t	*width_for_unic(t_format *f, wchar_t *str, int *size)
{
	char	*tmp;
	wchar_t	*ret;
	int		i;
	int		r;
	int		t;

	i = -1;
	r = 0;
	t = f->after_dot;
	while (str[++i] != '\0')
	{
		r += ft_putchar_fd(str[i], -2, t);
		if (t != -1)
			t -= ft_putchar_fd(str[i], -2, t);
	}
	if (f->before_dot > r && f->flags[2] == 0 && f->flags[3] == 0)
	{
		i = f->before_dot - r;
		tmp = ft_strnew(i);
		i--;
		while (i + 1)
			tmp[i--] = ' ';
		ret = ft_ustrdup(tmp);
		if (*size != -1)
			*size += ft_ustrlen(ret);
		ret = ft_ustrjoin(ret, str);
	}
	else
		ret = str;
	return (ret);
}

wchar_t	*minus_for_unic(t_format *f, wchar_t *str, int *size)
{
	char	*tmp;
	wchar_t	*ret;
	int		i;
	int		r;
	int		t;

	i = -1;
	r = 0;
	t = f->after_dot;
	while (str[++i] != '\0')
	{
		r += ft_putchar_fd(str[i], -2, t);
		if (t != -1)
			t -= ft_putchar_fd(str[i], -2, t);
	}
	if (f->before_dot > r)
	{
		i = f->before_dot - r;
		tmp = ft_strnew(i);
		i--;
		while (i + 1)
			tmp[i--] = ' ';
		ret = ft_ustrdup(tmp);
		if (*size != -1)
			*size += ft_ustrlen(ret);
		ret = ft_ustrjoin(str, ret);
	}
	else
		ret = str;
	return (ret);
}

wchar_t	*zero_for_unic(t_format *f, wchar_t *str, int *size)
{
	char	*tmp;
	wchar_t	*ret;
	int		i;
	int		r;
	int		t;

	i = -1;
	r = 0;
	t = f->after_dot;
	while (str[++i] != '\0')
	{
		r += ft_putchar_fd(str[i], -2, t);
		if (t != -1)
			t -= ft_putchar_fd(str[i], -2, t);
	}
	if (f->before_dot > r)
	{
		i = f->before_dot - r;
		tmp = ft_strnew(i);
		i--;
		while (i + 1)
			tmp[i--] = '0';
		ret = ft_ustrdup(tmp);
		if (*size != -1)
			*size += ft_ustrlen(ret);
		ret = ft_ustrjoin(ret, str);
	}
	else
		ret = str;
	return (ret);
}

int		unicodhandler(t_format *f, va_list *ap)
{
	wchar_t *str;
	int		size;

	if (f->spec == 'S' || (f->spec == 's' &&
			ft_strcmp(f->num_type, "l") == 0))
	{
		str = va_arg(*ap, wchar_t *);
		if (!str)
			str = ft_ustrdup("(null)");
	}
	else if (f->spec == 'C' || (f->spec == 'c' &&
			ft_strcmp(f->num_type, "l") == 0))
	{
		str = (wchar_t *)malloc(sizeof(wchar_t) * 2);
		str[0] = va_arg(*ap, wchar_t);
		if (str[0] == 0)
			str[0] = '\300';
		str[1] = 0;
	}
	size = (f->spec == 'S' || f->spec == 's') ? f->after_dot : -1;
	(f->flags[2] == 1) && (str = minus_for_unic(f, str, &size));
	(f->flags[3] == 1) && (str = zero_for_unic(f, str, &size));
	str = width_for_unic(f, str, &size);
	save_args(str, size);
	return (1);
}
