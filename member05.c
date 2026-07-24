#include <stdio.h>
#include <string.h>

#define MAX 100
#define NUM_MOVIES 5

char movies[NUM_MOVIES][30] =
{
    "Super girl",
    "Avatar 03",
    "Jurassic World Rebirth",
    "Moana(Live Action)",
    "The Odyssey"
};

struct Booking
{
    int bookingID;
    char customerName[50];
    char movieName[50];
    int tickets;
    float price;
    int status;   /* 1 = Active, 0 = Cancelled */
};

struct Booking bookings[MAX];
int count = 0;

/* ---------- Error-handling helpers ---------- */
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
    (void) size; /* buffer is sized for the %49[^\n] format below */
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

/* ---------- Core functions ---------- */
void addBooking(void)
{
    int choice;

    if (count >= MAX)
    {
        printf("Booking List is Full!\n");
        return;
    }

    int newID = readInt("Enter Booking ID: ", 1, 999999);

    for (int i = 0; i < count; i++)
    {
        if (bookings[i].bookingID == newID)
        {
            printf("Booking ID Already Exists!\n");
            return;
        }
    }
    bookings[count].bookingID = newID;

    readLine("Enter Customer Name: ", bookings[count].customerName, 50);

    printf("\nAvailable Movies\n");
    for (int i = 0; i < NUM_MOVIES; i++)
        printf("%d. %s\n", i + 1, movies[i]);

    choice = readInt("Select Movie (1-5): ", 1, NUM_MOVIES);
    strcpy(bookings[count].movieName, movies[choice - 1]);

    bookings[count].tickets = readInt("Enter Number of Tickets: ", 1, 1000);
    bookings[count].price = readPositiveFloat("Enter Ticket Price: ");
    bookings[count].status = 1;

    count++;
    printf("Booking Added Successfully!\n");
}

void searchBooking(void)
{
    int id = readInt("Enter Booking ID: ", 1, 999999);
    int found = 0;

    for (int i = 0; i < count; i++)
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

    for (int i = 0; i < count; i++)
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

    for (int i = 0; i < count; i++)
    {
        if (bookings[i].status == 1)
            total += bookings[i].tickets * bookings[i].price;
    }

    printf("\n===== Revenue Report =====\n");
    printf("Total Revenue = Rs. %.2f\n", total);
}

/* ---------- Menu-driven main ---------- */
int main(void)
{
    int choice;

    do
    {
        printf("\n========== Movie Ticket Booking System ==========\n");
        printf("1. Add Booking\n");
        printf("2. Search Booking\n");
        printf("3. Cancel Booking\n");
        printf("4. Revenue Report\n");
        printf("5. Exit\n");

        choice = readInt("Enter Choice: ", 1, 5);

        switch (choice)
        {
            case 1: addBooking();     break;
            case 2: searchBooking();  break;
            case 3: cancelBooking();  break;
            case 4: revenueReport();  break;
            case 5: printf("Thank You!\n"); break;
        }

    } while (choice != 5);

    return 0;
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
