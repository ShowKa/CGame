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
	(*new_p).show = 1;
	(*new_p).next = explosions;
	(*new_p).isDummy = 0;
	explosions = new_p;
	return *new_p;
}

Explosion *getExplosions() {
	return explosions;
}

static void removeFirstExplosion() {
	Explosion first = *explosions;
	explosions = first.next;
	free(&first);
}

static void removeExplosionByIndex(int index) {
	int i = 0;
	Explosion *target_p = explosions;
	Explosion *prev_p = NULL;
	if (index < 0) {
		return;
	}
	if (index == 0) {
		removeFirstExplosion();
		return;
	}
	while(i < index) {
		prev_p = target_p;
		target_p = target_p->next;
		i++;
	}
	prev_p->next = target_p->next;
	free(target_p);
}

void removeDisappearedExplosions() {
	Explosion *wp = explosions;
	int i = 0;
	while (!wp->isDummy) {
		if (wp->age >= 3) {
			wp = wp->next;
			removeExplosionByIndex(i);
			continue;
		}
		wp = wp->next;
		i++;
	}
}

static void twinkle(Explosion *target) {
	target->age += 1;
	target->show = target->show ? 0 : 1;
}

void twinkleAllExplosion() {
	Explosion *wp = explosions;
	while (!wp->isDummy) {
		twinkle(wp);
		wp = wp->next;
	}
}
