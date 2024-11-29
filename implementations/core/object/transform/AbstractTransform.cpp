#include "../headers/core/object/transform/AbstractTransform.hpp"

AbstractTransform::operator std::string() const{

    std::ostringstream oss;

    oss << "Translation matrix:\n";
    oss << this->print_translation() << std::endl;
    oss << "Rotation Matrix:\n";
    oss << this->print_rotation() << std::endl;
    oss << "Scaling Matrix:\n";
    oss << this->print_scaling() << std::endl;
    oss << "Model Matrix:\n";
    oss << this->print_model_matrix() << std::endl;

    // Return the constructed string
    return oss.str();

}