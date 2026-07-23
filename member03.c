#include <stdio.h>

/* ------------------------------------------------------------------
   Dummy versions of Member 2's data, ONLY so this file can run alone.
------------------------------------------------------------------- */

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

/* ------------------------------------------------------------------ */

/* Mark a seat as booked. Returns 1 on success, 0 if already booked/invalid */
int bookSeat(int movie, int show, int row, int col)
{
    if(row < 0 || row >= 5 || col < 0 || col >= 10)
    {
        printf("Invalid seat position.\n");
        return 0;
    }

    if(seats[movie][show][row][col] == 1)
    {
        printf("Seat already booked!\n");
        return 0;
    }

    seats[movie][show][row][col] = 1;
    return 1;
}

/* Small helper to show seat status */
void printSeatStatus(int movie, int show, int row, int col)
{
    if(row < 0 || row >= 5 || col < 0 || col >= 10)
    {
        printf("Invalid seat position.\n");
        return;
    }

    printf("\nSeat %c%d status: %s\n",
           'A' + row,
           col + 1,
           seats[movie][show][row][col] == 1 ? "Booked (X)" : "Available (O)");
}

/* Print the entire seat map for a movie/show as a grid */
void printSeatMap(int movie, int show)
{
    int r, c;

    printf("\n===== Seat Map: %s (Show %d - %s) =====\n",
           movies[movie], show + 1, showTimes[movie][show]);

    printf("      ");
    for(c = 0; c < 10; c++)
        printf("%2d ", c + 1);
    printf("\n");

    for(r = 0; r < 5; r++)
    {
        printf("Row %c: ", 'A' + r);
        for(c = 0; c < 10; c++)
        {
            printf(" %c ", seats[movie][show][r][c] == 1 ? 'X' : 'O');
        }
        printf("\n");
    }
    printf("=====================================\n");
}

/* ---------------- TEST MAIN ---------------- */

int main()
{
    int movie, show, row, col;
    char rowCh;
    char again;

    printf("Movies Available\n");
    printf("1. Super girl\n");
    printf("2. Avatar 03\n");
    printf("3. Jurassic World Rebirth\n");
    printf("4. Moana (Live Action)\n");
    printf("5. The Odyssey\n");

    printf("\nSelect Movie (1-5): ");
    scanf("%d", &movie);

    if(movie < 1 || movie > 5)
    {
        printf("Invalid movie selection!\n");
        return 0;
    }

    printf("Select Show (1-2): ");
    scanf("%d", &show);

    if(show < 1 || show > 2)
    {
        printf("Invalid show selection!\n");
        return 0;
    }

    movie--;
    show--;

    /* Loop: let the user book as many seats as they want, one at a time */
    do
    {
        printf("\nEnter Row (A-E): ");
        scanf(" %c", &rowCh);

        if(rowCh >= 'a' && rowCh <= 'e')
        {
            rowCh = rowCh - 32;
        }

        row = rowCh - 'A';

        printf("Enter Seat Number (1-10): ");
        scanf("%d", &col);
        col--;

        /* Validate row/col BEFORE using them anywhere */
        if(row < 0 || row >= 5 || col < 0 || col >= 10)
        {
            printf("Invalid seat position entered. Try again.\n");
        }
        else
        {
            printSeatStatus(movie, show, row, col);

            if(bookSeat(movie, show, row, col))
            {
                printf("Seat booked successfully!\n");
            }

            printSeatStatus(movie, show, row, col);
        }

        printf("\nBook another seat? (y/n): ");
        scanf(" %c", &again);

    } while(again == 'y' || again == 'Y');

    /* Final seat map after all bookings are done */
    printf("\n===== FINAL seat map after all bookings =====\n");
    printSeatMap(movie, show);

    return 0;
}
