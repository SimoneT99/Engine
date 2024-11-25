#include "headers\legacy\Object.hpp"

//Constructors

Object::Object(){
    this->vertexes = new std::map<int, Vertex>();
    this->faces = new std::list<std::tuple<int, int, int>>();
}

Object::Object(const std::list<Vertex>& vertexes) : Object(){

    int key = 1; 
    //we iterate on the iterator
    for(std::list<Vertex>::const_iterator iterator = vertexes.cbegin();
        iterator != vertexes.cend();
        ++iterator) //faster
    {
        this->vertexes->insert({key, *iterator});
        key++;
    }
}


Object::Object(const std::list<Vertex>& vertexes, const std::list<std::tuple<int, int, int>>& faces): Object(vertexes){

    for(std::list<std::tuple<int, int, int>>::const_iterator iterator = faces.cbegin();
        iterator != faces.cend();
        ++iterator){
            this->faces->push_back(*iterator); 
        }

}

Object::Object(const Object& other) : Object(){

    //we need to manually insert the values of the other map
    for(std::map<int, Vertex>::const_iterator iterator = other.vertexes->cbegin();
    iterator != other.vertexes->cend();
    ++iterator
    ){
        this->vertexes->insert(*iterator);
    }

    //we need to manually insert the values of the other edges
    for(std::list<std::tuple<int,int,int>>::const_iterator iterator = other.faces->cbegin();
    iterator != other.faces->cend();
    ++iterator
    ){
        this->faces->push_back(*iterator);
    }
}

Object& Object::operator=(Object& other){

    if(this == &other){
        return *this;
    }

    delete(this->vertexes);
    delete(this->faces);

    this->vertexes = other.vertexes;
    this->faces = other.faces;

    other.vertexes = nullptr;
    other.faces = nullptr;

    return *this;
}



Object::~Object(){
    delete(this->faces);
    delete(this->vertexes);
}


