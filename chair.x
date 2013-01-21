xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

Frame RootFrame {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,-1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
  Frame Plane {

    FrameTransformMatrix {
      1.000000,0.000000,-0.000000,0.000000,
      0.000000,1.000000,0.007100,0.000000,
      0.000000,-0.007100,1.000000,0.000000,
      124.119000,-73.471400,0.000000,1.000000;;
    }
Mesh {
316;
6.000000; -6.000000; -16.999900;,
4.000000; -6.000000; -16.999900;,
4.000000; -8.000000; -16.999900;,
6.000000; -8.000000; -16.999900;,
-6.000000; -8.000000; -16.999900;,
-4.000000; -8.000000; -16.999900;,
-4.000000; -6.000000; -16.999900;,
-6.000000; -6.000000; -16.999900;,
-6.000000; 2.000000; -16.999900;,
-4.000000; 2.000000; -16.999900;,
-4.000000; 4.000000; -16.999900;,
-6.000000; 4.000000; -16.999900;,
4.000000; 2.000000; -16.999900;,
6.000000; 2.000000; -16.999900;,
6.000000; 4.000000; -16.999900;,
4.000000; 4.000000; -16.999900;,
6.000000; 2.000000; -16.999900;,
4.000000; 2.000000; -16.999900;,
4.000000; 2.000000; -1.999900;,
6.000000; 2.000000; -1.999900;,
6.000000; 4.000000; -16.999900;,
6.000000; 2.000000; -16.999900;,
6.000000; 2.000000; -1.999900;,
6.000000; 4.000000; -1.999900;,
4.000000; 4.000000; -16.999900;,
6.000000; 4.000000; -16.999900;,
6.000000; 4.000000; -1.999900;,
4.000000; 4.000000; -1.999900;,
4.000000; 2.000000; -16.999900;,
4.000000; 4.000000; -16.999900;,
4.000000; 4.000000; -1.999900;,
4.000000; 2.000000; -1.999900;,
-6.000000; 2.000000; -16.999900;,
-6.000000; 4.000000; -16.999900;,
-6.000000; 4.000000; -1.999900;,
-6.000000; 2.000000; -1.999900;,
-6.000000; 4.000000; -16.999900;,
-4.000000; 4.000000; -16.999900;,
-4.000000; 4.000000; -1.999900;,
-6.000000; 4.000000; -1.999900;,
-4.000000; 4.000000; -16.999900;,
-4.000000; 2.000000; -16.999900;,
-4.000000; 2.000000; -1.999900;,
-4.000000; 4.000000; -1.999900;,
-4.000000; 2.000000; -16.999900;,
-6.000000; 2.000000; -16.999900;,
-6.000000; 2.000000; -1.999900;,
-4.000000; 2.000000; -1.999900;,
-4.000000; -8.000000; -16.999900;,
-6.000000; -8.000000; -16.999900;,
-6.000000; -8.000000; -1.999900;,
-4.000000; -8.000000; -1.999900;,
-4.000000; -6.000000; -16.999900;,
-4.000000; -8.000000; -16.999900;,
-4.000000; -8.000000; -1.999900;,
-4.000000; -6.000000; -1.999900;,
-6.000000; -6.000000; -16.999900;,
-4.000000; -6.000000; -16.999900;,
-4.000000; -6.000000; -1.999900;,
-6.000000; -6.000000; -1.999900;,
-6.000000; -8.000000; -16.999900;,
-6.000000; -6.000000; -16.999900;,
-6.000000; -6.000000; -1.999900;,
-6.000000; -8.000000; -1.999900;,
4.000000; -8.000000; -16.999900;,
4.000000; -6.000000; -16.999900;,
4.000000; -6.000000; -1.999900;,
4.000000; -8.000000; -1.999900;,
4.000000; -6.000000; -16.999900;,
6.000000; -6.000000; -16.999900;,
6.000000; -6.000000; -1.999900;,
4.000000; -6.000000; -1.999900;,
6.000000; -6.000000; -16.999900;,
6.000000; -8.000000; -16.999900;,
6.000000; -8.000000; -1.999900;,
6.000000; -6.000000; -1.999900;,
6.000000; -8.000000; -16.999900;,
4.000000; -8.000000; -16.999900;,
4.000000; -8.000000; -1.999900;,
6.000000; -8.000000; -1.999900;,
4.000000; 4.000000; -1.999900;,
-4.000000; 4.000000; -1.999900;,
-4.000000; 4.000000; 0.000100;,
4.000000; 4.000000; 0.000100;,
-6.000000; -6.000000; -1.999900;,
-6.000000; 2.000000; -1.999900;,
-6.000000; 2.000000; 0.000100;,
-6.000000; -6.000000; 0.000100;,
-4.000000; -8.000000; -1.999900;,
4.000000; -8.000000; -1.999900;,
4.000000; -8.000000; 0.000100;,
-4.000000; -8.000000; 0.000100;,
6.000000; -6.000000; -1.999900;,
6.000000; 2.000000; -1.999900;,
6.000000; 2.000000; 0.000100;,
6.000000; -6.000000; 0.000100;,
6.000000; -8.000000; -1.999900;,
4.000000; -8.000000; -1.999900;,
4.000000; -8.000000; 0.000100;,
6.000000; -8.000000; 0.000100;,
6.000000; -6.000000; -1.999900;,
6.000000; -8.000000; -1.999900;,
6.000000; -8.000000; 0.000100;,
6.000000; -6.000000; 0.000100;,
-6.000000; -8.000000; -1.999900;,
-6.000000; -6.000000; -1.999900;,
-6.000000; -6.000000; 0.000100;,
-6.000000; -8.000000; 0.000100;,
-4.000000; -8.000000; -1.999900;,
-6.000000; -8.000000; -1.999900;,
-6.000000; -8.000000; 0.000100;,
-4.000000; -8.000000; 0.000100;,
-6.000000; 4.000000; -1.999900;,
-4.000000; 4.000000; -1.999900;,
-4.000000; 4.000000; 0.000100;,
-6.000000; 4.000000; 0.000100;,
-6.000000; 2.000000; -1.999900;,
-6.000000; 4.000000; -1.999900;,
-6.000000; 4.000000; 0.000100;,
-6.000000; 2.000000; 0.000100;,
4.000000; 4.000000; -1.999900;,
6.000000; 4.000000; -1.999900;,
6.000000; 4.000000; 0.000100;,
4.000000; 4.000000; 0.000100;,
6.000000; 4.000000; -1.999900;,
6.000000; 2.000000; -1.999900;,
6.000000; 2.000000; 0.000100;,
6.000000; 4.000000; 0.000100;,
4.000000; -6.000000; 0.000100;,
4.000000; 2.000000; 0.000100;,
-4.000000; 2.000000; 0.000100;,
-4.000000; -6.000000; 0.000100;,
4.000000; 2.000000; 0.000100;,
4.000000; 4.000000; 0.000100;,
-4.000000; 4.000000; 0.000100;,
-4.000000; 2.000000; 0.000100;,
-6.000000; 2.000000; 0.000100;,
-4.000000; 2.000000; 0.000100;,
-4.000000; -6.000000; 0.000100;,
-6.000000; -6.000000; 0.000100;,
-4.000000; -8.000000; 0.000100;,
4.000000; -8.000000; 0.000100;,
4.000000; -6.000000; 0.000100;,
-4.000000; -6.000000; 0.000100;,
4.000000; 2.000000; 0.000100;,
4.000000; -6.000000; 0.000100;,
6.000000; -6.000000; 0.000100;,
6.000000; 2.000000; 0.000100;,
4.000000; -6.000000; 0.000100;,
6.000000; -6.000000; 0.000100;,
6.000000; -8.000000; 0.000100;,
4.000000; -8.000000; 0.000100;,
-6.000000; -6.000000; 0.000100;,
-4.000000; -6.000000; 0.000100;,
-4.000000; -8.000000; 0.000100;,
-6.000000; -8.000000; 0.000100;,
6.000000; 2.000000; 0.000100;,
4.000000; 2.000000; 0.000100;,
4.000000; 2.000000; 5.000100;,
6.000000; 2.000000; 5.000100;,
-4.000000; 2.000000; 0.000100;,
-6.000000; 2.000000; 0.000100;,
-6.000000; 2.000000; 5.000100;,
-4.000000; 2.000000; 5.000100;,
-4.000000; 4.000000; 0.000100;,
-4.000000; 2.000000; 0.000100;,
-4.000000; 2.000000; 5.000100;,
-4.000000; 4.000000; 5.000100;,
4.000000; 2.000000; 0.000100;,
4.000000; 4.000000; 0.000100;,
4.000000; 4.000000; 5.000100;,
4.000000; 2.000000; 5.000100;,
6.000000; 4.000000; 0.000100;,
6.000000; 2.000000; 0.000100;,
6.000000; 2.000000; 5.000100;,
6.000000; 4.000000; 5.000100;,
4.000000; 4.000000; 0.000100;,
6.000000; 4.000000; 0.000100;,
6.000000; 4.000000; 5.000100;,
4.000000; 4.000000; 5.000100;,
-6.000000; 2.000000; 0.000100;,
-6.000000; 4.000000; 0.000100;,
-6.000000; 4.000000; 5.000100;,
-6.000000; 2.000000; 5.000100;,
-6.000000; 4.000000; 0.000100;,
-4.000000; 4.000000; 0.000100;,
-4.000000; 4.000000; 5.000100;,
-6.000000; 4.000000; 5.000100;,
-6.000000; 4.000000; 5.000100;,
-4.000000; 4.000000; 5.000100;,
-4.000000; 4.000000; 7.000100;,
-6.000000; 4.000000; 7.000100;,
-6.000000; 2.000000; 5.000100;,
-6.000000; 4.000000; 5.000100;,
-6.000000; 4.000000; 7.000100;,
-6.000000; 2.000000; 7.000100;,
4.000000; 4.000000; 5.000100;,
6.000000; 4.000000; 5.000100;,
6.000000; 4.000000; 7.000100;,
4.000000; 4.000000; 7.000100;,
6.000000; 4.000000; 5.000100;,
6.000000; 2.000000; 5.000100;,
6.000000; 2.000000; 7.000100;,
6.000000; 4.000000; 7.000100;,
-4.000000; 2.000000; 5.000100;,
-6.000000; 2.000000; 5.000100;,
-6.000000; 2.000000; 7.000100;,
-4.000000; 2.000000; 7.000100;,
6.000000; 2.000000; 5.000100;,
4.000000; 2.000000; 5.000100;,
4.000000; 2.000000; 7.000100;,
6.000000; 2.000000; 7.000100;,
6.000000; 2.000000; 7.000100;,
4.000000; 2.000000; 7.000100;,
4.000000; 2.000000; 12.000100;,
6.000000; 2.000000; 12.000100;,
-4.000000; 2.000000; 7.000100;,
-6.000000; 2.000000; 7.000100;,
-6.000000; 2.000000; 12.000100;,
-4.000000; 2.000000; 12.000100;,
-4.000000; 4.000000; 7.000100;,
-4.000000; 2.000000; 7.000100;,
-4.000000; 2.000000; 12.000100;,
-4.000000; 4.000000; 12.000100;,
4.000000; 2.000000; 7.000100;,
4.000000; 4.000000; 7.000100;,
4.000000; 4.000000; 12.000100;,
4.000000; 2.000000; 12.000100;,
6.000000; 4.000000; 7.000100;,
6.000000; 2.000000; 7.000100;,
6.000000; 2.000000; 12.000100;,
6.000000; 4.000000; 12.000100;,
4.000000; 4.000000; 7.000100;,
6.000000; 4.000000; 7.000100;,
6.000000; 4.000000; 12.000100;,
4.000000; 4.000000; 12.000100;,
-6.000000; 2.000000; 7.000100;,
-6.000000; 4.000000; 7.000100;,
-6.000000; 4.000000; 12.000100;,
-6.000000; 2.000000; 12.000100;,
-6.000000; 4.000000; 7.000100;,
-4.000000; 4.000000; 7.000100;,
-4.000000; 4.000000; 12.000100;,
-6.000000; 4.000000; 12.000100;,
-6.000000; 4.000000; 12.000100;,
-4.000000; 4.000000; 12.000100;,
-4.000000; 4.000000; 14.000100;,
-6.000000; 4.000000; 14.000100;,
-6.000000; 2.000000; 12.000100;,
-6.000000; 4.000000; 12.000100;,
-6.000000; 4.000000; 14.000100;,
-6.000000; 2.000000; 14.000100;,
4.000000; 4.000000; 12.000100;,
6.000000; 4.000000; 12.000100;,
6.000000; 4.000000; 14.000100;,
4.000000; 4.000000; 14.000100;,
6.000000; 4.000000; 12.000100;,
6.000000; 2.000000; 12.000100;,
6.000000; 2.000000; 14.000100;,
6.000000; 4.000000; 14.000100;,
4.000000; 2.000000; 12.000100;,
4.000000; 4.000000; 12.000100;,
4.000000; 4.000000; 14.000100;,
4.000000; 2.000000; 14.000100;,
-4.000000; 2.000000; 12.000100;,
-6.000000; 2.000000; 12.000100;,
-6.000000; 2.000000; 14.000100;,
-4.000000; 2.000000; 14.000100;,
6.000000; 2.000000; 12.000100;,
4.000000; 2.000000; 12.000100;,
4.000000; 2.000000; 14.000100;,
6.000000; 2.000000; 14.000100;,
-6.000000; 4.000000; 14.000100;,
-4.000000; 4.000000; 14.000100;,
-4.000000; 2.000000; 14.000100;,
-6.000000; 2.000000; 14.000100;,
4.000000; 4.000000; 14.000100;,
6.000000; 4.000000; 14.000100;,
6.000000; 2.000000; 14.000100;,
4.000000; 2.000000; 14.000100;,
-4.000000; 2.000000; 7.000100;,
-4.000000; 4.000000; 7.000100;,
4.000000; 4.000000; 7.000100;,
4.000000; 2.000000; 7.000100;,
-4.000000; 2.000000; 5.000100;,
-4.000000; 2.000000; 7.000100;,
4.000000; 2.000000; 7.000100;,
4.000000; 2.000000; 5.000100;,
-4.000000; 4.000000; 7.000100;,
-4.000000; 4.000000; 5.000100;,
4.000000; 4.000000; 5.000100;,
4.000000; 4.000000; 7.000100;,
-4.000000; 4.000000; 5.000100;,
-4.000000; 2.000000; 5.000100;,
4.000000; 2.000000; 5.000100;,
4.000000; 4.000000; 5.000100;,
4.000000; 4.000000; 5.000100;,
4.000000; 2.000000; 5.000100;,
4.000000; 2.000000; 7.000100;,
4.000000; 4.000000; 7.000100;,
-4.000000; 2.000000; 14.000100;,
-4.000000; 4.000000; 14.000100;,
4.000000; 4.000000; 14.000100;,
4.000000; 2.000000; 14.000100;,
-4.000000; 2.000000; 12.000100;,
-4.000000; 2.000000; 14.000100;,
4.000000; 2.000000; 14.000100;,
4.000000; 2.000000; 12.000100;,
-4.000000; 4.000000; 14.000100;,
-4.000000; 4.000000; 12.000100;,
4.000000; 4.000000; 12.000100;,
4.000000; 4.000000; 14.000100;,
-4.000000; 4.000000; 12.000100;,
-4.000000; 2.000000; 12.000100;,
4.000000; 2.000000; 12.000100;,
4.000000; 4.000000; 12.000100;;
79;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
4; 48, 51, 50, 49;,
4; 52, 55, 54, 53;,
4; 56, 59, 58, 57;,
4; 60, 63, 62, 61;,
4; 64, 67, 66, 65;,
4; 68, 71, 70, 69;,
4; 72, 75, 74, 73;,
4; 76, 79, 78, 77;,
4; 80, 83, 82, 81;,
4; 84, 87, 86, 85;,
4; 88, 91, 90, 89;,
4; 92, 95, 94, 93;,
4; 96, 99, 98, 97;,
4; 100, 103, 102, 101;,
4; 104, 107, 106, 105;,
4; 108, 111, 110, 109;,
4; 112, 115, 114, 113;,
4; 116, 119, 118, 117;,
4; 120, 123, 122, 121;,
4; 124, 127, 126, 125;,
4; 128, 131, 130, 129;,
4; 132, 135, 134, 133;,
4; 136, 139, 138, 137;,
4; 140, 143, 142, 141;,
4; 144, 147, 146, 145;,
4; 148, 151, 150, 149;,
4; 152, 155, 154, 153;,
4; 156, 159, 158, 157;,
4; 160, 163, 162, 161;,
4; 164, 167, 166, 165;,
4; 168, 171, 170, 169;,
4; 172, 175, 174, 173;,
4; 176, 179, 178, 177;,
4; 180, 183, 182, 181;,
4; 184, 187, 186, 185;,
4; 188, 191, 190, 189;,
4; 192, 195, 194, 193;,
4; 196, 199, 198, 197;,
4; 200, 203, 202, 201;,
4; 204, 207, 206, 205;,
4; 208, 211, 210, 209;,
4; 212, 215, 214, 213;,
4; 216, 219, 218, 217;,
4; 220, 223, 222, 221;,
4; 224, 227, 226, 225;,
4; 228, 231, 230, 229;,
4; 232, 235, 234, 233;,
4; 236, 239, 238, 237;,
4; 240, 243, 242, 241;,
4; 244, 247, 246, 245;,
4; 248, 251, 250, 249;,
4; 252, 255, 254, 253;,
4; 256, 259, 258, 257;,
4; 260, 263, 262, 261;,
4; 264, 267, 266, 265;,
4; 268, 271, 270, 269;,
4; 272, 275, 274, 273;,
4; 276, 279, 278, 277;,
4; 280, 283, 282, 281;,
4; 284, 287, 286, 285;,
4; 288, 291, 290, 289;,
4; 292, 295, 294, 293;,
4; 296, 299, 298, 297;,
4; 300, 303, 302, 301;,
4; 304, 307, 306, 305;,
4; 308, 311, 310, 309;,
4; 312, 315, 314, 313;;
  MeshMaterialList {
    0;
    79;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;;
    }  //End of MeshMaterialList
  MeshNormals {
316;
    -0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    0.707083; 0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.577349; 0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.577349; 0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.707083; -0.707083; 0.000000;,
    0.948668; 0.316202; 0.000000;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    0.948668; 0.316202; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    0.707083; 0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    0.948668; -0.316202; 0.000000;,
    0.577349; 0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.948668; -0.316202; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.577349; 0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    0.577349; 0.577349; 0.577349;,
    0.707083; 0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    0.577349; -0.577349; 0.577349;,
    0.948668; -0.316202; 0.000000;,
    0.948668; 0.316202; 0.000000;,
    0.904508; 0.301492; -0.301492;,
    0.707083; 0.000000; -0.707083;,
    -0.707083; 0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.447188; -0.894406; 0.000000;,
    -0.447188; -0.894406; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.447188; -0.894406; 0.000000;,
    -0.577349; 0.577349; -0.577349;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; 0.577349; -0.577349;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.948668; -0.316202; 0.000000;,
    0.707083; 0.000000; -0.707083;,
    0.577349; 0.577349; -0.577349;,
    -0.707083; 0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.577349; 0.577349; -0.577349;,
    -0.447188; -0.894406; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    0.707083; -0.707083; 0.000000;,
    0.948668; 0.316202; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.904508; 0.301492; -0.301492;,
    0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.577349; -0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    0.000000; 0.000000; 1.000000;,
    0.301492; 0.301492; 0.904508;,
    -0.577349; 0.577349; 0.577349;,
    -0.554674; -0.832026; 0.000000;,
    0.301492; 0.301492; 0.904508;,
    0.577349; -0.577349; 0.577349;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    0.904508; 0.301492; -0.301492;,
    -0.577349; 0.577349; 0.577349;,
    -0.554674; -0.832026; 0.000000;,
    0.707083; 0.000000; -0.707083;,
    -0.447188; -0.894406; 0.000000;,
    0.447188; -0.894406; 0.000000;,
    0.000000; 0.000000; 1.000000;,
    -0.554674; -0.832026; 0.000000;,
    0.301492; 0.301492; 0.904508;,
    0.000000; 0.000000; 1.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    0.000000; 0.000000; 1.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.577349; 0.577349; -0.577349;,
    0.447188; -0.894406; 0.000000;,
    0.707083; 0.000000; -0.707083;,
    -0.554674; -0.832026; 0.000000;,
    -0.447188; -0.894406; 0.000000;,
    0.577349; 0.577349; -0.577349;,
    -0.577349; 0.577349; 0.577349;,
    0.301492; 0.301492; 0.904508;,
    0.000000; 0.948668; 0.316202;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    0.904508; 0.301492; -0.301492;,
    0.707083; 0.707083; 0.000000;,
    -0.301492; 0.904508; 0.301492;,
    -0.577349; -0.577349; 0.577349;,
    -0.577349; 0.577349; 0.577349;,
    -0.301492; 0.904508; 0.301492;,
    -0.301492; -0.904508; 0.301492;,
    0.301492; 0.301492; 0.904508;,
    0.577349; -0.577349; 0.577349;,
    0.000000; -0.948668; 0.316202;,
    0.000000; 0.948668; 0.316202;,
    -0.707083; -0.707083; 0.000000;,
    -0.577349; 0.577349; 0.577349;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.577349; -0.577349; 0.577349;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.000000; -0.948668; 0.316202;,
    0.904508; 0.301492; -0.301492;,
    0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.577349; -0.577349; 0.577349;,
    -0.301492; -0.904508; 0.301492;,
    0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.301492; -0.904508; 0.301492;,
    -0.301492; -0.904508; -0.301492;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.000000; -0.948668; 0.316202;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.000000; -0.948668; -0.316202;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    -0.301492; 0.904508; 0.301492;,
    0.707083; 0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    -0.301492; 0.904508; -0.301492;,
    -0.707083; 0.707083; 0.000000;,
    0.000000; 0.948668; 0.316202;,
    0.000000; 0.948668; -0.316202;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    0.000000; 0.948668; -0.316202;,
    0.534501; 0.801782; 0.267251;,
    -0.707083; 0.707083; 0.000000;,
    -0.301492; 0.904508; -0.301492;,
    0.707083; 0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    -0.301492; 0.904508; 0.301492;,
    -0.301492; -0.904508; -0.301492;,
    -0.301492; 0.904508; -0.301492;,
    -0.301492; 0.904508; 0.301492;,
    -0.301492; -0.904508; 0.301492;,
    0.000000; 0.948668; -0.316202;,
    0.000000; -0.948668; -0.316202;,
    0.534501; -0.801782; 0.267251;,
    0.534501; 0.801782; 0.267251;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.000000; -0.948668; -0.316202;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; -0.707083; 0.000000;,
    0.534501; -0.801782; 0.267251;,
    0.707083; 0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.707083; 0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.301492; -0.904508; -0.301492;,
    -0.301492; -0.904508; 0.301492;,
    0.707083; -0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    -0.301492; -0.904508; 0.301492;,
    0.000000; -0.707083; -0.707083;,
    0.577349; -0.577349; -0.577349;,
    0.707083; 0.707083; 0.000000;,
    0.707083; -0.707083; 0.000000;,
    0.577349; -0.577349; -0.577349;,
    0.577349; 0.577349; -0.577349;,
    0.534501; -0.801782; 0.267251;,
    -0.707083; -0.707083; 0.000000;,
    -0.577349; -0.577349; -0.577349;,
    0.333323; -0.666646; -0.666646;,
    -0.707083; -0.707083; 0.000000;,
    -0.707083; 0.707083; 0.000000;,
    -0.577349; 0.577349; -0.577349;,
    -0.577349; -0.577349; -0.577349;,
    0.534501; 0.801782; 0.267251;,
    0.534501; -0.801782; 0.267251;,
    0.333323; -0.666646; -0.666646;,
    0.333323; 0.666646; -0.666646;,
    -0.301492; 0.904508; 0.301492;,
    0.707083; 0.707083; 0.000000;,
    0.577349; 0.577349; -0.577349;,
    0.000000; 0.707083; -0.707083;,
    -0.707083; 0.707083; 0.000000;,
    0.534501; 0.801782; 0.267251;,
    0.333323; 0.666646; -0.666646;,
    -0.577349; 0.577349; -0.577349;,
    0.577349; -0.577349; -0.577349;,
    0.000000; -0.707083; -0.707083;,
    0.000000; 0.707083; -0.707083;,
    0.577349; 0.577349; -0.577349;,
    0.333323; -0.666646; -0.666646;,
    -0.577349; -0.577349; -0.577349;,
    -0.577349; 0.577349; -0.577349;,
    0.333323; 0.666646; -0.666646;,
    -0.301492; 0.904508; -0.301492;,
    -0.301492; -0.904508; -0.301492;,
    0.000000; -0.948668; -0.316202;,
    0.000000; 0.948668; -0.316202;,
    -0.301492; 0.904508; 0.301492;,
    -0.301492; 0.904508; -0.301492;,
    0.000000; 0.948668; -0.316202;,
    0.000000; 0.948668; 0.316202;,
    -0.301492; -0.904508; -0.301492;,
    -0.301492; -0.904508; 0.301492;,
    0.000000; -0.948668; 0.316202;,
    0.000000; -0.948668; -0.316202;,
    -0.301492; -0.904508; 0.301492;,
    -0.301492; 0.904508; 0.301492;,
    0.000000; 0.948668; 0.316202;,
    0.000000; -0.948668; 0.316202;,
    0.000000; -0.948668; 0.316202;,
    0.000000; 0.948668; 0.316202;,
    0.000000; 0.948668; -0.316202;,
    0.000000; -0.948668; -0.316202;,
    0.000000; 0.707083; -0.707083;,
    0.000000; -0.707083; -0.707083;,
    0.333323; -0.666646; -0.666646;,
    0.333323; 0.666646; -0.666646;,
    -0.301492; 0.904508; 0.301492;,
    0.000000; 0.707083; -0.707083;,
    0.333323; 0.666646; -0.666646;,
    0.534501; 0.801782; 0.267251;,
    0.000000; -0.707083; -0.707083;,
    -0.301492; -0.904508; 0.301492;,
    0.534501; -0.801782; 0.267251;,
    0.333323; -0.666646; -0.666646;,
    -0.301492; -0.904508; 0.301492;,
    -0.301492; 0.904508; 0.301492;,
    0.534501; 0.801782; 0.267251;,
    0.534501; -0.801782; 0.267251;;
79;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
4; 48, 51, 50, 49;,
4; 52, 55, 54, 53;,
4; 56, 59, 58, 57;,
4; 60, 63, 62, 61;,
4; 64, 67, 66, 65;,
4; 68, 71, 70, 69;,
4; 72, 75, 74, 73;,
4; 76, 79, 78, 77;,
4; 80, 83, 82, 81;,
4; 84, 87, 86, 85;,
4; 88, 91, 90, 89;,
4; 92, 95, 94, 93;,
4; 96, 99, 98, 97;,
4; 100, 103, 102, 101;,
4; 104, 107, 106, 105;,
4; 108, 111, 110, 109;,
4; 112, 115, 114, 113;,
4; 116, 119, 118, 117;,
4; 120, 123, 122, 121;,
4; 124, 127, 126, 125;,
4; 128, 131, 130, 129;,
4; 132, 135, 134, 133;,
4; 136, 139, 138, 137;,
4; 140, 143, 142, 141;,
4; 144, 147, 146, 145;,
4; 148, 151, 150, 149;,
4; 152, 155, 154, 153;,
4; 156, 159, 158, 157;,
4; 160, 163, 162, 161;,
4; 164, 167, 166, 165;,
4; 168, 171, 170, 169;,
4; 172, 175, 174, 173;,
4; 176, 179, 178, 177;,
4; 180, 183, 182, 181;,
4; 184, 187, 186, 185;,
4; 188, 191, 190, 189;,
4; 192, 195, 194, 193;,
4; 196, 199, 198, 197;,
4; 200, 203, 202, 201;,
4; 204, 207, 206, 205;,
4; 208, 211, 210, 209;,
4; 212, 215, 214, 213;,
4; 216, 219, 218, 217;,
4; 220, 223, 222, 221;,
4; 224, 227, 226, 225;,
4; 228, 231, 230, 229;,
4; 232, 235, 234, 233;,
4; 236, 239, 238, 237;,
4; 240, 243, 242, 241;,
4; 244, 247, 246, 245;,
4; 248, 251, 250, 249;,
4; 252, 255, 254, 253;,
4; 256, 259, 258, 257;,
4; 260, 263, 262, 261;,
4; 264, 267, 266, 265;,
4; 268, 271, 270, 269;,
4; 272, 275, 274, 273;,
4; 276, 279, 278, 277;,
4; 280, 283, 282, 281;,
4; 284, 287, 286, 285;,
4; 288, 291, 290, 289;,
4; 292, 295, 294, 293;,
4; 296, 299, 298, 297;,
4; 300, 303, 302, 301;,
4; 304, 307, 306, 305;,
4; 308, 311, 310, 309;,
4; 312, 315, 314, 313;;
}  //End of MeshNormals
  }  // End of the Mesh Plane 
  }  // SI End of the Object Plane 
  Frame Cube {

    FrameTransformMatrix {
      1.000000,0.000000,0.000000,0.000000,
      0.000000,1.000000,0.000000,0.000000,
      0.000000,0.000000,1.000000,0.000000,
      0.044500,-0.036400,1.597400,1.000000;;
    }
Mesh {
4;
1.000000; 1.000000; 0.000000;,
-1.000000; 1.000000; 0.000000;,
-1.000000; -1.000000; 0.000000;,
1.000000; -1.000000; 0.000000;;
1;
4; 0, 3, 2, 1;;
  MeshMaterialList {
    0;
    1;
    0;;
    }  //End of MeshMaterialList
  MeshNormals {
4;
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;;
1;
4; 0, 3, 2, 1;;
}  //End of MeshNormals
  }  // End of the Mesh Cube 
  }  // SI End of the Object Cube 
}  // End of the Root Frame