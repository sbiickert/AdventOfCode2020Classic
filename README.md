# AdventOfCode2020Classic
 Learning C++98 on a 20-year-old PowerBook

## Background

I recently upgraded my old PowerBook G4 with an SSD. I blame [this video](https://youtu.be/_2jvRgRQXIE) and the fact that the SSD and the mSATA to IDE enclosure only cost me $50. It’s an old computer and slow, but by the standards 20 years ago it’s a rocket ship, especially now that it’s got a super fast and huge drive. I turned the screws and installed the SSD.

So, what do you do with an old laptop? Code, of course. I started with learning the PowerPlant framework by Metrowerks, and it became clear that my C++ knowledge was a real shortcoming. I started digging into the STL and figured that the Advent of Code was a good match for learning the basics. Especially since I have already solved it in a language (see my Swift repo) that I know.

## How's It Going?

Pretty well. I have finished three days so far. Each day I've been adding another C++ technique. Day 01 was using vectors and iterators. Day 02 introduced using structs and parsing strings. Day 03 saw my first class and using std::auto_ptr, as well as working with integer numbers larger than 4 bytes.

The challenge is that using late-1990’s coding tools means that even a language as venerable as C++ has changed a lot since then. I have learned that the Metrowerks Standard Library that comes with CodeWarrior is a C++98 compliant version of the STL. That means I can do some Google searching for pre-C++11 examples on how to do things. There still are some gotchas, but it’s better than nothing.

## Updated: Day 7 Complete

I will say that today's surprise was that I managed to parse the "bags containing bags" rules *without* regular expressions. C++98 STL does not have regex. I took a couple of days to investigate Boost and tried to figure out how to get it to build in Codewarrior, but gave up. I thought I would not be able to work this challenge without regex. But it turns out I could do it with the std::string.find* functions. I guess when your first programming language was Perl, not having regex seems wrong. The actual recursion code was more concise than it was in Swift. In fact, I'm finding that my code solutions are generally the same length or shorter in C++. I think part of that is I'm not putting the error-handling in that you would need to for production code, though. You can't avoid the Optional-checking in Swift.
