//Martyna Cios
#include <string>
#include <cstdarg>
using namespace std;

char IntToChar(int intDigit) {
    return '0' + intDigit;
}

int CharToInt(char charDigit) {
    return charDigit - '0';
}

bool OnlyZeros ( const string& number, int index )
{
    if ( index >= number.length() )
        return true;

    if ( number[index] != '0' )
        return false;

    index++;
    return OnlyZeros ( number, index );
}

bool Minus ( const string& number )
{
    if ( number.empty() )
        return false;

    if ( number [ 0 ] != '-' )
        return false;

    return !OnlyZeros( number, 1 );
}

string GetTheStringNumber ( const string& number, int index = 0 ) {
    if ( index == number.length() )
        return "";
    if ( index == 0 && number [ index ] == '-' ) {
        index++;
    }
    index++;
    return number [ index - 1] + GetTheStringNumber ( number, index );
}

string FillWithZeros ( int index, const string& number ) {
    string zero = "0";
    if ( index != 0 ) {
        index--;
        return zero + FillWithZeros ( index, number );
    }
    else
        return number;
}

string AddOtherMinusValue ( string minuend, string subtrahend, int lastIndex ) {
    int penultimateIndex = lastIndex - 1;
    if ( lastIndex < 0 )
        return minuend;
    else {
        if ( minuend [ lastIndex ] < subtrahend [ lastIndex ] ) {
            minuend [ lastIndex ] += 10;
            minuend [ penultimateIndex ] -= 1;
        }
        minuend [ lastIndex ] = IntToChar ( minuend [ lastIndex ] - subtrahend [ lastIndex ] );
        return AddOtherMinusValue ( minuend, subtrahend, penultimateIndex );
    }
}

string AddSameMinusValue ( string firstNumber, string secondNumber, int lastIndex, int lovelyCarry = 0, string summary = "" ) {
    int lovelySum;
    if ( lovelyCarry > 0 || lastIndex >= 0 ) {
        lovelySum = lovelyCarry;
        if ( lastIndex >= 0 ) {
            int addIt = CharToInt ( firstNumber [ lastIndex ] ) + CharToInt ( secondNumber [ lastIndex ] );
            lovelySum += addIt;
        }
        char babySum = IntToChar ( lovelySum % 10 );
        lastIndex--;
        lovelyCarry = lovelySum / 10;
        return AddSameMinusValue ( firstNumber, secondNumber, lastIndex,lovelyCarry, babySum + summary );
    }
    return summary;
}

string SumHelper ( string firstNumber, string secondNumber ) {

    bool minusFirstNum = false;
    bool minusSecondNum = false;

    if ( Minus ( firstNumber ) )
        minusFirstNum = true;
    if ( Minus ( secondNumber ) )
        minusSecondNum = true;

    firstNumber = GetTheStringNumber ( firstNumber );
    secondNumber = GetTheStringNumber ( secondNumber );

    int firstSmallerSize = secondNumber.length() - firstNumber.length();
    int secondSmaller = firstNumber.length() - secondNumber.length();

    if ( firstNumber.length() > secondNumber.length () )
        secondNumber = FillWithZeros ( secondSmaller, secondNumber );
    if ( secondNumber.length() > firstNumber.length() )
        firstNumber = FillWithZeros( firstSmallerSize, firstNumber );

    int firstLastIndex = firstNumber.length() - 1;
    int secondLastIndex = secondNumber.length() - 1;

    if ( minusSecondNum == minusFirstNum ) {
        if ( minusFirstNum )
            return "-" + AddSameMinusValue( firstNumber, secondNumber, firstLastIndex, 0 );
        if ( !minusFirstNum )
            return AddSameMinusValue( firstNumber, secondNumber, firstLastIndex, 0 );
    } else if ( secondNumber > firstNumber ) {
        if ( minusSecondNum )
            return "-" + AddOtherMinusValue( secondNumber, firstNumber, secondLastIndex );
        else
            return AddOtherMinusValue( secondNumber, firstNumber, secondLastIndex );
    } else if ( firstNumber > secondNumber ) {
        if (minusFirstNum)
            return "-" + AddOtherMinusValue(firstNumber, secondNumber, firstLastIndex);
        else
            return AddOtherMinusValue(firstNumber, secondNumber, firstLastIndex);
    } else if ( firstNumber == secondNumber )
        return AddOtherMinusValue ( firstNumber, secondNumber, firstLastIndex );
}

string NoPlus ( const string& s, int index = 0 ) {
    int size = s.length();
    if ( index == size )
        return "";
    char digitOrSth = s [ index ];
    if ( digitOrSth != '+' )
        return digitOrSth + NoPlus( s, index + 1 );
    else
        return NoPlus ( s, index + 1 );
}

string NoSpaces ( const string & s, int index = 0 ) {
    if ( index == s.length() )
        return "";
    index++;
    if ( s [ index - 1 ] != ' ' )
        return s [ index - 1 ] + NoSpaces ( s, index );
    else
        return NoSpaces ( s, index );
}
string Sum_Minor ( int size, const string* array, int index, string theSummary = "0" ) {
    string digit;
    string noSpacesDigit;
    string noPlusDigit;

    if ( index < 0 )
        return theSummary;
    else {
        digit = array [ index ];
        noSpacesDigit = NoSpaces (digit );
        noPlusDigit = NoPlus ( noSpacesDigit );
    }
    string actualSum = SumHelper ( noPlusDigit, theSummary );
    index--;
    return Sum_Minor ( size , array, index, actualSum );
}

void ArgumentsToArray ( int size, string array [], va_list arguments, int index = 0 ) {
    if ( index < size ) {
        string s = (string)va_arg ( arguments, char* );
        array [ index ] = s;
        index++;
        ArgumentsToArray ( size, array, arguments, index );
    }
}

string RemoveFirstZeros_ ( string finalNumber, int index = 0, bool minus = false ) {
    if ( index == finalNumber.length() )
        return "0";
    else {
        if ( finalNumber [ index ] == '-' ) {
            minus = true;
            index++;
            return RemoveFirstZeros_ ( finalNumber, index, minus );
        } else if ( finalNumber [ index ] == '0' ) {
            index++;
            return RemoveFirstZeros_ ( finalNumber, index, minus );
        } else {
            if ( !minus )
                return finalNumber.erase ( 0, index );
            else
                return "-" + finalNumber.erase ( 0, index );
        }
    }
}

string Sum ( int size, const string* array ) {
    string maybeFinalSum = Sum_Minor(size, array, size - 1 );
    return RemoveFirstZeros_(maybeFinalSum);

}

string Sum ( int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ] ;
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string maybeFinalSum = Sum_Minor(size, array, size - 1);
    return  RemoveFirstZeros_(maybeFinalSum);

}

void Sum ( string* output, int size, const string* array ) {
    string maybeFinalSum = Sum_Minor(size, array, size - 1 );
    *output = RemoveFirstZeros_(maybeFinalSum);

}
void Sum ( string* output, int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ] ;
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string maybeFinalSum = Sum_Minor(size, array, size - 1 );
    *output = RemoveFirstZeros_(maybeFinalSum);
}
void Sum ( string& output, int size, const string* array ) {
    string maybeFinalSum = Sum_Minor(size, array, size - 1 );
    output = RemoveFirstZeros_(maybeFinalSum);
}
void Sum ( string& output, int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ] ;
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string maybeFinalSum = Sum_Minor(size, array, size - 1 );
    output = RemoveFirstZeros_(maybeFinalSum);
}