#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <iostream>

namespace ecoli{


enum TypeMesh{
    GRID    //!< Grid "verical and orizontal"
};

template<std::size_t dimS>
class Mesh
{
    public:
        Mesh();
        virtual ~Mesh();
    protected:

        int typeMesh;   //!< Type of mesh we are using




    private:
};

}
#endif // MESH_H
