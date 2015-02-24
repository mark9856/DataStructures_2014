#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>


template <class T>
class priority_queue {
    private:
        std::vector<T> m_heap;

    public:
        priority_queue() {}

        priority_queue( std::vector<T> const& values )
        {
            std::vector<T> tmp = values;
            for(int i = 0; i < tmp.size(); ++ i){
                push(tmp[i]);
            }
        }

        const T& top() const 
        {
            assert( !m_heap.empty() );
            return m_heap[0]; 
        }

        void push( const T& entry )
        {
            m_heap.push_back(entry);
            int i = m_heap.size() - 1;
            while(i >= 1){
                T p = m_heap[int((i - 1)/2)];
                T c = m_heap[i];
                if(p > c){
                    std::swap(m_heap[int((i - 1)/2)], m_heap[i]);
                }
                i = int((i - 1)/ 2);
            }
        }

        void pop() 
        {
            assert( !m_heap.empty() );
            if(m_heap.size() > 1){
                std::swap(m_heap[0], m_heap[m_heap.size() - 1]);
            }
            m_heap.pop_back();
            int i = 0;
            while(2 * i + 2 < m_heap.size()){
                if(m_heap[2 * i + 1] >= m_heap[2 * i + 2]){
                    if(m_heap[i] >= m_heap[2 * i + 2]){
                        std::swap(m_heap[i], m_heap[2 * i + 2]);
                        i = 2 * i + 2;
                    }
                    else{
                        //std::cout << "wrong"<< std::endl;
                        break;
                    }
                }
                else{
                    if(m_heap[i] >= m_heap[2 * i + 1]){
                        std::swap(m_heap[i], m_heap[2 * i + 1]);
                        i = 2 * i + 1;
                    }
                    else{
                        //std::cout << "wrong"<< std::endl;
                        break;
                    }
                }
            }
            if(2 * i + 1 == m_heap.size() - 1){
                if(m_heap[i] >= m_heap[2 * i + 1]){
                    std::swap(m_heap[i], m_heap[2 * i + 1]);
                }
            }
        }

        int size() { return m_heap.size(); }
        bool empty() { return m_heap.empty(); }


        //  The following three functions are used for debugging.

        //  Check to see that internally the heap property is realized.
        bool check_heap( )
        {
            return this->check_heap( this->m_heap );
        }

        //  Check an external vector to see that the heap property is realized.
        bool check_heap( const std::vector<T>& heap )
        {
            for(int i = 0; i < heap.size(); ++ i){
                if(i > 0){
                    T p = heap[int((i - 1)/2)];
                    if(p > heap[i]) return false;
                }
            }
            return true;
        }

        //  A utility to print the contents of the heap.  Use it for debugging.
        void print_heap( std::ostream & ostr )
        {
            for ( unsigned int i=0; i<m_heap.size(); ++i )
                ostr << i << ": " << m_heap[i] << std::endl;
        }

};


    template <class T>
void heap_sort( std::vector<T> & v )
{
    /*
    for(int i = 0; i < v.size(); ++ i){
        if(2 * i + 2 < v.size()){
            if(v[2 * i + 1] < v[2 * i + 2]){
                if(v[i] > v[2 * i + 1]){
                    std::swap(v[i], v[2 * i + 1]);
                }
            }
            else{
                if(v[i] > v[2 * i + 2]){
                    std::swap(v[i], v[2 * i + 2]);
                }
            }
        }
        if(2 * i + 1 < v.size() && 2 * i + 2 == v.size()){
            if(v[i] > v[2 * i + 1]){
                std::swap(v[i], v[2 * i + 1]);
            }
        }
    }
    */
    //std::sort(v.begin(), v.end());

    
    priority_queue<T> tmp;
    for(int i = 0; i < v.size(); ++ i){
        tmp.push(v[i]);
    }
    v.clear();
    while(!tmp.empty()){
        v.push_back(tmp.top());
        tmp.pop();
    }
}

#endif
