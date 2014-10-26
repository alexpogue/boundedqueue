BoundedQueue:

To compile everything, just run:
make

This will create executables "bq" and "test".

Run ./test to run the test suite.
Run ./bq to run the command line application

The tests:

The tests are built from an extremely simple library called QUnit which is
contained entirely within QUnit.hpp. The tests basically test each operation
of the bounded queue.

The app:

The command line application first asks what size it should make the bounded
queue. Creating a bounded queue of at most 25 elements will cause it to be 
printed every time an operation is done. After creation, it asks which 
operation to invoke. The user can invoke (e)nqueue, (d)equeue, or (q)uit.

The bounded queue will throw exceptions if the user enqueues on a full bounded
queue or dequeue an empty bounded queue. 
