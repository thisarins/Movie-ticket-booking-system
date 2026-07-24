/* ==========================================================
   MEMBER 4 — Ticket Pricing & Discounts
   ========================================================== */
#include <stdio.h>

#define NUM_MOVIES 5

char movies[NUM_MOVIES][30] =
{
    "Super girl",
    "Avatar 03",
    "Jurassic World Rebirth",
    "Moana(Live Action)",
    "The Odyssey"
};

double basePrice[NUM_MOVIES] = {800.00, 750.00, 900.00, 850.00, 900.00};

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

/* ---------- Standalone test main ---------- */
int main(void)
{
    int movie;
    char discount;
    int groupSize = 1;
    double price;

    printf("Movies available: 1-Super girl  2-Avatar 03  3-Jurassic World Rebirth  4-Moana  5-The Odyssey\n");

    movie = readInt("Select Movie (1-5): ", 1, NUM_MOVIES) - 1;

    discount = readDiscountType();

    if (discount == 'G' || discount == 'g')
        groupSize = readInt("Enter Group Size: ", 1, 1000);

    price = calculatePrice(movie, discount, groupSize);

    printf("\nMovie      : %s\n", movies[movie]);
    printf("Final Price: Rs. %.2f\n", price);

    return 0;
}
