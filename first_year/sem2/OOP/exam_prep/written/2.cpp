#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <excpt.h>
using namespace std;

// template <typename T>
// class Adder {
// public:
//     vector<T> elems;
//     Adder(): elems(vector<T>()) {}
//     Adder(vector<T> _elems): elems(_elems) {}
//     Adder(T elem){
//         elems.push_back(elem);
//     }

//     Adder& operator+(const T& elem){
//         elems.push_back(elem);
//         return *this;
//     }

//     Adder& operator++(){
//         elems.push_back(elems[elems.size() - 1]);
//         return *this;
//     }

//     Adder& operator--(){
//         if(elems.size() == 0)
//             throw runtime_error("No more values!");

//         elems.pop_back();
//         return *this;
//     }

//     T sum(){
//         T s = T();
//         for(auto& e : elems){
//             s += e;
//         }

//         return s;
//     }
// };

// void function2(){
//     Adder<int> add{ 5 };
//     add = add + 5 + 2;
//     ++add;
//     add + 8;
    
//     cout << add.sum() << '\n';
//     --add;
//     cout << add.sum() << '\n';
//     --(--add);
//     cout << add.sum() << '\n';

//     try{
//         --(--(--add));
//     }
//     catch(runtime_error& ex){
//         cout << ex.what();
//     }
// }

// int fct(string v){
//     if (v == "") {throw string{"2"};}
//     cout << "1 ";
//     if(v.size() > 4){
//         throw std::runtime_error{"Not empty"};
//     }
//     return 0;
// }

class B{
public:
    B() {}
    B(const B& b) {cout << "copy "; }
    virtual void f() {cout << "B.f "; }
    void g(B b) {cout << "B.g "; }
    virtual ~B() {cout << "~B "; }
};

class D: public B {
public:
    D() {}
    void f(){B::f(); cout << "D.f ";}
    void g(D d) {B::g(d); cout << "D.g "; }
};

class A {
private:
    int* x;
public:
    A(int _x = 0){
        x = new int(_x);
    }

    A(const A& a) {
        x = new int{*a.x};
    }

    int get() {return *x;}
    void set(int _x) {*x = _x;}

    ~A() {delete x; }
};

int main(){

    // A a1, a2; a1.set(8);
    // A a3; a3 = a1;
    
    // A a4 = a1;
    // a1.set(5);

    // cout << a1.get() << " ";
    // cout << a2.get() << " ";
    // cout << a3.get() << " ";
    // cout << a4.get() << " ";

    // system("pause");
    // return 0;
    B* b = new B{};
    B* d = new D{};
    d->f();
    d->g(*b);
    delete b;
    delete d;

    // function2();

    // try{
    //     cout << fct("Hi") << " ";
    //     cout << fct("Hello") << " ";
    //     cout << fct("") << " ";
    // }
    // catch (string& e){
    //     cout << e;
    // }
    // catch (std::runtime_error& e){
    //     cout << e.what();
    // }

    // vector<int> v{1, 2, 3, 4, 5};
    // vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
    // v.insert(it, 7);
    // it = v.begin() + 2;
    // *it = 11;

    // vector<int> x;
    // std::copy_if(v.begin(), v.end(), back_inserter(x), [](int a){return a % 2 == 1;});
    // for (auto a : x)
    //     cout << a << " ";

    return 0;
}