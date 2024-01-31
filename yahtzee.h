#define MAX_DIE 5
#define RULES 1
#define GAME 2
#define EXIT 3
#define ROLLS 3

#define CATEGORIES 13
/*
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define THREEKIND 7
#define FOURKIND 8
#define FULLHOUSE 9
#define SMSTRAIGHT 10
#define LGSTRAIGHT 11
#define YAHTZEE 12
#define CHANCE 13
*/
#define TURNS 13

enum { one, two, three, four, five, six, threekind, fourkind, fullhouse, smstraight, lgstraight, yahtzee, chance };

//the columns for scorecard, 3 total: 0 is where the score category is stored, 1 is where the score value is stored, 2 is where the boolean "is scored" is stored  

#define COLS 3
#define ZERO 0
#define COL 1
#define IS_SCORED_COL 2



//==============================FUNCTION PROTOTYPES=================================


void outputPrintLines();
	//function to print the printer lines 

void resetPrintLines();
	//funtion to reset the line printing strings 

int rollDie();
	//simple function to generate a random number 1-6 and returns the value

int displayGameMenu();
	//displays a game menu to allow user input for what they want to do.  as of now user can:
	//input to display game rules
	//input to play the game
	//input to exit

void gameRules();
	//prints the game rules

void clearScreen();
	//clears the screen when user is ready

void printDie(int, int[], int, int, int);
	//this function builds printer lines for dice
	//numDieTotal - how many die are to be printed
	//dieVals[] - the values for the die to be printed
	//startingBlanks - the amount of blank die "spaces" to print before printing the designated number of dice
	//numDieSlots - the total number of die slots available to be printed, including die "spaces"
	//printSlots - a true/false enable to print a slot number under each die printed.  the slot numbers start at 1 at the first die printed, they do not start at the first blank slot
	//ie/output: _ _ _ [5] _ _ _
	//	              slot 1
	//is passed to printDie as (1, 5, 3, 7, 1)

void displayRandomDice();
	//function for testing purposes, displays random dice

void playGame();
	//function to play the game, ties a lot of functions together

void initializeDieArray(int[MAX_DIE]);
	//a simple function to set all dice in passed array to value 0
	//the function is both initializeDice and resetKeep from the assignment. 

int rollDice(int[MAX_DIE], int[MAX_DIE]);
	//function that rolls all die except the die marked as keep

void initializeScores(int[CATEGORIES][COLS]);
	//accepts the scorecard array as input and resets scores to 0 and categories to values ZERO to CATEGORIES 

int selectCategory();
	//simple function to retrieve users selection for category when scoring die

void selectDice(int[MAX_DIE], int[MAX_DIE]);
	//allows the user to select which die to keep

void updateScore(int[CATEGORIES][COLS], int, int[MAX_DIE]);
	
void displayScoreCard(int[CATEGORIES][COLS]);
	//displays the scoreboard and adds totals

void displayUpperSection(int[CATEGORIES][COLS]);
	//displays the upper section of the scoreboard

void displayLowerSection(int[CATEGORIES][COLS]);
	//displays the lower section of the scoreboard

int sumCategory(int[MAX_DIE], const int);
	//function to sum up the dice for the categories 1s, 2s, 3s, 4s, 5s, and 6s

int sumChance(int[MAX_DIE]);
	//simple function to score chance category, adds all the dice

int arrcmp(int[], int, int[], int);
	//simple function to compare if 2 arrays are the same size and contain the same data

int sortDice(int[MAX_DIE]);
	//function to sort the dice array from highest to lowest

int checkLgStraight(int[MAX_DIE]);
	//function to check if the die are a large straight, returns the score for a large straight or 0

int checkSmStraight(int[MAX_DIE]);
	//function to check if the die are a small straight, returns the score for a small straight or 0

int checkYahtzee(int[MAX_DIE]);
	//function to check the dice for a yahtzee, returns 0 if none or 50 if there is

int checkFourKind(int[MAX_DIE]);
//function to check if the dice are four of a kind and returns score for dice or 0

int checkThreeKind(int[MAX_DIE]);
	//function to check if the dice are three of a kind and returns score for dice or 0

int checkFullHouse(int[MAX_DIE]);
	//function to check dice for a full house and returns the score or a 0

int sumUpper(int scoreCard[CATEGORIES][COLS]);
	//function to sum all upper scores and return their value

int sumLower(int scoreCard[CATEGORIES][COLS]);
	//function to sum all lower scores and return their value
	
int checkBonus(int scoreCard[CATEGORIES][COLS]);
	//function that returns the bonus value, if applicable