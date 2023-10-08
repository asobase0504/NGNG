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
 92;
 -3.67842;0.00000;-5.01187;,
 3.67233;0.00000;-5.01187;,
 3.67233;-2.50594;-4.34043;,
 -3.67842;-2.50594;-4.34043;,
 3.67233;-4.34038;-2.50594;,
 -3.67842;-4.34038;-2.50594;,
 3.67233;-5.01187;-0.00000;,
 -3.67842;-5.01187;0.00000;,
 3.67233;-4.34038;2.50594;,
 -3.67842;-4.34038;2.50594;,
 3.67233;-2.50594;4.34043;,
 -3.67842;-2.50594;4.34043;,
 3.67233;0.00000;5.01187;,
 -3.67842;0.00000;5.01187;,
 3.67233;2.50594;4.34043;,
 -3.67842;2.50594;4.34043;,
 3.67233;4.34043;2.50594;,
 -3.67842;4.34043;2.50594;,
 3.67233;5.01187;0.00000;,
 -3.67842;5.01187;0.00000;,
 3.67233;4.34043;-2.50594;,
 -3.67842;4.34043;-2.50594;,
 3.67233;2.50594;-4.34043;,
 -3.67842;2.50594;-4.34043;,
 3.67233;0.00000;-5.01187;,
 -3.67842;0.00000;-5.01187;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 -3.67842;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 3.67233;0.00000;0.00000;,
 1.94662;-0.46336;1.73137;,
 1.94662;-0.46336;-1.73137;,
 -1.51613;-0.46336;-1.73137;,
 -1.51613;-0.46336;1.73137;,
 1.94662;-2.28128;-3.46275;,
 1.94662;-13.18895;-3.46275;,
 -1.51613;-13.18895;-3.46275;,
 -1.51613;-2.28128;-3.46275;,
 1.94662;-15.00691;-1.73137;,
 1.94662;-15.00691;1.73137;,
 -1.51613;-15.00691;1.73137;,
 -1.51613;-15.00691;-1.73137;,
 1.94662;-13.18895;3.46275;,
 1.94662;-2.28128;3.46275;,
 -1.51613;-2.28128;3.46275;,
 -1.51613;-13.18895;3.46275;,
 -3.24750;-2.28128;1.73137;,
 -3.24750;-2.28128;-1.73137;,
 -3.24750;-13.18895;-1.73137;,
 -3.24750;-13.18895;1.73137;,
 3.67800;-13.18895;1.73137;,
 3.67800;-13.18895;-1.73137;,
 3.67800;-2.28128;-1.73137;,
 3.67800;-2.28128;1.73137;,
 1.94662;-0.46336;-1.73137;,
 -1.51613;-2.28128;-3.46275;,
 -1.51613;-0.46336;-1.73137;,
 1.94662;-13.18895;-3.46275;,
 -1.51613;-15.00691;-1.73137;,
 -1.51613;-13.18895;-3.46275;,
 1.94662;-2.28128;3.46275;,
 -1.51613;-0.46336;1.73137;,
 -1.51613;-2.28128;3.46275;,
 1.94662;-15.00691;1.73137;,
 -1.51613;-13.18895;3.46275;,
 -1.51613;-15.00691;1.73137;,
 -3.24750;-2.28128;-1.73137;,
 -3.24750;-13.18895;1.73137;,
 -3.24750;-13.18895;-1.73137;,
 3.67800;-2.28128;1.73137;,
 3.67800;-2.28128;-1.73137;,
 3.67800;-13.18895;-1.73137;;
 
 62;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 3;26,0,3;,
 3;27,3,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 3;34,17,19;,
 3;35,19,21;,
 3;36,21,23;,
 3;37,23,25;,
 3;38,2,1;,
 3;39,4,2;,
 3;40,6,4;,
 3;41,8,6;,
 3;42,10,8;,
 3;43,12,10;,
 3;44,14,12;,
 3;45,16,14;,
 3;46,18,16;,
 3;47,20,18;,
 3;48,22,20;,
 3;49,24,22;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,54,75,76;,
 4;77,58,78,79;,
 4;80,50,81,82;,
 4;83,62,84,85;,
 4;76,86,66,81;,
 4;85,87,88,78;,
 4;50,89,90,74;,
 4;58,91,70,83;,
 4;79,88,86,75;,
 4;82,66,87,84;,
 4;54,90,91,77;,
 4;62,70,89,80;,
 3;76,75,86;,
 3;54,74,90;,
 3;79,78,88;,
 3;82,81,66;,
 3;58,77,91;,
 3;85,84,87;,
 3;50,80,89;,
 3;62,83,70;;
 
 MeshMaterialList {
  14;
  62;
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
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.078400;0.429600;0.800000;1.000000;;
   12.000000;
   0.120000;0.120000;0.120000;;
   0.011760;0.064440;0.120000;;
  }
  Material {
   0.213600;0.213600;0.213600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.288800;0.288800;0.288800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.166400;0.166400;0.166400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.580000;0.527200;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.511200;0.464000;0.344800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.455200;0.455200;0.455200;1.000000;;
   25.000000;
   0.220000;0.220000;0.220000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.044000;0.232000;0.432800;1.000000;;
   12.000000;
   0.120000;0.120000;0.120000;;
   0.006600;0.034800;0.064920;;
  }
  Material {
   0.024800;0.125600;0.235200;1.000000;;
   12.000000;
   0.120000;0.120000;0.120000;;
   0.003720;0.018840;0.035280;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.545600;0.128800;0.930000;;
   15.000000;
   0.020000;0.020000;0.020000;;
   0.240000;0.163680;0.038640;;
  }
  Material {
   0.718400;0.021600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  38;
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.500003;-0.866024;,
  0.000000;-0.866026;-0.499999;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.866026;0.499999;,
  0.000000;-0.500003;0.866024;,
  0.000000;0.000000;1.000000;,
  0.000000;0.499997;0.866027;,
  0.000000;0.866027;0.499997;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.866027;-0.499997;,
  0.000000;0.499997;-0.866027;,
  1.000000;0.000000;0.000000;,
  0.377300;0.845747;0.377300;,
  -0.377300;0.845747;0.377300;,
  0.377300;0.845747;-0.377300;,
  -0.377300;0.845747;-0.377300;,
  0.368278;0.355362;-0.859121;,
  -0.368278;0.355362;-0.859121;,
  0.368279;-0.355357;-0.859123;,
  -0.368279;-0.355357;-0.859123;,
  0.377305;-0.845743;-0.377305;,
  -0.377305;-0.845743;-0.377305;,
  0.377305;-0.845743;0.377305;,
  -0.377305;-0.845743;0.377305;,
  0.368279;-0.355357;0.859123;,
  -0.368279;-0.355357;0.859123;,
  0.368278;0.355362;0.859121;,
  -0.368278;0.355362;0.859121;,
  -0.859121;0.355362;0.368278;,
  -0.859123;-0.355357;0.368279;,
  -0.859121;0.355362;-0.368278;,
  -0.859123;-0.355357;-0.368279;,
  0.859123;-0.355357;0.368279;,
  0.859121;0.355362;0.368278;,
  0.859123;-0.355357;-0.368279;,
  0.859121;0.355362;-0.368278;;
  62;
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,1,1;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  4;14,16,17,15;,
  4;18,20,21,19;,
  4;22,24,25,23;,
  4;26,28,29,27;,
  4;30,32,33,31;,
  4;34,36,37,35;,
  4;16,18,19,17;,
  4;20,22,23,21;,
  4;28,14,15,29;,
  4;24,26,27,25;,
  4;17,32,30,15;,
  4;25,31,33,23;,
  4;14,35,37,16;,
  4;22,36,34,24;,
  4;21,33,32,19;,
  4;29,30,31,27;,
  4;18,37,36,20;,
  4;26,34,35,28;,
  3;17,19,32;,
  3;18,16,37;,
  3;21,23,33;,
  3;29,15,30;,
  3;22,20,36;,
  3;25,27,31;,
  3;14,28,35;,
  3;26,24,34;;
 }
 MeshTextureCoords {
  92;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.083330;1.000000;,
  0.083330;0.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.416670;1.000000;,
  0.416670;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.583330;1.000000;,
  0.583330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  0.916670;1.000000;,
  0.916670;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.041670;0.000000;,
  0.125000;0.000000;,
  0.208330;0.000000;,
  0.291670;0.000000;,
  0.375000;0.000000;,
  0.458330;0.000000;,
  0.541670;0.000000;,
  0.625000;0.000000;,
  0.708330;0.000000;,
  0.791670;0.000000;,
  0.875000;0.000000;,
  0.958330;0.000000;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
