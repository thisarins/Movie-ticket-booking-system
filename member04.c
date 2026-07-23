#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------
   Dummy version of Member 2's movie names, ONLY so this file can run
   alone (just to print which movie the price is for).
------------------------------------------------------------------- */
char movies[5][30] =
{
    "Supergirl",
    "Avatar 03",
    "Jurassic World Rebirth",
    "Moana (live action)",
    "The Odyssey"
};
/* ------------------------------------------------------------------ */

/* ---- Ticket base price for each movie (Rs.) ---- */
double basePrice[5] = {800.00, 750.00, 900.00, 850.00, 900.00};

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

/* ---------------- TEST MAIN (Price Calculation only) ---------------- */
int main()
{
    int movie;
    char discount;
    int groupSize;
    double price;
    int inputResult;

    printf("Movies available: 1-Supergirl  2-Avatar 03  3-Jurassic World Rebirth  4-Moana  5-The Odyssey\n");

    do {
        printf("Select Movie (1-5): ");
        inputResult = scanf("%d", &movie);

        if (inputResult != 1 || movie < 1 || movie > 5) {
            printf("[ERROR] Invalid choice! Please select a valid movie number between 1 and 5.\n\n");
            while (getchar() != '\n'); // Clear residual input buffer to prevent infinite loops
        } else {
            break;
        }
    } while (1);

    movie--; 

    /* Loop for Discount Type Selection */
    do {
        printf("Discount Type (S=Student, E=Senior, G=Group, N=None): ");
        inputResult = scanf(" %c", &discount);

        if (inputResult != 1 || (discount != 'S' && discount != 's' &&
                                 discount != 'E' && discount != 'e' &&
                                 discount != 'G' && discount != 'g' &&
                                 discount != 'N' && discount != 'n')) {
            printf("[ERROR] Invalid discount code! Please enter S, E, G, or N.\n\n");
            while (getchar() != '\n'); // Clear residual input buffer
        } else {
            break;
        }
    } while (1);

    groupSize = 1;

    /* Loop for Group Size Entry if Group Discount Selected */
    if(discount == 'G' || discount == 'g')
    {
        do {
            printf("Enter Group Size: ");
            inputResult = scanf("%d", &groupSize);

            if (inputResult != 1 || groupSize <= 0) {
                printf("[ERROR] Invalid group size! Please enter a valid number (1 or more).\n\n");
                while (getchar() != '\n'); // Clear residual input buffer
            } else {
                break;
            }
        } while (1);
    }

    price = calculatePrice(movie, discount, groupSize);

    printf("\nMovie      : %s\n", movies[movie]);
    printf("Final Price: Rs. %.2f\n", price);

    return 0;
}
