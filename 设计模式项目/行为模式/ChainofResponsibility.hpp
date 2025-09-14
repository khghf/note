#pragma once
/**
 * The Handler interface declares a method for building the chain of handlers.
 * It also declares a method for executing a request.
 * Handler接口声明了一个构建责任链的方法以及另一个执行请求的方法
 */
//处理者
class Handler {
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};
/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
//基础处理者实现了处理者的共有行为
class AbstractHandler : public Handler {
private:
    Handler* next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {
    }
    Handler* SetNext(Handler* handler) override {
        this->next_handler_ = handler;
        // Returning a handler from here will let us link handlers in a convenient
        // way like this:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }
    std::string Handle(std::string request) override {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};
/**
 * All Concrete Handlers either handle a request or pass it to the next handler
 * in the chain.
 * 所有具体的处理者要么处理请求要么把请求传递给责任链上的下一个处理者
 */
//具体处理者猴子
class MonkeyHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
//具体处理者松鼠
class SquirrelHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
//具体处理者狗
class DogHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
/**
 * The client code is usually suited to work with a single handler. In most
 * cases, it is not even aware that the handler is part of a chain.
 */
void ClientCode(Handler& handler) {
    std::vector<std::string> food = { "Nut", "Banana", "Cup of coffee" };
    for (const std::string& f : food) {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        }
        else {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}
void ChainofResponsibility_test()
{
    MonkeyHandler* monkey = new MonkeyHandler;
    SquirrelHandler* squirrel = new SquirrelHandler;
    DogHandler* dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);
    /**
     * The client should be able to send a request to any handler, not just the
     * first one in the chain.
     */
    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;
}
