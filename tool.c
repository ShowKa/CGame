void wait(long int time);
void waitUntil(char *switchAdress, char condition);
void waitBreakable(long int time, char *switchAdress, char condition);
void keepGate();
int seg7_ic(int number);
int seg7_ic_reverse(char seg);

void wait(long int time) {
	long int i;
	for(i = 0; i < time; i++);
}

void waitUntil(char *switchAdress, char condition) {
	while(1) {
		if ((*switchAdress & condition) == condition) {
			break;
		}
	}
}

void waitBreakable(long int time, char *switchAdress, char condition) {
	long int i;
	long int _time = time / 2;
	for(i = 0; i < _time; i++) {
		if ((*switchAdress & condition) == condition) {
			break;
		}
	}
}

void keepGate() {
	while(1);
}
