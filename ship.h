struct Ship {
	int row;
	int column;
	int symbol;
};

void moveUpShip();
char existShipAt(int r, int c);
char isShip(char target);
int getRowOfShip();
void launch();
char getShipSymbol();
struct Ship getShip();
