void music(void) {
	setBuzzerTempo(90.0);
	// g f b- cf d cf b- a g f
	sound(-2, 4);
	sound(-2, 4);
	sound(5, 4);
	sound(2, 2);
	sound(5, 2);
	sound(-3, 4);
	sound(-2, 2);
	sound(5, 2);
	sound(-3, 4);
	sound(-4, 4);
	sound(2, 4);
	sound(-5, 4);
	sound(-2, 4);
	// g f b- cf d cf b- a g f
	sound7(2, 4);
	sound7(-2, 4);
	sound7(5, 4);
	sound7(2, 2);
	sound7(5, 2);
	sound7(-3, 4);
	sound7(-2, 2);
	sound7(5, 2);
	sound7(-3, 4);
	sound7(-4, 4);
	sound7(2, 4);
	sound7(-5, 4);
	sound7(-2, 4);
	// f g d fg c ga f
	sound(0, 2);
	sound(2, 2);
	sound(-5, 4);
	sound(3, 2);
	sound(2, 2);
	sound(-7, 4);
	sound(7, 2);
	sound(2, 2);
	sound(-4, 4);
	// +f d c b- f
	sound7(12, 4);
	sound7(-3, 4);
	sound7(-2, 2);
	sound7(-2, 2);
	sound7(-5, 8);
}

void music_01(void) {
	// cdefg
	sound(3, 4);	sound(2, 4); sound(2, 4);	sound(1, 4);	sound(2, 4);	sound(-2, 4);	sound(-1, 4);	sound(-2, 4);	sound(-2, 4);
	// cdefg
	sound7(0, 4); 	sound7(2, 4);	sound7(2, 4);	sound7(1, 4);	sound7(2, 4);	sound7(-2, 4);	sound7(-1, 4);	sound7(-2, 4);	sound7(-2, 4);
}

void music_test(void) {
	soundTPU3_TEST();
	soundTPU5_TEST();
}