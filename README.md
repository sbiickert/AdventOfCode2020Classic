# AdventOfCode2020Classic
 Learning C++98 on a 20-year-old PowerBook

## Background

I recently upgraded my old PowerBook G4 with an SSD. I blame [this video](https://youtu.be/_2jvRgRQXIE) and the fact that the SSD and the mSATA to IDE enclosure only cost me $50. It’s an old computer and slow, but by the standards 20 years ago it’s a rocket ship, especially now that it’s got a super fast and huge drive. I turned the screws and installed the SSD.

So, what do you do with an old laptop? Code, of course. I started with learning the PowerPlant framework by Metrowerks, and it became clear that my C++ knowledge was a real shortcoming. I started digging into the STL and figured that the Advent of Code was a good match for learning the basics. Especially since I have already solved it in a language (see my Swift repo) that I know.

## How's It Going?

Pretty well. I have finished three days so far. Each day I've been adding another C++ technique. Day 01 was using vectors and iterators. Day 02 introduced using structs and parsing strings. Day 03 saw my first class and using std::auto_ptr, as well as working with integer numbers larger than 4 bytes.

The challenge is that using late-1990’s coding tools means that even a language as venerable as C++ has changed a lot since then. I have learned that the Metrowerks Standard Library that comes with CodeWarrior is a C++98 compliant version of the STL. That means I can do some Google searching for pre-C++11 examples on how to do things. There still are some gotchas, but it’s better than nothing.

## Updated: Day 7 Complete

I will say that today's surprise was that I managed to parse the "bags containing bags" rules *without* regular expressions. C++98 STL does not have regex. I took a couple of days to investigate Boost and tried to figure out how to get it to build in CodeWarrior, but gave up. I thought I would not be able to work this challenge without regex. But it turns out I could do it with the std::string.find* functions. I guess when your first programming language was Perl, not having regex seems wrong. The actual recursion code was more concise than it was in Swift. In fact, I'm finding that my code solutions are generally the same length or shorter in C++. I think part of that is I'm not putting the error-handling in that you would need to for production code, though. You can't avoid the Optional-checking in Swift.

## Updated: Day 11 Complete

The learning continues. Today's solution started with a simple idea: passing a function as an argument. The logic for seat empty/occupied was the only thing that changed in parts 1 and 2. I typedef'd the function signature. 👍  But the resulting code ran... slow. I didn't know why, but even when the solution was complete it was bugging me. Yes, I'm running this on a 550 MHz PowerBook, but still... 

So I discovered the MW Profiler, part of the CodeWarrior suite. When I figured out how to add the right library, configure the target and add the code to start profiling and dump the results, I made another discovery: things are passed by value in C++. I was passing my main data structure (vector\<string\>) in and out of functions and inadvertently making a copy each time. Once I changed the function signatures to vector\<string\> **const &**, then the code ran super fast.

## Updated: Day 14 Complete

Note to self: Mac OS 9 has a different memory model than a modern OS. Each app (including the simple apps I'm writing for the AoC) has a memory allocation. If you run out of memory, bad things happen. And the ridiculous default memory allocation for an app from a CodeWarrior project is 512 kB. Yes, *kilobytes*. So when doing today's challenge when allocating a fair number of 64-bit numbers to a map, I ran out. But it took me a couple of hours to figure it out. I was obsessing over the particular inputs and wondering why *this one* was failing. Turns out the crash happened where the memory ran out, nothing more. So, I allocated a whopping 5 MB of memory and all was well.

## Updated: Day 17 Complete

This might be the end of this effort: not that it isn't fun, but I'm looking to switch it up and do something else. I think I've gotten a ton out of this, but the next challenge (Day 18) is so focused on regex that I can't imagine trying to solve without it.

Day 17 (Conway Pockets) was a challenge because for the first time I really tried moving beyond my Swift solution and tried something new. I wanted to (and eventually succeeded) make an N-dimensional solution. My Swift solution was originally hard coded for 3 dimensions, and then I hacked a fourth dimension on for part 2. I tried a couple different ways to approach this with N dimensions in C++, so it took many days to solve. I am quite happy with the result. The code is clean and actually runs well. It's slower than my Swift solution, but if you consider that my Powerbook is probably 20 times slower than my MacBook Pro, it's something to be proud of.
