#pragma once
#include<iostream>
/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */
 /**
  * 同一类型的不同风格的产品都要有一个基础的接口，所有该类型产品的变体都必须实现该接口
  */
//抽象产品A
class AbstractProductA {
public:
    virtual ~AbstractProductA() {};
    virtual std::string UsefulFunctionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
 /**
  * 具体产品由对应的具体工厂创建
  */
//具体产品A1(A的变体1)
class ConcreteProductA1 : public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A1.";
    }
};
//具体产品A2(A的变体2)
class ConcreteProductA2 : public AbstractProductA {
    std::string UsefulFunctionA() const override {
        return "The result of the product A2.";
    }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */
 /**
  * 这是另一种产品的基础接口。所有的产品之间都能进行交互，但是只有同一类型的变体产品才能这样做
  */

 //抽象产品B
class AbstractProductB {
    /**
    *  产品 B 能够做自己的事情......
    * 
    * ...但它也可以与 ProductA 协作。
    * 抽象工厂确保它创建的所有产品都是
    * 相同的变体，因此兼容。
    */

    /**
     * Product B is able to do its own thing...
     */
public:
    virtual ~AbstractProductB() {};
    virtual std::string UsefulFunctionB() const = 0;
    /**
     * ...but it also can collaborate with the ProductA.
     *
     * The Abstract Factory makes sure that all products it creates are of the
     * same variant and thus, compatible.
     */
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
 //具体产品B1(B的变体1)
class ConcreteProductB1 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B1.";
    }
    /**
     * The variant, Product B1, is only able to work correctly with the variant,
     * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

//具体产品B2(B的变体2)
class ConcreteProductB2 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B2.";
    }
    /**
     * The variant, Product B2, is only able to work correctly with the variant,
     * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
 /**
  * Abstract Factory 接口声明了一组方法，这些方法返回不同的抽象产品。
  * 这些产品称为系列产品，并且是按主题或概念关联起来的(比如，桌子、椅子、沙发假设称呼为家具系列，
  * 家具为主题)。
  * 同一系列的产品可以相互合作、沟通。同一系列的产品可能有多种变体，但是同一种变体的产品与另一种变体的
  * 产品不能共存(举个例子，现代家具系列，不能有复古家具系列里面的椅子)
  */
//抽象工厂接口类
class AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */
 /**
  * 具体工厂生产单一变体的系列产品，并且确保产品是兼容的(都是同一种变体)。
  * 注意：具体工厂的函数签名返回的是抽象产品，但是方法里面实例化的是具体产品
  */
//具体工厂类1
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA1();
    }
    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 */
 //具体工厂类2
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA2();
    }
    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

void ClientCode(const AbstractFactory& factory) {
    const AbstractProductA* product_a = factory.CreateProductA();
    const AbstractProductB* product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}
void AbstractFactory_test()
{
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
}
