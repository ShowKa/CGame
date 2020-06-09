static int score = 0;
static char message[17] = "YOUR SCORE: ";

void initScore() {
	score = 0;
}

int getScore() {
	return score;
}

char *getScoreMessage() {
	char sign = score >= 0 ? '+' : '-';
	int abbs_score = score >= 0 ? score : -1 * score;
	message[12] = sign;
	message[13] = (abbs_score / 100) + '0';
	message[14] = ((abbs_score % 100) / 10) + '0';
	message[15] = (abbs_score % 10) + '0';
	return message;
}

void addPoint(int added) {
	score += added;
}