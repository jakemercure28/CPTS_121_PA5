#include "functions.h"

void print_rules(void) {
	printf("Yahtzee is composed of two sections. A upper section and a lower section.\nA total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\nThe upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\nIf a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\nOnce a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\nIf the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus.\nThe lower section contains a number of poker like combinations.\n7 = 3 of a kind\n8 = 4 of a kind\n9 = Fullhouse\n10 = Small straight\n11 = Large straight\n12 = Yahtzee (5 of a kind)\n13 = Chance (sum all dice)");
}

int get_menu_option(void) {
	int option = 1;
	do {
		printf("1.	Rules\n2.	Play Yahtzee\n3.	Exit\n\nEnter: ");
		scanf("%d", &option);
	}
	while (option < 0 || option > 3); // makes player choose option on menu

	return option;
}

int get_player_count(void) {

	int players = 0;
	
	do {
		printf("\n\nEnter the number of players:");
		scanf("%d", &players);
	} while (players < 0 || players > 4);
	 
	return players;
}

int press_roll(void) {
	
	int option = 0;
	do {
		printf("\n1. Roll again\n2. Pick option\n\nEnter: ");
		scanf("%d", &option);

		switch (option) {
		case 1: return 1;
			break;
		case 2: return 2;
			break;
		}
	} while (option != 1 || option != 2);
}

int roll_dice(void) {
	int die = rand() % 6 + 1; // determines random number between 1-6
	return die; // returns the rolled die to main
}

void display_dice(int dice_array[]) {

	for (int i = 0; i < 5; i++) {
		switch (dice_array[i]) { // prints correct die to console
	case 1:
		printf("\n+-------+\n|       |\n|   o   |\n|       |\n+-------+");
		break;

	case 2:
		printf("\n+-------+\n| o     |\n|       |\n|     o |\n+-------+\n");
		break;

	case 3:
		printf("\n+-------+\n| o     |\n|   o   |\n|     o |\n+-------+\n");
		break;

	case 4:
		printf("\n+-------+\n| o   o |\n|       |\n| o   o |\n+-------+\n");
		break;

	case 5:
		printf("\n+-------+\n| o   o |\n|   o   |\n| o   o |\n+-------+\n");
		break;

	case 6:
		printf("\n+-------+\n| o   o |\n| o   o |\n| o   o |\n+-------+\n");
		break;
	}
	}
}

void display_score_sheet(int scores_array[][4], int num_players) {

	switch (num_players) {
	case 1:printf("\n P| 1 |");
		printf("\n-------");
		break;
	case 2:printf("\n P| 1 | 2 |");
		printf("\n-----------");
		break;
	case 3:printf("\n P| 1 | 2 | 3 |");
		printf("\n---------------");
		break;
	case 4:printf("\n P| 1 | 2 | 3 | 4 |");
		printf("\n-------------------");
	}

	for (int row = 0; row < 13; row++) {
		if (row > 8) { // offset the display board
			printf("\n%d|", row + 1);
		}
		else printf("\n %d|", row + 1);
		for (int column = 0; column < num_players; column++) {

			printf(" %d |", scores_array[row][column]);

		}

	}
}

void get_score_option(int* option) {

	int option_local = 0;
	// player must now choose an option
	printf("\nEnter option (1 - 13)");
	scanf("%d", &option_local);

	*option = option_local;

	
}

void update_score_sheet(int dice_array[], int scores_array[][4], int option, int player) {
	
	int count = 0, total = 0, sum = 0, temp = 0, index = 0, index2 = 0;

	// sort array in ascending order
	for (int index = 0; index < 5; index++) {
		for (int index2 = index + 1; index2 < 5; index2++) {

			if (dice_array[index] > dice_array[index2]) {
				temp = dice_array[index];
				dice_array[index] = dice_array[index2];
				dice_array[index2] = temp;
			}
		}
	}


	// assign scoreboard option
	switch (option) {

	case 1: // ones: sums all ones together

		for (int i = 0; i < 5; i++) {
			if (dice_array[i] == 1) {
				sum++;
			}
		}
		break;

	case 2: // twos: sums all twos together
		for (int i = 0; i < 5; i++) {
			if (dice_array[i] == 2) {
				sum += 2;
			}
		}
		break;

	case 3: // threes: sums all threes together
		for (int i = 0; i < 5; i++) {
			if (dice_array[i] == 3) {
				sum += 3;
			}
		}
		break;

	case 4: // fours: sums all fours together
		for (int i = 0; i < 5; i++) {
			if (dice_array[i] == 4) {
				sum += 4;
			}
		}
		break;

	case 5: // fives: sums all fives together
		for (int i = 0; i < 5; i++) {
			if (dice_array[i] == 5) {
				sum += 5;
			}
		}
		break;

	case 6: // sixes: sums all sixes together
		for (int i = 0; i < 5; i++) {
			if (dice_array[i] == 6) {
				sum += 6;
			}
		}
		break;

	case 7: // three of a kind: check then sum total

		for (int i = 0; i < 5; i++) {
			total += dice_array[i];
			for (int j = i; j < 4; j++) {
				if (dice_array[i] == dice_array[j + 1]) {
					count++;
				}
			}
		}
		if (count >= 2) {
			sum = total;
		}
		break;

	case 8: // four of a kind:  check then sum total

		for (int i = 0; i < 5; i++) {
			total += dice_array[i];
			for (int j = i; j < 4; j++) {
				if (dice_array[i] == dice_array[j + 1]) {
					count++;
				}
			}
		}
		if (count >= 3) {
			sum = total;
		}
		break;


	case 9: // full house: dice show only 2 different values

		for (int i = 0; i < 5; i++) {

			for (int j = i; j < 4; j++) {
				if (dice_array[i] == dice_array[j + 1]) {
					count++;
				}
			}
		}
		if (count >= 2) {
			sum = 25;
		}
		break;

	case 10: // small straight: sequence of 4 or more

		for (int i = 0; i < 5; i++) {

			if (dice_array[i] == (dice_array[i + 1]) - 1) {
				count++;
			}
		}
		if (count >= 3) {
			sum = 30;
		}
		break;

	case 11: // large straight: sequence of 5

		for (int i = 0; i < 5; i++) {

			if (dice_array[i] == (dice_array[i + 1]) - 1) {
				count++;
			}
		}
		if (count == 4) {
			sum = 40;
		}
		break;

	case 12: // Yahtzee: 5 of a kind

		for (int i = 0; i < 5; i++) {

			if (dice_array[i] == dice_array[i + 1]) {
				count++;
			}
		}
		if (count == 4) {
			sum = 50;
		}
		break;

	case 13: // chance: sum all dice

		for (int i = 0; i < 5; i++) {
			sum += dice_array[i];
		}
		break;
	}

	// update score sheet array and display new scoresheet for that player
	scores_array[option - 1][player - 1] = sum;
}

int swap_player(int *num_players, int *player) {
		
	switch (*num_players) {
	// 1 player
	case 1: *player = 1;
		break;

	// 2 players
	case 2:
		switch (*player) {
		case 1: *player = 2;
			break;
		case 2: *player = 1;
			break;
		}
		break;

	// 3 players
	case 3:
		switch (*player) {
		case 1: *player = 2;
			break;
		case 2: *player = 3;
			break;
		case 3: *player = 1;
		}
		break;

	// 4 players
	case 4:
		switch (*player) {
		case 1: *player = 2;
			break;
		case 2: *player = 3;
			break;
		case 3: *player = 4;
			break;
		case 4: *player = 1;
			break;
		}
		break;
	}

	printf("\nPlayer %d is up!", *player);
}