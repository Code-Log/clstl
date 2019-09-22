namespace clstl {

    template<typename T>
    struct list {

    private:
        T m_Data;
        list<T>* m_Prev;
        list<T>* m_Next;
    
    public:
        list() : m_Next(nullptr), m_Prev(this) {}

        list(const T& data) : m_Data(data) {}

        template<typename... args_t>
        void emplace_back(args_t&&... args) {

            list<T>& last_item = this->last();
            last_item.m_Next = new list<T>(T(args...));
            last_item.m_Next->m_Prev = &last_item;

        }

        void push_back(const T& item) {

            list<T>& last_item = this->last();
            last_item.m_Next = new list<T>(item);
            last_item.m_Next->m_Prev = &last_item;

        }

        list<T>& next() { return *m_Next; }
        list<T>& previous() { return * m_Prev; }

        list<T>& first() {

            list<T>* current = this;
            while (current->m_Prev != current)
                current = current->m_Prev;

            return *current->m_Next;

        }

        list<T>& last() {

            list<T>* current = this;
            while (current->m_Next != nullptr)
                current = current->m_Next;

            return *current;

        }

        uint size() {

            uint ret = 1;
            list<T>* current = &this->first();
            while (current->m_Next != nullptr) {
                current = current->m_Next;
                ret++;
            }

            return ret;

        }

        T& get(uint index) { return (*this)[index]; }

        T& operator[](uint index) {

            list<T>* current = &this->first();
            for (int i = 0; i < index; i++) {
                current = current->m_Next;
            }

            return current->m_Data;

        }

    };

}