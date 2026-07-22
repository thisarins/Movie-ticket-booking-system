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
    "Jurassic World Rebirth"
    "Moana (live action)"
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

    printf("Movies available: 1-Superman  2-Avatar  3-Jurassic World\n");
    printf("Select Movie (1-3): ");
    scanf("%d", &movie);
    movie--;

    printf("Discount Type (S=Student, E=Senior, G=Group, N=None): ");
    scanf(" %c", &discount);

    groupSize = 1;
    if(discount == 'G' || discount == 'g')
    {
        printf("Enter Group Size: ");
        scanf("%d", &groupSize);
    }

    price = calculatePrice(movie, discount, groupSize);

    printf("\nMovie      : %s\n", movies[movie]);
    printf("Final Price: Rs. %.2f\n", price);

    return 0;
}
