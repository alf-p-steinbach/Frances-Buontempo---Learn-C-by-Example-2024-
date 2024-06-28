#include <iostream>
#include <string>
using   std::cin, std::cout, std::endl,
        std::getline, std::string;

#ifdef _WIN32           // Windows, 32-bit or 64-bit.
    #include <stdlib.h>     // system
    const int dummy_for_setting_utf8_in_console = system( "chcp 65001 >nul" );
#endif
        
auto input_line() -> string
{
    string line;
    getline( cin, line );   // TODO: failure handling.
    return line;
}

auto main() -> int
{
    cout << "Hi, what’s your name? ";
    const string name = input_line();
    for( const char ch: name ) { cout << +(unsigned char)ch << " "; }  cout << endl;
    cout << "Pleased to meet you, " << name << "!" << endl;
}
