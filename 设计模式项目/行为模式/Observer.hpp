#include <iostream>
#include <list>
#include <string>
//�۲���(������)�ӿ�
class IObserver {
public:
    virtual ~IObserver() {};
    //���ݷ����߸������Ϣ����
    //�������ڷ�����Ϣ���������ö����ߵ�Update����
    virtual void Update(const std::string& message_from_subject) = 0;
};
//����(������)�ӿ�
class ISubject {
public:
    virtual ~ISubject() {};
    //ע�ᶩ����
    virtual void Attach(IObserver* observer) = 0;
    //ע��������
    virtual void Detach(IObserver* observer) = 0;
    //֪ͨ������
    virtual void Notify() = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */
//����(������)��
class Subject : public ISubject {
private:
    std::list<IObserver*> list_observer_;//�۲���(������)����
    std::string message_;
public:
    virtual ~Subject() {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    
    void Attach(IObserver* observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver* observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }
    //��������Ϣ��������
    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

    /**
     * Usually, the subscription logic is only a fraction of what a Subject can
     * really do. Subjects commonly hold some important business logic, that
     * triggers a notification method whenever something important is about to
     * happen (or after it).
     */
    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }
};
//�۲���(������)��
class Observer : public IObserver {
private:
    std::string message_from_subject_;//�����߷�������Ϣ
    Subject& subject_;//��ע�ķ�����
    static int static_number_;//�����ߵľ�̬ȫ������
    int number_;
public:
    Observer(Subject& subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    //ȡ������
    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    }


};
int Observer::static_number_ = 0;
void ObserverModle_test() {
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}
