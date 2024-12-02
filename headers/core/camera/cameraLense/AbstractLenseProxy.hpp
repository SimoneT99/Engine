#include "./AbstractLense.hpp"
#include <memory>

class AbstractLenseProxy : public AbstractLense{

    protected:
        std::shared_ptr<AbstractLense> abstract_lense;

    public:
        AbstractLenseProxy(std::shared_ptr<AbstractLense> abstract_lense) :
            abstract_lense(std::move(abstract_lense)) {}
};