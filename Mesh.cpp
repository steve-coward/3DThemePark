/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "Mesh.h"
#include "ProjUtils.h"
#include "assert.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

Mesh::Mesh()
{
	nextVI = 0;
	nextFI = 0;
	nextMI = 0;
	nextNI = 0;

	numVerts = 0;
	numFaces = 0;
	numNormals = 0;
	numMaterials = 0;
	numTexCoors = 0;
	bUseTexCoors = false;
}

Mesh::~Mesh()
{
	glDeleteLists(m_dlMesh, 1);
}



void Mesh::CalcNormals()
{
	std::vector<Face>::iterator vitrf;
	std::vector<VertexID>::iterator vitri;
	Vector3 va;
	Vector3 vc;
	Vector3 vNormal;

	// for each face
	vitrf = vecFaces.begin();
	while (vitrf != vecFaces.end()) {
		vc = vecPts[vitrf->vecVert.at(0).vertIndex]-vecPts[vitrf->vecVert.at(1).vertIndex];
		va = vecPts[vitrf->vecVert.at(2).vertIndex]-vecPts[vitrf->vecVert.at(1).vertIndex];
		vNormal = va.cross(vc);
		vNormal.normalize();

		// for each index in the face
		vitri = vitrf->vecVert.begin();
		int ni = AddNormal(vNormal);
		while (vitri != vitrf->vecVert.end()) {
			(*vitri).normIndex = ni;
			++vitri;
		}
		++vitrf;
	}
}


int Mesh::AddFace()
{
	Face face;
	vecFaces.push_back(face);
	numFaces++;

	return(numFaces-1);
}
int Mesh::AddFace(int nFaceVerts, const int* vi)
{
	Face face;
	VertexID vid;
	int i;

	face.nVerts = nFaceVerts;
	face.materialIndex = -1;
	
	for (i=0;i<nFaceVerts;i++) {
		vid.normIndex = 0;
		vid.texCoorIndex = 0;
		vid.vertIndex = vi[i];
		face.vecVert.push_back(vid);
	}

	vecFaces.push_back(face);
	numFaces++;

	return(numFaces-1);
}
int Mesh::AddFace(int nFaceVerts, const int* vi, const int* vt)
{
	Face face;
	VertexID vid;
	int i;

	face.nVerts = nFaceVerts;
	face.materialIndex = -1;
	
	for (i=0;i<nFaceVerts;i++) {
		vid.normIndex = 0;
		vid.texCoorIndex = vt[i];
		vid.vertIndex = vi[i];
		face.vecVert.push_back(vid);
	}

	vecFaces.push_back(face);
	numFaces++;

	return(numFaces-1);
}

int Mesh::AddTexCoor(Vector3& vertex)
{
	vecTexCoors.push_back(vertex);
	numTexCoors++;
	return(numTexCoors-1);
}
int Mesh::AddNormal(Vector3& vertex)
{
	vecNorms.push_back(vertex);
	numNormals++;
	return(numNormals-1);
}
void Mesh::AddNormal(int nFace, const int* vi)
{
	int i;
	
	for (i=0;i<vecFaces.at(nFace).nVerts;i++) {
		vecFaces.at(nFace).vecVert[i].normIndex = vi[i];
	}
}
int Mesh::AddVertex(Vector3& vertex)
{
	vecPts.push_back(vertex);
	numVerts++;
	return(numVerts-1);
}
int Mesh::AddMaterial(const float* RGBA)
{
	Material m;

	m.RGBA[0] = RGBA[0];
	m.RGBA[1] = RGBA[1];
	m.RGBA[2] = RGBA[2];
	m.RGBA[3] = RGBA[3];
	
	vecMaterials.push_back(m);
	numMaterials++;

	return(numMaterials-1);
}



bool Mesh::Initialize()
{
	ubyte *image_data;
    int image_height, image_width;
	std::vector<VertexID>::iterator vitr;
	std::vector<Face>::iterator fitr;

    //bUseTexCoors = true;
	
	//if (bUseTexCoors) {
	//	// Load the image for the texture. The texture file has to be in
	//	// a place where it will be found.
	//	if ( ! ( image_data = (ubyte*)tga_load("woodr.tga", &image_width,
	//		&image_height, TGA_TRUECOLOR_24) ) )
	//	{
	//		fprintf(stderr, "Ground::Initialize: Couldn't load wood.tga\n");
	//		return false;
	//	}

	//	glEnable(GL_DEPTH_TEST);

	//	// This sets a parameter for how the texture is loaded and interpreted.
	//	// basically, it says that the data is packed tightly in the image array.
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//	// This creates a texture object and binds it, so the next few operations
	//	// apply to this texture.
	//	glGenTextures(1, &mesh_texture_obj);
	//	glBindTexture(GL_TEXTURE_2D, mesh_texture_obj);

	//	// This sets up the texture with high quality filtering. First it builds
	//	// mipmaps from the image data, then it sets the filtering parameters
	//	// and the wrapping parameters. We want the grass to be repeated over the
	//	// ground.
	//	gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
	//		GL_RGB, GL_UNSIGNED_BYTE, image_data);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	//		GL_NEAREST);

	//	// This says what to do with the texture. Modulate will multiply the
	//	// texture by the underlying color.
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//}

	m_dlMesh = glGenLists(1);
    glNewList(m_dlMesh, GL_COMPILE);
	
	//if (bUseTexCoors) {
	//	glEnable(GL_TEXTURE_2D);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//	glBindTexture(GL_TEXTURE_2D, mesh_texture_obj);
	//}
		
	fitr = vecFaces.begin();
	while (fitr != vecFaces.end())
	{
		glBegin(GL_POLYGON);
		
		if (numMaterials > 0) {
			if (fitr->materialIndex >= 0) {
				//glColor3f(vecMaterials.at(vecFaces[f].materialIndex).RGBA[0], vecMaterials.at(vecFaces[f].materialIndex).RGBA[1], vecMaterials.at(vecFaces[f].materialIndex).RGBA[2]);
				//glColor3f(1,0,0);
			}
		}
		vitr = fitr->vecVert.begin();
		while (vitr != fitr->vecVert.end()) {
			int in = vitr->normIndex;
			int iv = vitr->vertIndex;
			int it = vitr->texCoorIndex;

			if (bUseTexCoors) {
				glTexCoord2f(vecTexCoors[it].getGLfloatX(), vecTexCoors[it].getGLfloatY());
			}
			glNormal3fv(vecNorms[in].getGLfloat3v());
			glVertex3fv(vecPts[iv].getGLfloat3v());
			++vitr;
		}
		
		glEnd( );
		++fitr;
		//break;
	}

	//if (bUseTexCoors) {
	//	glDisable(GL_TEXTURE_2D);
	//}

	glEndList();
	
	return(true);
}

void Mesh::draw( ) // use openGL to draw this mesh
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//if (bUseTexCoors) {
	//	glEnable(GL_TEXTURE_2D);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//	glBindTexture(GL_TEXTURE_2D, mesh_texture_obj);
	//	glColor3f(1.0,1.0,1.0);
	//}

	GLfloat no_mat[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 0.5, 0.8, 1.0 };
	GLfloat high_shininess[] = { 100.0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glCallList(m_dlMesh);

	//if (bUseTexCoors) {
	//	glDisable(GL_TEXTURE_2D);
	//}
}

// to read in a filed mesh
// Currently ignores material info.
int Mesh::readFile(std::string fileName)
{
	int nVertis = 0;
	int nFaces = 0;
	int nFaceVerts = 0;
	int nVNormals = 0;
	int nFNormals = 0;
	int nFNormVerts = 0;
	int nTexCoors = 0;
	int nMaterials = 0;
	int nMaterialFacesAdded = 0;
	std::string line;
	std::string token;
	bool bInMesh = false;
	bool bInVertices = false;
	bool bInFaces = false;
	bool bFirstLine = false;
	bool bSecondLine = false;
	bool bInVNormals = false;
	bool bInFNormals = false;
	bool bInMaterials = false;
	bool bInMaterialList = false;
	bool bInTexCoors = false;

	size_t pos;
	Vector3 p3;
	int index[4]; // support triangles or quads only
	float vert[4]; // also used for RGBA

	std::ifstream myfile (fileName.c_str());
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			//std::cout << line << std::endl;

			if ((pos = line.find("//")) != std::string::npos) {
					line = line.substr(0, pos);
			}
			if ((pos = line.find("#")) != std::string::npos) {
					line = line.substr(0, pos);
			}
			
			if (line.length() == 0) {
				continue;
			}
			else if ((pos = line.find("Mesh ")) != std::string::npos) {
				bInMesh = true;
				bInVertices = true;
				bFirstLine = true;
			}
			else if (bInVertices && bFirstLine) {
				bFirstLine = false;
				pos = line.find(";");
				if (pos != std::string::npos) {
					line.erase(pos);
					nVertis = atoi(line.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
			}
			else if (bInVertices) {
				int i = 0;
				while (i < 3) {
					if ((pos = line.find(";")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						vert[i] = atof(token.c_str());
						i++;
					}
					else {
						myfile.close();
						return(1);
					}
				}
				p3 = vert;
				AddVertex(p3);
				if (nVertis == numVerts) {
					bInVertices = false;
					bInFaces = true;
					bFirstLine = true;
				}
			}


			else if (bInFaces && bFirstLine) {
				bFirstLine = false;
				pos = line.find(";");
				if (pos != std::string::npos) {
					line.erase(pos);
					nFaces = atoi(line.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
			}
			else if (bInFaces) {
				int i = 0;
				if ((pos = line.find(";")) != std::string::npos) {
					token = line.substr(0, pos);
					line = line.substr(pos+1);
					nFaceVerts = atoi(token.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
				while (i < nFaceVerts) {
					if ((pos = line.find(",")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						index[i] = atoi(token.c_str());
						i++;
					}
					else if ((pos = line.find(";")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						index[i] = atoi(token.c_str());
						i++;
					}
					else {
						myfile.close();
						return(1);
					}
				}
				AddFace(nFaceVerts, index);
				if (nFaces == numFaces) {
					bInFaces = false;
				}
			}




			else if ((pos = line.find("MeshNormals")) != std::string::npos) {
				bInVNormals = true;
				bFirstLine = true;
			}
			else if (bInVNormals && bFirstLine) {
				bFirstLine = false;
				pos = line.find(";");
				if (pos != std::string::npos) {
					line.erase(pos);
					nVNormals = atoi(line.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
			}
			else if (bInVNormals) {
				int i = 0;
				while (i < 3) {
					if ((pos = line.find(";")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						vert[i] = atof(token.c_str());
						i++;
					}
					else {
						myfile.close();
						return(1);
					}
				}
				p3 = vert;
				AddNormal(p3);
				if (nVNormals == numNormals) {
					bInVNormals = false;
					bInFNormals = true;
					bFirstLine = true;
				}
			}

			else if (bInFNormals && bFirstLine) {
				bFirstLine = false;
				pos = line.find(";");
				if (pos != std::string::npos) {
					line.erase(pos);
					//nFNormals = atoi(line.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
			}
			else if (bInFNormals) {
				int i = 0;
				if ((pos = line.find(";")) != std::string::npos) {
					token = line.substr(0, pos);
					line = line.substr(pos+1);
					nFNormVerts = atoi(token.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
				while (i < nFNormVerts) {
					if ((pos = line.find(",")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						index[i] = atoi(token.c_str());
						i++;
					}
					else if ((pos = line.find(";")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						index[i] = atoi(token.c_str());
						i++;
					}
					else {
						myfile.close();
						return(1);
					}
				}
				AddNormal(nFNormals, index);
				nFNormals++;
				if (nFNormals == numFaces) {
					bInFNormals = false;
				}
			}

			else if ((pos = line.find("MaterialList ")) != std::string::npos) {
				bInMaterialList = true;
				bFirstLine = true;
			}
			else if (bInMaterialList && bFirstLine) {
				bFirstLine = false;
				bSecondLine = true;

				int numMat = atoi(line.c_str());
				if (numMat == 0) {
					bInMaterialList = false;
					bSecondLine = false;
				}
			}
			else if (bInMaterialList && bSecondLine) {
				bFirstLine = false;
				bSecondLine = false;
			}
			else if (bInMaterialList) {
				vecFaces[nMaterialFacesAdded].materialIndex = atoi(line.c_str());
				nMaterialFacesAdded++;
				if (nMaterialFacesAdded == nFaces) {
					bInMaterialList = false;
				}
			}


			else if ((pos = line.find("Material ")) != std::string::npos) {
				bInMaterials = true;
				bFirstLine = true;
			}
			else if (bInMaterials && bFirstLine) {
				bInMaterials = false;
				bFirstLine = false;
				int i = 0;

				while (i < 4) {
					if ((pos = line.find(";")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						vert[i] = atof(token.c_str());
						i++;
					}
					else {
						myfile.close();
						return(1);
					}
				}
				AddMaterial(vert);
			}



			else if ((pos = line.find("MeshTextureCoords")) != std::string::npos) {
				bInTexCoors = true;
				bFirstLine = true;
			}
			else if (bInTexCoors && bFirstLine) {
				bFirstLine = false;
				pos = line.find(";");
				if (pos != std::string::npos) {
					line.erase(pos);
					nTexCoors = atoi(line.c_str());
				}
				else {
					myfile.close();
					return(1);
				}
			}
			else if (bInTexCoors) {
				int i = 0;
				while (i < 2) {
					if ((pos = line.find(";")) != std::string::npos) {
						token = line.substr(0, pos);
						line = line.substr(pos+1);
						vert[i] = atof(token.c_str());
						i++;
					}
					else {
						myfile.close();
						return(1);
					}
				}
				p3 = vert;
				AddTexCoor(p3);
				if (nTexCoors == numTexCoors) {
					bInTexCoors = false;
					bFirstLine = true;
				}
			}




		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl; 
	}

	return(0);
}

void Mesh::AddFace(const Vector3& va, const Vector3& vb, const Vector3& vc)
{
	Face face;
	std::vector<Vector3>::iterator result;
	VertexID vertexID;

	face.nVerts = 3;

	result = std::find( vecPts.begin(), vecPts.end(), va);
	if (result == vecPts.end()) {
		vecPts.push_back(va);
		vertexID.vertIndex = numVerts;
		numVerts++;
	}
	else {
		vertexID.vertIndex = (int)(result - vecPts.begin());
	}
	face.vecVert.push_back(vertexID);

	result = std::find( vecPts.begin(), vecPts.end(), vb);
	if (result == vecPts.end()) {
		vecPts.push_back(vb);
		vertexID.vertIndex = numVerts;
		numVerts++;
	}
	else {
		vertexID.vertIndex = (int)(result - vecPts.begin());
	}
	face.vecVert.push_back(vertexID);

	result = std::find( vecPts.begin(), vecPts.end(), vc);
	if (result == vecPts.end()) {
		vecPts.push_back(vc);
		vertexID.vertIndex = numVerts;
		numVerts++;
	}
	else {
		vertexID.vertIndex = (int)(result - vecPts.begin());
	}
	face.vecVert.push_back(vertexID);

	vecFaces.push_back(face);
	numFaces++;
}

void Mesh::Dump()
{
	std::vector<Face>::iterator vitrf;
	std::vector<VertexID>::iterator vitri;
	int i = 0;

	// for each face
	vitrf = vecFaces.begin();
	while (vitrf != vecFaces.end()) {
		//std::cout << "face " << i << "\n";
		// for each index in the face
		vitri = vitrf->vecVert.begin();
		while (vitri != vitrf->vecVert.end()) {
			std::cout << vitri->vertIndex << "\n";
			++vitri;
		}
		++vitrf;
		i++;
	}
}