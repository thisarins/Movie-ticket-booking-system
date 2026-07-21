#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------
   Dummy versions of Member 2's data, ONLY so this file can run alone
   for testing. When combining with the real project, DELETE this
   block and use the real movies/showTimes/seats from Member 2's file
   instead (with extern, like in member3_booking_pricing.c).
------------------------------------------------------------------- */
char movies[3][30] =
{
    "Superman",
    "Avatar",
    "Jurassic World"
};

char showTimes[3][2][20] =
{
    {"10.00 AM", "4.00 PM"},
    {"1.00 PM", "7.00 PM"},
    {"11.00 AM", "8.00 PM"}
};

int seats[3][2][5][10] = {0};
/* ------------------------------------------------------------------ */

/* ---- Ticket base price for each movie (Rs.) ---- */
double basePrice[3] = {800.00, 750.00, 900.00};

/* ---- Booking records (parallel arrays instead of struct) ---- */
char custName[50][30];
int bookMovie[50];
int bookShow[50];
int bookRow[50];
int bookCol[50];
double bookPrice[50];
int bookingCount = 0;

/*
   Calculate final price after discount.
   discountType: 'S'/'s' = Student (10% off)
                 'E'/'e' = Senior  (15% off)
                 'G'/'g' = Group of 5+ (20% off)
                 any other char = No discount
*/
double calculatePrice(int movie, char discountType, int groupSize)
{
    double price = basePrice[movie];

    if(discountType == 'S' || discountType == 's')
    {
        price = price * 0.90;
    }
    else if(discountType == 'E' || discountType == 'e')
    {
        price = price * 0.85;
    }
    else if(discountType == 'G' || discountType == 'g')
    {
        if(groupSize >= 5)
            price = price * 0.80;
        else
            printf("Group discount needs 5 or more people. Normal price applied.\n");
    }

    return price;
}

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

/* Save customer details and booking info */
void saveBooking(char name[], int movie, int show, int row, int col, double price)
{
    strcpy(custName[bookingCount], name);
    bookMovie[bookingCount] = movie;
    bookShow[bookingCount] = show;
    bookRow[bookingCount] = row;
    bookCol[bookingCount] = col;
    bookPrice[bookingCount] = price;

    bookingCount++;
}

/* Print receipt for the most recent booking */
void displayBookingReceipt(int index)
{
    printf("\n======= BOOKING CONFIRMED =======\n");
    printf("Customer   : %s\n", custName[index]);
    printf("Movie      : %s\n", movies[bookMovie[index]]);
    printf("Show Time  : %s\n", showTimes[bookMovie[index]][bookShow[index]]);
    printf("Seat       : %c%d\n", 'A' + bookRow[index], bookCol[index] + 1);
    printf("Amount Paid: Rs. %.2f\n", bookPrice[index]);
    printf("==================================\n");
}

/* Small helper just to show seat status while testing standalone */
void printSeatStatus(int movie, int show, int row, int col)
{
    printf("\nSeat %c%d status: %s\n", 'A' + row, col + 1,
           seats[movie][show][row][col] == 1 ? "Booked (X)" : "Available (O)");
}

/* ---------------- TEST MAIN ---------------- */
int main()
{
    char name[30];
    int movie, show, row, col;
    char rowCh, discount;
    int groupSize;
    double price;

    printf("Movies available: 1-Superman  2-Avatar  3-Jurassic World\n");
    printf("Select Movie (1-3): ");
    scanf("%d", &movie);
    printf("Select Show (1-2): ");
    scanf("%d", &show);
    movie--; show--;

    printf("\nEnter Row (A-E): ");
    scanf(" %c", &rowCh);
    row = rowCh - 'A';

    printf("Enter Seat Number (1-10): ");
    scanf("%d", &col);
    col--;

    printSeatStatus(movie, show, row, col);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", name);

    printf("Discount Type (S=Student, E=Senior, G=Group, N=None): ");
    scanf(" %c", &discount);

    groupSize = 1;
    if(discount == 'G' || discount == 'g')
    {
        printf("Enter Group Size: ");
        scanf("%d", &groupSize);
    }

    if(bookSeat(movie, show, row, col))
    {
        price = calculatePrice(movie, discount, groupSize);
        saveBooking(name, movie, show, row, col, price);
        displayBookingReceipt(bookingCount - 1);
    }

    printSeatStatus(movie, show, row, col);

    /* Try booking the SAME seat again to prove double-booking is blocked */
    printf("\n--- Trying to book the same seat again (should fail) ---\n");
    if(!bookSeat(movie, show, row, col))
    {
        printf("Good - duplicate booking correctly rejected.\n");
    }

    return 0;
}
