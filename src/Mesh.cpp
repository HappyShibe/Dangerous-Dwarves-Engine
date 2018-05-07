#include "Mesh.h"

Mesh::Mesh()
{
    //ctor
}

Mesh::~Mesh()
{
    //dtor
}

Mesh::Mesh(const Mesh& other)
{
    //copy ctor
}

Mesh& Mesh::operator=(const Mesh& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
