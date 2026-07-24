
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

/* ---------- Error-handling helpers (used by everyone) ---------- */
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

        if (discount == 'S'  discount == 's'
            discount == 'E'  discount == 'e'
            discount == 'G'  discount == 'g'
            discount == 'N' || discount == 'n')
        {
            return discount;
        }
        printf("Wrong Input! Enter S, E, G, or N.\n");
    }
}
