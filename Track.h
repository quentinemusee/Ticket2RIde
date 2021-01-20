#ifndef __TRACK_H__
#define __TRACK_H__

#include <stdlib.h>
#include <stdio.h>
#include "TicketToRideAPI.h"

typedef struct {
	int length, owner; /* no owner = 0, me = 1, ennemy = 2 */
	t_color color1, color2;
} t_track;

#endif