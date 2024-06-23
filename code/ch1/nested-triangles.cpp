#include <fmt/core.h>

#include <array>
#include <bitset>
#include <ranges>
#include <span>
#include <string>
using   std::array,                     // <array>
        std::bitset,                    // <bitset>
        std::ranges::iota_view,         // <ranges>
        std::span,                      // <span>
        std::string;                    // <string>

template< class Type > using in_ = const Type&;

auto up_to( const int n ) -> auto { return iota_view( 0, n ); }
auto one_through( const int n ) -> auto { return iota_view( 1, n + 1 ); }

using C_str = const char*;

const int n = 32;                   // The image is always a square with side `n` a power of 2.
using Bits_row = bitset<n>;         // Least significant bit on the left in image.
using Image = array<Bits_row, n>;   // Indexing as [y][x]. Too simple to define a class.

void display( in_<Image> image )
{
    constexpr C_str block_ch[] = {" ", "▀", "▄", "█"};
    for( const int half_y: up_to( n/2 ) ) {
        const int y = 2*half_y;
        string line;
        for( const int x: up_to( n ) ) {
            line += block_ch[image[y][x] + 2*image[y + 1][x]];
        }
        fmt::print( "{}\n", line );
    }
}

auto main() -> int
{
    // Generates the Pascal triangle modulo 2:
    Image image = {1};
    for( const int y: one_through( n - 1 ) ) {
        image[y] = image[y - 1] ^ (image[y - 1] << 1);      // Addition modulo 2 = XOR.
    }
    display( image );
}
