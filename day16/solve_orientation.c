#include <stdio.h>
#include <stdbool.h>

#define CUBE_LEN 54

#define CW(i)    ((i + 1) % 4)
#define ONE80(i) ((i + 2) % 4)
#define CCW(i)   ((i + 3) % 4)


/* Globals */
/*int original_cube[CUBE_LEN] = {0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,0,0,0,1,1,1,2,2,2,3,3,3,0,0,0,1,1,1,2,2,2,3,3,3,0,0,0,2,2,2,2,2,2,2,2,2};*/
int original_cube[CUBE_LEN] = {2, 3, 0, 2, 3, 3, 3, 1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 0, 0, 1, 3, 3, 2, 1, 3, 0, 0, 1, 1, 3, 1, 1, 3, 3, 2, 1, 1, 1, 1, 0, 0, 1, 1, 1, 3, 1, 1, 1, 0, 1, 1, 1, 2, 2};
int cube[CUBE_LEN];
int tmp_cube[CUBE_LEN];

void reset_cube();
void sync_tmp_cube();

char ori(int);
void print_cube();

void f();
void r();
void u();
void l();
void b();
void d();

void move_cube(int move) {
	while (move >= 0) {
		switch (move % 6) {
			case 0: {f(); break;}
			case 1: {r(); break;}
			case 2: {u(); break;}
			case 3: {l(); break;}
			case 4: {b(); break;}
			case 5: {d(); break;}
		}
		move -= 6;
	}
}


bool chk_cube();

void print_scramble(int scramble) {
	switch (scramble) {
		case 0: { printf ("f "); break; }
		case 1: { printf ("r "); break; }
		case 2: { printf ("u "); break; }
		case 3: { printf ("l "); break; }
		case 4: { printf ("b "); break; }
		case 5: { printf ("d "); break; }
		case 6: { printf ("f2 "); break; }
		case 7: { printf ("r2 "); break; }
		case 8: { printf ("u2 "); break; }
		case 9: { printf ("l2 "); break; }
		case 10: { printf ("b2 "); break; }
		case 11: { printf ("d2 "); break; }
		case 12: { printf ("f\' "); break; }
		case 13: { printf ("r\' "); break; }
		case 14: { printf ("u\' "); break; }
		case 15: { printf ("l\' "); break; }
		case 16: { printf ("b\' "); break; }
		case 17: { printf ("d\' "); break; }
	}
}

int main(void) {

	reset_cube();
	
	for (int i_0=0; i_0 < 18; i_0++) {
		for (int i_1=0; i_1 < 18; i_1++) {
			for (int i_2=0; i_2 < 18; i_2++) {
				for (int i_3=0; i_3 < 18; i_3++) {
					for (int i_4=0; i_4 < 18; i_4++) {
						move_cube(i_0);
						move_cube(i_1);
						move_cube(i_2);
						move_cube(i_3);
						move_cube(i_4);
						if (chk_cube()) {
							print_scramble(i_0);
							print_scramble(i_1);
							print_scramble(i_2);
							print_scramble(i_3);
							print_scramble(i_4);
							printf("\n");
							return 0;
						}
						reset_cube();
					}
				}
			}
		}
	}
	return 0;
}    


bool chk_cube() {
	for (int i=0; i < 9; i++) {
		if (cube[i] != cube[4]) return false;
	}

	for (int i=9; i < 12; i++) {
		if (cube[i] != cube[22]) return false;
	}
	for (int i=21; i < 24; i++) {
		if (cube[i] != cube[22]) return false;
	}
	for (int i=33; i < 36; i++) {
		if (cube[i] != cube[22]) return false;
	}

	for (int i=12; i < 15; i++) {
		if (cube[i] != cube[25]) return false;
	}
	for (int i=24; i < 27; i++) {
		if (cube[i] != cube[25]) return false;
	}
	for (int i=36; i < 39; i++) {
		if (cube[i] != cube[25]) return false;
	}
	
	for (int i=15; i < 18; i++) {
		if (cube[i] != cube[28]) return false;
	}
	for (int i=27; i < 30; i++) {
		if (cube[i] != cube[28]) return false;
	}
	for (int i=39; i < 42; i++) {
		if (cube[i] != cube[28]) return false;
	}

	for (int i=18; i < 21; i++) {
		if (cube[i] != cube[31]) return false;
	}
	for (int i=30; i < 33; i++) {
		if (cube[i] != cube[31]) return false;
	}
	for (int i=42; i < 45; i++) {
		if (cube[i] != cube[31]) return false;
	}

	for (int i=45; i < 54; i++) {
		if (cube[i] != cube[49]) return false;
	}

	return true;
}


void f() {
	sync_tmp_cube();

	cube[6] = CW(tmp_cube[35]);
	cube[7] = CW(tmp_cube[23]);
	cube[8] = CW(tmp_cube[11]);

	cube[11] = CW(tmp_cube[45]);
	cube[23] = CW(tmp_cube[46]);
	cube[35] = CW(tmp_cube[47]);

	cube[15] = CW(tmp_cube[6]);
	cube[27] = CW(tmp_cube[7]);
	cube[39] = CW(tmp_cube[8]);

	cube[45] = CW(tmp_cube[39]);
	cube[46] = CW(tmp_cube[27]);
	cube[47] = CW(tmp_cube[15]);

	cube[12] = CW(tmp_cube[36]);
	cube[13] = CW(tmp_cube[24]);
	cube[14] = CW(tmp_cube[12]);
	cube[24] = CW(tmp_cube[37]);
	cube[25] = CW(tmp_cube[25]);
	cube[26] = CW(tmp_cube[13]);
	cube[36] = CW(tmp_cube[38]);
	cube[37] = CW(tmp_cube[26]);
	cube[38] = CW(tmp_cube[14]);
}


void r() {
	sync_tmp_cube();

	cube[2] = tmp_cube[14];
	cube[5] = tmp_cube[26];
	cube[8] = tmp_cube[38];

	cube[14] = tmp_cube[47];
	cube[26] = tmp_cube[50];
	cube[38] = tmp_cube[53];

	cube[47] = ONE80(tmp_cube[42]);
	cube[50] = ONE80(tmp_cube[30]);
	cube[53] = ONE80(tmp_cube[18]);

	cube[18] = ONE80(tmp_cube[8]);
	cube[30] = ONE80(tmp_cube[5]);
	cube[42] = ONE80(tmp_cube[2]);

	cube[15] = CW(tmp_cube[39]);
	cube[16] = CW(tmp_cube[27]);
	cube[17] = CW(tmp_cube[15]);
	cube[27] = CW(tmp_cube[40]);
	cube[28] = CW(tmp_cube[28]);
	cube[29] = CW(tmp_cube[16]);
	cube[39] = CW(tmp_cube[41]);
	cube[40] = CW(tmp_cube[29]);
	cube[41] = CW(tmp_cube[17]);
}


void u() {
	sync_tmp_cube();

	cube[9] = tmp_cube[12];
	cube[10] = tmp_cube[13];
	cube[11] = tmp_cube[14];

	cube[12] = tmp_cube[15];
	cube[13] = tmp_cube[16];
	cube[14] = tmp_cube[17];

	cube[15] = tmp_cube[18];
	cube[16] = tmp_cube[19];
	cube[17] = tmp_cube[20];

	cube[18] = tmp_cube[9];
	cube[19] = tmp_cube[10];
	cube[20] = tmp_cube[11];

	cube[0] = CW(tmp_cube[6]);
	cube[1] = CW(tmp_cube[3]);
	cube[2] = CW(tmp_cube[0]);
	cube[3] = CW(tmp_cube[7]);
	cube[4] = CW(tmp_cube[4]);
	cube[5] = CW(tmp_cube[1]);
	cube[6] = CW(tmp_cube[8]);
	cube[7] = CW(tmp_cube[5]);
	cube[8] = CW(tmp_cube[2]);
}


void l() {
	sync_tmp_cube();

	cube[0] = ONE80(tmp_cube[44]);
	cube[3] = ONE80(tmp_cube[32]);
	cube[6] = ONE80(tmp_cube[20]);

	cube[12] = tmp_cube[0];
	cube[24] = tmp_cube[3];
	cube[36] = tmp_cube[6];

	cube[45] = tmp_cube[12];
	cube[48] = tmp_cube[24];
	cube[51] = tmp_cube[36];

	cube[20] = ONE80(tmp_cube[51]);
	cube[32] = ONE80(tmp_cube[48]);
	cube[44] = ONE80(tmp_cube[45]);

	cube[9]  = CW(tmp_cube[33]);
	cube[10] = CW(tmp_cube[21]);
	cube[11] = CW(tmp_cube[9]);
	cube[21] = CW(tmp_cube[34]);
	cube[22] = CW(tmp_cube[22]);
	cube[23] = CW(tmp_cube[10]);
	cube[33] = CW(tmp_cube[35]);
	cube[34] = CW(tmp_cube[23]);
	cube[35] = CW(tmp_cube[11]);
}


void b() {
	sync_tmp_cube();

	cube[0] = CCW(tmp_cube[17]);
	cube[1] = CCW(tmp_cube[29]);
	cube[2] = CCW(tmp_cube[41]);

	cube[9] =  CCW(tmp_cube[2]);
	cube[21] = CCW(tmp_cube[1]);
	cube[33] = CCW(tmp_cube[0]);

	cube[17] = CCW(tmp_cube[53]);
	cube[29] = CCW(tmp_cube[52]);
	cube[41] = CCW(tmp_cube[51]);

	cube[51] = CCW(tmp_cube[9]);
	cube[52] = CCW(tmp_cube[21]);
	cube[53] = CCW(tmp_cube[33]);

	cube[18] = CW(tmp_cube[42]);
	cube[19] = CW(tmp_cube[30]);
	cube[20] = CW(tmp_cube[18]);
	cube[30] = CW(tmp_cube[43]);
	cube[31] = CW(tmp_cube[31]);
	cube[32] = CW(tmp_cube[19]);
	cube[42] = CW(tmp_cube[44]);
	cube[43] = CW(tmp_cube[32]);
	cube[44] = CW(tmp_cube[20]);
}


void d() {
	sync_tmp_cube();

	cube[33] = tmp_cube[42];
	cube[34] = tmp_cube[43];
	cube[35] = tmp_cube[44];

	cube[36] = tmp_cube[33];
	cube[37] = tmp_cube[34];
	cube[38] = tmp_cube[35];

	cube[39] = tmp_cube[36];
	cube[40] = tmp_cube[37];
	cube[41] = tmp_cube[38];

	cube[42] = tmp_cube[39];
	cube[43] = tmp_cube[40];
	cube[44] = tmp_cube[41];

	cube[45] = CW(tmp_cube[51]);
	cube[46] = CW(tmp_cube[48]);
	cube[47] = CW(tmp_cube[45]);
	cube[48] = CW(tmp_cube[52]);
	cube[49] = CW(tmp_cube[49]);
	cube[50] = CW(tmp_cube[46]);
	cube[51] = CW(tmp_cube[53]);
	cube[52] = CW(tmp_cube[50]);
	cube[53] = CW(tmp_cube[47]);
}


void reset_cube() {
	for (int i=0; i < CUBE_LEN; i++) {
		cube[i] = original_cube[i];
	}
}


void sync_tmp_cube() {
	for (int i=0; i < CUBE_LEN; i++) {
		tmp_cube[i] = cube[i];
	}
}


char ori(int orientation) {
	switch(orientation) {
		case 0:
			return '^';
		case 1:
			return '>';
		case 2:
			return 'v';
		case 3:
			return '<';
		default:
			return 'X';
	}
}


void print_cube() {
	printf("            .---.---.---.\n");
	printf("            | %c | %c | %c |\n", ori(cube[0]), ori(cube[1]), ori(cube[2]));
	printf("            :---:---:---:\n");
	printf("            | %c | %c | %c |\n", ori(cube[3]), ori(cube[4]), ori(cube[5]));
	printf("            :---:---:---:\n");
	printf("            | %c | %c | %c |\n", ori(cube[6]), ori(cube[7]), ori(cube[8]));
	printf(".---.---.---:---:---:---:---.---.---.---.---.---.\n");
	printf("| %c | %c | %c ", ori(cube[9]), ori(cube[10]), ori(cube[11]));
	printf("| %c | %c | %c ", ori(cube[12]), ori(cube[13]), ori(cube[14]));
	printf("| %c | %c | %c ", ori(cube[15]), ori(cube[16]), ori(cube[17]));
	printf("| %c | %c | %c |\n", ori(cube[18]), ori(cube[19]), ori(cube[20]));
	printf(":---:---:---:---:---:---:---:---:---:---:---:---:\n");
	printf("| %c | %c | %c ", ori(cube[21]), ori(cube[22]), ori(cube[23]));
	printf("| %c | %c | %c ", ori(cube[24]), ori(cube[25]), ori(cube[26]));
	printf("| %c | %c | %c ", ori(cube[27]), ori(cube[28]), ori(cube[29]));
	printf("| %c | %c | %c |\n", ori(cube[30]), ori(cube[31]), ori(cube[32]));
	printf(":---:---:---:---:---:---:---:---:---:---:---:---:\n");
    printf("| %c | %c | %c ", ori(cube[33]), ori(cube[34]), ori(cube[35]));
	printf("| %c | %c | %c ", ori(cube[36]), ori(cube[37]), ori(cube[38]));
	printf("| %c | %c | %c ", ori(cube[39]), ori(cube[40]), ori(cube[41]));
	printf("| %c | %c | %c |\n", ori(cube[42]), ori(cube[43]), ori(cube[44]));
	printf("'---'---'---:---:---:---:---'---'---'---'---'---'\n");
	printf("            | %c | %c | %c |\n", ori(cube[45]), ori(cube[46]), ori(cube[47]));
	printf("            :---:---:---:\n");
	printf("            | %c | %c | %c |\n", ori(cube[48]), ori(cube[49]), ori(cube[50]));
	printf("            :---:---:---:\n");
	printf("            | %c | %c | %c |\n", ori(cube[51]), ori(cube[52]), ori(cube[53]));

	printf("            '---'---'---'\n");
	printf("\n");
}



