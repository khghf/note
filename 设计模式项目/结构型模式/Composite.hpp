#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
/**
 * The base Component class declares common operations for both simple and
 * complex objects of a composition.
 * 基础组件类为组合树上的简单、复杂对象声明了通用操作
 */
//组件 （Component） 接口描述了树中简单项目和复杂项目所共有的操作。
class Component {
    /**
     * @var Component
     */
protected:
    Component* parent_;
public:
    virtual ~Component() {}
    void SetParent(Component* parent) {
        this->parent_ = parent;
    }
    Component* GetParent() const {
        return this->parent_;
    }
    //添加到组合树
    virtual void Add(Component* component) {}
    //从组合树移除
    virtual void Remove(Component* component) {}
    //是否为组合树的一部分
    virtual bool IsComposite() const {
        return false;
    }
    virtual std::string Operation() const = 0;
};
/**
 * The Leaf class represents the end objects of a composition. A leaf can't have
 * any children.
 *
 * Usually, it's the Leaf objects that do the actual work, whereas Composite
 * objects only delegate to their sub-components.
 */

//叶节点 （Leaf） 是树的基本结构， 它不包含子项目。
//一般情况下， 叶节点最终会完成大部分的实际工作， 因为它们无法将工作指派给其他部分。
class Leaf : public Component {
public:
    std::string Operation() const override {
        return "Leaf";
    }
};
/**
 * The Composite class represents the complex components that may have children.
 * Usually, the Composite objects delegate the actual work to their children and
 * then "sum-up" the result.
 * Composite 类表示可能具有子项的复杂组件。
 * 通常，Composite 对象将实际工作委托给其子对象，然后对结果进行“求和”。
 */
class Composite : public Component {
protected:
    std::list<Component*> children_;
public:
   
    void Add(Component* component) override {
        this->children_.push_back(component);
        component->SetParent(this);
    }
    void Remove(Component* component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool IsComposite() const override {
        return true;
    }
    std::string Operation() const override {
        std::string result;
        for (const Component* c : children_) {
            if (c == children_.back()) {
                result += c->Operation();
            }
            else {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};
/**
 * The client code works with all of the components via the base interface.
 */
void ClientCode(Component* component) {
    // ...
    std::cout << "RESULT: " << component->Operation();
    // ...
}

/**
 * Thanks to the fact that the child-management operations are declared in the
 * base Component class, the client code can work with any component, simple or
 * complex, without depending on their concrete classes.
 */
void ClientCode2(Component* component1, Component* component2) {
    // ...
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    std::cout << "RESULT: " << component1->Operation();
    // ...
}

void Composite_test()
{
    Component* simple = new Leaf;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);

    Component* tree = new Composite;
    Component* branch1 = new Composite;

    Component* leaf_1 = new Leaf;
    Component* leaf_2 = new Leaf;
    Component* leaf_3 = new Leaf;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component* branch2 = new Composite;
    branch2->Add(leaf_3);
    tree->Add(branch1);
    tree->Add(branch2);
    std::cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    std::cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
}

