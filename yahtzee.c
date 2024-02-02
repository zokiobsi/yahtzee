#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "yahtzee.h"

//Hello world! testing git and github

//the printer lines, used to build the graphics.  global because several functions need these and passing by reference makes function calls very long
char printLine1[300] = "";
char printLine2[300] = "";
char printLine3[300] = "";
char printLine4[300] = "";
char printLine5[300] = "";
char printLine6[300] = "";
char printLine7[300] = "";
char printLine8[300] = "";

int main() {

	//seed random number generator
	srand(time(0));

	int play = 1;
	char enter = ' ';
	
	//calibrateScreen();
	//splashScreen();

	//loop until the input from displayGameMenu is EXIT
	while (play) {
		switch (displayGameMenu()) {
		
		//if input is RULES, displays the rules screen
		case RULES:
			clearScreen();
			gameRules();
			break;

		//if input is GAME rolls several sets of random dice and prints them (for now)
		case GAME:
			clearScreen();
			playGame();
			//displayRandomDice();
			clearScreen();
			break;

		//if input is EXIT, ends the loop and program ends
		case EXIT:
			printf("\nThank you for playing!\n");
			play = 0;
			break;
		
		//catches any bad entries
		default:
			printf("\nIncorrect option, hit enter and try again.\n");
			scanf("%c", enter);
			break;
		
		}//end switch
	}//end while
	
	return 0;
}//end main

void initializeDieArray(int dieArray[MAX_DIE]) {
	//a simple function to set all dice in passed array to value 0
	//the function is both initializeDice and resetKeep from the assignment.  I don't see a reason to make 2 functions that do the exact same thing.

	for (int i = 0; i < MAX_DIE; i++) {
		dieArray[i] = 0;
	}//end for loop

}//end initializeDice

void playGame() {
	//function to play the game, ties a lot of functions together

	int scoreCard[CATEGORIES][COLS];
	int category = 0; //category for the scorecard

	int keep[MAX_DIE]; //die to be kept
	int dice[MAX_DIE]; //rolled die
	initializeDieArray(dice);
	initializeDieArray(keep);
	initializeScores(scoreCard);
	//int keepTEST[MAX_DIE] = {1, 1, 1, 1, 1};

	//iterate for TURNS times
	for (int turn = 0; turn < TURNS; turn++){
		
		//at the begining of each turn reset dice and keep arrays
		initializeDieArray(dice);
		initializeDieArray(keep);

		//prints the header line for each turn (add 1 beacuse turn starts at 0 for use with arrays)
		printf("\nTurn %d / %d\n===========\n", turn+1, TURNS);

		//iterate for ROLLS times, start of a turn
		for (int rolls = 0; rolls < ROLLS; rolls++) {

			printf("\nRolling...\n");

			rollDice(dice, keep); //roll the die except those marked for keep

			printDie(MAX_DIE, dice, 0, 5, 1); //build the printer lines for die printing
			outputPrintLines(); //output the printer lines
			
			if (rolls != ROLLS - 1) //dont do this on the last turn
				selectDice(dice, keep); //select dice to be kept

			getchar(); //pause

		}//end rolls for loop, end of a turn

		category = selectCategory(); //get users input for where they want to score their roll

		//make sure they havent already scored to that category
		while (scoreCard[category-1][IS_SCORED_COL]) {
			printf("\n You have already scored this category. Please select another category.\n");
			getchar();
			category = selectCategory();
		}

		updateScore(scoreCard, category, dice); //update the score with the users input

		displayScoreCard(scoreCard); //display current scores

		getchar();
		clearScreen();
	} //end turns for loop

	printf("\n\nGood Game!\n\nYour Final Score: %d", (sumLower(scoreCard) + sumUpper(scoreCard) + checkBonus(scoreCard)) );

} //end playGame

int rollDie() {
	//simple function to generate a random number 1-6 and returns the value
	int dieVal = 0;
	dieVal = rand() % 6 + 1;
	return dieVal;
} //end rollDie

int rollDice(int dieVals[MAX_DIE], int keep[MAX_DIE]) {
	//function that rolls all die except the die marked as keep

	//loop through all die
	for (int i = 0; i < MAX_DIE; i++) {
		
		if (keep[i]); //if slot marked as keep, dont roll (do nothing)
			//do nothing
		else 
			dieVals[i] = rollDie();
		//i think this if/else structure makes a bit more sense than other methods

	}//end for
}//end rollDice

int displayGameMenu() {
	//displays a game menu to allow user input for what they want to do.  as of now user can:
	//input to display game rules
	//input to play the game
	//input to exit

	int select = 0;

	//print header
	printf("\t\t\t\tLET'S PLAY YAHTZEE!!!\n\n");

	//loop the game menu until a valid input is entered
	do {
		
		//prints the menu
		printf("\n%d. Display Game Rules", RULES);
		printf("\n%d. Start a game of Yahtzee!", GAME);
		printf("\n%d. Exit", EXIT);
		
		//prints the input promt and gets user input
		printf("\n\nEnter Selection Number: ");
		scanf("%d", &select);

		//displays an error if user input is bad
		if (select != RULES && select != GAME && select != EXIT) {
			printf("\nPlease select a valid option.%d\n", select);
			
		}

		//repeats until user input is good
	} while (select != RULES && select != GAME && select != EXIT);

	//returns selection and exits
	return select;
}//end displayGameMenu

void resetPrintLines() {
	//funtion to reset the line printing strings 
	strcpy(printLine1, "");
	strcpy(printLine2, "");
	strcpy(printLine3, "");
	strcpy(printLine4, "");
	strcpy(printLine5, "");
	strcpy(printLine6, "");
	strcpy(printLine7, "");
	strcpy(printLine8, "");
} //end reset print lines

void outputPrintLines() {
	//function to print the printer lines 
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", printLine1, printLine2, printLine3, printLine4, printLine5, printLine6, printLine7, printLine8);
	
	//once the lines are printed, reset
	resetPrintLines();

} //end outputPrintLines

void displayRandomDice() {
	//function for testing purposes, displays random dice
	//array to store the values of the die
	int dieVals[MAX_DIE];

	//rolls however many times ROLLS is set to and displays that many sets of 5 dice (if MAX_DIE is set to 5 which it likely will be)
	for (int i = 0; i < ROLLS; i++) {
		
		//randomize the die values
		for (int j = 0; j < MAX_DIE; j++) {
			dieVals[j] = rollDie();
		}

		//build the printer lines
		printDie(5, dieVals, 0, 5, 0);

		//output the printer lines
		outputPrintLines();

	}//end for


}//end displayRandomDice

void gameRules() {


	//prints the game rules

	printf("\t\t\t\tLET'S PLAY YAHTZEE!!!\n\n");

	printf("RULES OF THE GAME:\n");
	printf("\t1. The scorecard used for Yahtzee is composed of an upper section and a lower section.\n");
	printf("\t2. A total of 13 scoring combinations are divided amongst the sections.\n");
	printf("\t3. The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\n");
	printf("\t4. If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\n");
	printf("\t5. Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for the future rounds.\n");
	printf("\t6. If the sum of the scores in the upper section is greater than or equal to 63, ");
	printf("then 35 more points are added to the players overall score as a bonus.  The lower section contains a number of poker like combinations.\n\n");


	//clear the screen when done
	clearScreen();

}

void clearScreen() {
	//clears the screen when user is ready

	char clear;

	//prompt user
	printf("\n\n\t\t\t\tHit <ENTER> to continue!\n");
	
	//wait user input
	scanf("%c", &clear);
	
	//clears screen
	system("cls");	//comment for mac os || uncomment for windows os
	//system("clear"); //comment for windows os || uncomment for mac os
}

void printDie(int numDieTotal, int dieVals[], int startingBlanks, int numDieSlots, int printSlots) {
	
	//this function builds printer lines for dice
	//numDieTotal - how many die are to be printed
	//dieVals[] - the values for the die to be printed
	//startingBlanks - the amount of blank die "spaces" to print before printing the designated number of dice
	//numDieSlots - the total number of die slots available to be printed, including die "spaces"
	//printSlots - a true/false enable to print a slot number under each die printed.  the slot numbers start at 1 at the first die printed, they do not start at the first blank slot
	//ie/output: _ _ _ [5] _ _ _
	//	              slot 1
	//is passed to printDie as (1, 5, 3, 7, 1)
	
	int numDiePrinted = 0;

	//iterate through all designated die slots. some before and after the die to be printed may be blanks
	for (int i = 0; i < numDieSlots; i++) {
		
		//if the die slot is not designated as blank (startingBlanks < 1 and the die have not all been printed yet) then print a die
		if (startingBlanks < 1 && numDiePrinted != numDieTotal) {

			//build top and bottom lines of die print
			strcat(printLine1, "[]===========[] ");
			strcat(printLine7, "[]===========[] ");



			//build the print lines for each die
			switch (dieVals[numDiePrinted]) {

			case 1:
				strcat(printLine2, "||           || ");
				strcat(printLine3, "||           || ");
				strcat(printLine4, "||     O     || ");
				strcat(printLine5, "||           || ");
				strcat(printLine6, "||           || ");
				break;

			case 2:
				strcat(printLine2, "||           || ");
				strcat(printLine3, "||   O       || ");
				strcat(printLine4, "||           || ");
				strcat(printLine5, "||       O   || ");
				strcat(printLine6, "||           || ");
				break;

			case 3:
				strcat(printLine2, "||           || ");
				strcat(printLine3, "||  O        || ");
				strcat(printLine4, "||     O     || ");
				strcat(printLine5, "||        O  || ");
				strcat(printLine6, "||           || ");
				break;

			case 4:
				strcat(printLine2, "||  O     O  || ");
				strcat(printLine3, "||           || ");
				strcat(printLine4, "||           || ");
				strcat(printLine5, "||           || ");
				strcat(printLine6, "||  O     O  || ");
				break;

			case 5:
				strcat(printLine2, "||  O     O  || ");
				strcat(printLine3, "||           || ");
				strcat(printLine4, "||     O     || ");
				strcat(printLine5, "||           || ");
				strcat(printLine6, "||  O     O  || ");
				break;

			case 6:
				strcat(printLine2, "||  O     O  || ");
				strcat(printLine3, "||           || ");
				strcat(printLine4, "||  O     O  || ");
				strcat(printLine5, "||           || ");
				strcat(printLine6, "||  O     O  || ");
				break;

				//if input is bad for some reason, throw error for easy debug
			default:
				printf("\n\nan error occured in the die printing function (check inputs)\n\n");
				break;

			} //end switch


			//similarily, build slot line values
			if (printSlots)
				switch (numDiePrinted) {
				case 0:
					strcat(printLine8, "  [[Slot  1]]   ");
					break;
				case 1:
					strcat(printLine8, "  [[Slot  2]]   ");
					break;
				case 2:
					strcat(printLine8, "  [[Slot  3]]   ");
					break;
				case 3:
					strcat(printLine8, "  [[Slot  4]]   ");
					break;
				case 4:
					strcat(printLine8, "  [[Slot  5]]   ");
					break;

				}//end switch
			else
				strcat(printLine8, "                ");
			
			//when a die is printed, count it for comparison of total die so know when all die are printed
			numDiePrinted++;
		
		} //end if statement startingBlanks<0

		//if there are starting blanks or no more die to print, print a blank "dice" instead and decrement startingBlanks
		else {
			strcat(printLine1, "                ");
			strcat(printLine2, "                ");
			strcat(printLine3, "                ");
			strcat(printLine4, "                ");
			strcat(printLine5, "                ");
			strcat(printLine6, "                ");
			strcat(printLine7, "                ");
			strcat(printLine8, "                ");
			startingBlanks--;
			
		}
	} //end for loop


}//end printDie

void initializeScores(int scorecard[CATEGORIES][COLS]) {
	//accepts the scorecard array as input and resets scores to 0 and categories to values ZERO to CATEGORIES 
	
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < CATEGORIES; j++) {
			if (i == ZERO)
				scorecard[j][i] = j;
			else
				scorecard[j][i] = 0;

		

		}//end inner for
	}//end outer for


}//end initializeScores

int selectCategory() {
	//simple function to retrieve users selection for category when scoring die

	int select = 0;

	printf("\n\t\tSelect Catagory to Score Dice:\n");
	printf("1. Ones\n");
	printf("2. Twos\n");
	printf("3. Threes\n");
	printf("4. Fours\n");
	printf("5. Fives\n");
	printf("6. Sixes\n");
	printf("7. Three of a Kind\n");
	printf("8. Four of a Kind\n");
	printf("9. Full House\n");
	printf("10. Small Straight\n");
	printf("11. Large Straight\n");
	printf("12. Yahtzee!\n");
	printf("13. Chance\n");
	
	printf("\nEnter option: ");
	scanf("%d", &select);

	return select;
} //end selectCategory

void selectDice(int dice[MAX_DIE], int keep[MAX_DIE]){
	//allows the user to select which die to keep
	char data[MAX_DIE*4+1];
	int die = 0;
	char* value;
	int valid = 1;
	int i = 0;

	//resets the die selected to be kept
	initializeDieArray(keep);
	
	do { //loop to check for bad data, gets input until data is good
		
		printf("\nSelect dice to keep; Enter Slot values 1 through 5 with a space between each number:\n");
		fgets(data, MAX_DIE*4, stdin);

		while (data[i] != '\0') {
			//cycle through string data to get case numbers.  I did this differently from word doc because I couldn't get the other way to work.

				//switch to change from character inputs to integer inputs
			switch (data[i]) {
			case '1':
				printf("Keeping die in [[Slot 1]]\n");
				keep[0] = 1;
				valid = 1;
				break;

			case '2':
				printf("Keeping die in [[Slot 2]]\n");
				keep[1] = 1;
				valid = 1;
				break;

			case '3':
				printf("Keeping die in [[Slot 3]]\n");
				keep[2] = 1;
				valid = 1;
				break;

			case '4':
				printf("Keeping die in [[Slot 4]]\n");
				keep[3] = 1;
				valid = 1;
				break;

			case '5':
				printf("Keeping die in [[Slot 5]]\n");
				keep[4] = 1;
				valid = 1;
				break;

			case ' ':
			case '\n':
				break;


			default:
				printf("\nInvalid Input(s)\n");
				valid = 0;
				break;
			} //end switch

			i++;
		
		
		}//end while loop through switch 
	
		i = 0;
	
	} while (!valid);//end while loop outer, for error catching

}//end selectDice

void updateScore(int scoreCard[CATEGORIES][COLS], int category, int dice[MAX_DIE]) {
	//update score fucntion, under construction. I assume it will eventually add up the scores as well.  for now, it just prints a statement for the appropriate category
	
	//the enum starts at 0 instead of 1, update category to match
	category--;

	//set the category to IS_SCORED
	scoreCard[category][IS_SCORED_COL] = 1;
	
	switch (category) {
	case one:
		printf("\nScoring Ones...\n");
		scoreCard[one][COL] = sumCategory(dice, one);
		break;
	case two:
		scoreCard[two][COL] = sumCategory(dice, two);
		printf("\nScoring Twos...\n");
		break;
	case three:
		scoreCard[three][COL] = sumCategory(dice, three);
		printf("\nScoring Threes...\n");
		break;
	case four:
		scoreCard[four][COL] = sumCategory(dice, four);
		printf("\nScoring Fours...\n");
		break;
	case five:
		scoreCard[five][COL] = sumCategory(dice, five);
		printf("\nScoring Fives...\n");
		break;
	case six:
		scoreCard[six][COL] = sumCategory(dice, six);
		printf("\nScoring Sixes...\n");
		break;
	case threekind:
		scoreCard[threekind][COL] = checkThreeKind(dice);
		printf("\nScoring Three of a Kind...\n");
		break;
	case fourkind:
		scoreCard[fourkind][COL] = checkFourKind(dice);
		printf("\nScoring Four of a Kind...\n");
		break;
	case fullhouse:
		scoreCard[fullhouse][COL] = checkFullHouse(dice);
		printf("\nScoring Full House...\n");
		break;
	case smstraight:
		scoreCard[smstraight][COL] = checkSmStraight(dice);
		printf("\nScoring Small Straight...\n");
		break;
	case lgstraight:
		scoreCard[lgstraight][COL] = checkLgStraight(dice);
		printf("\nScoring Large Straight...\n");
		break;
	case yahtzee:
		scoreCard[yahtzee][COL] = checkYahtzee(dice);
		printf("\nScoring Yahtzee...\n");
		break;
	case chance:
		scoreCard[chance][COL] = sumChance(dice);
		printf("\nScoring Chance...\n");
		break;
	default:
		printf("\nInvalid Category.\n");
		break;
	}
} //end updateScore

void displayScoreCard(int scoreCard[CATEGORIES][COLS]) {
	//displays the scoreboard and adds totals
	
	int totalLower = sumLower(scoreCard);
	int totalUpper = sumUpper(scoreCard);
	int bonus = checkBonus(scoreCard);

	totalUpper = totalUpper + bonus;

	int grandTotal = totalUpper + totalLower;

	//print title line
	printf("\n\n");
	printf("        YAHTZEE SCORECARD        \n");
	

	//print upper section
	displayUpperSection(scoreCard);

	//print lower section
	displayLowerSection(scoreCard);
	
	//print totals
	printf("|  TOTAL (upper)    |   %-8d|\n", totalUpper);
	printf("+-------------------+-----------+\n");
	printf("|  GRAND TOTAL      |   %-8d|\n", grandTotal);
	printf("+-------------------+-----------+\n");
	

} //end displayScoreCard

void displayUpperSection(int scoreCard[CATEGORIES][COLS]) {
	//displays the upper section of the scoreboard
	int totalScore = sumUpper(scoreCard) + checkBonus(scoreCard);
	
	//print the upper portion of the scorecard
	printf("+-------------------+-----------+\n");
	printf("|  UPPER SECTION    |   SCORE   |\n");
	printf("+-------------------+-----------+\n");
	printf("|  ONES             |   %-8d|\n", scoreCard[one][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  TWOS             |   %-8d|\n", scoreCard[two][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  THREES           |   %-8d|\n", scoreCard[three][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  FOURS            |   %-8d|\n", scoreCard[four][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  FIVES            |   %-8d|\n", scoreCard[five][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  SIXES            |   %-8d|\n", scoreCard[six][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  TOTAL SCORE      |   %-8d|\n", sumUpper(scoreCard));
	printf("+-------------------+-----------+\n");
	printf("|  BONUS            |   %-8d|\n", checkBonus(scoreCard));
	printf("+-------------------+-----------+\n");
	printf("|  SCORE            |   %-8d|\n", totalScore);
	printf("+-------------------+-----------+\n");


}//end display upper section

void displayLowerSection(int scoreCard[CATEGORIES][COLS]) {
	//displays the lower section of the scoreboard
	

	printf("+-------------------+-----------+\n");
	printf("|  LOWER SECTION    |   SCORE   |\n");
	printf("+-------------------+-----------+\n");
	printf("|  THREE OF A KIND  |   %-8d|\n", scoreCard[threekind][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  FOUR OF A KIND   |   %-8d|\n", scoreCard[fourkind][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  FULL HOUSE       |   %-8d|\n", scoreCard[fullhouse][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  SM STRAIGHT      |   %-8d|\n", scoreCard[smstraight][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  LG STRAIGHT      |   %-8d|\n", scoreCard[lgstraight][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  YAHTZEE          |   %-8d|\n", scoreCard[yahtzee][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  CHANCE           |   %-8d|\n", scoreCard[chance][COL]);
	printf("+-------------------+-----------+\n");
	printf("|  TOTAL (lower)    |   %-8d|\n", sumLower(scoreCard));
	printf("+-------------------+-----------+\n");

} //end displayLowerSection

int sumCategory(int dice[MAX_DIE], const int category) {
	//function to sum up the dice for the categories 1s, 2s, 3s, 4s, 5s, and 6s
	

	int sum = 0;

	//loop through die array
	for (int i = 0; i < MAX_DIE; i++) {
		//if the each die is in the category to be scored (1s add all 1 value dice) then add to the sum.  category + 1 because the category enum starts at 0
		if (dice[i] == category + 1) {
			sum = sum + dice[i];
		}
	}

	return sum;

}//end sumCategory

int sumChance(int dice[MAX_DIE]) {
	//simple function to score chance category, adds all the dice
	int sum = 0;

	//loop the the dice and add them up
	for (int i = 0; i < MAX_DIE; i++) {
		sum = sum + dice[i];
	}

	return sum;
} //end sumChance

int arrcmp(int arr1[], int i1, int arr2[], int i2) {
	//simple function to compare if 2 arrays are the same size and contain the same data

	//if the arrays are different sizes, return false
	if (i1 != i2) {
		return 0;
	} //end if

	//if the arrays are the same size, check if any elements are not equal.  if they any element is not equal, return false
	else for (int i = 0; i < i1; i++) {
		if (arr1[i] != arr2[i]) {
			return 0;
		} //end if

	} //end else for

	//if the above tests pass and the function does not return false, then return true.  if the tests above pass the arrays are equal.
	return 1;
}

int checkLgStraight(int dice[MAX_DIE]) {
	//function to check if the die are a large straight, returns the score for a large straight or 0
	int scoreSum = 0;

	//sort the die highest to lowest
	sortDice(dice);

	//options for a lg straight
	int lgStraight1[MAX_DIE] = { 5, 4, 3, 2, 1 };
	int lgStraight2[MAX_DIE] = { 6, 5, 4, 3, 2 };

	//if dice is equal to either of the options for a large straight
	if (arrcmp(dice, MAX_DIE, lgStraight1, MAX_DIE) || arrcmp(dice, MAX_DIE, lgStraight2, MAX_DIE)) {
		scoreSum = 40;
	}

	//not a large straight
	else
		scoreSum = 0;

	return scoreSum;
} //end checkLargeStraight

int sortDice(int dice[MAX_DIE]) {
	//function to sort the dice array from highest to lowest
	//temp variable for swaps
	int temp = 0;
	
	//cycle through all the die...
	for (int i = 0; i < MAX_DIE; i++) {
		//for each die, check all of the die after it...
		for (int j = i + 1; j < MAX_DIE; j++) {
			//if the die after it is higher, swap them.
			if (dice[i] < dice[j]) {
				temp = dice[i];
				dice[i] = dice[j];
				dice[j] = temp;
			}//end if
		} //end inner for
	} //end outer for


}//end sort dice

int checkSmStraight(int dice[MAX_DIE]) {
	//function to check if the die are a small straight, returns the score for a small straight or 0
	int scoreSum = 0;

	//sort the die highest to lowest
	sortDice(dice);

	//options for a sm straight
	int smStraight1[MAX_DIE] = { 4, 3, 2, 1, 0 };
	int smStraight2[MAX_DIE] = { 5, 4, 3, 2, 0 };
	int smStraight3[MAX_DIE] = { 6, 5, 4, 3, 0 };
	

	//if dice is equal to either of the options for a small straight score a small straight; have arrcmp only compare the first 4 elements of each array
	if (arrcmp(dice, MAX_DIE - 1, smStraight1, MAX_DIE - 1) || arrcmp(dice, MAX_DIE - 1, smStraight2, MAX_DIE - 1) || arrcmp(dice, MAX_DIE - 1, smStraight3, MAX_DIE - 1)) {
		scoreSum = 30;
	}

	//not a small straight
	else
		scoreSum = 0;

	return scoreSum;

}//end checkSmStraight

int checkYahtzee(int dice[MAX_DIE]) {
	//function to check the dice for a yahtzee, returns 0 if none or 50 if there is
	
	//variable to store the score, assume its a yahtzee
	int scoreSum = 50;

	//cycle through all the die, if theyre not all equal to the first die, its not a yahtzee, set score to 0
	for (int i = 0; i < MAX_DIE; i++) {
		if (dice[0] != dice[i]) {
			scoreSum = 0;
		}//end if
	} // end for

	return scoreSum;
}

int checkFourKind(int dice[MAX_DIE]) {
	//function to check if the dice are four of a kind and returns score for dice or 0

	int scoreSum = 0;
	int ofKind = 0;
	int ofKindCount = 0;
	
	sortDice(dice);

	//sorted four of a kind is either XXXX0 or 0XXXX the "of kind" will always be in the center
	ofKind = dice[2];

	//cycle through all die, count up how many are "of kind"
	for (int i = 0; i < MAX_DIE; i++) {
		//go ahead and add score sum up assuming it is a four of a kind
		scoreSum = scoreSum + dice[i];
		
		if (dice[i] == ofKind) {
			ofKindCount++;
		}//end if
	}//end for

	//check if there are at least 4 (you could score a yahtzee as a 4 of a kind if you wanted I guess...)
	if (ofKindCount < 4) {
		scoreSum = 0;
	}//end if

	return scoreSum;
}//end checkFourKind

int checkThreeKind(int dice[MAX_DIE]) {
	//function to check if the dice are three of a kind and returns score for dice or 0

	int scoreSum = 0;
	int ofKind = 0;
	int ofKindCount = 0;

	sortDice(dice);

	//sorted three of a kind is either XXXYZ or YZXXX or YXXXZ the "of kind" will always be in the center
	ofKind = dice[2];

	//cycle through all die, count up how many are "of kind"
	for (int i = 0; i < MAX_DIE; i++) {
		//go ahead and add score sum up assuming it is a four of a kind
		scoreSum = scoreSum + dice[i];

		if (dice[i] == ofKind) {
			ofKindCount++;
		}//end if
	}//end for

	//check if there are at least 3 (you could score a yahtzee/4 of a kind as a 3 of a kind if you wanted I guess...)
	if (ofKindCount < 3) {
		scoreSum = 0;
	}//end if

	return scoreSum;
}//end checkThreeKind

int checkFullHouse(int dice[MAX_DIE]) {
	//function to check dice for a full house and returns the score or a 0
	
	//assume not a full house scoreSum = 0
	int scoreSum = 0;
	
	sortDice(dice);

	//sorted full house is either YYXXX or XXXYY the middle is always the 3 of a kind

	//if XXXYY, the rules seem to say X != Y
	if ((dice[2] == dice[0] && dice[2] == dice[1]) && (dice[3] == dice[4]) && (dice[0] != dice[4])) {
		scoreSum = 25;
	} //end if

	//if YYXXX
	else if ((dice[2] == dice[3] && dice[2] == dice[4]) && (dice[0] == dice[1]) && (dice[0] != dice[4])) {
		scoreSum = 25;
	} //end else if

	return scoreSum;

} //end checkFullHouse

int sumUpper(int scoreCard[CATEGORIES][COLS]) {
	//function to sum all upper scores and return their value
	
	int totalUpper = 0;
	
	//cycle through the enums for all upper values
	for (int i = one; i <= six; i++) {
		totalUpper = totalUpper + scoreCard[i][COL];
	}

	return totalUpper;
}

int sumLower(int scoreCard[CATEGORIES][COLS]) {
	//function to sum all lower scores and return their value
	int totalLower = 0;

	//cycle through the enums for all lower values
	for (int i = threekind; i <= chance; i++) {
		totalLower = totalLower + scoreCard[i][COL];
	}

	return totalLower;
}

int checkBonus(int scoreCard[CATEGORIES][COLS]) {
	//function that returns the bonus value, if applicable
	
	//add the bonus if applicable
	int totalUpper = sumUpper(scoreCard);
	int bonus = 0;

	if (totalUpper >= 63)
		bonus = 35;

	return bonus;
}