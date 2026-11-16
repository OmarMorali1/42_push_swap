/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atahlawi <atahlawi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:07:10 by ommorali          #+#    #+#             */
/*   Updated: 2026/11/12 12:03:36 by atahlawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	final_alignment(t_stack **a, t_bench *bench)
{
	t_stack	*curr;
	int		min_pos;
	int		len;

	curr = *a;
	min_pos = 0;
	len = stack_len(*a);
	while (curr && curr->index != 0)
	{
		curr = curr->next;
		min_pos++;
	}
	if (min_pos <= len / 2)
	{
		while (min_pos-- > 0)
			ra(a, bench, 1);
	}
	else
	{
		while (min_pos++ < len)
			rra(a, bench, 1);
	}
}

static void	push_all_save_three(t_stack **a, t_stack **b, t_bench *bench)
{
	int	limit;

	limit = stack_len(*a) - 3;
	while (stack_len(*a) > 3)
	{
		if ((*a)->index >= limit)
			ra(a, bench, 1);
		else
		{
			pb(a, b, bench);
			if ((*b)->index < limit / 2)
				rb(b, bench, 1);
		}
	}
}

void	turk_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	index_stack(*a);
	if (is_sorted(*a))
		return ;
	if (stack_len(*a) == 2)
	{
		sa(a, bench, 1);
		return ;
	}
	push_all_save_three(a, b, bench);
	sort_three(a, bench);
	push_back_to_a(a, b, bench);
	final_alignment(a, bench);
}
