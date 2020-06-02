#include <stdio.h>
#include "explosion.h"

typedef struct Explosion Explosion;

static const char EXPLOSION = 0xf4;
static Explosion *explosions;
static Explosion explosionDummy= {0};

void initExplosion() {
	Explosion *wp = explosions;
	while (!wp->isDummy) {
		Explosion *backup_p = wp->next;
		free(wp);
		wp = backup_p;
	}
	explosionDummy.row = -1;
	explosionDummy.column = -1;
	explosionDummy.isDummy = 1;
	explosions = &explosionDummy;
}

Explosion generateExplosion(int row, int column) {
	Explosion *new_p = (Explosion *)malloc(sizeof(Explosion));
	(*new_p).row = row;
	(*new_p).column = column;
	(*new_p).age = 0;
	(*new_p).symbol = EXPLOSION;
	(*new_p).next = explosions;
	(*new_p).isDummy = 0;
	explosions = new_p;
	return *new_p;
}

Explosion *getExplosions() {
	return explosions;
}
