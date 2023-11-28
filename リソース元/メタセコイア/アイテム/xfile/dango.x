xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 89;
 -10.77678;5.00000;0.00000;,
 -7.24125;3.53554;0.00000;,
 -10.77678;3.53554;-3.53554;,
 -10.77678;5.00000;0.00000;,
 -10.77678;3.53554;3.53554;,
 -10.77678;5.00000;0.00000;,
 -14.31232;3.53554;0.00000;,
 -10.77678;5.00000;0.00000;,
 -10.77678;3.53554;-3.53554;,
 -5.77678;0.00000;0.00000;,
 -10.77678;0.00000;-5.00000;,
 -10.77678;0.00000;5.00000;,
 -15.77678;0.00000;0.00000;,
 -10.77678;0.00000;-5.00000;,
 -7.24125;-3.53554;0.00000;,
 -10.77678;-3.53554;-3.53554;,
 -10.77678;-3.53554;3.53554;,
 -14.31232;-3.53554;0.00000;,
 -10.77678;-3.53554;-3.53554;,
 -10.77678;-5.00000;0.00000;,
 -10.77678;-5.00000;0.00000;,
 -10.77678;-5.00000;0.00000;,
 -10.77678;-5.00000;0.00000;,
 -2.47808;5.00000;0.00000;,
 1.05745;3.53554;0.00000;,
 -2.47808;3.53554;-3.53554;,
 -2.47808;5.00000;0.00000;,
 -2.47808;3.53554;3.53554;,
 -2.47808;5.00000;0.00000;,
 -6.01362;3.53554;0.00000;,
 -2.47808;5.00000;0.00000;,
 -2.47808;3.53554;-3.53554;,
 2.52192;-0.00000;0.00000;,
 -2.47808;0.00000;-5.00000;,
 -2.47808;0.00000;5.00000;,
 -7.47807;0.00000;0.00000;,
 -2.47808;0.00000;-5.00000;,
 1.05745;-3.53554;0.00000;,
 -2.47808;-3.53554;-3.53554;,
 -2.47808;-3.53554;3.53554;,
 -6.01362;-3.53554;0.00000;,
 -2.47808;-3.53554;-3.53554;,
 -2.47808;-5.00000;0.00000;,
 -2.47808;-5.00000;0.00000;,
 -2.47808;-5.00000;0.00000;,
 -2.47808;-5.00000;0.00000;,
 6.29969;5.00000;0.00000;,
 9.83523;3.53554;0.00000;,
 6.29969;3.53554;-3.53554;,
 6.29969;5.00000;0.00000;,
 6.29969;3.53554;3.53554;,
 6.29969;5.00000;0.00000;,
 2.76416;3.53554;0.00000;,
 6.29969;5.00000;0.00000;,
 6.29969;3.53554;-3.53554;,
 11.29969;-0.00000;0.00000;,
 6.29969;0.00000;-5.00000;,
 6.29969;-0.00000;5.00000;,
 1.29970;0.00000;-0.00000;,
 6.29969;0.00000;-5.00000;,
 9.83523;-3.53554;0.00000;,
 6.29969;-3.53554;-3.53554;,
 6.29969;-3.53554;3.53554;,
 2.76416;-3.53554;-0.00000;,
 6.29969;-3.53554;-3.53554;,
 6.29969;-5.00000;-0.00000;,
 6.29969;-5.00000;-0.00000;,
 6.29969;-5.00000;-0.00000;,
 6.29969;-5.00000;-0.00000;,
 -14.17490;0.28696;-0.28696;,
 21.89369;0.28696;-0.28696;,
 21.89369;-0.28696;-0.28696;,
 -14.17490;-0.28696;-0.28696;,
 21.89369;0.28696;-0.28696;,
 21.89369;0.28696;0.28696;,
 21.89369;-0.28696;0.28696;,
 21.89369;-0.28696;-0.28696;,
 21.89369;0.28696;0.28696;,
 -14.17490;0.28696;0.28696;,
 -14.17490;-0.28696;0.28696;,
 21.89369;-0.28696;0.28696;,
 -14.17490;0.28696;0.28696;,
 -14.17490;0.28696;-0.28696;,
 -14.17490;-0.28696;-0.28696;,
 -14.17490;-0.28696;0.28696;,
 21.89369;0.28696;-0.28696;,
 -14.17490;0.28696;-0.28696;,
 -14.17490;-0.28696;-0.28696;,
 21.89369;-0.28696;-0.28696;;
 
 54;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 4;2,1,9,10;,
 4;1,4,11,9;,
 4;4,6,12,11;,
 4;6,8,13,12;,
 4;10,9,14,15;,
 4;9,11,16,14;,
 4;11,12,17,16;,
 4;12,13,18,17;,
 3;15,14,19;,
 3;14,16,20;,
 3;16,17,21;,
 3;17,18,22;,
 3;23,24,25;,
 3;26,27,24;,
 3;28,29,27;,
 3;30,31,29;,
 4;25,24,32,33;,
 4;24,27,34,32;,
 4;27,29,35,34;,
 4;29,31,36,35;,
 4;33,32,37,38;,
 4;32,34,39,37;,
 4;34,35,40,39;,
 4;35,36,41,40;,
 3;38,37,42;,
 3;37,39,43;,
 3;39,40,44;,
 3;40,41,45;,
 3;46,47,48;,
 3;49,50,47;,
 3;51,52,50;,
 3;53,54,52;,
 4;48,47,55,56;,
 4;47,50,57,55;,
 4;50,52,58,57;,
 4;52,54,59,58;,
 4;56,55,60,61;,
 4;55,57,62,60;,
 4;57,58,63,62;,
 4;58,59,64,63;,
 3;61,60,65;,
 3;60,62,66;,
 3;62,63,67;,
 3;63,64,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;81,74,85,86;,
 4;87,88,75,84;;
 
 MeshMaterialList {
  5;
  54;
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
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.627200;0.780800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.558400;0.800000;0.545600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.615200;0.455200;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  66;
  0.000000;1.000000;0.000000;,
  0.267627;0.791445;-0.549537;,
  0.549537;0.791445;-0.267627;,
  0.267627;0.791445;0.549537;,
  -0.549536;0.791445;0.267627;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  0.267627;-0.791445;-0.549537;,
  0.549537;-0.791445;-0.267627;,
  0.267627;-0.791445;0.549537;,
  -0.549536;-0.791445;0.267627;,
  0.000000;-1.000000;-0.000000;,
  0.678598;0.281084;0.678598;,
  -0.678598;0.281084;0.678598;,
  -0.678598;0.281084;-0.678598;,
  -0.707107;0.000000;-0.707107;,
  0.678598;-0.281084;0.678598;,
  -0.678598;-0.281084;0.678598;,
  -0.678598;-0.281084;-0.678598;,
  0.000000;1.000000;0.000000;,
  0.267627;0.791445;-0.549537;,
  0.549537;0.791445;-0.267627;,
  0.267627;0.791445;0.549537;,
  -0.549537;0.791445;0.267627;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  0.267627;-0.791445;-0.549537;,
  0.549537;-0.791445;-0.267627;,
  0.267627;-0.791445;0.549537;,
  -0.549537;-0.791445;0.267627;,
  0.000000;-1.000000;-0.000000;,
  0.678598;0.281084;0.678598;,
  -0.678599;0.281084;0.678598;,
  -0.678599;0.281084;-0.678598;,
  -0.707107;0.000000;-0.707107;,
  0.678598;-0.281084;0.678598;,
  -0.678599;-0.281084;0.678598;,
  -0.678599;-0.281084;-0.678598;,
  -0.000000;1.000000;0.000000;,
  0.267627;0.791445;-0.549537;,
  0.549536;0.791445;-0.267627;,
  0.267627;0.791445;0.549537;,
  -0.549537;0.791445;0.267627;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  -0.707107;0.000000;0.707107;,
  0.267627;-0.791445;-0.549537;,
  0.549536;-0.791445;-0.267627;,
  0.267627;-0.791445;0.549537;,
  -0.549537;-0.791445;0.267627;,
  -0.000000;-1.000000;0.000000;,
  0.678598;0.281084;0.678599;,
  -0.678598;0.281084;0.678598;,
  -0.678598;0.281084;-0.678598;,
  -0.707107;0.000000;-0.707107;,
  0.678598;-0.281084;0.678599;,
  -0.678598;-0.281084;0.678598;,
  -0.678598;-0.281084;-0.678598;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  54;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,1,4;,
  4;1,2,5,5;,
  4;13,3,6,6;,
  4;14,4,7,7;,
  4;15,15,16,16;,
  4;5,5,9,8;,
  4;6,6,10,17;,
  4;7,7,11,18;,
  4;16,16,19,19;,
  3;8,9,12;,
  3;9,10,12;,
  3;10,11,12;,
  3;11,8,12;,
  3;20,22,21;,
  3;20,23,22;,
  3;20,24,23;,
  3;20,21,24;,
  4;21,22,25,25;,
  4;33,23,26,26;,
  4;34,24,27,27;,
  4;35,35,36,36;,
  4;25,25,29,28;,
  4;26,26,30,37;,
  4;27,27,31,38;,
  4;36,36,39,39;,
  3;28,29,32;,
  3;29,30,32;,
  3;30,31,32;,
  3;31,28,32;,
  3;40,42,41;,
  3;40,43,42;,
  3;40,44,43;,
  3;40,41,44;,
  4;41,42,45,45;,
  4;53,43,46,46;,
  4;54,44,47,47;,
  4;55,55,56,56;,
  4;45,45,49,48;,
  4;46,46,50,57;,
  4;47,47,51,58;,
  4;56,56,59,59;,
  3;48,49,52;,
  3;49,50,52;,
  3;50,51,52;,
  3;51,48,52;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;;
 }
 MeshTextureCoords {
  89;
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
