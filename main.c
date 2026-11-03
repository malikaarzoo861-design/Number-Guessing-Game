#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function for valid input
int getInput()
{
    char input[100];
    int num;
    char extra;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        if (sscanf(input, " %d %c", &num, &extra) == 1 && num > 0)
        {
            return num;
        }

        printf("Invalid input! Enter a positive whole number: ");
    }
}

// Function to play the game
void playGame(int maxNumber, int maxAttempts, int *bestScore)
{
    int randomNumber = rand() % maxNumber + 1;
    int guessed;
    int attempts = 0;
    int won = 0;

    printf("\nGuess a number between 1 to %d\n", maxNumber);
    printf("You have %d attempts.\n", maxAttempts);

    while (attempts < maxAttempts)
    {
        printf("\nAttempt %d/%d\n", attempts + 1, maxAttempts);
        printf("Enter your guess: ");

        guessed = getInput();

        if (guessed > maxNumber)
        {
            printf("Number out of range! Try again.\n");
            continue;
        }

        attempts++;

        if (guessed > randomNumber)
        {
            printf("Too high! Try a lower number.\n");
        }
        else if (guessed < randomNumber)
        {
            printf("Too low! Try a higher number.\n");
        }
        else
        {
            printf("\nCongratulations! YOU WON!\n");
            printf("Total Attempts: %d\n", attempts);

            if (attempts <= 4)
                printf("Performance: Excellent!\n");

            else if (attempts <= 7)
                printf("Performance: Good!\n");

            else
                printf("Performance: Winner!\n");

            won = 1;

            if (*bestScore == 0 || attempts < *bestScore)
            {
                *bestScore = attempts;
                printf("New Best Score!\n");
            }

            break;
        }
    }

    if (won == 0)
    {
        printf("\nGAME OVER! YOU LOST!\n");
        printf("Correct Number was: %d\n", randomNumber);
    }

    printf("Best Score: ");

    if (*bestScore == 0)
        printf("Not available yet\n");
    else
        printf("%d attempts\n", *bestScore);
}

// Main function
int main()
{
    int choice;
    int maxNumber, maxAttempts;
    int bestScores[3] = {0, 0, 0};
    char playAgain;

    srand(time(0));

    printf("====================================\n");
    printf("       NUMBER GUESSING GAME         \n");
    printf("====================================\n");

    do
    {
        printf("\nSelect Difficulty Level:\n");
        printf("1. Easy   (1-50)   - 10 Attempts\n");
        printf("2. Medium (1-100)  - 8 Attempts\n");
        printf("3. Hard   (1-500)  - 6 Attempts\n");

        printf("\nEnter your choice: ");
        choice = getInput();

        switch (choice)
        {
        case 1:
            maxNumber = 50;
            maxAttempts = 10;
            break;

        case 2:
            maxNumber = 100;
            maxAttempts = 8;
            break;

        case 3:
            maxNumber = 500;
            maxAttempts = 6;
            break;

        default:
            printf("Invalid choice! Please select 1, 2 or 3.\n");
            continue;
        }

        playGame(maxNumber, maxAttempts, &bestScores[choice - 1]);

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

        // Clear remaining input
        while (getchar() != '\n')
            ;

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\n====================================\n");
    printf("       THANK YOU FOR PLAYING!       \n");
    printf("====================================\n");

    return 0;
}