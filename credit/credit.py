# implements a program to check the validity of a credit card number
from cs50 import get_string


def main():

    # prompts user for card number and converts it into a list of integers
    number = get_string("Card number: ")

    # print results
    if checksum(number) == True:

        # tests 13-digit numbers
        if len(number) == 13 and number[0] == '4':
            print("VISA")

        # tests 15-digit numbers
        elif len(number) == 15:
            if number[0] == '3':
                if number[1] == '4' or number[1] == '7':
                    print("AMEX")

        # tests 16-digit numbers
        elif len(number) == 16:
            if number[0] == '4':
                print("VISA")
            elif number[0] == '5':
                if number[1] == '1' or '2' or '3' or '4' or '5':
                    print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def checksum(number):

    # converts string to list of integers
    number = list(number)
    number = [int(x) for x in number]

    # uses Luhn's algorithm to verify number
    digit = 0
    digitsum = 0
    for i in range(len(number) - 2, len(number), -2):
        digit = (i * 2)
        if digit > 9:
            digit = digit % 10 + 1
        digitsum += digit
    for j in range(len(number) - 1, len(number), -2):
        digitsum += j
    if digitsum % 10 == 0:
        return True


main()
