/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_chunk_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahlawi <atahlawi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:05:11 by ommorali          #+#    #+#             */
/*   Updated: 2026/11/12 12:03:53 by atahlawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_chunk_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	while (stack_len(*a) > 3)
	{
		if ((*a)->index >= 3)
			pb(a, b, bench);
		else
			ra(a, bench, 1);
	}
	if (stack_len(*b) == 2 && (*b)->index > (*b)->next->index)
		sb(b, bench, 1);
	sort_three(a, bench);
	while (*b)
	{
		pa(a, b, bench);
		ra(a, bench, 1);
	}
}
