#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROW 104
#define COL 9
#define WORD 3
#define UNLINK_TOT_NUM 512
#define BASIS_TOT_NUM 512

void to_binary_f(int, char, char *);
char ucn_f(char *);
char sub_ucn_f(char *, char);
void lb_f(char *, char (*)[COL]);
void cn_f(char(*)[COL], char *, const char *);
char * lbp_f(char);
char * multiplier_f(char(*)[COL], char, int);

// Unlink Polynomials
char P_1O[] = "(1)";
char P_2O[] = "((v**(-1) - v) * z**(-1))";
char P_3O[] = "(((v**(-1) - v) * z**(-1))**2)";
char P_4O[] = "(((v**(-1) - v) * z**(-1))**3)";
char P_5O[] = "(((v**(-1) - v) * z**(-1))**4)";
char P_6O[] = "(((v**(-1) - v) * z**(-1))**5)";
// Unlink Polynomials

// Multiplier
char h1[] = "(v**(2 * n))";
char h2[] = "((v * z * (1 - v**(2 * n))) / (1 - v**2))";
char v1[] = "(v**(-2 * n))";
char v2[] = "((z * (1 - v**(-2 * n))) / (v**(-1) - v))";
// Multiplier

int main(int argc, char *argv[])
{
	// Files and their names
	FILE *in, *unlinks;
	char out_unlinks[FILENAME_MAX] = "unlinks.txt";
	// File and their names

	// Unlink
	char unlink[UNLINK_TOT_NUM][COL];
	char(*unlink_ptr)[COL], *unlink_col_ptr;
	int unlink_index = 0, unlink_col_index = 0;
	// Unlink

	// Unlink Component Numbers
	char ucn[UNLINK_TOT_NUM];
	char *ucn_ptr;
	int ucn_index = 0;
	// Unlink Component Numbers

	// Link 2n
	char link[ROW][COL];
	char(*link_row_ptr)[COL], *link_col_ptr;
	int link_row_index = 0;
	int link_col_index = 0;
	// Link 2n

	// Link Basis
	char basis[BASIS_TOT_NUM][COL];
	char(*basis_ptr)[COL], *basis_col_ptr;
	int basis_index = 0;
	int basis_col_index = 0;
	char cn[BASIS_TOT_NUM];  //component number
	// Link Basis

	// Assign values
	{
		unlink_ptr = unlink;
		unlink_col_ptr = unlink[0];
		ucn_ptr = ucn;
		link_row_ptr = link;
		link_col_ptr = link[0];
		basis_ptr = basis;
		basis_col_ptr = basis[0];
	}
	// Assign values

	// Check and open files
	{
		if (argc < 2) {
			fprintf(stderr, "Usage: %s filename\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		if ((in = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "I could not open the file \"%s\".\n", argv[1]);
			exit(EXIT_FAILURE);
		}

		if ((unlinks = fopen(out_unlinks, "w")) == NULL) {
			fprintf(stderr, "Can not create unlinks file.\n");
			exit(EXIT_FAILURE);
		}
	}
	// Check and open files

	// Calculate all unlinks
	for (unlink_index = 0; unlink_index < UNLINK_TOT_NUM; unlink_index++) {
		unlink_col_ptr = *unlink_ptr;
		to_binary_f(unlink_index, 1, unlink_col_ptr + COL - 1);
		unlink_ptr++;
	}
	// Calculate all unlinks

	// Calculate the number of components in each unlink
	unlink_ptr = unlink;
	for (ucn_index = 0; ucn_index < UNLINK_TOT_NUM; ucn_index++) {
		*ucn_ptr = ucn_f(*unlink_ptr);
		unlink_ptr++;
		ucn_ptr++;
	}
	// Calculate the number of components in each unlink

	// Display all unlinks and their numbers of components
	fprintf(unlinks, "Unlink\tNumber of components\n");
	for (unlink_index = 0; unlink_index < UNLINK_TOT_NUM; unlink_index++) {
		for (unlink_col_index = 0; unlink_col_index < COL; unlink_col_index++) {
			fprintf(unlinks, "%d", unlink[unlink_index][unlink_col_index]);
		}
		fprintf(unlinks, "\t%d\n", ucn[unlink_index]);
	}
	// Display all unlinks and their numbers of components

	// Read links into the computer memory
	{
		char link_tmp[ROW][COL][WORD];
		char(*link_tmp_col_ptr)[WORD], *link_tmp_word_ptr;

		link_tmp_col_ptr = link_tmp[0];
		link_tmp_word_ptr = link_tmp[0][0];

		for (link_row_index = 0; link_row_index < ROW; link_row_index++) {
			for (link_col_index = 0; link_col_index < COL; link_col_index++) {
				fscanf(in, "%s", link_tmp_col_ptr++);
			}
		}

		link_tmp_word_ptr = link_tmp_word_ptr + 1;
		for (link_row_index = 0; link_row_index < ROW; link_row_index++) {
			for (link_col_index = 0; link_col_index < COL; link_col_index++) {
				if (*link_tmp_word_ptr == 'h')
					*link_col_ptr = 'h';
				else
					*link_col_ptr = 'v';
				link_tmp_word_ptr = link_tmp_word_ptr + 3;
				link_col_ptr++;
			}
		}
	}
	// Read links into the computer memory

	// Calculate HOMFLY polynomials
	FILE *homfly[ROW];
	char out_homfly[ROW][4] = {
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13",
		"14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
		"25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35",
		"36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46",
		"47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57",
		"58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68",
		"69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
		"80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90",
		"91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101",
		"102", "103", "104" };
	char(*out_homfly_ptr)[4];
	out_homfly_ptr = out_homfly;

	for (link_row_index = 0; link_row_index < ROW; link_row_index++) {
		if ((homfly[link_row_index] = fopen(out_homfly[link_row_index], "w")) == NULL) {
			fprintf(stderr, "Can not create %s file.\n", out_homfly[link_row_index]);
			exit(EXIT_FAILURE);
		}

		lb_f(*link_row_ptr, basis_ptr);
		cn_f(basis_ptr, cn, ucn);

		for (basis_index = 0; basis_index < BASIS_TOT_NUM; basis_index++) {
			for (basis_col_index = 0; basis_col_index < COL; basis_col_index++) {
				fprintf(homfly[link_row_index], "%s", 
					multiplier_f(link_row_ptr, basis[basis_index][basis_col_index], basis_col_index));
			}
			fprintf(homfly[link_row_index], "%s", lbp_f(cn[basis_index]));
			if (basis_index < BASIS_TOT_NUM - 1) {
				fprintf(homfly[link_row_index], " +\n");
			}
		}

		if (fclose(homfly[link_row_index]) != 0)
			fprintf(stderr, "Error in closing files\n");

		link_row_ptr++;
	}
	// Calculate HOMFLY polynomials

	// Close files
	if (fclose(in) != 0 || fclose(unlinks) != 0)
		fprintf(stderr, "Error in closing files\n");
	// Close files

	printf("Calculation complete. Congratulations!\n");

	return 0;
}

// To_binary
void to_binary_f(int num, char times, char *tb_ptr)
{
	char remainder = 0;

	remainder = num % 2;

	if (times < COL) {
		tb_ptr--;
		to_binary_f(num / 2, ++times, tb_ptr);
		tb_ptr++;
	}

	*tb_ptr = remainder;
}
// To_binary

// The number of components in the unlink
char ucn_f(char *u_ptr)
{
	char zero_num = 0;
	char cpnt_num = 0;
	char *u_ptrv;
	int u_col_index = 0;

	u_ptrv = u_ptr;

	for (u_col_index = 0; u_col_index < COL; u_col_index++) {
		if (*u_ptrv == 0)
			zero_num++;
		u_ptrv++;
	}

	if (zero_num >= 0 && zero_num <= 2) {
		cpnt_num = 6 - zero_num;
	}
	else if (zero_num >= 3 && zero_num <= 4) {
		cpnt_num = sub_ucn_f(u_ptr, zero_num);
	}
	else if (zero_num == 5) {
		if ((*(u_ptr + 0) == 0 && *(u_ptr + 1) == 0 && *(u_ptr + 4) == 0 &&
			*(u_ptr + 5) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 1) == 0 && *(u_ptr + 2) == 0 && *(u_ptr + 3) == 0 &&
			*(u_ptr + 5) == 0 && *(u_ptr + 6) == 0) ||
			(*(u_ptr + 0) == 0 && *(u_ptr + 2) == 0 && *(u_ptr + 3) == 0 &&
			*(u_ptr + 4) == 0 && *(u_ptr + 7) == 0) ||
			(*(u_ptr + 0) == 0 && *(u_ptr + 3) == 0 && *(u_ptr + 5) == 0 &&
			*(u_ptr + 7) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 1) == 0 && *(u_ptr + 3) == 0 && *(u_ptr + 4) == 0 &&
			*(u_ptr + 6) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 2) == 0 && *(u_ptr + 4) == 0 && *(u_ptr + 5) == 0 &&
			*(u_ptr + 6) == 0 && *(u_ptr + 7) == 0)){
			cpnt_num = 3;
		}
		else {
			cpnt_num = sub_ucn_f(u_ptr, zero_num);
		}
	}
	else if (zero_num == 6) {
		if ((*(u_ptr + 0) == 0 && *(u_ptr + 1) == 0 && *(u_ptr + 2) == 0  &&
			 *(u_ptr + 6) == 0 && *(u_ptr + 7) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 0) == 0 && *(u_ptr + 1) == 0 && *(u_ptr + 2) == 0  &&
			 *(u_ptr + 3) == 0 && *(u_ptr + 5) == 0 && *(u_ptr + 6) == 0) ||
			(*(u_ptr + 0) == 0 && *(u_ptr + 1) == 0 && *(u_ptr + 2) == 0  &&
			 *(u_ptr + 3) == 0 && *(u_ptr + 4) == 0 && *(u_ptr + 7) == 0) ||
			(*(u_ptr + 0) == 0 && *(u_ptr + 1) == 0 && *(u_ptr + 2) == 0  &&
			 *(u_ptr + 4) == 0 && *(u_ptr + 5) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 0) == 0 && *(u_ptr + 3) == 0 && *(u_ptr + 5) == 0  &&
			 *(u_ptr + 6) == 0 && *(u_ptr + 7) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 1) == 0 && *(u_ptr + 3) == 0 && *(u_ptr + 4) == 0  &&
			 *(u_ptr + 6) == 0 && *(u_ptr + 7) == 0 && *(u_ptr + 8) == 0) ||
			(*(u_ptr + 2) == 0 && *(u_ptr + 4) == 0 && *(u_ptr + 5) == 0  &&
			 *(u_ptr + 6) == 0 && *(u_ptr + 7) == 0 && *(u_ptr + 8) == 0)){
			cpnt_num = 4;
		}
		else {
			cpnt_num = 2;
		}
	}
	else if (zero_num == 7) {
		cpnt_num = 3;
	}
	else if (zero_num == 8) {
		cpnt_num = 4;
	}
	else if (zero_num == 9) {
		cpnt_num = 5;
	}

	return cpnt_num;
}
// The number of components in the unlink

// Subfunction of ucn_f
char sub_ucn_f(char *su_ptr, char szero_num)
{
	char scpnt_num = 0;
	scpnt_num = 6 - szero_num;
	if ((*(su_ptr + 0) == 0 && *(su_ptr + 1) == 0 &&
		*(su_ptr + 2) == 0) ||
		(*(su_ptr + 6) == 0 && *(su_ptr + 7) == 0 &&
		*(su_ptr + 8) == 0) ||
		(*(su_ptr + 0) == 0 && *(su_ptr + 3) == 0 &&
		*(su_ptr + 5) == 0 && *(su_ptr + 6) == 0) ||
		(*(su_ptr + 1) == 0 && *(su_ptr + 3) == 0 &&
		*(su_ptr + 4) == 0 && *(su_ptr + 7) == 0) ||
		(*(su_ptr + 2) == 0 && *(su_ptr + 4) == 0 &&
		*(su_ptr + 5) == 0 && *(su_ptr + 8) == 0)){ 
		scpnt_num += 2;
	}
	return scpnt_num;
}
// Subfunction of ucn_f

// Construct link basis
void lb_f(char *link_ptr, char (*lb_ptr)[COL])
{
	int lb_index = 0;
	int lb_col_index = 0;
	int x = 0;
	int partition = 0;
	char(*lb_ptrv)[COL];

	lb_ptrv = lb_ptr;

	for (lb_col_index = 0; lb_col_index < COL; lb_col_index++) {
		lb_ptrv = lb_ptr;
		x = (int)pow((double)2, (double)(lb_col_index + 1));
		partition = BASIS_TOT_NUM / x;
		if (*(link_ptr + lb_col_index) == 'h') {
			for (lb_index = 0; lb_index < BASIS_TOT_NUM; lb_index++) {
				if (((lb_index / partition) % 2) == 0) {
					*(*lb_ptrv + lb_col_index) = 1;
				}
				else {
					*(*lb_ptrv + lb_col_index) = 0;
				}
				lb_ptrv++;
			}
		}
		else if (*(link_ptr + lb_col_index) == 'v') {
			for (lb_index = 0; lb_index < BASIS_TOT_NUM; lb_index++) {
				if (((lb_index / partition) % 2) == 0) {
					*(*lb_ptrv + lb_col_index) = 0;
				}
				else {
					*(*lb_ptrv + lb_col_index) = 1;
				}
				lb_ptrv++;
			}
		}
	}
}
// Construct link basis

// Calculate component numbers of link basis
void cn_f(char(*lb_ptr)[COL], char *cn, const char *ucn)
{
	int lb_index = 0;
	int lb_col_index = 0;
	int dr = 0;  //decimal representation
	char(*lb_ptrv)[COL];
	char *cn_ptr;

	lb_ptrv = lb_ptr;
	cn_ptr = cn;

	for (lb_index = 0; lb_index < BASIS_TOT_NUM; lb_index++) {
		dr = 0;
		for (lb_col_index = 0; lb_col_index < COL; lb_col_index++) {
			dr = dr + (*(*lb_ptrv + lb_col_index))*((int)pow((double)2, (double)(COL - lb_col_index - 1)));
		}
		lb_ptrv++;
		*cn_ptr = *(ucn + dr);
		cn_ptr++;
	}
}
// Calculate component numbers of link basis

// Obtain the HOMFLY polynomials of link basis
char * lbp_f(char cn)
{
	switch (cn)
	{
		case 1: return P_1O;
		case 2: return P_2O;
		case 3: return P_3O;
		case 4: return P_4O;
		case 5: return P_5O;
		case 6: return P_6O;
		default: return 0;
	}
}
// Obtain the HOMFLY polynomials of link basis

// Derive multipliers
char * multiplier_f(char(*link_ptr)[COL], char bc, int i)
{
	if ((*((*link_ptr) + i)) == 'h') {
		switch (bc)
		{
			case 0: return h2;
			case 1: return h1;
			default: return 0;
		}
	}
	else if ((*((*link_ptr) + i)) == 'v') {
		switch (bc)
		{
			case 0: return v1;
			case 1: return v2;
			default: return 0;
		}
	}
}
// Derive multipliers
