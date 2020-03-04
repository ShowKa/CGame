struct Block {
	int row;
	int column;
	char symbol;
	int velocity;
	struct Block *next;
	char isDummy;
};

char isBlock(char target);
int decideRow();
void moveBlocks();
struct Block generateBlock(int row);
struct Block *getBlocks();
void removeDisappearedBlocks();
