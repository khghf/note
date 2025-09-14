#pragma once
#include<iostream>
/**
 * The Abstract Class defines a template method that contains a skeleton of some
 * algorithm, composed of calls to (usually) abstract primitive operations.
 *
 * Concrete subclasses should implement these operations, but leave the template
 * method itself intact.
 */

//抽象类 （Abstract­Class） 会声明作为算法步骤的方法， 以及依次调用它们的实际模板方法。
//算法步骤可以被声明为 抽象类型， 也可以提供一些默认实现。
//抽象类
class AbstractClass {
    /**
     * The template method defines the skeleton of an algorithm.
     */
public:
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }
    /**
     * These operations already have implementations.
     */
protected:
    void BaseOperation1() const {
        std::cout << "AbstractClass says: I am doing the bulk of the work\n";
    }
    void BaseOperation2() const {
        std::cout << "AbstractClass says: But I let subclasses override some operations\n";
    }
    void BaseOperation3() const {
        std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
    }
    /**
     * These operations have to be implemented in subclasses.
     */
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;
    /**
     * These are "hooks." Subclasses may override them, but it's not mandatory
     * since the hooks already have default (but empty) implementation. Hooks
     * provide additional extension points in some crucial places of the
     * algorithm.
     */
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};
/**
 * Concrete classes have to implement all abstract operations of the base class.
 * They can also override some operations with a default implementation.
 * 具体类必须实现基类的所有抽象操作，
 * 他们也可以重写默认操作
 */
//具体类1
class ConcreteClass1 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation1\n";
    }
    void RequiredOperation2() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation2\n";
    }
};
/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
 //具体类2
class ConcreteClass2 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation1\n";
    }
    void RequiredOperation2() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation2\n";
    }
    void Hook1() const override {
        std::cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};
/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void TemplateMethod_test()
{
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    concreteClass1->TemplateMethod();
    std::cout << "\n";
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    concreteClass2->TemplateMethod();
    delete concreteClass1;
    delete concreteClass2;
}
