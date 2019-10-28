#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"

//using namespace cs221util;
using namespace std;

TEST_CASE("deque::basic functions","[weight=1][part=deque]"){
    //cout << "Testing Stack..." << endl;
    Deque<int> deq;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <=10; i++) {
        deq.pushR(i);
        expected.push_back(i);
    }
    while(!deq.isEmpty()) {
        result.push_back(deq.popL());
    }
    REQUIRE( result == expected);
}

TEST_CASE("deque::resize wraparaound","[weight=1][part=deque]"){
    //cout << "Testing Stack..." << endl;
    Deque<int> deq;
    vector<int> result;
    vector<int> expected;
    for (int i = 0; i < 8; i++) {
        deq.pushR(i);
    }
    for (int i = 0; i < 3; i++)
        deq.popL();
    deq.pushR(8);
    for (int i = 0; i < 4; i++)
        deq.popL();

    while (!deq.isEmpty())
        result.push_back(deq.popR());

    expected.push_back(8);
    expected.push_back(7);
    REQUIRE( result == expected);

}

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}

TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    int i = 0;
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
        if (i++ > 20)
            break;
    }
    REQUIRE( result == expected);
}

