#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// function prototype
bool checksum(int *array, int len);

int main(void)
{
    // prompt user for credit card number
    char number[17];
    printf("Card number: ");
    scanf("%s", number);

    // copies string as integer array
    int len = strlen(number);
    int array[len];
    for (int x = 0; x < len; x++)
    {
        array[x] = (int) number[x] - 48;
    }

    // checks if card number is valid
    bool check = checksum(array, len);

    // prints card type
    if (check == true)
    {
        // tests 13-digit numbers
        if (strlen(number) == 13 && array[0] == 4)
        {
            printf("VISA\n");
        }

        // tests 15-digit numbers
        else if (strlen(number) == 15)
        {
            if (array[0] == 3)
            {
                if (array[1] == 4 || array[1] == 7)
                {
                    printf("AMEX\n");
                }
            }
        }

        // tests 16-digit numbers
        else if (strlen(number) == 16)
        {
            if (array[0] == 4)
            {
                printf("VISA\n");
            }

            else if (array[0] == 5)
            {
                if (array[1] > 0 || array[1] < 6)
                {
                    printf("MASTERCARD\n");
                }
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }

}

// Uses Luhn's algorithm to test validity of card number
bool checksum(int *array, int len)
{
    // declare and assign variables
    int digit = 0, digitsum = 0;

    // Multiplies every other digit by 2, starting with the number’s second-to-last digit, then adds those products’ digits together
    for (int i = len - 2; i >= 0; i -= 2)
    {
        digit = array[i] * 2;

        if (digit > 9)
        {
            digit = digit % 10 + 1;
        }

        digitsum += digit;
    }

    // Adds the sum to the sum of the digits that weren’t multiplied by 2
    for (int j = len - 1; j >= 0; j -= 2)
    {
        digitsum += array[j];
    }

    // if the total's last digit is zero, the card number is valid
    if (digitsum % 10 == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}
