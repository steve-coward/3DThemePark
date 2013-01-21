Material RedMaterial {
1.000000;0.000000;0.000000;1.000000;;    // R = 1.0, G = 0.0, B = 0.0
0.000000;
0.000000;0.000000;0.000000;;
0.000000;0.000000;0.000000;;
}
Material GreenMaterial {
0.000000;1.000000;0.000000;1.000000;;     // R = 0.0, G = 1.0, B = 0.0
0.000000;
0.000000;0.000000;0.000000;;
0.000000;0.000000;0.000000;;
}
// Define a mesh with 8 vertices and 12 faces (triangles). Use 
// optional data objects in the mesh to specify materials, normals,
// and texture coordinates.
Mesh CubeMesh {
8;                                // 8 vertices
5.000000;5.000000;-5.000000;,     // vertex 0
-5.000000;5.000000;-5.000000;,    // vertex 1
-5.000000;5.000000;5.000000;,     // etc...
5.000000;5.000000;5.000000;,
5.000000;-5.000000;-5.000000;,
-5.000000;-5.000000;-5.000000;,
-5.000000;-5.000000;5.000000;,
5.000000;-5.000000;5.000000;;

12;                      // 12 faces
3;0,1,2;,                // face 0 has 3 vertices
3;0,2,3;,                // etc...
3;0,4,5;,
3;0,5,1;,
3;1,5,6;,
3;1,6,2;,
3;2,6,7;,
3;2,7,3;,
3;3,7,4;,
3;3,4,0;,
3;4,7,6;,
3;4,6,5;;

// All required data has been defined. Now define optional data
// using the hierarchical nature of the file format.
MeshMaterialList {
2;                    // Number of materials used
12;                   // A material for each face
0,                    // face 0 uses the first
0,                    // material
0,
0,
0,
0,
0,
0,
1,                    // face 8 uses the second
1,                    // material
1,
1;;
{RedMaterial}         // References to the definitions
{GreenMaterial}       // of material 0 and 1
}
MeshNormals {
8;                    // define 8 normals
0.577;0.577;-0.577;,
-0.577;0.577;-0.577;,
-0.577;0.577;0.577;,
0.577;0.577;0.577;,
0.577;-0.577;-0.577;,
-0.577;-0.577;-0.577;,
-0.577;-0.577;0.577;,
0.577;-0.577;0.577;;
12;                   // For the 12 faces,
3;0,1,2;,             // define the normals
3;0,2,3;,
3;0,4,5;,
3;0,5,1;,
3;1,5,6;,
3;1,6,2;,
3;2,6,7;,
3;2,7,3;,
3;3,7,4;,
3;3,4,0;,
3;4,7,6;,
3;4,6,5;;
}
MeshTextureCoords {
8;                        // Define texture coords
0.000000;1.000000;        // for each of the vertices
1.000000;1.000000;
0.000000;1.000000;
1.000000;1.000000;
0.000000;0.000000;
1.000000;0.000000;
0.000000;0.000000;
1.000000;0.000000;;
}
}

