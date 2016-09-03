#include <iostream>
#include <stdexcept>
#include "QUnit.hpp"
#include "BoundedQueue.h"

int testSimpleEnqueueDequeue();
int testEnqueueDequeueAll();
int testEnqueueDequeueRepeated();
int testEnqueueAllButOne_ThenDequeue_ThenEnqueueAllButOne();
int testEnqueueWithReinit();
int testTooManyElementsException();
int testTooFewElementsException();

int main(int argc, char** argv) {
    int errors = 0;
	errors += testSimpleEnqueueDequeue();
	errors += testEnqueueDequeueAll();
	errors += testEnqueueDequeueRepeated();
	errors += testEnqueueAllButOne_ThenDequeue_ThenEnqueueAllButOne();

	errors += testEnqueueWithReinit();

	errors += testTooManyElementsException();
	errors += testTooFewElementsException();
	return errors;
}

int testSimpleEnqueueDequeue() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	BoundedQueue q(1);
	q.enqueue(0);
	QUNIT_IS_EQUAL(0, q.dequeue());
    return qunit.errors();
}

int testEnqueueDequeueAll() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	int size = 5;
	BoundedQueue q(size);

	for(int i = 0; i < size; i++) {
		q.enqueue(i);
	}

	for(int i = 0; i < size; i++) {
		QUNIT_IS_EQUAL(i, q.dequeue());
	}
    return qunit.errors();
}

int testEnqueueDequeueRepeated() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	int numRepetitions = 5;
	BoundedQueue q(2);

	for(int i = 0; i < numRepetitions; i++) {
		q.enqueue(i);
		int result = q.dequeue();
		QUNIT_IS_EQUAL(i, result);
	}
    return qunit.errors();
}

int testEnqueueAllButOne_ThenDequeue_ThenEnqueueAllButOne() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	int size = 5;
	BoundedQueue q(size);

	for(int i = 0; i < size - 1; i++) {
		q.enqueue(i);
	}
	for(int i = 0; i < size - 1; i++) {
		q.dequeue();
	}
	for(int i = 0; i < size - 1; i++) {
		q.enqueue(i);
	}
	for(int i = 0; i < size - 1; i++ ) {
		QUNIT_IS_EQUAL(i, q.dequeue());
	}
    return qunit.errors();
}

int testEnqueueWithReinit() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	BoundedQueue q(5);

	q.enqueue(0);
	q.reinit();
	q.enqueue(1);
	QUNIT_IS_EQUAL(1, q.dequeue());
    return qunit.errors();
}

int testTooManyElementsException() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);
	BoundedQueue q(1);
	try {
		q.enqueue(0);
		q.enqueue(0);
		QUNIT_IS_TRUE(false);
	}
	catch(const std::runtime_error& ex) {
		QUNIT_IS_TRUE(true);
	}
    return qunit.errors();
}

int testTooFewElementsException() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);
	BoundedQueue q(1);

	try {
		q.dequeue();
		QUNIT_IS_TRUE(false);
	}
	catch(const std::runtime_error& ex) {
		QUNIT_IS_TRUE(true);
	}
    return qunit.errors();
}
