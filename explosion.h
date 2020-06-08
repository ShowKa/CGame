struct Explosion {
	int row;
	int column;
	int age;
	char symbol;
	char show;
	char isDummy;
	struct Explosion *next;
};

void initExplosion();
struct Explosion generateExplosion(int row, int column);
struct Explosion *getExplosions();
void removeDisappearedExplosions();
void twinkleAllExplosion();
