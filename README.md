A June 2024 review & critique of
# <span>Frances Buontempo &ndash; “Learn C++ by Example” (2024)</span>

<img src="images/cover.png" width="50%" align="right">

When someone attempted to post a pirate copy of this book to a Facebook group that I moderate, I notified Frances and apologized for viewing (actually downloading!) the PDF, and starting to read it. She suggested that I publish a review of the book. So, hereby.

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [My perspective.](#my-perspective)
- [The book’s goal.](#the-books-goal)
- [Chapter 1 &mdash; “Hello again, C++!”.](#chapter-1-mdash-hello-again-c)
- [Chapter 2 &mdash; “Containers, iterators, and ranges”.](#chapter-2-mdash-containers-iterators-and-ranges)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## My perspective.

Frances writes in “Who should read this book” that

> ❞ If you have used C++ before but have failed to keep up with recent
changes, this book is for you.

That’s me. I jumped off the train between C++17 and C++20. Considering that Apple clang++ doesn’t even implement all of C++17 &mdash; as of this writing, June 2024, there’s still no support for floating point [`std::from_chars`](https://en.cppreference.com/w/cpp/utility/from_chars) &mdash; I thought it was reasonable to stick with C++17 for a while.

Another reason was that I was really disappointed with C++20, e.g.:

* *Modules*, of very limited utility because   
  they’re still only reasonably supported by one compiler.
* The C++20 *sabotage of `std::filesystem`*  
  with the changed `fs::path::u8string` adding needless string copying overhead in Windows, and `fs::u8path` deprecated to add needless warnings, and the incorrectness that`fs::path` constructors etc. were still formally required to garble path specifications in a Windows UTF-8 based program (because the Windows changes of June 2019, with support for UTF-8 as a process’ internal ANSI codepage, made the C++17 wording a defect, which was [not fixed in C++20](https://github.com/alf-p-steinbach/C---how-to---make-non-English-text-work-in-Windows/blob/main/how-to-use-utf8-in-windows.md#5-how-to-make-stdfilesystempath-do-the-work)).
* *Coroutines* support that was half finished, too limited & too inefficient,  
  half finished because one needed a DIY or 3<sup>rd</sup> party framework in addition to the core language support; limited because  C++ for efficiency supports only stackless coroutines; and, ironically, inefficient because every coroutine instantiation by default involves a dynamic allocation, because by default these beasts support recursive instantiation.
* The *Ranges* sub-library, a good way to write concise but brittle code,  
  and to some degree write-only code, with dysmal performance. The ranges sub-library adds some scripting language feeling that some people find very desirable, and (so) it has some enthusiastic supporters. But it could and IMHO should have continued to be a 3<sup>rd</sup> party special interest library: not adding all that to compilations and to user programs and to the standard’s text. 
* Minor point but still *no qualified function name macro* like [`__func__`](https://en.cppreference.com/w/c/language/function_definition#func);  
  instead C++20 added `std::source_location`, which does not help when one still has to use macros with compiler specific implementations to get qualified function names for source locations, and which additionally does not have no-throwing copying so that it’s grossly imperfectly suited for being carried by an exception.

So, I am a reader primarily interested in the new C++20 and C++23 core language stuff. As the bullet points show I have some strong and well founded opinions. As they also show I’m not shy of pointing out problems.

I’m well versed in C++98, C++03, C++11, C++14 and C++17, and so able to evaluate how well and how widely the book covers the new features in C++11 and later standards.

I have worked as a vocational school teacher and as a college lecturer, and over the years I’ve used much of my time on discussing C++ and helping students, but I would not claim to be able to evaluate teaching, the pedagogical aspect. As I see it what suits one person may not necessarily suit another. What I find clear may be ungrokable to some student and vice versa; all I can say is that this book is *not unclear*.

## The book’s goal.

In “Why read this book?” Frances writes

> ❞ The [[ISOCpp](https://isocpp.org)] site even has a section for people
with a background in other languages who want to learn C++. It
doesn’t have a section for “Learning C++ if you already knew C++ a
while ago.” This book plugs that gap. You don’t need a long list of
every feature that’s been introduced over the years. You need just
enough to get your confidence back.

It seems the aim is to provide a clear solid learning path through the main features of C++11 through C++23, enabling the reader to explore further.

The aim is clearly *not* to cover or even mention all of the myriad new features. Rather, the path will visit some main features that were needed or convenient in some concrete examples, which is an approach to relevance that I agree with. And in “Who this book is for” Frances writes:

> ❞ If you used to know all the gnarly edge cases
and quote chapter and verse of a previous standard, this book will
help you focus on a handful of new features to get you back in the
driving seat.

## Chapter 1 &mdash; “Hello again, C++!”.

Chapter 1, called “Hello again, C++!”, is a bit of this and that:

* some praise of the C++ language, mentioning many different things it’s used for;
* a long-winded heads up warning that there’s much to learn;
* some more praise for C++, e.g. “C++ can be awesome”;
* the aforementioned “Why read this book”;
* a section “Who this book is for” where incongrously all that's said about that is the very first sentence, “This book is aimed at people who have used a little, or even a lot, of
the language and lost track of recent changes”, and the rest reiterates how the book will guide the reader so don’t panic;
* a C++11 “Hello, world!” program that introduces the trailing return type syntax (modern function declaration syntax like `auto foo() -> int`); and
* an elaboration of that example that shows the power of the new syntax, and additionally introduces deduced return type but without introducing a term for that;
* an overview of what one can expect to learn from the book; and
* a section “Some pro tips” that introduces three currently very useful web sites, namely [C++ Insights](https://cppinsights.io/), [Compiler Explorer](https://godbolt.org/) and [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support), plus reiterates the advice **Don’t Panic!** which I think is very good advice, except perhaps after some dolphin says “So long and thanks for all the fish!”.

I would have liked Frances to cut down on all the rest, drastically, and expand on the two “Hello, world!” examples.

First, the book doesn’t mention that this is a *C++11* “Hello, world!”:

[*C++11*](code/ch1/hello.book.cpp):

```cpp
#include <iostream>

auto main() -> int
{
    std::cout << "Hello, world!\n";
}
```

Why does that matter? Well, with C++11 the only change from C++03 was the trailing return type syntax. But with C++23 one will reasonably use `std::print` instead of iostreams, both in order to get general Unicode text presented correctly, for the better support for internationalization that format strings give, and as a single unified way to do formatting that is super fast, efficiency!, efficiency!, for number-to-text conversion. 

The C++23 example below is unfortunately not given in the book:

[*C++23*](code/ch1/hello.c++23.cpp):

```cpp
#include <print>

auto main() -> int
{
    std::print( "Hello, world!\n" );        // Supports Unicode output also in Windows.
}
```

When the book was written compiler support for `std::print` was probably rare. For this review I had to upgrade Visual C++ to compile that code. My usual MinGW g++ compiler (version 11.2.0 from the Nuwen distro) did not support it, but the MSYS2 distro’s MinGW g++ version 14.1.0 did, and even linked successfully when given option `-lstdc++exp`.

The replacement of iostreams output with functionality adopted from [the {fmt} library](https://github.com/fmtlib/fmt), such as `std::print`, is a fundamental change, that I think should have been mentioned for “Hello, world!”.

And also, how one can use the {fmt} library also with C++17, instead of the currently bleeding edge C++23 `std::print`. Perhaps also mention that the {fmt} library, but not the adoption in the C++ standard library, supports colored output via ANSI escapes. I believe that that is of interest to students: they often ask how to do colors.

And in the area of mentioning problems and not shoving them under the nearest carpet: mentioning that C++ as of C++23 still lacks portable Unicode *console input* functionality, which it should have so that a student also in portable C++ can write a little program that asks for his or her name, and that displays it correctly in a personalized greeting &mdash; the natural “Hello, world!” 2 program.

Nitpick 1: for the deduced return type *discussion* I would have liked mention of and a link to Andrei Alexandrescu’s classic C++03 article [“Min and Max Redivivus”](https://web.archive.org/web/20030114105307/http://www.cuj.com/experts/1904/alexandr.htm).

Nitpick 2: for deduced return type *notation* I prefer to specify that explicitly, like `auto foo() -> auto { …`, instead of implicitly like `auto foo() { …` as in the book’s example. I’m not entirely sure but I think the explicit deduced return type notation, my preferred notation, was introduced in C++14. It was not valid in C++11.

Nitpick 3: `main` is described as “the usual entry point for executable
code”. The “entry point” term for `main` has unfortunately now been adopted even by cppreference, so this description uses now established terminology and is OK that way. But there’s no need to use that term and using it is very misleading, in two ways: (1) user code can be executed before and after `main`, so `main` is decidely not where execution enters the user code of the program, not to mention the notion of `main` as entry point for executable code, and (2) the term *entry point* used to refer unambigously to the machine code level entry point, the entry point that one specifies to a linker, but now when *entry point* is used also for `main` one may need to clarify (especially to learners) whether one is talking about the *machine code entry point* or the *user code “entry point”*, which should be unnecessary to do.

General impression: the chapter does a good job of pointing out that modern C++ is different from C++03, but is too long-winded about other intro stuff, and as I see it the text really should have mentioned replacing iostreams output with C++23’s `std::print` or the {fmt} library &mdash; a big and fundamental change. 

## Chapter 2 &mdash; “Containers, iterators, and ranges”.

<img src="images/wikipedia-pascal-triangle.svg" align="right">

Chapter 2, titled “Containers, iterators, and ranges”, primarily introduces item list notation (curly braces), move semantics and range based loops with `auto`.

This is done very naturally by iterative development of code to display [Pascal’s triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle), a triangle of numbers where each is the sum of the two numbers above.

Along the way the ranges sub-library and C++20’s `std::format` appear, with mention that the latter is a partial adoption from the 3<sup>rd</sup> party [{fmt} library](https://github.com/fmtlib/fmt), but alas no mention of the separate original 3<sup>rd</sup> party [Ranges v3 library](https://github.com/ericniebler/range-v3) or its precursor the [Boost Range sub-library](https://www.boost.org/doc/libs/1_85_0/libs/range/doc/html/index.html).

---

Three main improvement potentials I see with this chapter:

* Considering efficiency.  
  Relative to the overhead of console output, internal efficiency for computing and for checking the triangle is insignificant. But the final console presentation is not the goal: the goal is to learn about C++ things. And in *that* context grossly inefficient techniques such as using a `vector` of `vector`s as a half matrix to store the triangle in, is very un-C++-ish and misleading about what’s reasonable: pointing out and exemplifying how one can do things in more reasonably efficient ways could really help the reader.
* Guaranteeing rather than just checking correctness.  
  When one deals directly with a `vector` of `vector`s one has no guarantee what they contain. Then checking (as the chapter exemplifies) can be a good idea. But I wish this chapter had also or alternatively exemplified and emphasized that providing the data via a class, an abstraction, can *guarantee* correctness.
* Crossing all the t’s, dotting all the i’s, and filling in all the spaces.  
  I would have liked an *explanation* of the connection between Pascal’s triangle and combinations (see below, if you like math then it’s easy when you have seen it); I would have liked a reference to I believe it was MIT’s Barbara Liskov for the triangles pattern; and, efficiency!, efficiency!, I would have liked mention of how that pattern needs no more than 0 and 1 for each number, so that it can be arbitrarily large (as opposed to max 35 rows), and not just that but also an example and reference to Stephen Wolfram’s “A New Kind of Science” for [how to do that pattern *efficiently*](https://www.wolframscience.com/nks/p608--traditional-mathematics-and-mathematical-formulas/) and *amazingly* with O(log *n*) or for small *n* O(1) storage instead of O(*n*²), by using the C++ bit level operators.

There is a strong connection between the three points above, for both efficiency and correctness depend crucially on *understanding* and/or *knowing* a good deal about the problem that the code is intended to solve, and understanding and acquiring knowledge of the problem is much easier when one is given an explanation and/or references.

The “and/or”: one doesn’t always need to understand everything about the problem; knowledge can suffice. For example, the sum of 1² through *n*² can be calculated as just *n*(*n* + 1)(2*n* + 1)/6. It’s OK to just use the formula in one’s code without understanding the details of how to derive it or prove it, and understanding the formula will probably not help, but a reference, e.g. a mention of and perhaps also link to “[pyramidal numbers](https://en.wikipedia.org/wiki/Square_pyramidal_number)”, can help.

---

A C++-ish efficiency oriented perspective on Pascal’s triangle (or whatever!) starts with *understanding* what it is about, not just remembering the mechanics of one way to generate it.

Probably Pascal was investigating the coefficients of the terms that you get when you multiply out $(a + b)^n$. For example, $(a + b)^2 = a^2 + 2ab + b^2$, with coefficients **1**, **2** and **1**, which are the third line in Pascal’s triangle. And what do you get when you multiply that by $(a + b)$ again, thus forming $(a + b)^3$?

Well, *a* and *b* are on an equal footing so the result will necessarily be symmetrical, as 1, 2 and 1 is:

$$ \begin{align*}
    (a + b)\cdot(a^2 + 2ab + b^2) &= a\cdot(a^2 + 2ab + b^2) + b\cdot(a^2 + 2ab + b^2)\\
    \\
    &= (a^3 + 2a^2b + ab^2) + (a^2b + 2ab^2 + b^3)
\end{align*} $$

&hellip; where the two parenthesized expressions in the result contain some terms that match, and thus can be added together, when one of the expressions is shifted one step to the right or left:

$$ \begin{matrix}
    a^3 & + & 2a^2b & + & ab^2 & {} & {} \\
    {} & {} & a^2b & + & 2ab^2 & + & b^3 \\
    \hline \\
    a^3 & + & 3a^2b & + & 3ab^2 & + & b^3 \\
\end{matrix} $$

The first row here has the coefficients 1, 2, 1; and the second row also has the coefficients 1, 2, 1, just shifted one step to the right. And they’re then added together in each column. This shifting of a row and columnwise addition with the original, is exactly the common procedure for Pascal’s triangle.

This chapter of the book exemplifies but does not explain that the coefficients of this Pascal row #4, namely 1, 3, 3 and 1, are also the number of possible ways to select respectively *r* = 0, 1, 2 or 3 *b*’s from a sequence of *n* = 3 *b*’s. Which is called the number of **combinations** of respectively 0, 1, 2 or 3 *b*’s from 3 *b*’s, typically labeled “**nCr**” on a calculator. One way to understand it is to view $a^3 + 3a^2b + 3ab^2 + b^3 = (a + b)^3$ as

$$(a + b)\cdot(a + b)\cdot(a + b)$$

When you multiply that out without collecting like terms and without reducing e.g. $a \cdot a \cdot a$ to just $a^3$ (etc.), then you get a number of terms like $(a \cdot a \cdot a)$, $(a \cdot a \cdot b)$, $(a \cdot b \cdot a)$ etc. “A number of”: each such basic term has 3 symbols where each symbol can be one of 2 possibilities, either *a* or *b*, which means that there are $2^3 = 8$ possible terms. Which means that the sum of the coefficients will be 8 for this row, and generally $2^{k-1}$ for row *k* (with *k* starting at 1 for the first row), which Frances uses as one validity check on data that should be the coefficients.

And e.g. the coefficient for $a^2b$, namely 3, is the number of basic terms that reduce to $a^2b$, i.e. the number of basic terms that have 2 *a*’s, which is the number of ways to choose 2 *a*’s in $(a + b)\cdot(a + b)\cdot(a + b)$ when the order you choose them in doesn’t matter.

If the order did matter then there would be 3 possibilities for the first *a* and for each of them 2 possibilities for the second, i.e. $3 \cdot 2 = 6$ ways to choose them. More generally that’s $n \cdot (n-1) \cdot (n-2) \cdot \ldots \cdot (n-r+1)$ ways, with *r* factors in that product, $= n!/(n - r)!$. But since the order should not matter one must divide that again by the number of possible orders of the *r* chosen symbols, namely $r!$, which means that 

$$
\text{nCr} = \frac{n!}{(n - r)!\cdot r!}
$$

In math the calculator notation nCr is written as ${n \choose r}$. A sum of two things like $(a + b)$ is known as a [**binomial**](https://en.wikipedia.org/wiki/Binomial_(polynomial)), a polynomial with 2 terms, and thus ${n \choose r}$ is a **binomial coefficient**. So Pascal’s triangle is a table of binomial coefficients, the number of ways to choose things from sets of things.

Anyway this means &mdash; efficiency!, efficiency! &mdash; that each number in Pascal’s table can be calculated from the previous reading order one in *constant time*, O(1), which is how I did this in high school roughly 1980:

$$ \begin{align*}
    {n \choose {r + 1}} \bigg / {n \choose r} &= 
        {\frac{n!}{(n - (r + 1))!\cdot (r + 1)!}} \bigg / {\frac{n!}{(n - r)!\cdot r!}} \\
        \\
        &= \frac {(n - r)!\cdot r!} {(n - (r + 1))!\cdot (r + 1)!} \\
        \\
        &= (n - r) / (r + 1)
\end{align*} $$

[*pascal-triangle.incremental.cpp*](code/ch1/pascal-triangle.incremental.cpp):

```cpp
#include <fmt/core.h>

#include <cassert>
#include <ranges>
#include <string>
using   std::ranges::iota_view, // <ranges>
        std::stoi;              // <string>

auto up_to( const int n ) -> auto { return iota_view( 0, n ); }

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
```
Outputs e.g.

```text
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
```

I wish the chapter had demonstrated this kind of efficiency, the C++ mindset, rather than or in addition to use of a vector of vectors to store the generated triangle. Perhaps with a more clear and easy to understand explanation than I managed in the short space here. Incidentally, this little program also demonstrates deduced return type, due to convenience use of the ranges sub-library’s `iota_view`, in the `up_to` function.

----

The fractal triangles-within-triangles image presented in section §2.3.6 is a nice example of *exploration*.

IMO it’s very good that a book encourages exploration.

So, plus marks to the book for that.

I believe that pointing out to students that they can find interesting patterns by coloring the numbers in Pascal’s triangle, e.g. based on the odd/even property, was popularized by Barbara Liskov at MIT, the lady famous for Liskov’s substitution principle. But with limited effort I was unable to google up a reference. However, Frances does mention that the fractal is called a Sierpinski triangle, so that the reader can find out more about the fractal, at least.

On the third hand, in this section I would have liked mention of the fact that calculating the full numbers severely limits the size of the image because one gets integer overflow (which has already been discussed), but that calculating the full numbers is unnecessary because when only the odd/even property is considered only the values modulo 2, i.e. 0 and 1, need to be calculated:

```cpp
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
```

Output:

```text
█▄
█▄█▄
█▄  █▄
█▄█▄█▄█▄
█▄      █▄
█▄█▄    █▄█▄
█▄  █▄  █▄  █▄
█▄█▄█▄█▄█▄█▄█▄█▄
█▄              █▄
█▄█▄            █▄█▄
█▄  █▄          █▄  █▄
█▄█▄█▄█▄        █▄█▄█▄█▄
█▄      █▄      █▄      █▄
█▄█▄    █▄█▄    █▄█▄    █▄█▄
█▄  █▄  █▄  █▄  █▄  █▄  █▄  █▄
█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄█▄
```

Since the image storage is quite minimal there’s not much point in optimizing this further. But in principle for the above approach one only needs *two* `Bits_row` of storage, with one of them representing the previous row in the iteration over rows. And even that can be dispensed with by calculating the value at any point (*x*, *y*) directly, in constant time!, as just [`!(x & ~y)`](https://www.wolframscience.com/nks/p608--traditional-mathematics-and-mathematical-formulas/); the trick by Stephen Wolfram that I referenced earlier.

So, these are the kind of C++-ish efficient and tight coding examples, and background explanation + references, that I wish had been presented in addition to or perhaps instead of checking oddness in a vector-of-vectors storage of range-limited numbers &mdash; it’s an idea for a second edition of the book!

---

Now for a slightly embarrassing terminological issue, namely a misleading conflation of C++ *moving*, which is done with `std::move`, with the special concept of C++ *perfect forwarding*, done with `std::forward`.

To wit, in section §2.2.3 “Move semantics and perfect forwarding” Frances presents the `std::vector` example

> ```cpp
> void push_back( T&& value ) {
>     emplace_back(std::move(value));
> }
> ```

&hellip; and writes, evidently with reference to the parameter named `value`, that

> ❞ C++’s `move` operation does not actually move anything. It
casts a value to an rvalue. This allows an overload taking an rvalue to
be called, referred to as *perfect forwarding*.



perfect forwarding

jølkjaøsd
