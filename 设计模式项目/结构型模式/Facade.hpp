#pragma once
#include<iostream>
/**
 * The Subsystem can accept requests either from the facade or client directly.
 * In any case, to the Subsystem, the Facade is yet another client, and it's not
 * a part of the Subsystem.
 * Subsystem可以直接接受facade或者client的请求
 * 在任何情况下，Facade对于Subsystem来说相当于另一个客户端，并且Facade不是Subsystem的一部分
 */
//外部接入的库1
class Subsystem1 {
public:
    std::string Operation1() const {
        return "Subsystem1: Ready!\n";
    }
    // ...
    std::string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};
 //外部接入的库2
class Subsystem2 {
public:
    std::string Operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    // ...
    std::string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
//Facade类为一个或者多个复杂的subsystem提供简单的接口
//Facade代表客户端的请求来访问subsystem内的对象，
//Facade负责管理他们的生命周期
//所有这些都使客户端免受子系统的不必要复杂性的影响
//外观类
class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;
public:
    Facade(
        Subsystem1* subsystem1 = nullptr,
        Subsystem2* subsystem2 = nullptr) {
        this->subsystem1_ = subsystem1 ? nullptr : new Subsystem1;
        this->subsystem2_ = subsystem2 ? nullptr : new Subsystem2;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

/**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 */
void ClientCode(Facade* facade) {
    // ...
    std::cout << facade->Operation();
    // ...
}
void Facade_test()
{
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;
    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);
    delete facade;
}
