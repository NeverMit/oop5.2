#include<iostream>
using namespace std;
class Base {//родительский класс
public:
	Base() {
		cout << "Base()" << endl;
	}
	Base(Base* obj) {
		cout << "Base(Base* obj)" << endl;
	}
	Base(Base& obj) {
		cout << "Base(Base& obj)" << endl;
	}
	virtual ~Base() {//виртуальный деструктор
		cout << "~Base()" << endl;
	}
	void someMethod1() {//невиртуальный метод 1
		cout << "Base::someMethod1() not virtual" << endl;
		someMethod3();
	}
	void someMethod2() {//невиртуальный метод 2
		cout << "Base::someMethod2() not virtual" <<endl;
		someMethod4();
	}
	void someMethod3() {//невиртуальный метод 3
		cout << "Base::someMethod3() not virtual" << endl;
	}
	virtual void someMethod4() {//виртуальный метод 4
		cout << "Base::someMethod2() virtual" << endl;
	}
	virtual string classname() {//метод возвращения имени класс объекта
		return "Base";
	}
	virtual bool IsA(std::string classname) {//метод для предварительной проверки при приведении типа
		return classname == "Base";
	}
};
class Desk : public Base {//Дочерний класс
public:
	Desk() {
		cout << "Desk()" << endl;
	}
	Desk(Desk* obj) {
		cout << "Desk(Desk* obj)" << endl;
	}
	Desk(Desk& obj) {
		cout << "Desk(Desk& obj)" << endl;
	}
	virtual ~Desk() {
		cout << "~Desk()" << endl;
	}
	void someMethod3() {//невиртуальный метод 3
		cout << "Desk::someMethod2() not virtual" << endl;
	}
	void someMethod4() override {//виртуальный метод 4
		cout << "Desk::someMethod2() virtual" << endl;
	}
	string classname() override {
		return "Desk";
	}
	bool IsA(string classname) override {
		return classname == "Desk";
	}
};
void func() {
	cout << "func()" << endl;
}
void func(Base* obj) {
	cout << "func(Base* obj)" << endl;
	(static_cast<Desk*>(obj))->someMethod3();
}
void func(Base& obj) {
	cout << "func(Base& obj)" << endl;
	(static_cast<Desk*>(&obj))->someMethod3();
}
Base func1() {
	cout << "Base func1()\n";
	Base local;
	return local;
}
Base* func2() {
	cout << "Base* func2()\n";
	Base local;
	return &local;
}
Base& func3() {
	cout << "Base& func3()\n";
	Base local;
	return local;
}
Base func4() {
	cout << "Base func4() with dynamic cast \n";
	Base* local = new Base();
	return *local;
}
Base* func5() {
	cout << "Base* func5() with dynamic cast \n";
	Base* local = new Base();
	return local;
}
Base& func6() {
	cout << "Base& func6() with dynamic cast \n";
	Base* local = new Base();
	return *local;
}
int main() {
	setlocale(LC_ALL, "rus");
	cout << "1)жизненный цикл unique_ptr\n----------------\n";//жизненный цикл unique_ptr
	cout << "std::unique_ptr<Base> smartPointer(new Base())" << endl;
	
	unique_ptr <Base> smartPointer(new Base());
	
	cout << "----------------\n";
	cout << "2)жизненный цикл shared_ptr\n----------------\n";//жизненный цикл shared_ptr
	cout << "std::shared_ptr<Base> shPointer(new Base())" << endl;
	
	shared_ptr <Base> shPointer(new Base());
		
	shared_ptr<Base> shPointer1 = shPointer;
	cout << shPointer << endl << shPointer1 << endl;
		
	
	cout << "----------------\n";
	cout << "3)небезопасное приведение типов\n----------------\n";//небезопасное приведение типов
	
	cout << "(static_cast<Desk*>(stСast))->someMethod3()" << endl;
	Base* stСast = new Desk();
	if (stСast->IsA("Desk")) 
		{
			(static_cast<Desk*>(stСast))->someMethod3();
		}
		delete stСast;
	
	cout << "----------------\n";
	cout << "4)безопасное приведение типов\n----------------\n";//безопасное приведение типов
	
	cout << "(dynamic_cast<Desk*>(dСast))->someMethod3()" << endl;
	Base* dСast = new Desk();
	Desk* c = dynamic_cast<Desk*>(dСast);
	if (c != nullptr) 
	{
		c->someMethod3();
	}
	delete dСast;
	
	cout << "----------------\n";
	cout << "5)вызов виртуальных и невиртуальных методов в дочернем объекте\n----------------\n";//вызов виртуальных и невиртуальных методов в дочернем объекте
	
	Desk testDaughter;
	cout << "Result of Desk::someMethod1() and not virtual someMethod2(): " << endl;
	testDaughter.someMethod1();
	cout << "Result of Desk::someMethod1() and virtual someMethod2(): " << endl;
	testDaughter.someMethod2();
	
	cout << "----------------\n";
	cout << "6)передача объектов в качестве параметров\n----------------\n";//передача объектов в качестве параметров
	
	unique_ptr <Base> test(new Desk());
	func(*test);
	func(test.get());
	
	cout << "}\n";
	cout << "7)возврат созданных в функциях объектов\n----------------\n";//возврат созданных в функциях объектов
		Base b1;
		b1 = func1();
		Base* b2;
		b2 = func2();
		Base& b3 = func3();
		Base b4;
		b4 = func4();
		Base* b5;
		b5 = func5();
		Base& b6 = func6();
	cout << "----------------\n";
	return 0;
}