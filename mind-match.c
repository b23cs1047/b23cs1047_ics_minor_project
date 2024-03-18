#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Created a function to check if a number has unique digits.
int has_unique_digits(int num) {
   int digits[10] = {0}; //Declare an array to store each digit.
    while (num > 0) {
        int digit = num % 10;
        if (digits[digit] == 1) {
            return 0; 
        }
        digits[digit] = 1; 
        num /= 10;
    }
    return 1; 
}

//Created a function to generate a random 4 digit number with unique digits.
int random_number() {
    int x;
    do {
        x = rand() % 9000 + 1000;
    } while (!has_unique_digits(x)); // Keep regenerating until x has unique digits
    return x;
}

//Created a function to check whether the number guessed by player is equal to the secret code.
int checking(int guess, int secret_code) {
    return guess == secret_code;
}
//Created a function to extract digits of guesses and secret code and compare them to count the number of bulls and cows present.
void counting_bulls_and_cows(int guess, int secret_code, int *bulls, int *cows) {
    int code_digits[4];
    int guess_digits[4];
    *bulls = 0;
    *cows = 0;

    for(int i=0; i<4; i++) {
        code_digits[i] = secret_code % 10;
        guess_digits[i] = guess % 10;
        secret_code /= 10;
        guess /= 10;
    }

    for(int i=0; i<4; i++) {
        if(guess_digits[i] == code_digits[i]) {
            (*cows)++;
        }
    }
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
        if(guess_digits[i] == code_digits[j] && i != j) {
            (*bulls)++;
        }
    }
}
}

int main() {
    int numofPlayers;
    int secret_code;
    int numofAttempts = 1;
    //Declared another flag to tell whether the code is guessed correctly or not.
    int flag2 = 0;
    int winner;

//This is a function to start the random number generating process. And also to change the number every time the program runs.
    srand(time(0));

//Introduction to my game.
    printf("Hello There! Welcome to Mind Match: The Guessing Game of Bulls and Cows.\n\n");
    usleep(5000000);
    printf("Alas! All of you are trapped in this jungle! The only way for you to get out is to find the secret code!\n\n");
    usleep(5000000);
    printf("Here are some rules to find the secret code:\n");
    usleep(3000000);
    printf("1.The code is a simple 4-digit number. All the digits are unique, i.e., none of them are repeated.\n");
    usleep(5000000);
    printf("2.For every guess you make, number of bulls and cows are shown.\n");
    usleep(5000000);
    printf("3.Bulls show the number of digits that match the secret code with your guess, but are in the wrong position. And cows show the number of digits that match the secret code with your guess and are in the right position.\n");
    usleep(5000000);
    printf("4.If multiple players are present, they get consecutive chances and the one who cracks the secret code escapes the jungle!\n");
    usleep(5000000);
    printf("Enter the number of players(1-4): ");
    scanf("%d", &numofPlayers);
    if(numofPlayers > 4 || numofPlayers < 1) {
        printf("Please enter a valid number.\n");
        return 1;
    }
    getchar();
    printf("Press ENTER to start the game.\n");
    getchar();

//Calling the first function to generate the secret code.
    secret_code = random_number();

//Game loop begins.
    while(!flag2) {
        printf("Attempt %d\n", numofAttempts);

    //Each player makes a guess.
    for(int i=0; i<numofPlayers; i++) {
        if(!flag2) {
        int player_guess;
            printf("Player %d's turn: ", i+1);
            scanf("%d", &player_guess);
        //Moving on to the next plaer if the number entered is not a 4-digit number.
        if(player_guess < 1000 || player_guess > 9999) {
                printf("Please enter a 4-digit number next time.\n");
                continue;
        }
        //Checking if the guess if correct by calling second function.
        if(checking(player_guess, secret_code)) {
            winner = i+1;
            flag2 = 1;
            break;
        }
        //Counting bulls and cows by calling the third function.
        int bulls=0, cows=0;
        counting_bulls_and_cows(player_guess, secret_code, &bulls, &cows);
        printf("Bulls: %d, Cows: %d\n", bulls, cows);

        if(cows == 4) {
            winner = i+1;
            flag2 = 1; //changing flag to when the code is cracked.
            break;
        }
        }
    }

    numofAttempts++;
}

    printf("Player %d has escaped the jungle! The secret code was: %d.\n", winner, secret_code);
    usleep(3000000);
    printf("Hope you liked my game :)\n");
    //Game by Pradeepika Nori. Hope you liked it.
return 0;
}