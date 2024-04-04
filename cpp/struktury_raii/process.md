# UTF8String Class Implementation

## Problem 1: Design the Class

### Class Definition

Define a class named UTF8String.

### Member Variables

Determine the necessary member variables for the class. (e.g., pointer to byte data, size of data, capacity, etc.)

### Constructor

Implement constructors to create UTF8String objects from C/C++ strings or vectors of code points.

### Destructor

Implement a destructor to properly deallocate memory.

### Copy Constructor

Implement a copy constructor to perform deep copying of data.

### Copy Assignment Operator

Implement the copy assignment operator to handle assignment between objects.

### RAII

Ensure that the class follows the RAII (Resource Acquisition Is Initialization) principle.

## Problem 2: String Length and Capacity

### Method: get_byte_count()

Implement a method to return the number of currently stored bytes.

### Method: get_point_count()

Implement a method to return the number of currently stored code points.

## Problem 3: Indexing

### Operator Overloading: []

Implement the [] operator to allow indexing by bytes.

### Method: nth_code_point()

Implement a method to allow indexing by code points.

## Problem 4: Append Operations

### Method: append() (ASCII)

Implement a method to add new ASCII characters to the string.

### Method: append() (Code Point)

Implement a method to add new code points to the string.

## Problem 5: Concatenation and Comparison

### Operator Overloading: +

Implement the + operator to concatenate two strings.

### Operator Overloading: +=

Implement the += operator to append a string to an existing string.

### Operator Overloading: ==

Implement the == operator to compare two strings for equality.

## Problem 6: Conversion

### Explicit Cast to std::string

Implement a cast operator to convert UTF8String to std::string.
