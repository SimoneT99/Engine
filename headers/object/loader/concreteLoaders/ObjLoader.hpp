#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include "../AbstractLoader.hpp"


class ObjLoader : public AbstractLoader{

    private:
        std::string path;

    public:

        ObjLoader(std::unique_ptr<AbstractObjectBuilder> builder, std::string path) 
            : AbstractLoader(std::move(builder)), path(std::move(path)) {}
            
        std::unique_ptr<AbstractObject> loadObject() override;

};