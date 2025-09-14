#pragma once
#include<iostream>
namespace Decorator
{
    /**
 * The base Component interface defines operations that can be altered by
 * decorators.
 */
 //���� ��Component�� ������װ���ͱ���װ����Ĺ��ýӿڡ�
    class Component {
    public:
        virtual ~Component() {}
        virtual std::string Operation() const = 0;
    };
    /**
     * Concrete Components provide default implementations of the operations. There
     * might be several variations of these classes.
     */
     //���岿�� ��Concrete Component�� ���Ǳ���װ�����������ࡣ �������˻�����Ϊ�� ��װ������Ըı���Щ��Ϊ��
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
     * ���� Decorator ��ѭ�����������ͬ�Ľӿڡ�
     * ��������ҪĿ����Ϊ���о���װ���������װ�ӿڡ�
     * ��װ�����Ĭ��ʵ�ֿ��ܰ������ڴ洢��װ������ֶ��Լ���ʼ��������ķ�����
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
     //����װ���� ��Concrete Decorators�� �����˿ɶ�̬��ӵ������Ķ�����Ϊ�� 
     //����װ�������дװ�λ���ķ����� ���ڵ��ø��෽��֮ǰ��֮����ж������Ϊ��
     //����װ����A
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
     //����װ����B
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
