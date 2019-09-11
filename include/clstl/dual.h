namespace clstl {

    template<typename T1, typename T2>
    struct dual {

    private:
        T1 m_Head;
        T2 m_Tail;

    public:

        dual() = default;
        dual(const T1& head, const T2& tail) : m_Head(head), m_Tail(tail) {}

        T1& head() { return m_Head; }
        T2& tail() { return m_Tail; }

    };

}