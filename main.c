#include <stdio.h>
#include <string.h>

#define MAX_BOOKINGS 100
#define NUM_MOVIES   5
#define NUM_SHOWS    2
#define NUM_ROWS     5
#define NUM_COLS     10

char movies[NUM_MOVIES][30] =
{
    "Super girl",
    "Avatar 03",
    "Jurassic World Rebirth",
    "Moana(Live Action)",
    "The Odyssey"
};

char showTimes[NUM_MOVIES][NUM_SHOWS][20] =
{
    {"10.00 AM", "4.00 PM"},
    {"1.00 PM",  "7.00 PM"},
    {"11.00 AM", "8.00 PM"},
    {"10.00 AM", "2.00 PM"},
    {"1.00 PM",  "7.00 PM"}
};

int seats[NUM_MOVIES][NUM_SHOWS][NUM_ROWS][NUM_COLS] = {0};

double basePrice[NUM_MOVIES] = {800.00, 750.00, 900.00, 850.00, 900.00};

struct Booking
{
    int  bookingID;
    char customerName[50];
    char movieName[50];
    int  tickets;
    float price;
    int  status;   /* 1 = Active, 0 = Cancelled */
};

struct Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

/* ---------- Error-handling helpers (shared by everyone) ---------- */
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int readInt(const char *prompt, int min, int max)
{
    int value, result;
    while (1)
    {
        printf("%s", prompt);
        result = scanf("%d", &value);
        if (result != 1)
        {
            printf("Wrong Input! Please enter numbers only.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        if (value < min || value > max)
        {
            printf("Wrong Input! Enter a value between %d and %d.\n", min, max);
            continue;
        }
        return value;
    }
}

float readPositiveFloat(const char *prompt)
{
    float value;
    int result;
    while (1)
    {
        printf("%s", prompt);
        result = scanf("%f", &value);
        if (result != 1 || value <= 0)
        {
            printf("Wrong Input! Enter a valid positive number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        return value;
    }
}

void readLine(const char *prompt, char *buffer, int size)
{
    (void) size;
    while (1)
    {
        printf("%s", prompt);
        if (scanf(" %49[^\n]", buffer) != 1 || strlen(buffer) == 0)
        {
            printf("Wrong Input! Text cannot be empty.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        return;
    }
}

char readDiscountType(void)
{
    char discount;
    while (1)
    {
        printf("Discount Type (S=Student, E=Senior, G=Group, N=None): ");
        if (scanf(" %c", &discount) != 1)
        {
            printf("Wrong Input! Please try again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (discount == 'S' || discount == 's' ||
            discount == 'E' || discount == 'e' ||
            discount == 'G' || discount == 'g' ||
            discount == 'N' || discount == 'n')
        {
            return discount;
        }
        printf("Wrong Input! Enter S, E, G, or N.\n");
    }
}

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

/* Seat Booking Function */
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

double calculatePrice(int movie, char discountType, int groupSize)
{
    double price = basePrice[movie];

    if (discountType == 'S' || discountType == 's')
    {
        price = price * 0.90;
    }
    else if (discountType == 'E' || discountType == 'e')
    {
        price = price * 0.85;
    }
    else if (discountType == 'G' || discountType == 'g')
    {
        if (groupSize >= 5)
            price = price * 0.80;
        else
            printf("Group discount needs 5 or more people. Normal price applied.\n");
    }

    return price;
}

void priceCalculator(void)
{
    int movie;
    char discount;
    int groupSize = 1;
    double price;

    displayMovies();
    movie = readInt("\nSelect Movie (1-5): ", 1, NUM_MOVIES) - 1;

    discount = readDiscountType();

    if (discount == 'G' || discount == 'g')
        groupSize = readInt("Enter Group Size: ", 1, 1000);

    price = calculatePrice(movie, discount, groupSize);

    printf("\nMovie      : %s\n", movies[movie]);
    printf("Final Price: Rs. %.2f\n", price);
}

/* ---------- Booking records / revenue ---------- */
void addBooking(void)
{
    int choice;

    if (bookingCount >= MAX_BOOKINGS)
    {
        printf("Booking List is Full!\n");
        return;
    }

    int newID = readInt("Enter Booking ID: ", 1, 999999);

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].bookingID == newID)
        {
            printf("Booking ID Already Exists!\n");
            return;
        }
    }
    bookings[bookingCount].bookingID = newID;

    readLine("Enter Customer Name: ", bookings[bookingCount].customerName, 50);

    printf("\nAvailable Movies\n");
    for (int i = 0; i < NUM_MOVIES; i++)
        printf("%d. %s\n", i + 1, movies[i]);

    choice = readInt("Select Movie (1-5): ", 1, NUM_MOVIES);
    strcpy(bookings[bookingCount].movieName, movies[choice - 1]);

    bookings[bookingCount].tickets = readInt("Enter Number of Tickets: ", 1, 1000);
    bookings[bookingCount].price = readPositiveFloat("Enter Ticket Price: ");
    bookings[bookingCount].status = 1;

    bookingCount++;
    printf("Booking Added Successfully!\n");
}

void searchBooking(void)
{
    int id = readInt("Enter Booking ID: ", 1, 999999);
    int found = 0;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].bookingID == id)
        {
            printf("\nBooking ID : %d\n", bookings[i].bookingID);
            printf("Customer   : %s\n", bookings[i].customerName);
            printf("Movie      : %s\n", bookings[i].movieName);
            printf("Tickets    : %d\n", bookings[i].tickets);
            printf("Price      : Rs. %.2f\n", bookings[i].price);
            printf("Status     : %s\n", bookings[i].status == 1 ? "Active" : "Cancelled");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Booking Not Found!\n");
}

void cancelBooking(void)
{
    int id = readInt("Enter Booking ID: ", 1, 999999);
    int found = 0;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].bookingID == id)
        {
            if (bookings[i].status == 0)
                printf("Booking Already Cancelled!\n");
            else
            {
                bookings[i].status = 0;
                printf("Booking Cancelled Successfully!\n");
            }
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Booking Not Found!\n");
}

void revenueReport(void)
{
    float total = 0;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].status == 1)
            total += bookings[i].tickets * bookings[i].price;
    }

    printf("\n===== Revenue Report =====\n");
    printf("Total Revenue = Rs. %.2f\n", total);
}

void seatBookingMenu(void)
{
    int movie, show;

    displayMovies();
    movie = readInt("\nSelect Movie (1-5): ", 1, NUM_MOVIES) - 1;
    show  = readInt("Select Show (1-2)  : ", 1, NUM_SHOWS) - 1;

    printSeatMap(movie, show);
    seatBooking(movie, show);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n========== Movie Ticket Booking System ==========\n");
        printf("1. Show Movies & Showtimes\n");
        printf("2. Book Seats\n");
        printf("3. Calculate Ticket Price\n");
        printf("4. Add Booking Record\n");
        printf("5. Search Booking\n");
        printf("6. Cancel Booking\n");
        printf("7. Revenue Report\n");
        printf("8. Exit\n");

        choice = readInt("Enter Choice: ", 1, 8);

        switch (choice)
        {
            case 1: displayMovies();     break;
            case 2: seatBookingMenu();   break;
            case 3: priceCalculator();   break;
            case 4: addBooking();        break;
            case 5: searchBooking();     break;
            case 6: cancelBooking();     break;
            case 7: revenueReport();     break;
            case 8: printf("Thank You!\n"); break;
        }

    } while (choice != 8);

    return 0;
}
