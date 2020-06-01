static int score = 0;

void initScore() {
	score = 0;
}

int getScore() {
	return score;
}

char *getScoreMessage() {
	int score = getScore();
	static char message[17] = "YOUR SCORE: ";
	message[12] = score >= 0 ? '+' : '-';
	message[13] = (score / 100) + '0';
	message[14] = ((score % 100) / 10) + '0';
	message[15] = (score % 10) + '0';
	return message;
}

void addPoint(int added) {
	score += added;
}