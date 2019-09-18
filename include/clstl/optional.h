namespace clstl {

    template<typename T>
    struct optional {

    private:
        T m_Data;
        bool m_HasData;

    public:

        optional() : m_HasData(false) {}
        optional(T data) : m_Data(data), m_HasData(true) {}

        bool has_data() const { return m_HasData; }
        
        T data() { return m_Data; }
        T data_or(T def_data) { return (m_HasData) ? m_Data : def_data; }      

        void operator=(T data) {
            this->m_Data = data;
            this->m_HasData = true;
        }
        operator bool() const { return this->has_data(); }

    };

}