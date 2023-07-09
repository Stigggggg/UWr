namespace calc
{
    template<typename T>
    class list
    {
        private:
            class node
            {
                public:
                    T data;
                    node *next;
                    node(const T& d, node *n): data(d), next(n) {}
            };
            node *head;
            size_t size;
        public:
            list();
            list(const std::initializer_list<T> ilist);
            list(const list<T> &other);
            list(list<T> &&other);
            list<T> &operator=(const list<T> &other);
            list<T> &operator=(list<T> &&other);
            ~list();
            void insert(const T& value, size_t pos);
            void insert_front(const T &value);
            void insert_back(const T &value);
            void remove(size_t pos);
            void remove_front();
            void remove_back();
            void remove_value(const T &value);
            void remove_all_values(const T &value);
            void clear();
            size_t find(const T &value) const;
            size_t count(const T &value) const;
            size_t length() const;
            bool empty() const;
            const T& front() const;
            friend std::ostream &operator<<(std::ostream &wyj, const list<T> &l);
    };
    template<typename T>
    class queue: private list<T>
    {
        public:
            void enqueue(const T& element);
            T dequeue();
            T front() const;
            bool empty() const;
            size_t size() const;
    };
    template<typename T>
    class stack: private list<T>
    {
        public:
            void push(const T& element);
            T pop();
            T top() const;
            bool empty() const;
            size_t size() const;
    };
}

#include "zad9.tpp"

