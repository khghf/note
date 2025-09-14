#pragma once
#include<iostream>
#include<unordered_map>
using std::string;
// Prototype Design Pattern
//
// Intent: Lets you copy existing objects without making your code dependent on
// their classes.

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

/**
 * The example class that has cloning ability. We'll see how the values of field
 * with different types will be cloned.
 */
//原型抽象基类
class Prototype {
protected:
    string prototype_name_;
    float prototype_field_;

public:
    Prototype() {}
    Prototype(string prototype_name)
        : prototype_name_(prototype_name) {
    }
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
    virtual void Method(float prototype_field) {
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
    }
};

/**
 * ConcretePrototype1 is a Sub-Class of Prototype and implement the Clone Method
 * In this example all data members of Prototype Class are in the Stack. If you
 * have pointers in your properties for ex: String* name_ ,you will need to
 * implement the Copy-Constructor to make sure you have a deep copy from the
 * clone method
 * ConcretePrototype1 是 Prototype 的子类，实现了 Clone Method
 * 在此示例中，Prototype 类的所有数据成员都在堆栈中。如果你
 * 在你的属性中有指针，例如： String* name_ ，你需要
 * 实现 Copy-Constructor 以确保拥有来自 clone 方法的深层副本
 */
//具体原型类1
class ConcretePrototype1 : public Prototype {
private:
    float concrete_prototype_field1_;

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {
    }
    /**
     * Notice that Clone method return a Pointer to a new ConcretePrototype1
     * replica. so, the client (who call the clone method) has the responsability
     * to free that memory. If you have smart pointer knowledge you may prefer to
     * use unique_pointer here.
     * 
     * 请注意，Clone 方法返回一个指向新 ConcretePrototype1 的 Pointer
     * 复制品。因此，客户端 （调用 clone 方法） 有责任
     * 释放该内存。如果您了解智能指针，您可能更喜欢在此处使用 unique_pointer。
     */
    Prototype* Clone() const override {
        return new ConcretePrototype1(*this);
    }
};
//具体原型类2
class ConcretePrototype2 : public Prototype {
private:
    float concrete_prototype_field2_;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {
    }
    Prototype* Clone() const override {
        return new ConcretePrototype2(*this);
    }
};

/**
 * In PrototypeFactory you have two concrete prototypes, one for each concrete
 * prototype class, so each time you want to create a bullet , you can use the
 * existing ones and clone those.
 * 
 * 在 PrototypeFactory 中，您有两个具体原型，每个具体原型类一个，
 * 因此每次您想要创建一个项目符号时，您都可以使用现有的原型并克隆它们。
 */
//原型工厂
class PrototypeFactory {
private:
    //储存拥有的原型类的对应实例
    std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;

public:
    PrototypeFactory() {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    /**
     * Be carefull of free all memory allocated. Again, if you have smart pointers
     * knowelege will be better to use it here.
     */

    ~PrototypeFactory() {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    /**
     * Notice here that you just need to specify the type of the prototype you
     * want and the method will create from the object with this type.
     */
    Prototype* CreatePrototype(Type type) {
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory& prototype_factory) {
    std::cout << "Let's create a Prototype 1\n";

    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);

    delete prototype;
}
void Prototype_test()
{
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;
}