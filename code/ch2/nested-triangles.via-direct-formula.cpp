#include <fmt/core.h>

#include <ranges>
#include <string>
using   std::ranges::iota_view,         // <ranges>
        std::string;                    // <string>

template< class Type > using in_ = const Type&;
using Bit = enum{ zero, one };
using C_str = const char*;

auto up_to( const int n ) -> auto { return iota_view( 0, n ); }

auto image_at( const int x, const int y )
    -> Bit
{ return Bit( !(x & ~y) ); }

void display_image( const int n )
{
    constexpr C_str block_ch[] = {" ", "▀", "▄", "█"};
    for( const int half_y: up_to( n/2 ) ) {
        const int y = 2*half_y;
        string line;
        for( const int x: up_to( n ) ) {
            line += block_ch[image_at( x, y ) + 2*image_at( x, y + 1 )];
        }
        fmt::print( "{}\n", line );
    }
}

auto main() -> int
{
    display_image( 32 );        // The image is always a square with side `n` a power of 2.
}
