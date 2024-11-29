#include "./Observer.hpp"
#include <memory>
#include <list>

class Observable{
    private:
        std::list<std::shared_ptr<Observer>> subscribers;

    public:
        void subscribe(std::shared_ptr<Observer> subscriber);
        void unsuscribe(std::shared_ptr<Observer> subscriber);
        void notify();

};
