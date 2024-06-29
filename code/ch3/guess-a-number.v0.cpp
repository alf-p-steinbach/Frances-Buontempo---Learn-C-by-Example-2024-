
#include <fmt/core.h>

#include <cassert>          // assert
#include <cctype>
#include <cstdlib>          // EXIT_...

#include <iostream>
#include <string_view>

using Byte = unsigned char;
template< class T > using in_ = const T&;

namespace cpp_machinery {
    using   std::isspace,               // <cctype>
            std::exit,                  // <cstdlib>
            std::cin, std::istream,     // <iostream>
            std::string_view;           // <string_view>

    auto is_ascii_space( const Byte code ) -> bool { return (code < 128 and ::isspace( code )); }

    struct Clearing_result{ enum Enum{ all_space, not_all_space, error }; };

    auto clear_through_eol( istream& stream )
        -> Clearing_result::Enum
    {
        auto result = Clearing_result::all_space;
        for( ;; ) {
            const char ch = char( stream.get() );
            if( stream.fail() ) {
                return (stream.eof()? result : Clearing_result::error);
            }
            if( ch == '\n' ) {
                return result;
            }
            if( not is_ascii_space( ch ) ) { result = Clearing_result::not_all_space; }
        }
        for( ;; ) {}        // Should never get here (avoids possible silly-warning).
    }

    // With more of C++ on board this would throw an exception and formally return `bool`.
    [[noreturn]] void fail( in_<string_view> message )
    {
        fmt::print( stderr, "\n!{}\n", message );
        exit( EXIT_FAILURE );
    }

    // Abort messages. Can be in English because aborts will normally not occur, and English
    // is used for fatal error messages everywhere so it’s OK. This is not normal UI stuff.
    const auto& cin_eof_msg     = "End-of-file on input stream; terminating (sorry).";
    const auto& cin_failure_msg = "Input stream failure; terminating (sorry).";
    const auto& cin_mystery_msg = "Read failure with nothing or only spaces left (a mystery!).";

    // Default messages for number reading. English is just the default.
    const auto& invalid_spec_default_msg    = "? That was not a valid integer spec.";
    const auto& noise_default_msg           =
        "? Extraneous characters after a valid number spec (which was therefore ignored).";

    auto input_int_from_valid_stream(
        in_<string_view>    prompt,
        in_<string_view>    invalid_message = invalid_spec_default_msg,
        in_<string_view>    noise_message   = noise_default_msg
        ) -> int
    {
        for( ;; ) {
            fmt::print( "{}", prompt );
            int result;
            cin >> result;

            using CR = Clearing_result;
            const bool success = not cin.fail();
            if( success ) {
                switch( clear_through_eol( cin ) ) {
                    case CR::all_space:        { return result; }
                    case CR::not_all_space:    { fmt::print( "{}\n", noise_message );  break; }
                    case CR::error:            { fail( cin_failure_msg ); }
                }
            } else if( cin.eof() ) {
                fail( cin_eof_msg );
            } else {
                cin.clear();        // Clear all failure mode flags.
                switch( clear_through_eol( cin ) ) {
                    case CR::all_space:        { fail( cin_mystery_msg ); }
                    case CR::not_all_space:    { fmt::print( "{}\n", invalid_message );  break; }
                    case CR::error:            { fail( cin_failure_msg ); }
                }
            }
        }
        for( ;; ) {}        // Should never get here (avoids possible silly-warning).
    }

    auto input_int(
        in_<string_view>    prompt,
        in_<string_view>    invalid_message = invalid_spec_default_msg,
        in_<string_view>    noise_message   = noise_default_msg
        ) -> int
    {
        if( cin.eof() ) { fail( cin_eof_msg ); }
        else if( cin.fail() ) { fail( cin_failure_msg ); }

        return input_int_from_valid_stream( prompt, invalid_message, noise_message );
    }
}  // namespace cpp_machinery

namespace app {
    using   cpp_machinery::input_int;

    void guess_number( const int number )
    {
        assert( 1 <= number and number <= 100 );
        fmt::print( "In this game your goal is to guess a secret number 1...100.\n" );
        for( ;; ) {
            const int guess = input_int( "Guess the number: " );
            if( guess == number ) { break; }
            fmt::print( "{} is unfortunately wrong. Try again.\n", guess );
        }
        fmt::print( "Well done!\n" );
    }
}  // namespace app

auto main() -> int { app::guess_number( 42 ); }
