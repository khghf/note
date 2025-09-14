#include<iostream>
/**
 * The Command interface declares a method for executing a command.
 * Command接口声明了执行命令的方法
 */
//抽象命令基类(接口)
class Command {
public:
    virtual ~Command() {
    }
    virtual void Execute() const = 0;
};
/**
 * Some commands can implement simple operations on their own.
 */
//实现了简单操作的命令
class SimpleCommand : public Command {
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {
    }
    void Execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
    }
};

/**
 * The Receiver classes contain some important business logic. They know how to
 * perform all kinds of operations, associated with carrying out a request. In
 * fact, any class may serve as a Receiver.
 */
//接受者，包含部分业务逻辑
class Receiver {
public:
    void DoSomething(const std::string& a) {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }
    void DoSomethingElse(const std::string& b) {
        std::cout << "Receiver: Also working on (" << b << ".)\n";
    }
};

/**
 * However, some commands can delegate more complex operations to other objects,
 * called "receivers."
 */
//复杂命令
class ComplexCommand : public Command {
    /**
     * @var Receiver
     */
private:
    Receiver* receiver_;
    /**
     * Context data, required for launching the receiver's methods.
     */
    std::string a_;
    std::string b_;
    /**
     * Complex commands can accept one or several receiver objects along with any
     * context data via the constructor.
     */
public:
    ComplexCommand(Receiver* receiver, std::string a, std::string b) : receiver_(receiver), a_(a), b_(b) {
    }
    /**
     * Commands can delegate to any methods of a receiver.
     */
    void Execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};

/**
 * The Invoker is associated with one or several commands. It sends a request to
 * the command.
 * Invoker存储一个或多个命令的引用，它发送请求给命令
 */
//触发者
class Invoker {
    /**
     * @var Command
     */
private:
    Command* on_start_;
    /**
     * @var Command
     */
    Command* on_finish_;
    /**
     * Initialize commands.
     */
public:
    ~Invoker() {
        delete on_start_;
        delete on_finish_;
    }

    void SetOnStart(Command* command) {
        this->on_start_ = command;
    }
    void SetOnFinish(Command* command) {
        this->on_finish_ = command;
    }
    /**
     * The Invoker does not depend on concrete command or receiver classes. The
     * Invoker passes a request to a receiver indirectly, by executing a command.
     */
    void DoSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};
/**
 * The client code can parameterize an invoker with any commands.
 */
void Command_test()
{
    Invoker* invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver* receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
}
