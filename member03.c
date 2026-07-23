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

// Book seat
int bookSeat(int movie, int show, int row, int col)
{
    if(row < 0 || row >= 5 || col < 0 || col >= 10)
    {
        printf("Wrong Input! Invalid seat position.\n");
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

// Show seat status
void printSeatStatus(int movie, int show, int row, int col)
{
    if(row < 0 || row >= 5 || col < 0 || col >= 10)
    {
        printf("Wrong Input! Invalid seat position.\n");
        return;
    }

    printf("\nSeat %c%d : %s\n",
           'A' + row,
           col + 1,
           seats[movie][show][row][col] == 1 ?
           "Booked (X)" : "Available (O)");
}
// Show seat map
void printSeatMap(int movie, int show)
{
    int i,j;

    printf("\n=========== SEAT MAP ===========\n");

    printf("    ");
    for(j = 1; j <= 10; j++)
        printf("%2d ", j);

    printf("\n");

    for(i = 0; i < 5; i++)
    {
        printf("%c   ", 'A' + i);

        for(j = 0; j < 10; j++)
        {
            if(seats[movie][show][i][j] == 0)
                printf(" O ");
            else
                printf(" X ");
        }

        printf("\n");
    }
    printf("O = Available\n");
    printf("X = Booked\n");
}
// Member 3 Seat Booking Function
void seatBooking(int movie, int show)
{
    char rowCh;
    int again;
    int row, col;
    do
    {
        // Row input
        do
        {
            printf("-------------------------------------");
            printf("\nEnter Seat Row (A-E)   : ");
            scanf(" %c", &rowCh);

            if(rowCh >= 'a' && rowCh <= 'e')
                rowCh = rowCh - 32;

            row = rowCh - 'A';

            if(row < 0 || row >= 5){
                printf("Wrong Input! Invalid row.\n");
            }

        }while(row < 0 || row >= 5);

        // Seat number input
        do
        {
            printf("\n-------------------------------------");
            printf("\nEnter Seat Number (1-10): ");

            if(scanf("%d", &col) != 1){
                printf("Wrong Input! Enter numbers only.\n");
                while(getchar() != '\n');
                col = 0;
            }

            else if(col < 1 || col > 10){
                printf("Wrong Input! Invalid seat number.\n");
            }
        }while(col < 1 || col > 10);

        col--;
        printSeatStatus(movie, show, row, col);
        
        if(bookSeat(movie, show, row, col)){
            printf("Seat booked successfully!\n");
        }

        printf("\nBook another seat? (yes = 1 / No = 0): ");
        scanf(" %d", &again);


    }while(again == 1);

    printSeatMap(movie, show);
    printf("\nThank you!\n");
}

