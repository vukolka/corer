/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvukolov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:51:16 by mvukolov          #+#    #+#             */
/*   Updated: 2018/02/05 19:51:17 by mvukolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"
#include "queue.h"
#include "linked_list.h"

void	make_classes(void)
{
	llist_init();
	room_init();
	queue_init();
}
