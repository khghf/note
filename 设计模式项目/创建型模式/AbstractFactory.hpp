#pragma once
#include<iostream>
/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */
 /**
  * ͬһ���͵Ĳ�ͬ���Ĳ�Ʒ��Ҫ��һ�������Ľӿڣ����и����Ͳ�Ʒ�ı��嶼����ʵ�ָýӿ�
  */
//�����ƷA
class AbstractProductA {
public:
    virtual ~AbstractProductA() {};
    virtual std::string UsefulFunctionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
 /**
  * �����Ʒ�ɶ�Ӧ�ľ��幤������
  */
//�����ƷA1(A�ı���1)
class ConcreteProductA1 : public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A1.";
    }
};
//�����ƷA2(A�ı���2)
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
  * ������һ�ֲ�Ʒ�Ļ����ӿڡ����еĲ�Ʒ֮�䶼�ܽ��н���������ֻ��ͬһ���͵ı����Ʒ����������
  */

 //�����ƷB
class AbstractProductB {
    /**
    *  ��Ʒ B �ܹ����Լ�������......
    * 
    * ...����Ҳ������ ProductA Э����
    * ���󹤳�ȷ�������������в�Ʒ����
    * ��ͬ�ı��壬��˼��ݡ�
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
 //�����ƷB1(B�ı���1)
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

//�����ƷB2(B�ı���2)
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
  * Abstract Factory �ӿ�������һ�鷽������Щ�������ز�ͬ�ĳ����Ʒ��
  * ��Щ��Ʒ��Ϊϵ�в�Ʒ�������ǰ������������������(���磬���ӡ����ӡ�ɳ������ƺ�Ϊ�Ҿ�ϵ�У�
  * �Ҿ�Ϊ����)��
  * ͬһϵ�еĲ�Ʒ�����໥��������ͨ��ͬһϵ�еĲ�Ʒ�����ж��ֱ��壬����ͬһ�ֱ���Ĳ�Ʒ����һ�ֱ����
  * ��Ʒ���ܹ���(�ٸ����ӣ��ִ��Ҿ�ϵ�У������и��żҾ�ϵ�����������)
  */
//���󹤳��ӿ���
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
  * ���幤��������һ�����ϵ�в�Ʒ������ȷ����Ʒ�Ǽ��ݵ�(����ͬһ�ֱ���)��
  * ע�⣺���幤���ĺ���ǩ�����ص��ǳ����Ʒ�����Ƿ�������ʵ�������Ǿ����Ʒ
  */
//���幤����1
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
 //���幤����2
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
