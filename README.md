A June 2014 review & critique of
# <span>Frances Buontempo &ndash; “Learn C++ by Example” (2024)</span>

<img src="images/cover.png" width="50%" align="right">

When someone attempted to post a pirate copy of this book to a Facebook group that I moderate, I notified Francis and apologized for viewing (actually downloading!) the PDF, and starting to read it. She suggested that I publish a review of the book. So, hereby.

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [My perspective.](#my-perspective)
- [The book’s goal.](#the-books-goal)
- [Snurrepip?](#snurrepip)
- [Bjeff!](#bjeff)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## My perspective.

Francis writes in “Who should read this book” that

> ❞ If you have used C++ before but have failed to keep up with recent
changes, this book is for you.

That’s me. I jumped off the train between C++17 and C++20. Considering that Apple clang++ doesn’t even implement all of C++17 &mdash; as of this writing, June 2024, there’s still no support for floating point [`std::from_chars`](https://en.cppreference.com/w/cpp/utility/from_chars) &mdash; I thought it was reasonable to stick with C++17 for a while.

Another reason was that I was really disappointed with C++20, e.g.:

* *Modules*, of very limited utility because   
  they’re still only reasonably supported by one compiler.
* The C++20 *sabotage of `std::filesystem`*  
  with the changed `fs::path::u8string` adding needless string copying overhead in Windows, and `fs::u8path` deprecated to add needless warnings, and the incorrectness that`fs::path` constructors etc. were still formally required to garble path specifications in a Windows UTF-8 based program (because the Windows changes of June 2019, with support for UTF-8 as a process’ internal ANSI codepage, made the C++17 wording a defect, which was [not fixed in C++20](https://github.com/alf-p-steinbach/C---how-to---make-non-English-text-work-in-Windows/blob/main/how-to-use-utf8-in-windows.md#5-how-to-make-stdfilesystempath-do-the-work)).
* *Coroutines* that were half finished, too limited & too inefficient,  
  half finished because one needed a DIY or 3<sup>rd</sup> party framework in addition to the core language support; limited because  C++ for efficiency supports only stackless coroutines; and, ironically, inefficient because every coroutine instantiation by default involves a dynamic allocation, because by default these beasts support recursive instantiation.
* The *Ranges* sub-library, a good way to write concise but brittle code,  
  and to some degree write-only code, with dysmal performance. The ranges sub-library adds some scripting language feeling that some people find very desirable, and (so) it has some enthusiastic supporters. But it could and IMHO should have continued to be a 3<sup>rd</sup> party special interest library: not adding all that to compilations and to user programs and to the standard’s text. 
* Minor point but still *no qualified function name macro* like [`__func__`](https://en.cppreference.com/w/c/language/function_definition#func);  
  instead C++20 added `std::source_location`, which does not help when one still has to use macros with compiler specific implementations to get qualified function names for source locations, and which additionally does not have no-throwing copying so that it’s grossly imperfectly suited for being carried by an exception.

So, I am reader primarily interested in the new C++20 and C++23 core language stuff. As the bullet points show I have some strong and well founded opinions. As they also show I’m not shy of pointing out problems.

I’m well versed in C++98, C++03, C++11, C++14 and C++17, and so able to evaluate how well and how widely the book covers the new features in C++11 and later standards.

I have worked as a vocational school teacher and as a college lecturer, and over the years I’ve used much of my time on discussing C++ and helping students, but I would not claim to be able to evaluate teaching, the pedagogical aspect. As I see it what suits one person may not necessarily suit another. What I find clear may be ungrokable to some student and vice versa; all I can say is that this book is *not unclear*.

## The book’s goal.

In “Why read this book?” Francis writes

> ❞ The [[ISOCpp](https://isocpp.org)] site even has a section for people
with a background in other languages who want to learn C++. It
doesn’t have a section for “Learning C++ if you already knew C++ a
while ago.” This book plugs that gap. You don’t need a long list of
every feature that’s been introduced over the years. You need just
enough to get your confidence back.

It seems the aim is to provide a clear solid learning path through the main features of C++11 through C++23, enabling the reader to explore further.

The aim is clearly *not* to cover or even mention all of the myriad new features. Rather, the path will visit some main features that were needed or convenient in some concrete examples, which is an approach to relevance that I agree with. And in “Who this book is for” Francis writes:

> ❞ If you used to know all the gnarly edge cases
and quote chapter and verse of a previous standard, this book will
help you focus on a handful of new features to get you back in the
driving seat.

## Snurrepip?

asdasdasdasd

## Bjeff!

asdasd