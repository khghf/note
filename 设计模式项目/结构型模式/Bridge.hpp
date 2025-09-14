#pragma once
#include<iostream>
/**
 * The Implementation defines the interface for all implementation classes. It
 * doesn't have to match the Abstraction's interface. In fact, the two
 * interfaces can be entirely different. Typically the Implementation interface
 * provides only primitive operations, while the Abstraction defines higher-
 * level operations based on those primitives.
 * 
 * Implementation ���������� implementation classes �Ľӿڡ�
 * �������� Abstraction �Ľӿ�ƥ�䡣��ʵ�ϣ��������ӿڿ�����ȫ��ͬ��
 * ͨ����Implementation �ӿڽ��ṩ�����Ĳ������� 
 * Abstraction ������Щ��������������߼��������
 */
//ʵ�ֲ���
class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * Each Concrete Implementation corresponds to a specific platform and
 * implements the Implementation interface using that platform's API.
 * ÿ�� Concrete Implementation ����Ӧһ���ض���ƽ̨����ʹ�ø�ƽ̨�� API ʵ�� Implementation �ӿڡ�
 */
 //����ʵ�ֲ���A
class ConcreteImplementationA : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};
//����ʵ�ֲ���B
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
 * ���󲿷ֶ����������νṹ�� ��control�� ���ֵĽӿڡ�
 * �����ж� Implementation ��νṹ�еĶ�������ã���������ʵ�ʹ���ί�и��ö���
 */
//���󲿷�
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
 * �������չ���󲿷ֶ�����Ҫ�ı�Implementation classes
 */
//���󲿷���չ
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
 * ����Ҫ�ڳ�ʼ���׶���Abstraction�������ض���Implementation�����⣬
 * �ͻ��˴���ֻ��Ҫ������Abstraction�࣬��������֧���κ�abstraction-implementation���
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
