#include<iostream>
#include "zad9.hpp"

int main()
{
    //TESTY DLA LIST
    calc::list<int> l1;
    // cout<<l1.size<<endl;
    l1.insert_front(5);
    cout<<l1.front()<<endl;
    calc::list<int> l2=l1;
    cout<<l2.front()<<endl;
    l2.insert_front(10);
    cout<<l2.front()<<endl;
    cout<<l2.length()<<endl;
    l2.remove_value(10);
    cout<<l2.front()<<endl;
    cout<<l2.length()<<endl;
    l2.insert_front(5);
    cout<<l2.length()<<endl;
    // calc::list<int> l4={1,1,1,1};
    // cout<<l4.front()<<endl;
    // l4.remove_all_values(1);
    // cout<<l4.front();
    //TESTY DLA STOSOW
    // calc::stack<char> s;
    // s.push('a');
    // cout<<s.top()<<endl;
    // s.push('b');
    // cout<<s.pop()<<endl;
    return 0;
}
