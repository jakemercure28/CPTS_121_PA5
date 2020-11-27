/*
Programmer: Jake Mercure
What: Yahtzee game, 1-4 players, age 8+

Start Date: 3/16/2020

End Date: 4/5/2020
Apologies on the delay Matt, thanks for understanding!

*/

#include "functions.h"

int main(void) {

	// used for time rand () function
	srand((unsigned int)time(NULL));

	// critical gameplay variables
	int num_players = 1, player = 0, option = 0, rolls = 0, 
		options_left = 0, sum = 0, gameplay = 0;

	// scores array and dice array
	int scores_array[13][4];
	int dice_array[5];

	// parallel array for saved dice
	int selection_array[5] = { 0,0,0,0,0 };
	int die_pos = 0, save_die = 0;

	// initialize scores array to 0
	for (int row = 0; row < 13; row++) {

		for (int column = 0; column < 4; column++) {
			scores_array[row][column] = 0;
		}
	}

	do {
		// player selects menu option
		option = get_menu_option();

		// process menu option
		switch (option) {
		case 1: // print rules
			print_rules();
			num_players = get_player_count(); // get amount of players playing the game (1-4)
			break;
		case 2: // start game
			num_players = get_player_count(); // get amount of players playing the game (1-4)
			break;
		case 3: // end program
			gameplay = 2;
			break;
		}
		// ends program
		if (gameplay == 2) {
			break;
		}

		// random player starts the game
		player = rand() % num_players + 1;

		// print the score board
		display_score_sheet(scores_array, num_players);

		// print player
		printf("\nPlayer %d is up!", player);

		// current player game loop
		do {

			// initial roll of 5  dice
			for (int i = 0; i < 5; i++) {
				dice_array[i] = roll_dice();
			}
			rolls++;

			// show dice
			display_dice(dice_array);

			// dice roll loop
			do {
				// ask player: 1. roll dice, 2. choose option
				option = press_roll();

				switch (option) {

				case 1: // re rolls dice

					// reset position in array
					die_pos = 0;

					// reads dice array
					for (int i = 0; i < 5; i++) {

						// ask player: 1. to save dice or 2. to not save dice
						printf("\nSave die?: %d\n\n1. Yes\n2. No", dice_array[die_pos]);
						scanf("%d", &save_die);

						// matches parallel array positions to remember saved die
						switch (save_die) {
						case 1: selection_array[die_pos] = dice_array[die_pos];
							// moves to next die
							die_pos++;
							break;

						default:
							// moves to next die
							die_pos++;
						}
					}

					// re rolls unsaved dice
					for (int i = 0; i < 5; i++) {

						// if not saved, then roll dice in that spot of the array
						if (selection_array[i] == 0) {
							dice_array[i] = roll_dice();
						}
						// if saved, then match the value in that location
						else if (selection_array[i] != 0) {
							dice_array[i] = selection_array[i];
						}
					}

					// add to rolls
					rolls++;

					// show new rolled dice
					display_dice(dice_array);

					break;
				case 2:
					rolls = 3;
					break;
				}
			} while (rolls < 3);

			// get score option 
			get_score_option(&option);

			// update scores, parameters: (dice array, scores array, option picked, current player)
			update_score_sheet(dice_array, scores_array, option, player);

			// print the score board so player can see new scores
			display_score_sheet(scores_array, num_players);

			// change player
			swap_player(&num_players, &player);

			// reset rolls and sum for next player
			rolls = 0, sum = 0;

			// add to options
			options_left++;

			// if options are not all picked, keep playing
		} while (options_left != (13 * num_players));

		printf("\nPlay again?\n1. Yes\n2. No");
		scanf("%d", &gameplay);

	} while (gameplay != 2);
	
	return 0;
}

