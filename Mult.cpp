//Martyna Cios
#include <string>
#include <cstdarg>
using namespace std;

char IntToChar ( int );
int CharToInt ( char );
string NoPlus (const string&, int index = 0);
string NoSpaces (const string&, int index = 0);
void ArgumentsToArray ( int size, string array [], va_list arguments, int index = 0 );
string RemoveFirstZeros_ ( string finalNumber, int index = 0, bool minus = false );

bool MinusforMult ( const string& n ) {
    if ( n [ 0 ] == '-' )
        return true;
    else
        return false;
}

string FillWithZerosAtTheEnd ( int zeros, const string& number ) {
    if ( zeros > 0 ) {
        zeros--;
        return FillWithZerosAtTheEnd(zeros, number) + '0';
    } else
        return number;

}

string SumIt ( string firstNumber, string secondNumber, int carry, string summary, int firstLastIndex, int secondLastIndex ) {
    char unitsDigit;
    int littleSum;
    if ( carry == 0 && firstLastIndex < 0  && secondLastIndex < 0 )
        return summary;

    littleSum = carry;

    if ( firstLastIndex >= 0 )
        littleSum += CharToInt ( firstNumber [ firstLastIndex ] );
    if ( secondLastIndex >= 0 )
        littleSum += CharToInt ( secondNumber [ secondLastIndex ] );
    unitsDigit = IntToChar ( littleSum % 10 );

    carry = littleSum / 10;
    summary = unitsDigit + summary;
    firstLastIndex--;
    secondLastIndex--;
    return SumIt( firstNumber, secondNumber, carry, summary, firstLastIndex, secondLastIndex );
}

string MultWithTheDigit ( string number, char digit, int carry, int lastIndex , string summary ) {
    char unitsDigit;
    if ( carry == 0 && lastIndex < 0 )
        return summary;
    int multiplication = carry;

    if ( lastIndex >= 0 )
        multiplication += CharToInt ( number [ lastIndex ] ) * CharToInt ( digit );

    unitsDigit = IntToChar ( multiplication % 10 );
    carry = multiplication / 10;
    summary = unitsDigit + summary;

    lastIndex--;
    return MultWithTheDigit ( number, digit, carry, lastIndex, summary );
}

string Multiply__ ( string firstNumber, string secondNumber, string finalSummary, int lastIndex, int zeros = 0 ) {
    if ( lastIndex < 0 )
        return finalSummary;
    string temp = MultWithTheDigit( firstNumber, secondNumber [ lastIndex ], 0, firstNumber.length() - 1, "" );
    temp = FillWithZerosAtTheEnd( zeros, temp );
    zeros++;
    int tempLastIndex = temp.length() - 1;
    int lastIndexOfTheSum = finalSummary.length() - 1;
    string sum = SumIt( temp, finalSummary, 0, "", tempLastIndex, lastIndexOfTheSum );
    lastIndex--;
    return Multiply__ ( firstNumber, secondNumber, sum, lastIndex, zeros );
}

string Mult___ ( int size, const string* array, int index = 0, string finalSummary = "1", bool minus = false ) {
    bool isLovelyNumberNegative;
    if ( index >= size ) {
        if ( ! minus )
            return finalSummary;
        else
            return "-" + finalSummary;
    }
    string lovelyNumber = NoSpaces ( array [ index ] );
    lovelyNumber = NoPlus ( lovelyNumber );
    isLovelyNumberNegative = MinusforMult( lovelyNumber );
    if ( isLovelyNumberNegative )
        lovelyNumber.erase( 0, 1 );
    minus = ( minus != isLovelyNumberNegative );
    index++;
    int lastIndexOfTheSum = finalSummary.length() - 1;
    string summary = Multiply__ ( lovelyNumber, finalSummary, "0", lastIndexOfTheSum );
    return Mult___ ( size, array, index, summary, minus );

}


string Mult ( int size, const string* array ) {
    string maybeFinalSum = Mult___(size, array);
    return RemoveFirstZeros_(maybeFinalSum);
}

string Mult ( int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ] ;
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string maybeFinalSum = Mult___(size, array);
    return RemoveFirstZeros_(maybeFinalSum);
}
void Mult ( string* output, int size, const string* array ) {
    string maybeFinalSum = Mult___(size, array);
    *output = RemoveFirstZeros_(maybeFinalSum);
}
void Mult ( string* output, int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ] ;
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string maybeFinalSum = Mult___(size, array);
    *output = RemoveFirstZeros_(maybeFinalSum);
}
void Mult ( string& output, int size, const string* array ) {
    string maybeFinalSum = Mult___(size, array);
    output = RemoveFirstZeros_(maybeFinalSum);
}
void Mult ( string& output, int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ] ;
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string maybeFinalSum = Mult___(size, array);
    output = RemoveFirstZeros_(maybeFinalSum);
}

