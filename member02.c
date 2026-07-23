#include <stdio.h>

char movies[5][30] =
{
    "Super girl",
    "Avatar 03",
    "Jurassic World Rebirth",
    "Moana(Live Action)",
    "The Odyssey"
};

char showTimes[5][2][20] =
{
    {"10.00 AM", "4.00 PM"},
    {"1.00 PM", "7.00 PM"},
    {"11.00 AM", "8.00 PM"},
    {"10.00 AM", "2.00 PM"},
    {"1.00 PM", "7.00 PM"}
};

int seats[5][2][5][10] = {0};

void displayMovies()
{
    int i, j;
    printf("\n=========== MOVIES ===========\n");

    for(i = 0; i < 5; i++)
    {
        printf("\nMovie %d : %s\n", i + 1, movies[i]);

        for(j = 0; j < 2; j++)
        {
            printf("Show %d  : %s\n", j + 1, showTimes[i][j]);
        }
    }
}

void displaySeatMap(int movie, int show)
{
    int i, j;

    printf("\n============ SEAT MAP ===========\n\n");

    printf("     ");

    for(j = 1; j <= 10; j++)
    {
        printf("%2d ", j);
    }

    printf("\n");

    for(i = 0; i < 5; i++)
    {
        printf(" %c    ", 'A' + i);

        for(j = 0; j < 10; j++)
        {
            if(seats[movie][show][i][j] == 0)
                printf("O  ");
            else
                printf("X  ");
        }

        printf("\n");
    }
    printf("\nO = Available\n");
    printf("X = Booked\n");
}

