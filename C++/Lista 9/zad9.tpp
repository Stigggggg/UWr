#include<iostream>
#include<initializer_list>
using namespace std;

template<typename T>
calc::list<T>::list(): head(nullptr), size(0) {}

template<typename T>
calc::list<T>::list(const initializer_list<T> ilist)
{
    for(const T &value: ilist)
    {
        insert_back(value);
    }
}

template<typename T>
calc::list<T>::list(const list<T> &other)
{
    node *curr=other.head;
    while(curr!=nullptr)
    {
        insert_back(curr->data);
        curr=curr->next;
    }
}

template<typename T>
calc::list<T>::list(list<T> &&other): head(other.head), size(other.size)
{
    other.head=nullptr;
    other.size=0;
}

template<typename T>
calc::list<T>& calc::list<T>::operator=(const list<T> &other)
{
    if(this==&other)
    {
        return *this;
    }
    clear();
    node *curr=other.head;
    while(curr!=nullptr)
    {
        insert_back(curr->data);
        curr=curr->next;
    }
    return *this;
}

template<typename T>
calc::list<T>& calc::list<T>::operator=(list<T>&& other)
{
    if(this==&other)
    {
        return *this;
    }
    clear();
    head=other.head;
    size=other.size;
    other.head=nullptr;
    other.size=0;
    return *this;
}

template<typename T>
void calc::list<T>::clear()
{
    while(head!=nullptr)
    {
        node *temp=head;
        head=head->next;
        delete temp;
    }
    size=0;
}

template<typename T>
calc::list<T>::~list()
{
    clear();
}

template<typename T>
void calc::list<T>::insert(const T& value, size_t pos)
{
    if(pos>size)
    {
        throw out_of_range("Przekroczono zakres");
    }
    if(pos==0)
    {
        insert_front(value);
        return;
    }
    node *curr=head;
    for(size_t i=0; i<pos-1; i++)
    {
        curr=curr->next;
    }
    curr->next=new node(value,curr->next);
    size++;
}

template<typename T>
void calc::list<T>::insert_front(const T& value)
{
    head=new node(value,head);
    size++;
}

template<typename T>
void calc::list<T>::insert_back(const T& value)
{
    if(head==nullptr)
    {
        head=new node(value,nullptr);
    }
    else
    {
        node *curr=head;
        while(curr->next!=nullptr)
        {
            curr=curr->next;
        }
        curr->next=new node(value,nullptr);
    }
    size++;
}

template<typename T>
void calc::list<T>::remove(size_t pos)
{
    if(pos>=size)
    {
        throw out_of_range("Przekroczono zakres");
    }
    if(pos==0)
    {
        remove_front();
        return;
    }
    node *curr=head;
    for(size_t i=0; i<pos-1; i++)
    {
        curr=curr->next;
    }
    node *to_delete=curr->next;
    curr->next=to_delete->next;
    delete to_delete;
    size--;
}

template<typename T>
void calc::list<T>::remove_front()
{
    if(head==nullptr)
    {
        throw out_of_range("Pusta lista");
    }
    node *to_delete=head;
    head=head->next;
    delete to_delete;
    size--;
}

template<typename T>
void calc::list<T>::remove_back()
{
    if(head==nullptr)
    {
        throw out_of_range("Pusta lista");
    }
    if(head->next==nullptr)
    {
        delete head;
        head=nullptr;
        size--;
        return;
    }
    node *curr=head;
    while(curr->next->next!=nullptr)
    {
        curr=curr->next;
    }
    delete curr->next;
    curr->next=nullptr;
    size--;
}

template<typename T>
void calc::list<T>::remove_value(const T& value)
{
    if(head==nullptr)
    {
        return;
    }
    if(head->data==value)
    {
        remove_front();
        return;
    }
    node *curr=head;
    while(curr->next!=nullptr && curr->next->data!=value)
    {
        curr=curr->next;
    }
    if(curr->next!=nullptr)
    {
        node *to_delete=curr->next;
        curr->next=to_delete->next;
        delete to_delete;
        size--;
    }
}

template<typename T>
void calc::list<T>::remove_all_values(const T& value)
{
    if(head==nullptr)
    {
        return;
    }
    if(head->data==value)
    {
        remove_front();
        if(head==nullptr)
        {
            return;
        }
    }
    node *curr=head;
    while(curr->next!=nullptr && curr->next->data!=value)
    {
        if(curr->next->data==value)
        {
            node *to_delete=curr->next;
            curr->next=to_delete->next;
            delete to_delete;
            size--;
        }
        else
        {
            curr=curr->next;
        }
    }
}

template<typename T>
size_t calc::list<T>::find(const T& value) const
{
    node *curr=head;
    size_t pos=0;
    while(curr!=nullptr)
    {
        if(curr->data==value)
        {
            return pos;
        }
        curr=curr->next;
        pos++;
    }
    return size;
}

template<typename T>
size_t calc::list<T>::count(const T& value) const
{
    size_t count=0;
    node *curr=head;
    while(curr!=nullptr)
    {
        if(curr->data==value)
        {
            count++;
        }
        curr=curr->next;
    }
    return count;
}

template<typename T>
size_t calc::list<T>::length() const
{
    return size;
}

template<typename T>
bool calc::list<T>::empty() const
{
    return head==nullptr;
}

template<typename T>
const T& calc::list<T>::front() const
{
    if(empty())
    {
        throw std::out_of_range("Pusta lista");
    }
    return head->data;
}

template<typename T>
ostream& calc::list<T>::operator<<(ostream &wyj, const list<T> &l)
{
    wyj<<'[';
    if(!l.empty())
    {
        node *curr=l.head;
        wyj<<curr->data;
        curr=curr->next;
        while(curr!=nullptr)
        {
            wyj<<", "<<curr->data;
            curr=curr->next;
        }
    }
    wyj<<']';
    return wyj;
}

template<typename T>
void calc::queue<T>::enqueue(const T& element)
{
    this->insert_back(element);
}

template<typename T>
T calc::queue<T>::dequeue()
{
    if(this->empty())
    {
        throw out_of_range("Pusta kolejka");
    }
    T element=this.front();
    this->remove_front();
    return element;
}

template<typename T>
T calc::queue<T>::front() const
{
    if(this->empty())
    {
        throw out_of_range("Pusta kolejka");
    }
    return this->list<T>::front();
}

template<typename T>
bool calc::queue<T>::empty() const
{
    return list<T>::empty();
}

template<typename T>
size_t calc::queue<T>::size() const
{
    return list<T>::size();
}

template<typename T>
void calc::stack<T>::push(const T& element)
{
    this->insert_front(element);
}

template<typename T>
T calc::stack<T>::pop()
{
    if(this->empty())
    {
        throw out_of_range("Stos jest pusty");
    }
    T element=this->front();
    this->remove_front();
    return element;
}

template<typename T>
T calc::stack<T>::top() const
{
    if(this->empty())
    {
        throw out_of_range("Stos jest pusty");
    }
    return this->list<T>::front();
}

template<typename T>
bool calc::stack<T>::empty() const
{
    return list<T>::empty();
}

template<typename T>
size_t calc::stack<T>::size() const
{
    return list<T>::length();
}
