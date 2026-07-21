#include <stdio.h>
#include <string.h>

#define MAX 100

struct Booking {
    int bookingID;
    char customerName[50];
    char movieName[50];
    int tickets;
    float price;
    int status;   // 1 = Active, 0 = Cancelled
};

struct Booking bookings[MAX];
int count = 0;


// Add sample bookings
void addBooking()
{
    printf("Enter Booking ID: ");
    scanf("%d", &bookings[count].bookingID);

    printf("Enter Customer Name: ");
    scanf("%s", bookings[count].customerName);

    printf("Enter Movie Name: ");
    scanf("%s", bookings[count].movieName);

    printf("Enter Number of Tickets: ");
    scanf("%d", &bookings[count].tickets);

    printf("Enter Ticket Price: ");
    scanf("%f", &bookings[count].price);

    bookings[count].status = 1;

    count++;

    printf("Booking Added Successfully!\n");
}


// Search booking
void searchBooking()
{
    int id, found = 0;

    printf("Enter Booking ID to search: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++)
    {
        if(bookings[i].bookingID == id)
        {
            printf("\nBooking ID: %d", bookings[i].bookingID);
            printf("\nCustomer: %s", bookings[i].customerName);
            printf("\nMovie: %s", bookings[i].movieName);
            printf("\nTickets: %d", bookings[i].tickets);

            if(bookings[i].status == 1)
                printf("\nStatus: Active\n");
            else
                printf("\nStatus: Cancelled\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("Booking Not Found!\n");
}


// Cancel booking
void cancelBooking()
{
    int id, found = 0;

    printf("Enter Booking ID to cancel: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++)
    {
        if(bookings[i].bookingID == id)
        {
            bookings[i].status = 0;
            printf("Booking Cancelled Successfully!\n");
            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("Booking Not Found!\n");
}


// Revenue report
void revenueReport()
{
    float total = 0;

    for(int i=0; i<count; i++)
    {
        if(bookings[i].status == 1)
        {
            total = total + (bookings[i].tickets * bookings[i].price);
        }
    }

    printf("\nTotal Revenue = Rs. %.2f\n", total);
}


int main()
{
    int choice;

    do
    {
        printf("\n===== Movie Ticket Booking System =====");
        printf("\n1. Add Booking");
        printf("\n2. Search Booking");
        printf("\n3. Cancel Booking");
        printf("\n4. Revenue Report");
        printf("\n5. Exit");

        printf("\nEnter your choice: ");
        scanf("%d",&choice);


        switch(choice)
        {
            case 1:
                addBooking();
                break;

            case 2:
                searchBooking();
                break;

            case 3:
                cancelBooking();
                break;

            case 4:
                revenueReport();
                break;

            case 5:
                printf("Exit System\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice != 5);


    return 0;
}
