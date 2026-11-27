#pragma once

#include <vector>
#include <cassert>

#include "graphics.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type) {
        switch (type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;

public:
    VertexBufferLayout()
        : m_stride(0) {}
    
    template<typename T>
    void push(unsigned int count) {
        static_assert(false);
    }

    inline const std::vector<VertexBufferElement>& get_elements() const {return m_elements;}
    inline unsigned int get_stride() const {return m_stride;}
};

template<>
inline void VertexBufferLayout::push<float>(unsigned int count) {
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count) {
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count) {
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
}