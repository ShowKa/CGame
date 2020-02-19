
int ex_for(void) {
	while(1) {
		turnOnAllLed();
		wait(2000000);
		turnOffAllLed();
		wait(2000000);
	}
	return 0;
}