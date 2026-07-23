#include <stdio.h>
#include <string.h>

#define MAX 100


char movies[3][30] =
{
    "Supergirl",
    "Avatar 3",
    "Jurassic World"
    "Moana(Live Action)"
    "The Odesey"
};

struct Booking
{
    int bookingID;
    char customerName[50];
    char movieName[50];
    int tickets;
    float price;
    int status;   //1 = Active, 0 = Cancelled
};

struct Booking bookings[MAX];
int count = 0;


void addBooking()
{
    int choice;

    if(count >= MAX)
    {
        printf("Booking List is Full!\n");
        return;
    }

    printf("Enter Booking ID: ");

    if(scanf("%d",&bookings[count].bookingID)!=1)
    {
        printf("Invalid Input!\n");
        while(getchar()!='\n');
        return;
    }

   
    for(int i=0;i<count;i++)
    {
        if(bookings[i].bookingID==bookings[count].bookingID)
        {
            printf("Booking ID Already Exists!\n");
            return;
        }
    }

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", bookings[count].customerName);

    printf("\nAvailable Movies\n");
    for(int i=0;i<3;i++)
    {
        printf("%d. %s\n",i+1,movies[i]);
    }

    printf("Select Movie (1-3): ");

    if(scanf("%d",&choice)!=1)
    {
        printf("Invalid Input!\n");
        while(getchar()!='\n');
        return;
    }

    if(choice<1 || choice>3)
    {
        printf("Invalid Choice!\n");
        return;
    }

    strcpy(bookings[count].movieName,movies[choice-1]);

    printf("Enter Number of Tickets: ");

    if(scanf("%d",&bookings[count].tickets)!=1 || bookings[count].tickets<=0)
    {
        printf("Invalid Input!\n");
        while(getchar()!='\n');
        return;
    }

    printf("Enter Ticket Price: ");

    if(scanf("%f",&bookings[count].price)!=1 || bookings[count].price<=0)
    {
        printf("Invalid Input!\n");
        while(getchar()!='\n');
        return;
    }

    bookings[count].status=1;

    count++;

    printf("Booking Added Successfully!\n");
}


void searchBooking()
{
    int id;
    int found=0;

    printf("Enter Booking ID: ");

    if(scanf("%d",&id)!=1)
    {
        printf("Invalid Input!\n");
        while(getchar()!='\n');
        return;
    }

    for(int i=0;i<count;i++)
    {
        if(bookings[i].bookingID==id)
        {
            printf("\nBooking ID : %d\n",bookings[i].bookingID);
            printf("Customer   : %s\n",bookings[i].customerName);
            printf("Movie      : %s\n",bookings[i].movieName);
            printf("Tickets    : %d\n",bookings[i].tickets);
            printf("Price      : Rs. %.2f\n",bookings[i].price);

            if(bookings[i].status==1)
                printf("Status     : Active\n");
            else
                printf("Status     : Cancelled\n");

            found=1;
            break;
        }
    }

    if(found==0)
    {
        printf("Booking Not Found!\n");
    }
}


void cancelBooking()
{
    int id;
    int found=0;

    printf("Enter Booking ID: ");

    if(scanf("%d",&id)!=1)
    {
        printf("Invalid Input!\n");
        while(getchar()!='\n');
        return;
    }

    for(int i=0;i<count;i++)
    {
        if(bookings[i].bookingID==id)
        {
            if(bookings[i].status==0)
            {
                printf("Booking Already Cancelled!\n");
            }
            else
            {
                bookings[i].status=0;
                printf("Booking Cancelled Successfully!\n");
            }

            found=1;
            break;
        }
    }

    if(found==0)
    {
        printf("Booking Not Found!\n");
    }
}


void revenueReport()
{
    float total=0;

    for(int i=0;i<count;i++)
    {
        if(bookings[i].status==1)
        {
            total += bookings[i].tickets * bookings[i].price;
        }
    }

    printf("\n===== Revenue Report =====\n");
    printf("Total Revenue = Rs. %.2f\n",total);
}

int main()
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

        printf("Enter Choice: ");

        if(scanf("%d",&choice)!=1)
        {
            printf("Invalid Input!\n");
            while(getchar()!='\n');
            continue;
        }

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
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice!=5);

    return 0;
}

