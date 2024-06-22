#include <fmt/core.h>
#include <assert.h>
#include <string>
using   std::stoi;          // <string>

auto main( int n_cmd_parts, char* cmd_parts[] ) -> int
{
    assert( n_cmd_parts == 2 );
    const int n = stoi( cmd_parts[1] );
    fmt::print( "The sum of 1² through {}² is {}.\n", n, n*(n + 1)*(2*n + 1)/6 );
}
