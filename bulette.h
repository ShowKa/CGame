struct bulette {
	int row;
	int column;
	char symbol;
	struct bulette *next;
};

extern struct bulette buletteDummy;
extern struct bulette *bulettes;

struct bulette generateBulette(int r, int c);
void initBulette();
