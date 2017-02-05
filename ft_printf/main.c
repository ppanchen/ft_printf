/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c           		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:58:56 by ppanchen          #+#    #+#             */
/*   Updated: 2017/01/15 15:59:00 by ppanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define TEST(args...) \
	printf("   printf: "); printf(args); printf("\n"); \
	ft_printf("ft_printf: "); ft_printf(args); ft_printf("\n");

int		main(int argc, char **argv)
{
	printf("ret(or) = %d\n", printf("% 4.5i", 42));
	printf("ret(my) = %d\n", ft_printf("% 4.5i", 42));
	printf("ret(or) = %d\n", printf("%.5c", 0));
	printf("ret(my) = %d\n", ft_printf("%.5c", 0));
//	TEST("%#.O", 0);
	return (0);
}
