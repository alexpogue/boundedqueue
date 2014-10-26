#include <iostream>
#include <stdexcept>
#include "QUnit.hpp"
#include "BoundedQueue.h"

void testSimpleEnqueueDequeue();
void testEnqueueDequeueAll();
void testEnqueueDequeueRepeated();
void testEnqueueAllButOne_ThenDequeue_ThenEnqueueAllButOne();
void testEnqueueWithReinit();
void testTooManyElementsException();
void testTooFewElementsException();

int main(int argc, char** argv) {
	testSimpleEnqueueDequeue();
	testEnqueueDequeueAll();
	testEnqueueDequeueRepeated();
	testEnqueueAllButOne_ThenDequeue_ThenEnqueueAllButOne();

	testEnqueueWithReinit();

	testTooManyElementsException();
	testTooFewElementsException();
	return 0;
}

void testSimpleEnqueueDequeue() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	BoundedQueue q(1);
	q.enqueue(0);
	QUNIT_IS_EQUAL(0, q.dequeue());
}

void testEnqueueDequeueAll() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	int size = 5;
	BoundedQueue q(size);

	for(int i = 0; i < size; i++) {
		q.enqueue(i);
	}

	for(int i = 0; i < size; i++) {
		QUNIT_IS_EQUAL(i, q.dequeue());
	}
}

void testEnqueueDequeueRepeated() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	int numRepetitions = 5;
	BoundedQueue q(2);

	for(int i = 0; i < numRepetitions; i++) {
		q.enqueue(i);
		int result = q.dequeue();
		QUNIT_IS_EQUAL(i, result);
	}
}

void testEnqueueAllButOne_ThenDequeue_ThenEnqueueAllButOne() {
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
}

void testEnqueueWithReinit() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);

	BoundedQueue q(5);

	q.enqueue(0);
	q.reinit();
	q.enqueue(1);
	QUNIT_IS_EQUAL(1, q.dequeue());
}

void testTooManyElementsException() {
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
}

void testTooFewElementsException() {
	QUnit::UnitTest qunit(std::cerr, QUnit::normal);
	BoundedQueue q(1);

	try {
		q.dequeue();
		QUNIT_IS_TRUE(false);
	}
	catch(const std::runtime_error& ex) {
		QUNIT_IS_TRUE(true);
	}
}
