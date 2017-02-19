/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:55:00 by ppanchen          #+#    #+#             */
/*   Updated: 2017/02/01 18:34:01 by ppanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_numlen(int n)
{
	int i;

	i = 0;
	if (n / 10 == 0)
		return (1);
	else
	{
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
		return (i);
	}
}
