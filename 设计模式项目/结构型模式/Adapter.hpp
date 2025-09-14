#pragma once
#include<iostream>
/**
 * The Target defines the domain-specific interface used by the client code.
 */
//当前服务，只接受XML文件格式
class Target {
public:
    virtual ~Target() = default;
    virtual std::string Request() const {
        return "Target: The default target's behavior.";
    }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 * 
 * Adaptee包含一些有用的方法，但它的接口与现存的客户端代码不兼容。
 * Adaptee 需要一些适应，然后客户端代码才能使用它。
 */
//需要接入的新服务，但不持支当前文件格式
class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface using multiple inheritance.
 * 适配器通过多重继承来让Adaptee的接口与Target的接口兼容
 */
//适配器通过多重继承来让Adaptee的接口与Target的接口兼容
class Adapter : public Target, public Adaptee {
public:
    Adapter() {}
    std::string Request() const override {
        std::string to_reverse = SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const Target* target) {
    std::cout << target->Request();
}
void Adapter_test()
{
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target* target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee* adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter* adapter = new Adapter;
    ClientCode(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;
}
