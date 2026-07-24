/* ==========================================================
   MEMBER 4 — Ticket Pricing & Discounts  (functions only)
   ========================================================== */

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
