void printSeatMap(int movie, int show)
{
    int i, j;
    printf("\n=========== SEAT MAP ===========\n");
    printf("    ");

    for (j = 1; j <= NUM_COLS; j++)
        printf("%2d ", j);
    printf("\n");

    for (i = 0; i < NUM_ROWS; i++)
    {
        printf("%c   ", 'A' + i);
        for (j = 0; j < NUM_COLS; j++)
            printf("%s", seats[movie][show][i][j] == 0 ? " O " : " X ");
        printf("\n");
    }
    printf("O = Available\n");
    printf("X = Booked\n");
}

int bookSeat(int movie, int show, int row, int col)
{
    if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS)
    {
        printf("Wrong Input! Invalid seat position.\n");
        return 0;
    }
    if (seats[movie][show][row][col] == 1)
    {
        printf("Seat already booked!\n");
        return 0;
    }
    seats[movie][show][row][col] = 1;
    return 1;
}

void printSeatStatus(int movie, int show, int row, int col)
{
    if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS)
    {
        printf("Wrong Input! Invalid seat position.\n");
        return;
    }
    printf("\nSeat %c%d : %s\n", 'A' + row, col + 1,
           seats[movie][show][row][col] == 1 ? "Booked (X)" : "Available (O)");
}

/* Member 3 Seat Booking Function */
void seatBooking(int movie, int show)
{
    char rowCh;
    int again;
    int row, col;

    do
    {
        do
        {
            printf("-------------------------------------");
            printf("\nEnter Seat Row (A-E)   : ");
            if (scanf(" %c", &rowCh) != 1)
            {
                printf("Wrong Input! Please try again.\n");
                clearInputBuffer();
                row = -1;
                continue;
            }
            clearInputBuffer();

            if (rowCh >= 'a' && rowCh <= 'z')
                rowCh = rowCh - 32;

            row = rowCh - 'A';

            if (row < 0 || row >= NUM_ROWS)
                printf("Wrong Input! Invalid row.\n");

        } while (row < 0 || row >= NUM_ROWS);

        col = readInt("\nEnter Seat Number (1-10): ", 1, NUM_COLS) - 1;

        printSeatStatus(movie, show, row, col);

        if (bookSeat(movie, show, row, col))
            printf("Seat booked successfully!\n");

        again = readInt("\nBook another seat? (yes = 1 / No = 0): ", 0, 1);

    } while (again == 1);

    printSeatMap(movie, show);
    printf("\nThank you!\n");
}
