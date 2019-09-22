namespace clstl {

    template<typename T>
    struct slist {

    private:
        T m_Data;
        slist<T>* m_Next;
    
    public:
        slist() : m_Next(nullptr) {}

        slist(const T& data) : m_Data(data) {}

        template<typename... args_t>
        void emplace_back(args_t&&... args) {

            slist<T>& last_item = this->last();
            last_item.m_Next = new slist<T>(T(args...));

        }

        void push_back(const T& item) {

            slist<T>& last_item = this->last();
            last_item.m_Next = new slist<T>(item);

        }

        slist<T>& next() { return *m_Next; }

        slist<T>& last() {

            slist<T>* current = this;
            while (current->m_Next != nullptr)
                current = current->m_Next;

            return *current;

        }

        uint size() {

            uint ret = 0;
            slist<T>* current = this;
            while (current->m_Next != nullptr) {
                current = current->m_Next;
                ret++;
            }

            return ret;

        }

        void for_each(void(*func)(T& item)) {

            for (uint i = 0; i < this->size(); i++) {
                func(this->get(i));
            }

        }

        T& get(uint index) { return (*this)[index]; }

        T& operator[](uint index) {

            slist<T>* current = this->m_Next;
            for (int i = 0; i < index; i++) {
                current = current->m_Next;
            }

            return current->m_Data;

        }

    };

}