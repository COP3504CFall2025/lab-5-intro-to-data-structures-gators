#ifdef MAIN

#include "ABDQ.hpp"
// #include "ABQ.hpp"
// #include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
// #include "LLDQ.hpp"
// #include "LLQ.hpp"
// #include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

template <typename T>
void section(const T& title) {
    std::cout << "\n==== " << title << " ====\n";
}

int main() {
    section("Create empty int list");
    LinkedList<int> a;
    std::cout << "Count: " << a.getCount() << std::endl;
    a.printForward();
    a.printReverse();

    section("addHead / addTail");
    a.addHead(2);
    a.addHead(1);
    a.addTail(3);
    a.addTail(4);
    std::cout << "Count: " << a.getCount() << std::endl;
    std::cout << "Forward:\n"; a.printForward();
    std::cout << "Reverse:\n"; a.printReverse();

    section("Accessors");
    if (a.getHead()) std::cout << "Head->data: " << a.getHead()->data << std::endl;
    if (a.getTail()) std::cout << "Tail->data: " << a.getTail()->data << std::endl;

    section("removeHead / removeTail");
    (void)a.removeHead();
    (void)a.removeTail();
    std::cout << "Count: " << a.getCount() << std::endl;
    std::cout << "Forward:\n"; a.printForward();
    std::cout << "Reverse:\n"; a.printReverse();

    section("Copy constructor");
    LinkedList<int> b(a);
    std::cout << "b (copy of a), Count: " << b.getCount() << std::endl;
    std::cout << "b Forward:\n"; b.printForward();

    section("Copy assignment");
    LinkedList<int> c;
    c = b;
    std::cout << "c (copy-assigned from b), Count: " << c.getCount() << std::endl;
    std::cout << "c Forward:\n"; c.printForward();

    section("Move constructor");
    LinkedList<int> d(std::move(c));
    std::cout << "d (moved-from c), Count: " << d.getCount() << std::endl;
    std::cout << "d Forward:\n"; d.printForward();
    std::cout << "c (after move), Count: " << c.getCount() << std::endl;

    section("Move assignment");
    LinkedList<int> e;
    e.addHead(42);
    e = std::move(d);
    std::cout << "e (move-assigned from d), Count: " << e.getCount() << std::endl;
    std::cout << "e Forward:\n"; e.printForward();
    std::cout << "d (after move), Count: " << d.getCount() << std::endl;

    section("Clear");
    e.Clear();
    std::cout << "e after Clear, Count: " << e.getCount() << std::endl;
    std::cout << "e Forward:\n"; e.printForward();

    section("String list test");
    LinkedList<std::string> s;
    s.addHead("beta");
    s.addHead("alpha");
    s.addTail("gamma");
    std::cout << "String list, Count: " << s.getCount() << std::endl;
    std::cout << "Forward:\n"; s.printForward();
    std::cout << "Reverse:\n"; s.printReverse();
    (void)s.removeHead();
    (void)s.removeTail();
    std::cout << "After removals, Count: " << s.getCount() << std::endl;
    std::cout << "Forward:\n"; s.printForward();

    section("End of tests");
    return 0;
}


#endif