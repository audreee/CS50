#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int length = 0, letters = 0, words = 1, sentences = 0, level;

    //prompts user for text
    string text = get_string("Text: ");
    length = strlen(text);

    for (int i = 0, n = length; i < n; i++)
    {

        // counts number of letters
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }

        //counts number of words
        if (isspace(text[i]) != 0)
        {
            words++;
        }

        //counts number of sentences
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }

    //determines grade level using Coleman-Liau index
    level = round(0.0588 * (float) letters / words * 100 - 0.296 * (float) sentences / words * 100 - 15.8);

    //prints grade levels below 1
    if (level < 1)
    {
        printf("Before Grade 1\n");
    }

    //prints grade levels above 16
    else if (level >= 16)
    {
        printf("Grade 16+\n");
    }

    //prints grade level
    else
    {
        printf("Grade %i\n", level);
    }
}
