#pragma once
#include<iostream>
#include<vector>
/**
 * It makes sense to use the Builder pattern only when your products are quite
 * complex and require extensive configuration.
 * 只有在你的产品非常复杂且有很多配置时使用生成器模式才有意义
 * Unlike in other creational patterns, different concrete builders can produce
 * unrelated products. In other words, results of various builders may not
 * always follow the same interface.
 * 与其它的创建型模式不同，不同的具体生成器可以生产没有关联的产品，总而言之，不同的生成器
 * 不总是有着一样的接口
 */
//产品类1
class Product1 {
public:
    std::vector<std::string> parts_;//组成部件
    void ListParts()const {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            }
            else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


/**
 * The Builder interface specifies methods for creating the different parts of
 * the Product objects.
 * Builder 接口指定了创建 Product 对象的不同部分的方法。
 */
//抽象生成器接口类
class Builder {
public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};
/**
 * The Concrete Builder classes follow the Builder interface and provide
 * specific implementations of the building steps. Your program may have several
 * variations of Builders, implemented differently.
 * Concrete Builder 类遵循 Builder 接口，并提供构建步骤的特定实现。
 * 您的程序可能有多种 Builder 变体，它们的实现方式不同。
 */
//具体生成器1
class ConcreteBuilder1 : public Builder {
private:

    Product1* product;

    /**
     * A fresh builder instance should contain a blank product object, which is
     * used in further assembly.
     */
public:

    ConcreteBuilder1() {
        this->Reset();
    }

    ~ConcreteBuilder1() {
        delete product;
    }

    void Reset() {
        this->product = new Product1();
    }
    /**
     * All production steps work with the same product instance.
     */

    void ProducePartA()const override {
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB()const override {
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC()const override {
        this->product->parts_.push_back("PartC1");
    }

    /**
     * Concrete Builders are supposed to provide their own methods for
     * retrieving results. That's because various types of builders may create
     * entirely different products that don't follow the same interface.
     * Therefore, such methods cannot be declared in the base Builder interface
     * (at least in a statically typed programming language). Note that PHP is a
     * dynamically typed language and this method CAN be in the base interface.
     * However, we won't declare it there for the sake of clarity.
     * 
     * Concrete Builders 应该提供自己的方法来检索结果。
     * 这是因为各种类型的构建器可能会创建完全不同的产品，
     * 这些产品没有继承相同的接口(基类)。因此，此类方法不能在 base Builder 接口中声明
     * (至少在静态类型的编程语言中)。请注意，PHP 是一种动态类型的语言，
     * 此方法可以在基本接口中。但是，为了清楚起见，我们不会在那里声明它。
     * 
     * Usually, after returning the end result to the client, a builder instance
     * is expected to be ready to start producing another product. That's why
     * it's a usual practice to call the reset method at the end of the
     * `getProduct` method body. However, this behavior is not mandatory, and
     * you can make your builders wait for an explicit reset call from the
     * client code before disposing of the previous result.
     * 
     * 通常，在将最终结果返回给客户端后，构建器实例应该准备好开始生产另一个产品。
     * 这就是为什么通常的做法是在 'getProduct' 方法主体的末尾调用 reset 方法。
     * 但是，此行为不是强制性的，您可以让生成器等待客户端代码的显式 reset 调用，
     * 然后再处理以前的结果。
     */

     /**
      * Please be careful here with the memory ownership. Once you call
      * GetProduct the user of this function is responsable to release this
      * memory. Here could be a better option to use smart pointers to avoid
      * memory leaks
      * 
      * 请在此处小心内存所有权。
      * 调用 GetProduct 后，此函数的用户负责释放此内存。
      * 在这里使用智能指针来避免内存泄漏是更好选择
      */

    Product1* GetProduct() {
        Product1* result = this->product;
        this->Reset();
        return result;
    }
};

/**
 * The Director is only responsible for executing the building steps in a
 * particular sequence. It is helpful when producing products according to a
 * specific order or configuration. Strictly speaking, the Director class is
 * optional, since the client can control builders directly.
 * 
 * Director 仅负责按特定顺序执行构建步骤。
 * 在根据特定订单或配置生产产品时，它很有帮助。
 * 严格来说，Director 类是可选的，因为客户端可以直接控制构建器。
 */
//主管类
class Director {
    /**
     * @var Builder
     */
private:
    Builder* builder;
    /**
     * The Director works with any builder instance that the client code passes
     * to it. This way, the client code may alter the final type of the newly
     * assembled product.
     * 控制器 （Director） 适用于客户端代码传递给它的任何生成器实例。
     * 这样，客户端代码可能会更改新组装产品的最终类型。
     */

public:

    void set_builder(Builder* builder) {
        this->builder = builder;
    }

    /**
     * The Director can construct several product variations using the same
     * building steps.
     * 主管可以用相同的步骤来构建多种产品变体
     */

    void BuildMinimalViableProduct() {
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedProduct() {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};
/**
 * The client code creates a builder object, passes it to the director and then
 * initiates the construction process. The end result is retrieved from the
 * builder object.
 * 
 * 客户端代码创建一个 builder 对象，将其传递给 director，
 * 然后启动构建过程。最终结果从builder对象处返回
 */
 /**
  * I used raw pointers for simplicity however you may prefer to use smart
  * pointers here
  */
void ClientCode(Director& director)
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();

    Product1* p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();

    p = builder->GetProduct();
    p->ListParts();
    delete p;

    // Remember, the Builder pattern can be used without a Director class.
    //记住，生成器模式可以不需要主管类
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}
void Builder_test()
{
    Director* director = new Director();
    ClientCode(*director);
    delete director;
}

