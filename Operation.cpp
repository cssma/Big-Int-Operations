//Martyna Cios
#include <string>
#include <cstdarg>
using namespace std;

void ArgumentsToArray ( int size, string array [], va_list arguments, int index = 0 );

string Operation ( string ( *Function )( int, const string* ), int size, const string* numbersArray ) {
    return Function ( size, numbersArray );
}

string Operation ( string ( *Function )( int, const string* ), int size, ... ){
    va_list arguments;
    va_start(arguments, size);

    string array [ size ];
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string result = Function ( size, array );
    return result;
}

void Operation ( string* output, string ( *Function )( int, const string* ), int size, const string* numbersArray ) {
    *output = Function ( size, numbersArray );
}

void Operation ( string* output, string ( *Function )( int, const string* ), int size , ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ];
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    string result = Function ( size, array );
    *output = result;
}

void Operation ( string& output, void ( *Function )(string*, int, const string*), int size, const string* numbersArray ) {
    Function ( &output, size, numbersArray );
}

void Operation ( string& output, void ( *Function )(string*, int, const string*), int size, ... ) {
    va_list arguments;
    va_start(arguments, size);

    string array [ size ];
    ArgumentsToArray ( size, array, arguments );

    va_end(arguments);

    Function ( &output, size, array );
}
