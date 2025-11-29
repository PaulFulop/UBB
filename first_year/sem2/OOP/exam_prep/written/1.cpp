#include <iostream>
#include <assert.h>
#include <excpt.h>   
#include <vector> 
#include <string>
#include <algorithm>

// Ex 1
// class Complex{
// private:
//     int real, img;
// public:
//     Complex(): real(0), img(0){}
//     Complex(int _real, int _img): real(_real), img(_img){}
//     Complex(const Complex& c): real(c.real), img(c.img){}
//     int getReal(){
//         return real;
//     }
//     int getImaginary(){
//         return img;
//     }

//     bool operator == (const Complex& c) {
//         return real == c.real && img == c.img;
//     } 

//     Complex operator/ (int num){
//         if (!num) throw std::runtime_error("Division by zero!");
//         return Complex(real / 2, img / 2);
//     }

//     friend std::ostream& operator<< (std::ostream& os, const Complex& c);
// };

// std::ostream& operator << (std::ostream& os, const Complex& c){
//         os << c.real << "+" << c.img << "i";
//         return os;
// }

// template <typename T>
// class Vector{
// private:
//     std::vector<T> v;
// public:
//     Vector(): v(std::vector<T>()){}
//     Vector(std::vector<T> _v): v(_v){}

//     void printAll(std::ostream& os){
//         for (const auto& elem : v)
//             os << elem << ',';
//     }
// };

// Ex 2 b

// class Ex1 {
// public:
//     Ex1() {std::cout << "Exception 1 "; }
//     Ex1(const Ex1& ex) {std::cout << "Copy_ex1 ";}
// };

// class Ex2 : public Ex1{
// public:
//     Ex2() {std::cout << "Exception 2 "; }
//     Ex2(const Ex2& ex) {std::cout << "Copy_exc2 ";}
// };

// void except(int x){
//     if (x < 0)
//         throw Ex1{};
//     else if (x == 0)
//         throw Ex2{};
//     std::cout << "Done ";
// }

// Ex 2 c
// class B{
// public:
//     void f() {std::cout << "B.f "; }
//     virtual ~B() {}
// };

// class D1 : public B{
// public:
//     virtual void f() {std::cout << "D1.f "; }
//     virtual ~D1() {}
// };

// class D2 : public D1{
// public:
//     void f() {std::cout << "D2.f"; } 
// };

// Ex 2 d

// class Vector{
//     int* elems;
//     int size;
// public:
//     Vector(): size{ 0 } { elems = new int[10]; }
//     void add(int elem){
//         elems[size++] = elem;}
    
//     int& operator[](int pos){
//         if (pos < 0 || pos >= size)
//             throw std::runtime_error{"Index out of bounds." };
//         return elems[pos];
//     }
//     ~Vector() { delete[] elems; }
// };

#include <iostream>
#include <vector>
#include <string>

class Action {
public:
    virtual void execute() = 0;
    virtual ~Action() {}
};

class CreateAction : public Action {
public:
    void execute() override { std::cout << "Create file\n"; }
};

class ExitAction : public Action {
public:
    void execute() override { std::cout << "Exit application\n"; }
};

class MenuItem {
protected:
    std::string text;
    Action* action;
public:
    MenuItem(const std::string& t, Action* a = nullptr) : text(t), action(a) {}
    virtual ~MenuItem() {}
    virtual void print() const { std::cout << text; }
    virtual void clicked() {
        print();
        std::cout << '\n';
        if (action) action->execute();
    }
};

class Menu : public MenuItem {
private:
    std::vector<MenuItem*> items;
public:
    Menu(const std::string& t = "", Action* a = nullptr) : MenuItem(t, a) {}
    ~Menu() {
        for (auto item : items) delete item;
    }
    void print() const override {
        std::cout << text << '\n';
        for (auto item : items) {
            item->print();
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    void add(MenuItem* m) {
        items.push_back(m);
    }
};

class MenuBar {
private:
    std::vector<Menu*> menus;
public:
    ~MenuBar() {
        for (auto m : menus) delete m;
    }
    void print() const {
        for (auto menu : menus)
            menu->print();
    }
    void add(Menu* m) {
        menus.push_back(m);
    }
};


int main(){
    Action* exitAction = new ExitAction();
    Action* createText = new CreateAction();
    Action* createCpp = new CreateAction();

    Menu* newMenu = new Menu("New");
    Menu* textMenu = new Menu("Text", createText);
    Menu* cppMenu = new Menu("C++", createCpp);
    newMenu->add(textMenu);
    newMenu->add(cppMenu);

    Menu* exitMenu = new Menu("Exit", exitAction);
    Menu* fileMenu = new Menu("File");
    fileMenu->add(newMenu);
    fileMenu->add(exitMenu);

    Menu* aboutMenu = new Menu("About");

    MenuBar mBar;
    mBar.add(fileMenu);
    mBar.add(aboutMenu);

    mBar.print();

    std::cout << "\nSimulated click sequence:\n";
    fileMenu->clicked();
    newMenu->clicked();
    cppMenu->clicked();
    exitMenu->clicked();

    // clean up
    delete exitAction;
    delete createText;
    delete createCpp;

    // // Ex 1
    // std::cout << "Ex 1\n\n";
    // Complex a{}, b{1, 2}, c{6, 4}, d{b};
    // assert(a.getReal() == 0 && a.getImaginary() == 0);
    // assert(c.getImaginary() == 4);
    // assert(b == d);
    // Complex res1 = c / 2;
    // std::cout << res1 << '\n'; // should print 3+2i

    // try{
    //     Complex res2 = b / 0;
    // }
    // catch(std::runtime_error& e){
    //     assert(strcmp(e.what(), "Division by zero!") == 0);
    // }

    // Vector<std::string> v1 {std::vector<std::string>{"hello", "bye"} };
    // v1.printAll(std::cout);

    // Vector<Complex> v2 {std::vector<Complex>{a, b, c, d} };
    // v2.printAll(std::cout);
    // std::cout << "\n\n\n";

    // // Ex 2 a
    // std::cout << "Ex 2 a\n";
    // //a
    // std::vector<int> v{1, 2, 3, 4, 5};
    // std::vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
    // v.insert(it, 8);
    // it = v.begin() + 2;
    // *it = 10;
    // std::vector<int> x;

    // std::copy_if(v.begin(), v.end(), back_inserter(x), [](int a){return a%2==0;});
    // for(auto a : x)
    //     std::cout << a << " ";
    // std::cout << "\n\n";

    // std::cout << "Ex 2 b\n";
    // // b
    // try{
    //     std::cout << "Start ";
    //     try{
    //         except(0);
    //     }
    //     catch (Ex1& e){}
    //     except(-2);
    // } catch (Ex1 e) {}
    //Start Exception 1 Exception 2 Exception 1 Copy_ex1

    // Ex 2 c
    // std::cout << "\n\n\n";
    // std::cout << "Ex 2 c\n";
    // B* b1 = new B{}; b1->f(); delete b1;
    // B* b2 = new D1{}; b2->f(); delete b2;
    // B* b3 = new D2{}; b3->f(); delete b3;
    // D1* d = new D2{}; d->f(); delete d;

    // Ex 2 d
    // Vector v1;
    // v1.add(0);
    // v1.add(1);
    // Vector v2 = v1;

    // try{
    //     v1[0] = 2;
    //     std::cout << v1[0] << " " << v1[1] << " ";
    //     std::cout << v2[0] << " " << v2[1] << " ";
    // }
    // catch (std::runtime_error& e) {std::cout << e.what(); }

    return 0;
}