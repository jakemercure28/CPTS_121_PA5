#ifndef FUNCTIONS_H // guard code
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> // rand (), srand ()
#include <time.h>

void print_rules(void);

int get_menu_option(void);

int get_player_count(void);

int press_roll(void);

int roll_dice(void);

void display_score_sheet(int scores_array[][4], int num_players);

void display_dice(int dice_array[]);

void get_score_option(int *option);

void update_score_sheet(int dice_array[], int scores_array[][4], int option, int player);

int swap_player(int *num_players, int *player);
#endif