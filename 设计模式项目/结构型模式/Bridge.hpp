#pragma once
#include<iostream>
/**
 * The Implementation defines the interface for all implementation classes. It
 * doesn't have to match the Abstraction's interface. In fact, the two
 * interfaces can be entirely different. Typically the Implementation interface
 * provides only primitive operations, while the Abstraction defines higher-
 * level operations based on those primitives.
 * 
 * Implementation 定义了所有 implementation classes 的接口。
 * 它不必与 Abstraction 的接口匹配。事实上，这两个接口可以完全不同。
 * 通常，Implementation 接口仅提供基本的操作，而 
 * Abstraction 基于这些基本操作定义更高级别的作。
 */
//实现部分
class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * Each Concrete Implementation corresponds to a specific platform and
 * implements the Implementation interface using that platform's API.
 * 每个 Concrete Implementation 都对应一个特定的平台，并使用该平台的 API 实现 Implementation 接口。
 */
 //具体实现部分A
class ConcreteImplementationA : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};
//具体实现部分B
class ConcreteImplementationB : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

/**
 * The Abstraction defines the interface for the "control" part of the two class
 * hierarchies. It maintains a reference to an object of the Implementation
 * hierarchy and delegates all of the real work to this object.
 * 抽象部分定义两个类层次结构的 “control” 部分的接口。
 * 它持有对 Implementation 层次结构中的对象的引用，并将所有实际工作委托给该对象。
 */
//抽象部分
class Abstraction {
    /**
     * @var Implementation
     */
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation) : implementation_(implementation) {
    }

    virtual ~Abstraction() {
    }

    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" +
            this->implementation_->OperationImplementation();
    }
};
/**
 * You can extend the Abstraction without changing the Implementation classes.
 * 你可以拓展抽象部分而不需要改变Implementation classes
 */
//抽象部分拓展
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {
    }
    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
            this->implementation_->OperationImplementation();
    }
};

/**
 * Except for the initialization phase, where an Abstraction object gets linked
 * with a specific Implementation object, the client code should only depend on
 * the Abstraction class. This way the client code can support any abstraction-
 * implementation combination.
 * 
 * 除了要在初始化阶段让Abstraction对象与特定的Implementation链接外，
 * 客户端代码只需要依赖与Abstraction类，这样才能支持任何abstraction-implementation组合
 */
void ClientCode(const Abstraction& abstraction) {
    // ...
    std::cout << abstraction.Operation();
    // ...
}
/**
 * The client code should be able to work with any pre-configured abstraction-
 * implementation combination.
 */
void Bridge_test()
{
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;
}
