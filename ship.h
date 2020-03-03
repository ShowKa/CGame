struct ship {
	int row;
	int symbol;
};

void moveUpShip();
char existShipAt(int r, int c);
char isShip(char target);
int getRowOfShip();
void launch();
char getShipSymbol();
