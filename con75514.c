/********************************************************************************

    This is to certify that this project is my own work, based on my personal
    efforts in studying and applying the concepts learned. I have constructed
    the functions and their respective algorithms and corresponding code by
    myself.  The program was run, tested, and debugged by my own efforts. I
    further certify that I have not copied in part or whole or otherwise
    plagiarized the work of other students and/or persons.

    Concepcion, Jeri Lei - 12275514 - S17A

 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Functions prototypes

void aiStoreCorrect(int *, int *, int *, int *, int *, int *, int *, int *, int);
void codeRandomizer(int *, int *, int *, int *, int);
void displayIntro();
void displayRules();
void displayEnding();
void finalScore(int, int);
void getNumbers(int *, int *, int *, int *, int);
void nextRound();
void playAgain();
int aiCodeGuesser(int, int);
void playMastermind(int, int, int *, int *);
int humanCodeGuesser(int, int);
int nGamesValidator();
int numberChecker(int *, int *, int *, int *, int *);

/**********************************************************
Description : This function loops the game and the choices.
@param : This function does not accept any parameters.
@return : This function does not return anyvalue.
***********************************************************/

void playAgain()
{
    // Declaration of variables:

    /* nChoice is the choice of the user in the main menu
        nDifficulty is the difficulty of the game
        nDigitCount is the number of digits in the code
        nGuessCount is the number of guesses the user has
        nScoreCount is the score of the user
        nScoreCountAI is the score of the AI
        nGames is the number of games the user wants to play */ 

    int nChoice, nDifficulty, nDigitCount, nGuessCount, nScore, nScoreAI, nGames;
    int *pDigits = &nDigitCount;                     // Pointer to the number of digits
    int *pGuesses = &nGuessCount;                    // Pointer to the number of guesses

    do
    {
        printf("\n--| Please enter the path that you want to take: |--\n");
        printf("\n[1.] *|| Play the game ||*\n");
        printf("[2.] *|| Exit the game ||*\n");
        printf("[3.] *|| Wanna know how to master the game, Human? ||*\n");
        printf("\nEnter your choice: --| ");
        scanf("%d", &nChoice);
    } while (nChoice < 1 || nChoice > 3);           // Choice validator

    switch (nChoice)
    {
    case 1:
        printf("\nYou want to play again? :D\n");
        printf("YAY!\n");
        switch (nChoice)                            // This switch statement will determine the path the player wants to take.
        {
        case 1:
            do
            {
                printf("\n**********************************************************************************\n");
                printf("\n[EASY] Pegs: 4, Numbers: 6 (1 - 6), Guesses: 10\n");
                printf("[MEDIUM] Pegs: 4, Numbers: 8 (1 - 8), Guesses: 12\n");
                printf("[HARD] Pegs: 4, Numbers: 10 (1 - 10), Guesses: 16\n");
                printf("[EXTREME - ONLY FOR S-TIER SLAYERS] Pegs: 4, Numers: 16 (1 - 16), Guesses: 20\n");
                printf("\n**********************************************************************************\n");
                printf("\n--| Please enter the difficulty level that you want to play: |-- \n");
                printf("\n[1.] Easy\n");
                printf("[2.] Medium\n");
                printf("[3.] Hard\n");
                printf("[4.] Extreme\n");
                printf("\nEnter your choice: --| ");
                scanf("%d", &nDifficulty);
            } while (nDifficulty < 1 || nDifficulty > 5); // Difficulty level validator

            nGames = nGamesValidator() / 2;               // Number of nGames validator

            for (int i = 0; i < nGames; i++)              // This loop will run the game for the number of nGames that the user wants to play.
            {

                switch (nDifficulty)                      // This switch statement will determine the difficulty level of the game.
                {
                case 1:
                    *pDigits = 6;   // Number of digits
                    *pGuesses = 10; // Number of guesses
                    break;
                case 2:
                    *pDigits = 8;
                    *pGuesses = 12;
                    break;
                case 3:
                    *pDigits = 10;
                    *pGuesses = 16;
                    break;
                case 4:
                    *pDigits = 16;
                    *pGuesses = 20;
                    break;
                }
                playMastermind(nDigitCount, nGuessCount, &nScoreAI, &nScore); // This function will run the game.
            }
            finalScore(nScore, nScoreAI);                                     // This function will display the final score of the game.
            displayEnding();                                                  // This function will display the ending of the game.
            playAgain();                                                      // This function will ask the user if they wants to play again.
            break;
        case 2:
            printf("\n|| You don't want to play with me anymore? :(( ||\n");
            printf("|| I'm VERY sad now.. ||\n");
            playAgain();
            break;
        case 3:                                                               // Display the rules of the game
            displayRules();
            printf("\n \t|| You should play the game now! ||\n\n");
            playAgain();
            break;
        default:
            printf("Invalid input!\n");
            break;
        }
        break;
    case 2:                                                                  // Exit the game
        printf("\n|| OKAY FINE! :(( ||\n");
        break;
    default:
        printf("Invalid input!\n");
        break;
    }
}

/*********************************************************************
Description : This function is for the game of the human code guesser.
This function contains all the functions that are needed for the game.
@param : int nDigitCount, int nGuessCount
@return : int; score, returns the score of the AI player.
*********************************************************************/

int humanCodeGuesser(int nDigitCount, int nGuessCount)
{   
    // nDigit1 - nDigit4 are the digits of the code and nG1 - nG4 are the guesses of the codemaker.
    int nDigit1, nDigit2, nDigit3, nDigit4, nG1, nG2, nG3, nG4;  

    // nFeedback1 - nFeedback4 are the feedbacks of the codebreaker. nRandom is the random number that will be generated. nStop is the variable that will stop the loop. nScore is the score of the AI player.
    int nFeedback1 = 0, nFeedback2 = 0, nFeedback3 = 0, nFeedback4 = 0, nRandom, nStop = 0, nScore = 0;; 

    printf("\n--| The codemaker is generating a code... Please be patient! |--\n");
    codeRandomizer(&nDigit1, &nDigit2, &nDigit3, &nDigit4, nDigitCount);         // This function will generate the code.
    printf("%d %d %d %d", nDigit1, nDigit2, nDigit3, nDigit4);                   // This line will display the code for debugging purposes.
    printf("\n !! THE CODE HAS BEEN GENERATED !!\n");
    printf("\n***********************************************\n");
    printf("\n\t || HUMAN BEGINNER GUIDE: ||\n");
    printf("\n   B = Correct number and correct position\n   W = Correct number but wrong position \n   Nothing = Not in the code\n");
    printf("\n***********************************************\n");

    while (nStop == 0 && nGuessCount > 0)
    {
        printf("\n\n--| Attempts left: %d |--\n", nGuessCount);
        printf("\n|| The number of pegs to choose from is 1 to %d. ||\n", nDigitCount);
        printf("\nEnter that guess, Human! \n");
        getNumbers(&nG1, &nG2, &nG3, &nG4, nDigitCount);                        // This function will get the guesses of the human player.

        printf("\n|| Here's the hint || --* ");

        // This will check if the 4nd digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback4 = numberChecker(&nG4, &nDigit4, &nDigit1, &nDigit2, &nDigit3);

        // This will check if the 2nd digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback2 = numberChecker(&nG2, &nDigit2, &nDigit1, &nDigit3, &nDigit4);

        // This will check if the 3nd digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback3 = numberChecker(&nG3, &nDigit3, &nDigit1, &nDigit2, &nDigit4);

        // This will check if the 1st digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback1 = numberChecker(&nG1, &nDigit1, &nDigit2, &nDigit3, &nDigit4);

        // This will stop the loop if the human player has guessed the code.
        if (nFeedback1 == 14 && nFeedback2 == 14 && nFeedback3 == 14 && nFeedback4 == 14)
        {
            printf("\n\n|| YAY!! You slayed!! The code was cracked! ||\n");
            nStop = 1;
        }
        else
        {
            nGuessCount--;                                            // This will decrease the number of guesses left.
            nScore++;                                                 // This will increase the score of the AI player for every wrong guess of the codebreaker.
        }
    }

    if (nStop == 0)
    {
        printf("\n\n|| Oh no! You have run out of attempts! ||\n");
        printf("\n|| Don't worry! You'll get it next time :)) Would you try again? Please? ||\n");
        printf("\n|| BTW! The code was %d %d %d %d hehe :D ||\n", nDigit1, nDigit2, nDigit3, nDigit4); // This will display the code if the human player has run out of attempts.
        nScore++;                                                     // This will increase the score of the AI player by 1 if the codebreaker was unable to crack the code.
    }

    return nScore;
}

/*********************************************************************
Description : This function is for the game of the AI code guesser.
This function contains all the functions that are needed for the game.
@param : int nDigitCount, int nGuessCount
@return : int; score, returns the score of the human player.
*********************************************************************/

int aiCodeGuesser(int nDigitCount, int nGuessCount)
{
    // nDigit1 - nDigit4 are the digits of the code and nG1 - nG4 are the guesses of the codebreaker.
    int nDigit1, nDigit2, nDigit3, nDigit4, nG1, nG2, nG3, nG4, score = 0;

    // nFeedback1 - nFeedback4 are the feedbacks of the codemaker. nRandom is the random number that will be generated. nStop is the variable that will stop the loop. nScore is the score of the human player.
    int nFeedback1 = 0, nFeedback2 = 0, nFeedback3 = 0, nFeedback4 = 0, nRandom, nStop = 0, nScore = 0;

    printf("\n--| The codemaker is generating a code... Please be patient |--\n");
    printf("\n|| Enter the code now, Human! I'm ready to beat you :B || \n");
    getNumbers(&nDigit1, &nDigit2, &nDigit3, &nDigit4, nDigitCount);                                // This function will get the code of the human player.

    printf("\nThe number of pegs to choose from is 1 to %d.\n", nDigitCount);

    while (nStop == 0 && nGuessCount > 0)
    {
        printf("\n\n--| Attempts left: %d |--\n", nGuessCount);
        printf("\n|| The number of pegs to choose from is 1 to %d. ||\n", nDigitCount);

        aiStoreCorrect(&nG1, &nG2, &nG3, &nG4, &nDigit1, &nDigit2, &nDigit3, &nDigit4, nDigitCount); // This function will store the correct guesses of the AI player and generate the guess.

        printf("|| Here's my guess, Human: %d %d %d %d\n", nG1, nG2, nG3, nG4);

        printf("\n|| Here's the hint || --* ");

        // This will check if the 4nd digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback4 = numberChecker(&nG4, &nDigit4, &nDigit1, &nDigit2, &nDigit3);

        // This will check if the 2nd digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback2 = numberChecker(&nG2, &nDigit2, &nDigit1, &nDigit3, &nDigit4);

        // This will check if the 3nd digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback3 = numberChecker(&nG3, &nDigit3, &nDigit1, &nDigit2, &nDigit4);

        // This will check if the 1st digit of the guess is in correct position, correct number wrong position, or nothing.
        nFeedback1 = numberChecker(&nG1, &nDigit1, &nDigit2, &nDigit3, &nDigit4);

        // This will stop the loop if the AI player has guessed the code. 
        if (nFeedback1 == 14 && nFeedback2 == 14 && nFeedback3 == 14 && nFeedback4 == 14) 
        {
            printf("\n\n|| AYE!! I cracked your code, Human!! How's that? ||\n");
            nStop = 1;
        }
        else
        {
            nGuessCount--;                  // This will decrease the number of guesses left.
            nScore++;                       // This will increase the score of the human player for every wrong guess of the AI player.
        }
    }
    if (nStop == 0)
    {
        printf("\n\n|| Well... That's a bit embarrassing. I'LL DEFINITELY CRACK IT NEXT TIME. HMP >:( ||\n");
        nScore++;                           // This will increase the score of the human player by 1 if the AI player was unable to crack the code.
    }

    return nScore;
}

/*********************************************************************
Description : This function is the start of the game.
This function contains all the functions that are needed for the game.
@param : int nDigitCount, int nGuessCount, int *pScore, int *pScoreAI
@return : This function does not return any value.
*********************************************************************/

void playMastermind(int nDigitCount, int nGuessCount, int *pScore, int *pScoreAI)
{
    int nChoice, nScore = 0, nScoreAI = 0;

        nScore = humanCodeGuesser(nDigitCount, nGuessCount);     // This will run the codebreaker game.
        *pScore = *pScore + nScore;                              // This will add the score of the human player to the total score.
        nextRound();                                             // This will ask the human player if he/she wants to play again.
        nScoreAI = aiCodeGuesser(nDigitCount, nGuessCount);      // This will run the codemaker game.
        *pScoreAI = *pScoreAI + nScoreAI;                        // This will add the score of the AI player to the total score.
}

/************************************************************************************************************************
Description : This function store the correct guesses of the AI and
randomizes the rest of the guesses, If one of the digits is wrong.
This function contains all the functions that are needed for the game.
@param : int *pG1, int *pG2, int *pG3, int *pG4, int *pDigit1, int *nDigit2, int *pDigit3, int *pDigit4, int nDigitCount
@return : This fuction does not return any value.
**************************************************************************************************************************/

void aiStoreCorrect(int *pG1, int *pG2, int *pG3, int *pG4, int *pDigit1, int *nDigit2, int *pDigit3, int *pDigit4, int nDigitCount)
{
    int nRandom;                                                    // This will store the random number that will be generated.

    // This will check if the 1st digit of the guess is correct.
    if (*pG1 != *pDigit1)                                          // If the guess is wrong, then the AI will generate a random number.
    {
        do
        {
            nRandom = rand() % nDigitCount + 1;
            *pG1 = nRandom;                                       // This will store the random number in the guess.
        } while (*pG1 == *pG2 || *pG1 == *pG3 || *pG1 == *pG4);   // This will check if the guess is not the same as the other guesses.
    }

    // This will check if the 2nd digit of the guess is correct.
    if (*pG2 != *nDigit2)                                         // If the guess is wrong, then the AI will generate a random number.
    {
        do
        {
            nRandom = rand() % nDigitCount + 1;
            *pG2 = nRandom;                                       // This will store the random number that will be generated.
        } while (*pG2 == *pG1 || *pG2 == *pG3 || *pG2 == *pG4);   // This will check if the guess is not the same as the other guesses.
    }

    // This will check if the 3rd digit of the guess is correct.
    if (*pG3 != *pDigit3)                                         // If the guess is wrong, then the AI will generate a random number.
    {
        do
        {
            nRandom = rand() % nDigitCount + 1;
            *pG3 = nRandom;                                      // This will store the random number in the 3rd digit of the guess.
        } while (*pG3 == *pG1 || *pG3 == *pG2 || *pG3 == *pG4);  // This will check if the guess is not the same as the other guesses.
    }

    // This will check if the 4th digit of the guess is correct.
    if (*pG4 != *pDigit4)                                        // If the guess is wrong, then the AI will generate a random number.
    {
        do
        {
            nRandom = rand() % nDigitCount + 1;
            *pG4 = nRandom;                                     // This will store the random number in the 4th digit of the guess.
        } while (*pG4 == *pG1 || *pG4 == *pG2 || *pG4 == *pG3); // This will check if the guess is not the same as the other guesses.
    }
}

/*****************************************************************
Description : This function displays the introduction of the game.
@param : This function does not accept any parameters.
@return : This function does not return anyvalue.
******************************************************************/

void displayIntro()
{
    printf("\t   Welcome to Mastermind, Human!\n");
    printf("\n****************************************************\n");
    printf("\n   ONLY S-TIER SLAYERS CAN BEAT ME AT THIS GAME!\n");
    printf("    Wanna find out if you're ans S-Tier Slayer?\n");
    printf("YES?? What are you waitng for? PLAY THE GAME WITH ME! \n");
    printf("\n****************************************************\n");
    printf("\n\t  Best of luck! You'll need it ;)\n");
}

/**********************************************************
Description : This function displays the rules of the game.
@param : This function does not accept any parameters.
@return : This function does not return anyvalue.
***********************************************************/

void displayRules()
{
    printf("\n********************************************************************************************************\n");
    printf("\n                                || HUMAN's GUIDE TO MASTERMIND ||\n");
    printf("\n                                        Both of us can be:\n");
    printf("\n                             ! The CODEMAKER: will generate a code.\n");
    printf("                         ! The CODEBREAKER: will attempt to crack the code.\n");
    printf("\n********************************************************************************************************\n");
    printf("\n********************************************************************************************************\n");
    printf("\n                    || STRICTLY no REPEATING of numbers when asked for input! ||\n");
    printf("\n********************************************************************************************************\n");
    printf("\n********************************************************************************************************\n");
    printf("\n                     ! The codebreaker will have a limited number of guesses.\n");
    printf("                       ! The codemaker will give feedback to the codebreaker.\n");
    printf("                    ! The codebreaker will use the feedback to guess the code.\n\n");
    printf("\n********************************************************************************************************\n");
    printf("\n********************************************************************************************************\n");
    printf("                       || BOTH players can only win if they are the CODEMAKER ||\n");
    printf("\n               ! For every guess the player makes, the codemaker's points go up by 1.\n");
    printf("  ! An extra point will be awarded to the codemaker if the codebreaker was not able to crack the code.\n");
    printf("\n                           !! THE CODEMAKER WITH THE HIGHEST SCORE WINS !!\n");
    printf("********************************************************************************************************\n");
}

void displayEnding()
{
    printf("\n********************************************\n");
    printf("\n|| Thank you for playing with me, Human! ||\n");
    printf("\n|| I hope you enjoyed the game! ||\n");
    printf("\n|| COME BACK SOON PLEASE! T-T ||\n");
    printf("\n|| YOU SLAY! ||\n");
    printf("\n********************************************\n");
}

/************************************************************
Description : This function displays the next round screen.
@param : This function does not accept any parameters.
@return : This function does not return any value.
************************************************************/

void nextRound()
{

    printf("\n***********************************************************\n");
    printf("\n*                       NEXT ROUND!                       *\n");
    printf("\n***********************************************************\n");
}

/**********************************************************************
Description : This function asks for the number of nGames and checks if
the number of nGames entered by the user is valid or invalid.
@param : This function does not accept any parameter.
@return : int; nnGames, returns the number of nGames entered by the user.
**********************************************************************/

int nGamesValidator()
{
    int nGames; // This will store the number of games entered by the user.

    do
    {
        printf("\nHow many games do we play, Human? You're the boss! --| ");
        scanf("%d", &nGames);
        if (nGames % 2 == 1 && nGames < 10)                                         // If the number of games is odd and less than ten, the loop will continue.
        {
            printf("\n|| That's not fair, Human! We need an even number of games to win fairly! ||\n");
        }
        else if (nGames < 0)                                                        // If the number of games is negative, the loop will continue.
        {
            printf("\n|| Who can play with a negative number of games, Human? Not me! ||\n");
        }
        else if (nGames == 0)                                                       // If the number of games is equal to zero, the loop will continue.
        {
            printf("\n|| You don't want to play? :(( We can't do anything with 0 games, Human! ||\n");
        }
        else if (nGames > 10 && nGames < 50)                                        // If the number of games is greater than 10 and less than 50, the loop will continue.
        {
            printf("\n|| That's too many nGames, Human! I can't play that many games! We'll get tired! ||\n");
        }
        else if (nGames >= 50)                                                      // If the number of games is more than 50, the loop will continue.
        {
            printf("\n|| Are you lonely, Human? You want to play that many games with me? This won't end! ||\n");
        }
    } while (nGames < 2 || nGames > 10 || nGames % 2 == 1);

    printf("\n|| Okay, Human! Let's play %d nGames! ||\n", nGames);                 // If the number of games is valid, the loop will stop, and it will display this.

    return nGames;
}

/**********************************************************
Description : This function randomizes the code.
@param : This function does not accept any parameters.
@return : This function does not return anyvalue.
***********************************************************/

void codeRandomizer(int *pDigit1, int *pDigit2, int *pDigit3, int *pDigit4, int nDigitCount)
{
    int nRandom;

    srand(time(NULL)); // To randomize the code.

    nRandom = rand() % nDigitCount + 1;                         // Generate the first digit of the code.
    *pDigit1 = nRandom;                                         // Store the first digit of the code.

    do
    {
        nRandom = rand() % nDigitCount + 1;                     // Generate the second digit of the code.
    } while (nRandom == *pDigit1);                              // If the second digit is equal to the first digit, the loop will continue.
    *pDigit2 = nRandom;                                         // Store the second digit of the code.

    do
    {
        nRandom = rand() % nDigitCount + 1;                     // Generate the third digit of the code.
    } while (nRandom == *pDigit1 || nRandom == *pDigit2);       // If the third digit is equal to the first digit or the second digit, the loop will continue.
    *pDigit3 = nRandom;                                         // Store the third digit of the code.

    do
    {
        nRandom = rand() % nDigitCount + 1;                     // Generate the fourth digit of the code.
    } while (nRandom == *pDigit1 || nRandom == *pDigit2 || nRandom == *pDigit3); // If the fourth digit is equal to the first digit or the second digit or the third digit, the loop will continue.
    *pDigit4 = nRandom;                                         // Store the fourth digit of the code.
}

/************************************************************************
Description : This function asks displays the final score and the winner
of the game.
@param : int score, int scoreAI
@return : This function does not return any value.
************************************************************************/

void finalScore(int nScore, int nScoreAI)
{
    printf("\n|| Your score is %d ||\n", nScore);           // Display the score of the player.
    printf("|| My score is %d ||\n", nScoreAI);             // Display the score of the AI.

    if (nScore > nScoreAI)                                  // If the score of the player is greater than the score of the AI, the player wins.
        printf("|| YOU BEAT ME!! WHAT AN S-TIER SLAYER!! ||");
    else if (nScore < nScoreAI)                             // If the score of the player is less than the score of the AI, the AI wins.
        printf("|| AYE! You lost to me, Human! BWAHAHA! But, That's okay! You can still try!\n Please try again! I think I like playing with you... ||\n");
    else                                                    // If the score of the player is equal to the score of the AI, it's a tie.
        printf("|| Wow! I guess we're both an S-TIER SLAYER!! SHEESH ||\n");
}

/****************************************************************
Description : This function asks for the numbers and checks
if the numbers entered by the player are valid or invalid.
@param : int *pG1, int *pG2, int *pG3, int *pG4, int nDigitCount
@return : This function does not return any value.
*****************************************************************/

void getNumbers(int *pG1, int *pG2, int *pG3, int *pG4, int nDigitCount)
{
    do
    {
        do
        {
            printf("\nHuman! Please enter your valid 4 digit numbers with spaces in between [i.e. 1 2 3 4]: ");
            scanf(" %d %d %d %d", &*pG1, &*pG2, &*pG3, &*pG4);                                                // Ask for the numbers.
            if (*pG1 == *pG2 || *pG1 == *pG3 || *pG1 == *pG4 || *pG2 == *pG3 || *pG2 == *pG4 || *pG3 == *pG4) // If the numbers are not valid, the loop will continue.
            {
                printf("\n|| Human! I said no repeating numbers!!! You won't win if u do that >:O ||\n");
            }
            else if (*pG1 < 0 || *pG2 < 0 || *pG3 < 0 || *pG4 < 0)                                            // If the numbers are negative, the loop will continue.
            {
                printf("\n|| Human! no negative numbers !!! How will you crack my code with negative numbers >:O ||\n");
            }
            else if (*pG1 > nDigitCount || *pG2 > nDigitCount || *pG3 > nDigitCount || *pG4 > nDigitCount)    // If the numbers are greater than the number of digits, the loop will continue.
            {
                printf("\n|| Human! no numbers greater than %d, That's not applicable to your choice of difficulty! >:O ||\n", nDigitCount);
            }
            else if (*pG1 == 0 || *pG2 == 0 || *pG3 == 0 || *pG4 == 0)                                        // If the numbers are equal to 0, the loop will continue.
            {
                printf("\n|| Human! no zeroes!!! >:O AAAAAA ||\n");
            }
        } while (*pG1 < 1 || *pG1 > nDigitCount || *pG2 < 1 || *pG2 > nDigitCount || *pG3 < 1 || *pG3 > nDigitCount || *pG4 < 1 || *pG4 > nDigitCount);
    } while (*pG1 == *pG2 || *pG1 == *pG3 || *pG1 == *pG4 || *pG2 == *pG3 || *pG2 == *pG4 || *pG3 == *pG4);
}

/*****************************************************************************************
Description : This function checks if the number entered is in the right position.
This also prints the hint.
@param : int *pNumber, int *pAnswer, int *pNotAnswer1, int *pNotAnswer2, int *pNotAnswer3
@return : This function does not return anyvalue.
*****************************************************************************************/

int numberChecker(int *pNumber, int *pAnswer, int *pNotAnswer1, int *pNotAnswer2, int *pNotAnswer3)
{
    int nCounter = 0;                                   // Counter for the storing the value.

    if (*pNumber == *pAnswer)
        nCounter = 14;                                  // If the number is in the right position, the counter will be 14.

        else if (*pNumber == *pNotAnswer1 || *pNumber == *pNotAnswer2 || *pNumber == *pNotAnswer3)
        nCounter = 30;                                  // If the number is in the wrong position, the counter will be 30.

            else
            nCounter = 0;                               // If the number is not in the code, the counter will be 0.

    switch (nCounter)
    {
        case 14: 
            printf("B ");                               // If the counter is 14, the hint will be B.
            break;
        case 30:
            printf("W ");                               // If the counter is 30, the hint will be W.
            break;
        case 0:                                         // If the counter is 0, the hint will be blank.
            break;
    }
    return nCounter;
}

/******************************************************************
Description : The main function contains the main menu of the game
@param : This function does not accept any parameters.
@return : This function does not return any value.
******************************************************************/

int main()
{

    // Declaration of variables: 

    int nChoice;                                   // Choice of the user.
    int nDifficulty;                               // Difficulty of the game.
    int nDigitCount;                               // Number of digits in the code.
    int nGuessCount;                               // Number of guesses the user has.
    int nScore = 0;                                // Score of the user.
    int nScoreAI = 0;                              // Score of the AI.
    int nGames;                                    // Number of games the user wants to play.
    int *pDigits = &nDigitCount;                   // Pointer to the number of digits
    int *pGuesses = &nGuessCount;                  // Pointer to the number of guesses

    // Displaying the intro of the game

    do
    {
        displayIntro();
        printf("\n--| Please enter the difficulty level that you want to play: |-- \n");
        printf("\n[1.] *|| Play the game ||*\n");
        printf("[2.] *|| Exit the game ||*\n");
        printf("[3.] *|| Wanna know how to master the game, Human? ||*\n");
        printf("\nEnter your choice: --| ");
        scanf("%d", &nChoice);
    } while (nChoice < 1 || nChoice > 3);

    switch (nChoice) 
    {

    // Play the game
    case 1:
        do
        {
            printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
            printf("\n[EASY] Pegs: 4, Numbers: 6 (1 - 6), Guesses: 10\n");
            printf("[MEDIUM] Pegs: 4, Numbers: 8 (1 - 8), Guesses: 12\n");
            printf("[HARD] Pegs: 4, Letters: 10 (1 - 10), Guesses: 16\n");
            printf("[EXTREME - ONLY FOR S-TIER SLAYERS] Pegs: 4, Letters: 16 (1 - 16), Guesses: 20\n");
            printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
            printf("\n--| Please enter the difficulty level that you want to play: |--  \n");
            printf("\n[1.] Easy\n");
            printf("[2.] Medium\n");
            printf("[3.] Hard\n");
            printf("[4.] Extreme\n\n");
            printf("\nEnter your choice: --| ");
            scanf("%d", &nDifficulty);
        } while (nDifficulty < 1 || nDifficulty > 5); // Difficulty level validator

            nGames = nGamesValidator() / 2;               // Number of nGames validator

        for (int i = 0; i < nGames; i++) // This loop will run the game for the number of nGames that the user wants to play.
        {
            switch (nDifficulty) // This switch statement will determine the difficulty level of the game.
            {
                case 1:

                    *pDigits = 6;   // Number of digits
                    *pGuesses = 10; // Number of guesses
                    printf("\n|| Only EASY mode, huh? ||\n");
                    break;
                case 2:
                    *pDigits = 8;
                    *pGuesses = 12;
                    printf("\n|| Woahh okay! You're going to be challenged, Human ;) ||\n");
                    break;
                case 3:
                    *pDigits = 10;
                    *pGuesses = 16;
                    printf("\n|| SHEESH HARD? Your're brave, Human.||\n");
                    break;
                case 4:
                    *pDigits = 16;
                    *pGuesses = 20;
                    printf("\n|| EXTREME? You're an S-TIER SLAYER, Human. Well, only if you win ;) ||\n");
                    break;
            }

                    playMastermind(nDigitCount, nGuessCount, &nScoreAI, &nScore); // This function will run the game.

        }

                    finalScore(nScore, nScoreAI);                                     // This function will display the final score of the game.
                    displayEnding();                                                  // This function will display the ending of the game.
                    playAgain();                                                      // This function will ask the user if they wants to play again.
        break;
    case 2:                                                               // Exit the game
        printf("\n || Don't you want to play the game? :(( || \n");
        printf(" || I'm sad now.. || \n");
        printf(" || Really want to exit? :(( Then press 2 below! >:( || \n");
        playAgain();
        break;
    case 3:                                                               // Display the rules of the game
        displayRules();
        printf("\n || You should play the game now! ||\n\n");
        playAgain();
        break;
    default:
        printf("Invalid input!\n");
        break;
    }

    return 0;
}