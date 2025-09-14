#pragma once
#include<iostream>
/**
 * The Target defines the domain-specific interface used by the client code.
 */
//��ǰ����ֻ����XML�ļ���ʽ
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
 * Adaptee����һЩ���õķ����������Ľӿ����ִ�Ŀͻ��˴��벻���ݡ�
 * Adaptee ��ҪһЩ��Ӧ��Ȼ��ͻ��˴������ʹ������
 */
//��Ҫ������·��񣬵�����֧��ǰ�ļ���ʽ
class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface using multiple inheritance.
 * ������ͨ�����ؼ̳�����Adaptee�Ľӿ���Target�Ľӿڼ���
 */
//������ͨ�����ؼ̳�����Adaptee�Ľӿ���Target�Ľӿڼ���
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
