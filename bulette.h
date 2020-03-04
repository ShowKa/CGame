struct Bulette {
	int row;
	int column;
	char symbol;
	char isDummy;
	struct Bulette *next;
};

struct Bulette *getBulettes();
struct Bulette generateBulette(int r, int c);
void initBulette();
void moveBulettes();
void removeDisappearedBulettes();
