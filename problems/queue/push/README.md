// Why we can't just print 'q':
// 1. Encapsulation: The underlying data container is private.
// 2. Underlying Architecture: It uses a std::deque under the hood.
// 3. Memory Structure: The deque holds data in small chunks (fixed-size arrays) 
//    managed by a central map of pointers.
// 4. Growth Efficiency: When it runs out of space, it simply allocates a new 
//    chunk and adds a pointer to the map. This is much more efficient than 
//    std::vector, which must copy the entire dataset to a new location when resizing.


also known as enqueue