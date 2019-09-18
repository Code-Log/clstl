#ifndef HASH_MAP_H
#define HASH_MAP_H

#pragma once

#include <clstl/array_list.h>
#include <clstl/types.h>

namespace clstl {

    template<typename K, typename V>
    struct hash_map {

    private:
        array_list<K> m_Keys;
        array_list<V> m_Values;

    public:

        hash_map() = default;
        hash_map(size_t size) : m_Keys(array_list<K>(size)), m_Values(array_list<V>(size)) {}

        void add(K key, V value) {

            m_Keys.push(key);
            m_Values.push(value);

        }

        void remove(const K& key) {

            bool found = false;
            size_t i = 0;
            while (!found && i < m_Keys.size()) {

                if (m_Keys[i] == key)
                    found = true;

            }

            m_Keys.splice(i, 1);
            m_Values.splice(i, 1);

        }

        V& get(const K& key) {

            bool found = false;
            size_t i = 0;
            while (!found && i < m_Keys.size()) {

                if (m_Keys[i] == key)
                    found = true;

            }

            return m_Values[i];

        }

        V& operator[](const K& key) { return get(key); }

    };

}

#endif