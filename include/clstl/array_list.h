namespace clstl {

    template<typename T>
    struct array_list {

    private:
        T* m_Data;
        unsigned int m_Count;

    public:
        array_list<T>(T* data, unsigned int count);
        array_list<T>();

        void push(T item);

        T& operator[](unsigned int index);

    };

}