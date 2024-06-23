#include <fmt/core.h>

#include <cassert>
#include <ranges>
#include <string>
using   std::views::iota,       // <ranges>
        std::stoi;              // <string>

auto up_to( const int n ) -> auto { return iota( 0, n ); }

auto main( int n_cmd_parts, char* cmd_parts[] ) -> int
{
    assert( n_cmd_parts == 2 or !"Usage: programname NUMBER" );
    const int n_rows = stoi( cmd_parts[1] );
    for( const int y: up_to( n_rows ) ) {
        int value = 1;
        for( const int x: up_to( y + 1 ) ) {
            fmt::print( "{} ", value );
            value = value*(y - x)/(x + 1);
        }
        fmt::print( "\n" );
    }
}
