#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member02.c"
#include "member03.c"
#include "member04.c"
#include "member05.c"

#define ROWS 5
#define COLS 10
#define TOTAL_SEATS 50

// --- Data Structures ---

typedef struct {
    char customerName[50];
    int seatRow;
    int seatCol;
    double pricePaid;
    int isBooked; // 0 = Available, 1 = Booked
} Booking;

typedef struct {
    char time[20];
    int seats[ROWS][COLS]; // 0 = Empty (.), 1 = Taken (X)
    Booking bookings[ROWS][COLS];
    double totalRevenue;
    int ticketsSold;
} Showtime;

typedef struct {
    int id;
    char title[50];
    Showtime showtimes[2]; // Each movie has 2 showtimes
} Movie;

// --- Function Prototypes for Team Members ---

void initData(Movie movies[]);
void viewShowtimes(Movie movies[]);                 // Member 2 Task
void viewSeatMap(Movie movies[]);                  // Member 2 Task
void bookSeat(Movie movies[]);                     // Member 3 & 4 Task
void cancelBooking(Movie movies[]);                // Member 5 Task
void searchBooking(Movie movies[]);                // Member 5 Task
void revenueReport(Movie movies[]);                // Member 5 Task

// --- Main Function (Member 1 Task) ---
int main() {
    Movie movies[3]; // Fixed list of 3 movies
    int choice;

    // Hardcode initial movie and showtime data
    initData(movies);

    while (1) {
        printf("\n=========================================\n");
        printf("   MOVIE TICKET BOOKING SYSTEM (CSC1031)  \n");
        printf("=========================================\n");
        printf("1. View Showtimes\n");
        printf("2. View Seat Map\n");
        printf("3. Book a Seat\n");
        printf("4. Cancel a Booking\n");
        printf("5. Search Booking\n");
        printf("6. View Revenue Report\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");

        // Input Validation: Prevents program from crashing if letters are typed
        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                viewShowtimes(movies);
                break;
            case 2:
                viewSeatMap(movies);
                break;
            case 3:
                bookSeat(movies);
                break;
            case 4:
                cancelBooking(movies);
                break;
            case 5:
                searchBooking(movies);
                break;
            case 6:
                revenueReport(movies);
                break;
            case 7:
                printf("\nThank you for using the system. Goodbye!\n");
                exit(0);
            default:
                printf("\n[Error] Invalid choice! Please select between 1 and 7.\n");
        }
    }
    return 0;
}

// --- Initialize Hardcoded Data ---
void initData(Movie movies[]) {
    // Movie 1 Setup
    movies[0].id = 1;
    strcpy(movies[0].title, "Movie Alpha");
    strcpy(movies[0].showtimes[0].time, "10:00 AM");
    strcpy(movies[0].showtimes[1].time, "02:00 PM");

    // Movie 2 Setup
    movies[1].id = 2;
    strcpy(movies[1].title, "Movie Beta");
    strcpy(movies[1].showtimes[0].time, "01:00 PM");
    strcpy(movies[1].showtimes[1].time, "06:00 PM");

    // Movie 3 Setup
    movies[2].id = 3;
    strcpy(movies[2].title, "Movie Gamma");
    strcpy(movies[2].showtimes[0].time, "04:00 PM");
    strcpy(movies[2].showtimes[1].time, "09:00 PM");

    // Set all seats across all showtimes to empty initially
    for (int m = 0; m < 3; m++) {
        for (int s = 0; s < 2; s++) {
            movies[m].showtimes[s].totalRevenue = 0;
            movies[m].showtimes[s].ticketsSold = 0;
            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    movies[m].showtimes[s].seats[r][c] = 0; // 0 = Available (.)
                    movies[m].showtimes[s].bookings[r][c].isBooked = 0;
                }
            }
        }
    }
}

// --- Empty Placeholder Functions for Team Implementation ---

void viewShowtimes(Movie movies[]) {
    // TODO: To be implemented by Member 2
    printf("\n[Under Construction] View Showtimes feature is coming soon!\n");
}

void viewSeatMap(Movie movies[]) {
    // TODO: To be implemented by Member 2
    printf("\n[Under Construction] View Seat Map feature is coming soon!\n");
}

void bookSeat(Movie movies[]) {
    // TODO: To be implemented by Member 3 and Member 4
    printf("\n[Under Construction] Book a Seat feature is coming soon!\n");
}

void cancelBooking(Movie movies[]) {
    // TODO: To be implemented by Member 5
    printf("\n[Under Construction] Cancel Booking feature is coming soon!\n");
}

void searchBooking(Movie movies[]) {
    // TODO: To be implemented by Member 5
    printf("\n[Under Construction] Search Booking feature is coming soon!\n");
}

void revenueReport(Movie movies[]) {
    // TODO: To be implemented by Member 5
    printf("\n[Under Construction] Revenue Report feature is coming soon!\n");
}
