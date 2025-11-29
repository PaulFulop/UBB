#include <iostream>
#include <vector>

// template<typename T>
// class SmartPointer{
// public:
//     T* elem;
//     SmartPointer(T* _elem): elem(_elem) {}
//     ~SmartPointer(){
//         delete elem;
//     }

//     T& operator*() {return *elem;}
//     bool operator==(const SmartPointer& p){
//         return *elem == *p.elem;
//     }

//     SmartPointer(const SmartPointer& other){
//         elem = new T;
//         *elem = *other.elem;
//     }

//     SmartPointer& operator=(const SmartPointer& other) {
//         if (this != &other) {
//             delete elem;
//             elem = new T(*other.elem);
//         }
//         return *this;
//     }
// };

// template<typename T>
// class Set{
// public:
//     std::vector<T> elems;

//     Set(): elems(std::vector<T>()) {}

//     Set& operator=(const Set& other){
//         elems = other.elems;
//         return *this;
//     }

//     Set operator+(const T& newElem){
//         for(const auto& e : elems)
//             if(e == newElem)
//                 throw std::runtime_error("Element already exists!");
        
//         elems.push_back(newElem);
//         return *this;
//     }

//     Set& remove(const T& elem){
//         for(int i = 0; i < elems.size(); ++i)
//             if(elems[i] == elem){
//                 elems.erase(elems.begin() + i);
//                 return *this;
//             }
        
//         return *this;
//     }

//     std::vector<T>::iterator begin(){
//         return elems.begin();
//     }

//     std::vector<T>::iterator end(){
//         return elems.end();
//     }
// };

// void function2(){
//     SmartPointer<std::string> s1{new std::string{ "A" }};
//     SmartPointer<std::string> s2 = s1;
//     SmartPointer<std::string> s3 {new std::string{"C"}};
//     Set<SmartPointer<std::string>> set1{};

//     try{
//         set1 = set1 + s1;
//         set1 = set1 + s2;
//     }
//     catch(std::runtime_error& ex){
//         std::cout << ex.what();
//     }

//     SmartPointer<int> i1{new int{ 1 }};
//     SmartPointer<int> i2{new int{ 2 }};
//     SmartPointer<int> i3{new int{ 3 }};
//     Set<SmartPointer<int>> set2{};

//     set2 = set2 + i1;
//     set2 = set2 + i2;
//     set2 = set2 + i3;
//     set2.remove(i1).remove(i3);
//     for(auto e : set2)
//         std::cout << *e << ", "; //prints 2
// }

// class B{
// public:
//     B() {}
//     B(const B&) {std::cout << "copy "; }
//     virtual B f() {std::cout << "B.f "; return *this; }
//     virtual ~B() {std::cout << "~B "; }
// };

// class D: public B{
// private:
//     B* b;
// public:
//     D(B* _b): b{_b} {std::cout << "D "; }
//     B f() override {std::cout << "D.f "; return b->f();}
// };

int main(){
    // function2();
    // B* b = new B();
    // B* d = new D{b};
    // d->f();
    // delete d;
    // delete b;

    return 0;
}