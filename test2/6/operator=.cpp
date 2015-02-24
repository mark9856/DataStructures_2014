template <class T> Vec<T> & Vec<T>::operator=(const Vec<T>& v){
    if(this != &v){
        if(this -> m_alloc != v.m_alloc){
            delete [] this -> m_data;
            this -> m_alloc = v.m_alloc;
            this -> m_data = new T[this -> m_alloc];
        }
        this -> m_size = v.m_size;
        for(unsigned int i = 0; i < this -> m_size; ++ i){
            this -> m_data[i] = v.m_data[i];
        }
    }
    return *this;
}

template <class T> T & Vec<T>::operator[] (unsigned int i){
    return m_data[m_first + i];
}

template <class T> void Vec<T>::push_front(const T& val){
    if(m_alloc == 0){
        push_back(val); return;
    }
    if(m_first == 0){
        m_alloc *= 2;
        T* newData = new T[m_alloc];
        m_first = m_alloc/2;
        for(unsigned int i = 0; i < m_size; ++ i){
            newData[m_first + i] = m_data[i];
        }
        delete [] m_data;
        m_data = newData;
    }
    m_first --;
    m_data[m_first] = val;
    ++ m_size;
}
