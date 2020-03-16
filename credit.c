//Credit Card number validator (Problem set 1 CS50x)
//git: NihilNovum

#include <stdio.h>
#include <cs50.h>

/*-------------functions declarations------------*/
//Checks if given number is a valid credit card number
bool validateInput(long number);

//Returns card type if valid, else returns INVALID
string getCardType(long number);

//Returns length of number given as an argument
int numberLength(long input);

//Returns number at given index of the number 
//(starting at index 0, from right to left)
int getNumberAtIndex(int index, long number);

//Validates the checksum with Luhn's algorithm
bool validateChecksum(long number);

/*Returns the correct value of credit card digit to add to checksum
  according to Hans Peter Luhn's algorithm*/
int digitToChecksum(int index, int digit);

/*-----------------main program-----------------*/
int main(void) 
{   
    //get user input 
    long ccNumber = get_long("Enter cc number: ");
    //validate if user input is vaild credit card number
    printf("User input is %s\n", validateInput(ccNumber) ? "valid" : "invalid");
    //return card type
    printf("%s", getCardType(ccNumber));
}

/*-------------functions definitions------------*/

//Validate credit card number length
bool validateInput(long number)
{
    //check if number matches valid credit card number lengths
    int length = numberLength(number);
    if (validateChecksum(number) && (length == 13 || length == 15 || length == 16))
    {
        return true;
    }
    return false;
}

//If the card is valid (length 13 || 15 || 16) checks for the type of card
//Visa starts with "4", American Express with "34" or "37"
//MasterCard starts with "51", "52", "53", "54", "55"
string getCardType(long number) 
{
    if (validateInput(number))
    {
        int lastDigit = getNumberAtIndex(numberLength(number) - 1, number);
        int secondToLastDigit = getNumberAtIndex(numberLength(number) - 2, number);
        if (lastDigit == 4)
        {
            return "VISA\n";
        }
        else if (lastDigit == 3 && 
                 (secondToLastDigit == 4 || 
                  secondToLastDigit == 7))
        {
            return "AMEX\n";
        }
        else if (lastDigit == 5 &&
                 (secondToLastDigit == 1 ||
                  secondToLastDigit == 2 ||
                  secondToLastDigit == 3 ||
                  secondToLastDigit == 4 ||
                  secondToLastDigit == 5))
        {
            return "MASTERCARD\n";
        }
    }
    return "INVALID\n";
}

bool validateChecksum(long number)
{
    int checkSum = 0;
    //iterate through every digit of credit card number, use
    //digitToChecksum function to analize each digit and add
    //correct value to total checkSum
    for (int i = 0; i < numberLength(number); i++)
    {
        int numberAtCurrentIndex = getNumberAtIndex(i, number);
        checkSum += digitToChecksum(i, numberAtCurrentIndex);
    }
    //if checkSum's last digit is 0, the credit card number
    //is valid
    if (checkSum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int digitToChecksum(int index, int digit)
{
    //converts the digit of the credit card at specified index
    //into a number as specified by Luhn's algorithm
    //(indexing starts from 0 therefore even indexes are
    //treated as odd positions in credit card number)
    
    int addToChecksum = 0;
    if (index % 2 == 0)
    {
        addToChecksum = digit;
    }
    else 
    {
        if (digit * 2 > 9) 
        {
            addToChecksum = ((digit * 2) / 10) + ((digit * 2) % 10);
        }
        else
        {
            addToChecksum = digit * 2;
        }
    }
    return addToChecksum;
}

//returns number at given index of given number(counting from right side)
int getNumberAtIndex(int index, long number)
{
    int i = 0;
    int numberAtIndex;
    while (true)
    {   
        //get the digit at current index 
        numberAtIndex = number % 10;
        //and return it if it matches requested index
        if (i == index)
        {
            return numberAtIndex;
        }
        //if the indexes doesnt match, keep going to the
        //next index (from right to left)
        number /= 10;
        i++;
    }

}

//Counts the length of given cc number
int numberLength(long number) 
{
    int length = 0;
    while (true)
    {
        //if only a single digit of a number remains,
        //ncrement the length and return it
        if (number / 10 == 0) 
        {
            length++;
            return length;
        }
        //keep dividing by 10 untill only single digit remains,
        //then increment length
        number /= 10;
        length++;
    }
}
