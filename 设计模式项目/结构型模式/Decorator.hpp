#pragma once
#include<iostream>
namespace Decorator
{
    /**
 * The base Component interface defines operations that can be altered by
 * decorators.
 */
 //部件 （Component） 声明封装器和被封装对象的公用接口。
    class Component {
    public:
        virtual ~Component() {}
        virtual std::string Operation() const = 0;
    };
    /**
     * Concrete Components provide default implementations of the operations. There
     * might be several variations of these classes.
     */
     //具体部件 （Concrete Component） 类是被封装对象所属的类。 它定义了基础行为， 但装饰类可以改变这些行为。
    class ConcreteComponent : public Component {
    public:
        std::string Operation() const override {
            return "ConcreteComponent";
        }
    };
    /**
     * The base Decorator class follows the same interface as the other components.
     * The primary purpose of this class is to define the wrapping interface for all
     * concrete decorators. The default implementation of the wrapping code might
     * include a field for storing a wrapped component and the means to initialize
     * it.
     * 基类 Decorator 遵循与其他组件相同的接口。
     * 这个类的主要目的是为所有具体装饰器定义包装接口。
     * 包装代码的默认实现可能包括用于存储包装组件的字段以及初始化该组件的方法。
     */

    class Decorator : public Component {
        /**
         * @var Component
         */
    protected:
        Component* component_;

    public:
        Decorator(Component* component) : component_(component) {
        }
        /**
         * The Decorator delegates all work to the wrapped component.
         */
        std::string Operation() const override {
            return this->component_->Operation();
        }
    };
    /**
     * Concrete Decorators call the wrapped object and alter its result in some way.
     */
     //具体装饰类 （Concrete Decorators） 定义了可动态添加到部件的额外行为。 
     //具体装饰类会重写装饰基类的方法， 并在调用父类方法之前或之后进行额外的行为。
     //具体装饰类A
    class ConcreteDecoratorA : public Decorator {
    public:
        ConcreteDecoratorA(Component* component) : Decorator(component) {
        }
        std::string Operation() const override {
            return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
        }
    };
    /**
     * Decorators can execute their behavior either before or after the call to a
     * wrapped object.
     */
     //具体装饰类B
    class ConcreteDecoratorB : public Decorator {
    public:
        ConcreteDecoratorB(Component* component) : Decorator(component) {
        }

        std::string Operation() const override {
            return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
        }
    };
    /**
     * The client code works with all objects using the Component interface. This
     * way it can stay independent of the concrete classes of components it works
     * with.
     */
    void ClientCode(Component* component) {
        // ...
        std::cout << "RESULT: " << component->Operation();
        // ...
    }
    void Decorator_test()
    {
        /**
        * This way the client code can support both simple components...
        */
        Component* simple = new ConcreteComponent;
        std::cout << "Client: I've got a simple component:\n";
        ClientCode(simple);
        std::cout << "\n\n";
        /**
         * ...as well as decorated ones.
         *
         * Note how decorators can wrap not only simple components but the other
         * decorators as well.
         */
        Component* decorator1 = new ConcreteDecoratorA(simple);
        Component* decorator2 = new ConcreteDecoratorB(decorator1);
        std::cout << "Client: Now I've got a decorated component:\n";
        ClientCode(decorator2);
        std::cout << "\n";

        delete simple;
        delete decorator1;
        delete decorator2;
    }

}
