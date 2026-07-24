/* ==========================================================
   MEMBER 2 — Movie & Showtime Display  (functions only)
   ========================================================== */

void displayMovies(void)
{
    int i, j;
    printf("\n=========== MOVIES ===========\n");

    for (i = 0; i < NUM_MOVIES; i++)
    {
        printf("\nMovie %d : %s\n", i + 1, movies[i]);
        for (j = 0; j < NUM_SHOWS; j++)
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

    for (j = 1; j <= NUM_COLS; j++)
        printf("%2d ", j);
    printf("\n");

    for (i = 0; i < NUM_ROWS; i++)
    {
        printf(" %c    ", 'A' + i);
        for (j = 0; j < NUM_COLS; j++)
            printf("%s  ", seats[movie][show][i][j] == 0 ? "O" : "X");
        printf("\n");
    }
    printf("\nO = Available\n");
    printf("X = Booked\n");
}
