#include "../headers/object/loader/concreteLoaders/ObjLoader.hpp"

/**
 * Concrete implementationo of the .obj loader
 */
std::unique_ptr<AbstractObject> ObjLoader::loadObject()
{

    this->abstractObjectBuilder->clean();

    std::ifstream file = std::ifstream(this->path); // stack is faster

    if (!file.is_open())
    {
        std::cerr << "Impossibile aprire il file: " << this->path << std::endl;
        return nullptr;
    }

    std::string line;

    int faces_number = 0; // we need to keep track of the index of the faces!

    while (std::getline(file, line))
    { // Leggi il file riga per riga

        std::istringstream stream = std::istringstream(line);
        std::string prefix;
        stream >> prefix; // Ottieni il primo elemento della riga

        if (prefix == "v")
        { // Vertice
            float x, y, z;
            stream >> x >> y >> z;
            this->abstractObjectBuilder->add_vertex(glm::vec4(x, y, z, 1));
        }

        else if (prefix == "vn")
        { // Normale
            // we ignore this for now
            float nx, ny, nz;
            stream >> nx >> ny >> nz;
            this->abstractObjectBuilder->add_normal(glm::vec3(nx, ny, nz));
        }

        else if (prefix == "f")
        { // Faccia
            // Parsing delle facce
            int v1 = 0, v2 = 0, v3 = 0;
            int normal_index = 0;

            std::string token = stream.str();

            int vertex_index = 0;

            while (stream >> token)
            {
            
                int v = 0, vt = 0, vn = 0;

                std::replace(token.begin(), token.end(), '/', ' '); // Sostituisce '/' con ' '
                
                std::istringstream tokenStream(token);

                tokenStream >> v; // Indice del vertice

                if (tokenStream.peek() == ' ')
                {
                    tokenStream.ignore();
                } // Ignora separatori

                if (tokenStream >> vt)
                { // Indice della texture (non usato qui)

                    if (tokenStream.peek() == ' ')
                    {
                        tokenStream.ignore();
                    }

                    tokenStream >> vn; // Indice della normale
                }

                // We have everything we need
                switch (vertex_index)
                {
                case 0:
                    v1 = v;
                    break;
                case 1:
                    v2 = v;
                    break;
                case 2:
                    v3 = v;
                    break;
                default:
                    throw std::runtime_error("Number of vertexes not supported! make sure the model use max 3 vertexes per face!");
                    break;
                }

                if (vertex_index == 0)
                {
                    normal_index = vn;
                }

                vertex_index++;
            }

            this->abstractObjectBuilder->add_face(std::tuple<int, int, int>(v1-1, v2-1, v3-1));
            this->abstractObjectBuilder->add_face_normal_mapping(std::tuple<int, int>(faces_number, normal_index - 1));

            faces_number++;
        }
    }

    file.close(); // Chiudi il file
    return this->abstractObjectBuilder->get_object();
}