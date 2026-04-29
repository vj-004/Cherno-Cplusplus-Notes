#include <iostream>
#include <array>
#include <cstring>

class Array_Without_Templates{

public:

    Array_Without_Templates(int size){
        m_Data = (int*)alloca(size * sizeof(int)); // alloca is a function which allows us to allocate memory in a stack and it takes in the number of bytes we want to allocate
        /*
            while using alloca, the memory is on the stack yes but the compiler doesn't really know how big the size will be that can lead to problems 
            and lack of compiler optimizations.       
            So lets avoid alloca in this instance but it is a very powerful function
        */
    }

    // The std::array class (and all stl) use tempalates to create the data structures, This a way to create the array class without templates. 
    // But we will use templates as it makes it easier to work with.

private:
    int* m_Data;

};

template<typename T, size_t S>
class Array{
public:

    constexpr size_t Size() const {
        return S;
    }

    /*
        T operator[](int index){
            return m_Data[index];
        }
        There are problems with returning a T when writing function for the operator[], what if T was a string, we don't want to create a whole new
        object and then return it, instead we return T&.
        Also without T& , if in the main code we tried to do something like data[2] = 3, this would simply not be possible since we are returning
        a non modifiable lvalue as we are simply returning a brand new copy of an integer here, there is nothing to assign, there is no storage.
        That is why return a reference even though the type is an int.
    */
    T& operator[](size_t index){
        return m_Data[index];
    }

    /*
        If we have something like this in the main function and we don't have the operator[] function given below
        const auto& arrayReference = data;
        In this case we when we are returning T& in the operator[] function, we can't do things like 
        arrayReference[2] = 3; this is obvious since we marked it as const but we also cannot do
        std::cout << arrayReference[2] << std::endl;

        To solve this we just create another version of the operator[] function which return a const T& and it is also marked as const

    */
    const T& operator[](size_t index) const{
        return m_Data[index];
    }

    T* Data() { return m_Data };
    const T* Data() const { return m_Data };

private:
    T m_Data[S];

};



int main(){

    // int size = 5;
    // int array[size]; this gives an error
    int array[5];

    int size = 5;
    int* heapArray = new int[size];

    delete[] heapArray;

    std::array<int, 10> collection;
    int s = collection.size();

    // What we are going to do is make the APIs which std::array provides to us without using std:array
    

    Array<int, 5> data;
    int length = data.Size();

    /* Since "5" the length of the array is something we know at compile time, so why not let other compile time tasks be able to take advantage
        of that value. One example is a static_assert which gets evaluated at compile time.

        static_assert(data.Size() < 10 , "Size is too large!"); 

        But this doesn't work (when data.Size() returns an int), the error you will get is the the expression must have a constant value. 
        That's because data.Size() was returning us an int, but if we were to make it return a constexpr int then it will work 
        By writing constexpr we are saying that this expression can be evaluated at compile time. So now it starts working.
    */
    
    static_assert(data.Size() < 10 , "Size is too large!"); 

    // return a constexpr int from data.Size() also lets us declare a new array using the data.Size() since it is not known at compile time.
    Array<std::string, data.Size()> newArray;

    for(size_t i=0; i < data.Size(); i++){
        std::cout << data[i] << '\n';
    }

    const auto& arrayReference = data;

    for(size_t i=0; i < data.Size(); i++){
        std::cout << arrayReference[i] << '\n';
    }

    memset(data.Data(), 0, data.Size()* sizeof(int));

    for(size_t i=0; i < data.Size(); i++){
        std::cout << data[i] << '\n';
    }

    /*
        what we would also like to do is write iterators
        for(auto& element: data){

        }

        This doesn't work right now. For this we need to write an iterator which will see later.
    */

}