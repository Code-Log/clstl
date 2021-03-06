#ifndef HASH_MAP_H
#define HASH_MAP_H

#pragma once

#include <clstl/dual.h>
#include <clstl/vector.h>

namespace clstl {

    template<typename K, typename V>
    struct hash_map {

    private:
        clstl::vector<clstl::dual<K, V>> m_Data;

    public:
        hash_map() = default;
        hash_map(unsigned int size) : m_Data(size) {}

        void add(K key, V value) {
            m_Data.emplace_back(key, value);
        }

        void remove(const K& key) {

            for (unsigned int i = m_Data.size() - 1; i >= 0; i--) {

                if (m_Data[i].head() == key) {
                    m_Data.erase(i, 1);
                    return;
                }

            }

        }

        V get(const K& key) {

            V val;
            for (unsigned int i = 0; i < m_Data.size(); i++) {

                if (m_Data[i].head() == key) {
                    return m_Data[i].tail();
                }

            }

            return val;

        }

    };

}

#endif
