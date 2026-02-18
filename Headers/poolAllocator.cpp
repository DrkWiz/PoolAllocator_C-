#include "poolAllocator.h"
#include <algorithm> // for std::max
 
//constructor
PoolAllocator::PoolAllocator(std::size_t tamanioBloque, std::size_t numBloques) {
    // validate input parameters
    m_tamanioBloque = std::max(tamanioBloque, sizeof(nodo));
    m_tamanioPool = m_tamanioBloque * numBloques;

    // reserve memory for the pool
    m_ptroInicial = std::malloc(m_tamanioPool);

    if (!m_ptroInicial) {
        throw std::bad_alloc();
    }

    // Initialize the free list: the first block is the start of the pool
    m_ListaLibre = static_cast<nodo*>(m_ptroInicial);
    
    // Link all blocks together
    nodo* actual = m_ListaLibre;
    for (std::size_t i = 0; i < numBloques - 1; ++i) {
        
        // Calculate the address of the next block and link it
        char* DireccionSiguienteBLoque = reinterpret_cast<char*>(actual) + m_tamanioBloque;
        actual->siguiente = reinterpret_cast<nodo*>(DireccionSiguienteBLoque);
        actual = actual->siguiente;

    }

    // The last block's next pointer should be null
    actual->siguiente = nullptr;
};

//destructor
PoolAllocator::~PoolAllocator() {
    std::free(m_ptroInicial);
};

// Allocate a block of memory from the pool
void* PoolAllocator::allocate() {
  
    if (!m_ListaLibre) {
        throw std::runtime_error("PoolAllocator: No more blocks available");
    }

    // Take the first block from the free list
    nodo* bloqueAsignado = m_ListaLibre;
    m_ListaLibre = m_ListaLibre->siguiente; // Move the free list head to the next block

    return static_cast<void*>(bloqueAsignado);
};


