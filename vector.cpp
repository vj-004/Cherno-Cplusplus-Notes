#include <iostream>
#include "Vector.h"




struct Vector3{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    Vector3() {}

    Vector3(float scaler): x(scaler), y(scaler), z(scaler) {}

    Vector3(float x, float y, float z): x(x), y(y), z(z) {}

    Vector3(const Vector3& other) = delete;
    
    Vector3(const Vector3&& other) : x(other.x), y(other.y), z(other.z)  {
        std::cout << "Move\n";
    }

    ~Vector3(){
        std::cout << "Destroy\n";
    }

    Vector3& operator=(Vector3&& other){
        std::cout << "Move " <<'\n';

        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3& operator=(const Vector3& other) = delete;

};

template<typename T>
void PrintVector(const Vector<T>& vector){
    for(size_t i = 0; i< vector.Size(); i++){
        std::cout << vector[i] << std::endl;
    }
    std::cout << "----------------------------------------\n";
}


template<>
void PrintVector(const Vector<Vector3>& vector){
    for(size_t i = 0; i< vector.Size(); i++){
        std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
    }
    std::cout << "----------------------------------------\n";
}

int main(){


    // Vector<std::string> vector;
    // vector.PushBack("Vayun");   
    // vector.PushBack("Backend");   
    // vector.PushBack("C++");   

    // PrintVector(vector);

    Vector<Vector3> vector;
    // vector.PushBack(Vector3(1.0f));
    // vector.PushBack(Vector3(2, 3, 4));
    // vector.PushBack(Vector3());

    vector.EmplaceBack(1.0f);
    vector.EmplaceBack(2, 3, 4);
    vector.EmplaceBack();
    PrintVector(vector);
    vector.PopBack();
    PrintVector(vector);
    vector.Clear();
    PrintVector(vector);

    Vector<int> intVector;
    intVector.PushBack(5);
    intVector.EmplaceBack(5);
    intVector.EmplaceBack(5);
    intVector.EmplaceBack(5);
    PrintVector(intVector);
    intVector.PushBack(5);
    PrintVector(intVector);
    intVector.PopBack();
    intVector.Clear();

    return 0;
}