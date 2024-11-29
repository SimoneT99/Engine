#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include "../AbstractLocalObjectLoader.hpp"

#pragma once

class ObjLoader : public AbstractLocalObjectLoader{

    private:
        std::string path;

    public:

        ObjLoader(std::unique_ptr<AbstractLocalObjectBuilder> builder, std::string path) 
            : AbstractLocalObjectLoader(std::move(builder)), path(std::move(path)) {}
            
        std::unique_ptr<AbstractLocalObject> loadObject() override;

};