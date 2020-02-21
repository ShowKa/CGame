void music_exibisition(void);

void music_exibisition(void) {
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

void music_morning(void) {
	setBuzzerTempo(90.0);
	// c1 f1.5 g.5 a1
	sound(3, 4);
	sound(5, 6);
	sound(2, 2);
	sound(2, 4);
	// f1 bb0.75 a.0.25 g.5 f.5 g1 
	sound(-4, 4);
	sound(5, 3);
	sound(-1, 1);
	sound(-2, 2);
	sound(-2, 2);
	sound(2, 4);
	// c1 g1.5 a.5 bb1
	sound(-7, 4);
	sound(7, 6);
	sound(2, 2);
	sound(1, 4);
	// +d1 +c2Å@a1
	sound7(4, 4);
	sound7(-2, 8);
	sound7(-3, 4);
	// f.5 g.5 +c1.5 +d.5 +c1
	sound(-4, 2);
	sound(2, 2);
	sound(5, 6);
	sound(2, 2);
	sound(-2, 4);
	// g.5 a.5 bb1.5 +c.5 bb1
	sound(-5, 2);
	sound(2, 2);
	sound(1, 6);
	sound(2, 2);
	sound(-2, 4);
	// a.5 bb.5 a1.5 f.5 c1
	sound7(-1, 2);
	sound7(1, 2);
	sound7(-1, 6);
	sound7(-4, 2);
	sound7(-5, 1);
	// g1 f3.
	sound7(7, 1);
	sound7(-2, 3);
}

void music(void) {
	music_exibisition();
}
