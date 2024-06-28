#include <fmt/core.h>

#include <iostream>
#include <string>
#include <string_view>
using   std::cin,                           // <iostream>
        std::getline, std::string,          // <string>
        std::string_view;                   // <string_view>

namespace my {
    using Byte = unsigned char;
    template< class T > using in_ = const T&;

    #ifdef _WIN32           // Windows, 32-bit or 64-bit.
        #include <stdlib.h>     // `::system`
        inline const int dummy_for_setting_utf8_encoding_in_console = system( "chcp 65001 >nul" );
    #endif
            
    auto input_line() -> string
    {
        // TODO: replace with infinite-input-safe line collection from C level `stdin`,
        //       corresponding to `fmt::print` outputting via C level `stdout`.
        string line;
        getline( cin, line );   // TODO: failure handling.
        return line;
    }

    auto is_utf8_tail( const Byte value ) -> bool { return (128 <= value and value < 192); }
}  // namespace my

using my::Byte, my::in_;

void display_encodings_of( in_<string_view> s )
{
    const int field_width = 4;      // Max 3 digits per encoding code 0 through 255.

    // Display the characters.
    for( int i = 0, n = int( s.size() ); i < n; ) {
        int next_i = i + 1;
        while( next_i < n and my::is_utf8_tail( Byte( s[next_i] ) ) ) { ++next_i; }
        const int n_bytes = next_i - i;
        fmt::print( "{:>{}s}", string_view( &s[i], n_bytes ), n_bytes*field_width );    // One char.
        i = next_i;
    }
    fmt::print( "\n" );
    
    // Display the codes.
    for( const Byte code: s ) { fmt::print( "{:>{}d}", code, field_width ); }
    fmt::print( "\n" );
}

auto main() -> int
{
    fmt::print( "Hi, what’s your name? " );
    const string name = my::input_line();

    fmt::print( "\n" );
    fmt::print( "Your name was encoded as:\n" );
    display_encodings_of( name );

    fmt::print( "\n" );
    fmt::print( "Pleased to meet you, {}!\n", name );
}
