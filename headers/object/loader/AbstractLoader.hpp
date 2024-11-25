#include "../AbstractObject.hpp"
#include "../AbstractObjectBuilder.hpp"
#include <memory>

#pragma once

class AbstractLoader{

    protected:
        std::unique_ptr<AbstractObjectBuilder> abstractObjectBuilder; //we assure the ownership

    public:

        AbstractLoader(std::unique_ptr<AbstractObjectBuilder> builder) : abstractObjectBuilder(std::move(builder)){};
        virtual std::unique_ptr<AbstractObject> loadObject() = 0;

};