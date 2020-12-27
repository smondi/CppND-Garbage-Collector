// This class defines an element that is stored
// in the garbage collection information list.
//

#include <algorithm>

template <class T>
class PtrDetails {
  public:
    int refcount{0}; // current reference count
    T *memPtr{nullptr};      // pointer to allocated memory
    bool isArray{false};     // true if pointing to array
    int arraySize{0}; // size of array

    PtrDetails(T *memPtr = nullptr, int size = 0)
    {
        if (size > 0) {
            this->isArray = true;
            this->arraySize = size;
        }
        
        this->memPtr = memPtr;
        
        ++refcount;
    }

    // Copy Constructor
    PtrDetails(const T &ptr)
        : refcount{ptr.refcount}, isArray{ptr.isArray}, 
          arraySize{ptr.arraySize}, memPtr{new T[ptr.arraySize]}
    {
        
        std::copy(ptr.memPtr, ptr.memPtr+ptr.arraySize, memPtr);
        
    }

    // Copy Assignment
    PtrDetails& operator=(const T &ptr)
    {
        if (this != &ptr) {
            T *temp = new T[ptr.arraySize];
            std::copy(ptr.memPtr, ptr.memPtr+ptr.arraySize, temp);
            delete[] memPtr;
            memPtr = temp;
            refcount = ptr.refcount;
            isArray = ptr.isArray;
            arraySize = ptr.arraySize;
        }
        return *this;
    }
};

template <class T>
bool operator==(const PtrDetails<T> &lhs, const PtrDetails<T> &rhs)
{
    return (lhs.memPtr == rhs.memPtr) && (lhs.arraySize == rhs.arraySize);
}

template <class T>
bool operator!=(const PtrDetails<T> &lhs, const PtrDetails<T> &rhs) 
{
    return (rhs.memPtr != lhs.memPtr) && (rhs.arraySize != lhs.memPtr);
}
