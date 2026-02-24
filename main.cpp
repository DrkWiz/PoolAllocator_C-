#include <iostream>
#include "Headers/poolAllocator.h"

int main() {

    // create a pool allocator with block size of 16 bytes and a total of 10 blocks
    PoolAllocator pool(16, 10);

    // allocate some blocks
    void* block1 = pool.allocate();
    void* block2 = pool.allocate();

    std::cout << "Allocated block 1 at: " << block1 << std::endl;
    std::cout << "Allocated block 2 at: " << block2 << std::endl;
    // deallocate block1
    if (pool.deallocate(block1)) {
        std::cout << "Deallocated block 1 successfully." << std::endl;
    } else {
        std::cout << "Failed to deallocate block 1." << std::endl;
    }

// allocate another block (should reuse the deallocated block1)
    void* block3 = pool.allocate();
    std::cout << "Allocated block 3 at: " << block3 << std::endl;

    // Check if block3 is the same as block1 (reused)
    if (block3 == block1) { 
        std::cout << "Block 3 reused the memory of Block 1." << std::endl;
    } else {
        std::cout << "Block 3 did not reuse the memory of Block 1." << std::endl;
    }

    return 0;
}