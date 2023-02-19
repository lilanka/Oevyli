# The Adventure to Oevyli
We start our journey with a reason. Getting to know our tools. As Hoare once said
"In all spheres of human intellectual and practical activity, from carpentry to golf,
from sculpture to space travel, the true craftsman is the one who thoroughly understands
his tools" [1].

The projects aim is to compile AI program into efficient CPU/GPU code. It contains a
frontend which can generate both `OIL - Oevyli Intermediate Language` and `LLVM-IR`.
The backend generate machine code and optimize for fast operations. When implementing the
compiler, I put lot of effort to make a very fast compiler.

# Implementation of the Frontend
## Scanner
Scanner converts the input, a stream of characters to stream of workds, in the form of
`(p, s)`. String with actual spelling of the word stored in a hash table. We uses a hand
coded scanner for our compiler. Why? because it's fun to write.

# References
1. http://web.eecs.umich.edu/~bchandra/courses/papers/Hoare_Hints.pdf
2. https://triton-lang.org/master/index.html