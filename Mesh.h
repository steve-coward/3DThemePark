#ifndef _MESH_H_
#define _MESH_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include <fl/math.h>
#include "ProjUtils.h"
#include "Vector3.h"
#include "libtarga.h"
#include <list>
#include <vector>

// ############### Material ######################
class Material {
public:
	GLfloat RGBA[4];
};

// ############### Vertex ID ######################
class VertexID {
public:
	int vertIndex; // index into vecPts
	int normIndex; // index into vecNorms
	int texCoorIndex; // index into vecTexCoor
};

// ############### Face ######################
class Face {
public:
	int nVerts; // number of vertices in this face
	std::vector<VertexID> vecVert; // the list of face vertices
	int materialIndex; // index into vecMaterials
	Face( ) { nVerts = 0;} // constructor
	~Face( ) { nVerts = 0; }; // destructor
};

// ############### Mesh ######################
class Mesh {
public:
	int nextVI;
	int numVerts; // number of vertices in the mesh
	std::vector<Vector3> vecPts; // array of 3D vertices

	int nextNI;
	int numNormals; // number of normal vertices for the mesh
	std::vector<Vector3> vecNorms; // array of normals
	
	int nextFI;
	int numFaces; // number of faces in the mesh
	std::vector<Face> vecFaces; // array of face data
	
	int nextMI;
	int numMaterials;
	std::vector<Material> vecMaterials; // array of material data

	std::vector<Vector3> vecTexCoors; // array of texture coordinates
	int numTexCoors; // number of texture coordinates in the mesh
	
	bool bUseTexCoors;

	//GLuint mesh_texture_obj; // The object for the texture.
	GLubyte m_dlMesh;

public:
	// Constructor
	Mesh();

	// Destructor
	~Mesh(void);

	void draw();
	bool Initialize();
	int AddFace();
	void AddFace(const Vector3& va, const Vector3& vb, const Vector3& vc);
	int AddFace(int nFaceVerts, const int* vi);
	int AddFace(int nFaceVerts, const int* vi, const int* vt);
	void removeFace(int fi);
	int AddVertex(Vector3& vertex);
	int AddNormal(Vector3& vertex);
	void AddNormal(int nFace, const int* vi);
	int AddMaterial(const float* RGBA);
	int AddTexCoor(Vector3& vertex);
	void Dump();

	void CalcNormals();

	int readFile(std::string fileName); // to read in a filed mesh
};

#endif // _MESH_H_