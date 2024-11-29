#include "../AbstractLocalObject.hpp"
#include "../AbstractLocalObjectBuilder.hpp"
#include <memory>

#pragma once

class AbstractLocalObjectLoader{

    protected:
        std::unique_ptr<AbstractLocalObjectBuilder> abstractObjectBuilder; //we assure the ownership

    public:

        AbstractLocalObjectLoader(std::unique_ptr<AbstractLocalObjectBuilder> builder) : abstractObjectBuilder(std::move(builder)){};
        virtual std::unique_ptr<AbstractLocalObject> loadObject() = 0;

};