# Implements a program that computes the approximate grade level of text using the Coleman-Liau index
from cs50 import get_string


def main():

    # gets text from user
    text = get_string("Text: ")

    # counts letters, words, and sentences in text
    letters, words, sentences = count(text)

    # calculates grade level using Coleman-Liau formula
    grade = round(0.0588 * letters / words * 100.00 - 0.296 * sentences / words * 100.00 - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade " + str(grade))


# counts number of letters, words, and spaces
def count(text):

    letters, words, sentences = 0, 1, 0

    for char in text:

        if char.isalpha() == True:
            letters += 1

        if char.isspace() == True:
            words += 1

        if "." in char or "!" in char or "?" in char:
            sentences += 1

    return letters, words, sentences


main()
