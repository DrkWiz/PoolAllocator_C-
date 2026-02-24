#ifndef poolAllocator_h
#define poolAllocator_h

#include <cstddef> /* used for size_t */
#include <stdexcept> /* used for std::runtime_error */
#include <vector> /* used for std::vector */

class PoolAllocator {

    
    public: 

        struct nodo{ 
            nodo* siguiente;
        };

        PoolAllocator(std::size_t tamanioBloque, std::size_t numBloques); 
        ~PoolAllocator(); 

        void* allocate();
        bool deallocate(void* ptr); 
        std::pair<std::size_t, std::size_t> getStats() const; // statistics about the pool
        
    private:
    
        void* m_ptroInicial = nullptr;    
        nodo* m_ListaLibre = nullptr;   
        std::size_t m_tamanioBloque;       
        std::size_t m_tamanioPool;        

};

#endif /* poolAllocator_h */