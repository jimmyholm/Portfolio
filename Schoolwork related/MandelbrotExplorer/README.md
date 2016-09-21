Mandelbrot Explorer
Written in 2013, in Java, as part of a course in Imperative and Object Oriented programming methodologies.
Makes use of Java threads in a naïve attempt at concurrency and showcases an MVC implementation.

Today, I would write the concurrency differently - using a threadpool to work with
much smaller clusters of pixels as individual tasks as opposed to, like in this implementation, divide
the screen into subsections to be calculated.