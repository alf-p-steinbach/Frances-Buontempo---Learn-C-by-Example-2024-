#include <fmt/core.h>
#include <assert.h>
#include <string>
using   std::stoi;          // <string>

auto squared( const int x ) -> int { return x*x; }

auto main( int n_cmd_parts, char* cmd_parts[] ) -> int
{
    assert( n_cmd_parts == 2 );
    const int n = stoi( cmd_parts[1] );
    int sum = 0;
    for( int i = 1; i <= n; ++i ) { sum += squared( i ); }      // O( n )
    fmt::print( "The sum of 1² through {}² is {}.\n", n, sum );
}
