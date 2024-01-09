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
 142;
 3.60152;21.21549;-1.95168;,
 4.24140;22.19175;-2.32111;,
 0.18887;22.19175;-4.66084;,
 0.18887;21.21549;-3.92198;,
 4.24140;20.23920;-2.32111;,
 0.18887;20.23920;-4.66084;,
 3.60152;21.21549;-1.95168;,
 0.18887;21.21549;-3.92198;,
 -3.86366;22.19175;-2.32111;,
 -3.22378;21.21549;-1.95168;,
 -3.86366;20.23920;-2.32111;,
 -3.22378;21.21549;-1.95168;,
 -3.86366;22.19175;2.35835;,
 -3.22378;21.21549;1.98892;,
 -3.86366;20.23920;2.35835;,
 -3.22378;21.21549;1.98892;,
 0.18887;22.19175;4.69808;,
 0.18887;21.21549;3.95922;,
 0.18887;20.23920;4.69808;,
 0.18887;21.21549;3.95922;,
 4.24140;22.19175;2.35835;,
 3.60152;21.21549;1.98892;,
 4.24140;20.23920;2.35835;,
 3.60152;21.21549;1.98892;,
 4.24140;22.19175;-2.32111;,
 3.60152;21.21549;-1.95168;,
 4.24140;20.23920;-2.32111;,
 3.60152;21.21549;-1.95168;,
 0.15191;21.61819;0.08043;,
 4.46102;20.58954;-2.40744;,
 0.15191;20.58954;-4.89530;,
 0.15191;21.61819;0.08043;,
 4.46102;20.58954;2.56829;,
 0.15191;21.61819;0.08043;,
 0.15191;20.58954;5.05616;,
 0.15191;21.61819;0.08043;,
 -4.15719;20.58954;2.56829;,
 0.15191;21.61819;0.08043;,
 -4.15719;20.58954;-2.40744;,
 0.15191;21.61819;0.08043;,
 0.15191;20.58954;-4.89530;,
 7.61551;17.77917;-4.22868;,
 0.15191;17.77917;-8.53779;,
 7.61551;17.77917;4.38954;,
 0.15191;17.77917;8.69865;,
 -7.31168;17.77917;4.38954;,
 -7.31168;17.77917;-4.22868;,
 0.15191;17.77917;-8.53779;,
 8.77012;13.94014;-4.89530;,
 0.15191;13.94014;-9.87103;,
 8.77012;13.94014;5.05616;,
 0.15191;13.94014;10.03188;,
 -8.46630;13.94014;5.05616;,
 -8.46630;13.94014;-4.89530;,
 0.15191;13.94014;-9.87103;,
 7.61551;10.10111;-4.22868;,
 0.15191;10.10111;-8.53779;,
 7.61550;10.10111;4.38954;,
 0.15191;10.10111;8.69865;,
 -7.31168;10.10111;4.38954;,
 -7.31168;10.10111;-4.22868;,
 0.15191;10.10111;-8.53779;,
 4.46102;7.29075;-2.40744;,
 0.15191;7.29075;-4.89530;,
 4.46102;7.29075;2.56829;,
 0.15191;7.29075;5.05616;,
 -4.15719;7.29075;2.56829;,
 -4.15719;7.29075;-2.40744;,
 0.15191;7.29075;-4.89530;,
 0.15191;6.26209;0.08043;,
 0.15191;6.26209;0.08043;,
 0.15191;6.26209;0.08043;,
 0.15191;6.26209;0.08043;,
 0.15191;6.26209;0.08043;,
 0.15191;6.26209;0.08043;,
 0.09601;31.50822;-0.02474;,
 2.54858;31.08769;-1.44074;,
 0.09601;31.08769;-2.85674;,
 0.09601;31.50822;-0.02474;,
 2.54858;31.08769;1.39125;,
 0.09601;31.50822;-0.02474;,
 0.09601;31.08769;2.80724;,
 0.09601;31.50822;-0.02474;,
 -2.35657;31.08769;1.39125;,
 0.09601;31.50822;-0.02474;,
 -2.35657;31.08769;-1.44074;,
 0.09601;31.50822;-0.02474;,
 0.09601;31.08769;-2.85674;,
 4.34399;28.73921;-2.47732;,
 0.09601;28.73921;-4.92990;,
 4.34399;28.73921;2.42783;,
 0.09601;28.73921;4.88040;,
 -4.15197;28.73921;2.42783;,
 -4.15197;28.73921;-2.47732;,
 0.09601;28.73921;-4.92990;,
 5.00116;25.53115;-2.85674;,
 0.09601;25.53115;-5.68872;,
 5.00116;25.53115;2.80724;,
 0.09601;25.53115;5.63923;,
 -4.80915;25.53115;2.80724;,
 -4.80915;25.53115;-2.85674;,
 0.09601;25.53115;-5.68872;,
 4.34399;22.32310;-2.47732;,
 0.09601;22.32310;-4.92990;,
 4.34399;22.32310;2.42783;,
 0.09601;22.32310;4.88040;,
 -4.15197;22.32310;2.42783;,
 -4.15197;22.32310;-2.47732;,
 0.09601;22.32310;-4.92990;,
 2.54858;19.97462;-1.44074;,
 0.09601;19.97462;-2.85674;,
 2.54858;19.97462;1.39125;,
 0.09601;19.97462;2.80724;,
 -2.35657;19.97462;1.39125;,
 -2.35657;19.97462;-1.44074;,
 0.09601;19.97462;-2.85674;,
 0.09601;19.11502;-0.02474;,
 0.09601;19.11502;-0.02474;,
 0.09601;19.11502;-0.02474;,
 0.09601;19.11502;-0.02474;,
 0.09601;19.11502;-0.02474;,
 0.09601;19.11502;-0.02474;,
 -1.23729;34.68172;-1.23729;,
 1.23729;34.68172;-1.23729;,
 1.23729;30.37711;-1.23729;,
 -1.23729;30.37711;-1.23729;,
 1.23729;34.68172;-1.23729;,
 1.23729;34.68172;1.23729;,
 1.23729;30.37711;1.23729;,
 1.23729;30.37711;-1.23729;,
 1.23729;34.68172;1.23729;,
 -1.23729;34.68172;1.23729;,
 -1.23729;30.37711;1.23729;,
 1.23729;30.37711;1.23729;,
 -1.23729;34.68172;1.23729;,
 -1.23729;34.68172;-1.23729;,
 -1.23729;30.37711;-1.23729;,
 -1.23729;30.37711;1.23729;,
 1.23729;34.68172;-1.23729;,
 -1.23729;34.68172;-1.23729;,
 -1.23729;30.37711;-1.23729;,
 1.23729;30.37711;-1.23729;;
 
 96;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;13,12,16,17;,
 4;12,14,18,16;,
 4;14,15,19,18;,
 4;17,16,20,21;,
 4;16,18,22,20;,
 4;18,19,23,22;,
 4;21,20,24,25;,
 4;20,22,26,24;,
 4;22,23,27,26;,
 3;28,29,30;,
 3;31,32,29;,
 3;33,34,32;,
 3;35,36,34;,
 3;37,38,36;,
 3;39,40,38;,
 4;30,29,41,42;,
 4;29,32,43,41;,
 4;32,34,44,43;,
 4;34,36,45,44;,
 4;36,38,46,45;,
 4;38,40,47,46;,
 4;42,41,48,49;,
 4;41,43,50,48;,
 4;43,44,51,50;,
 4;44,45,52,51;,
 4;45,46,53,52;,
 4;46,47,54,53;,
 4;49,48,55,56;,
 4;48,50,57,55;,
 4;50,51,58,57;,
 4;51,52,59,58;,
 4;52,53,60,59;,
 4;53,54,61,60;,
 4;56,55,62,63;,
 4;55,57,64,62;,
 4;57,58,65,64;,
 4;58,59,66,65;,
 4;59,60,67,66;,
 4;60,61,68,67;,
 3;63,62,69;,
 3;62,64,70;,
 3;64,65,71;,
 3;65,66,72;,
 3;66,67,73;,
 3;67,68,74;,
 3;75,76,77;,
 3;78,79,76;,
 3;80,81,79;,
 3;82,83,81;,
 3;84,85,83;,
 3;86,87,85;,
 4;77,76,88,89;,
 4;76,79,90,88;,
 4;79,81,91,90;,
 4;81,83,92,91;,
 4;83,85,93,92;,
 4;85,87,94,93;,
 4;89,88,95,96;,
 4;88,90,97,95;,
 4;90,91,98,97;,
 4;91,92,99,98;,
 4;92,93,100,99;,
 4;93,94,101,100;,
 4;96,95,102,103;,
 4;95,97,104,102;,
 4;97,98,105,104;,
 4;98,99,106,105;,
 4;99,100,107,106;,
 4;100,101,108,107;,
 4;103,102,109,110;,
 4;102,104,111,109;,
 4;104,105,112,111;,
 4;105,106,113,112;,
 4;106,107,114,113;,
 4;107,108,115,114;,
 3;110,109,116;,
 3;109,111,117;,
 3;111,112,118;,
 3;112,113,119;,
 3;113,114,120;,
 3;114,115,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;134,127,138,139;,
 4;140,141,128,137;;
 
 MeshMaterialList {
  2;
  96;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.577600;0.254400;1.000000;;
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
 }
 MeshNormals {
  86;
  -0.690548;0.603483;0.398688;,
  0.500000;0.000000;-0.866025;,
  0.000000;0.603481;0.797377;,
  0.690548;0.603483;0.398688;,
  -0.500000;0.000000;-0.866025;,
  0.690548;0.603483;-0.398688;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.603482;-0.797377;,
  -0.499999;0.000000;0.866026;,
  -0.690548;0.603483;-0.398688;,
  0.499999;0.000000;0.866026;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;0.911231;-0.411895;,
  0.356711;0.911231;-0.205948;,
  0.356712;0.911231;0.205948;,
  -0.000000;0.911231;0.411895;,
  -0.356712;0.911231;0.205948;,
  -0.356712;0.911231;-0.205948;,
  -0.000000;0.592866;-0.805301;,
  0.697411;0.592866;-0.402651;,
  0.697411;0.592866;0.402650;,
  -0.000000;0.592866;0.805301;,
  -0.697411;0.592867;0.402650;,
  -0.697411;0.592866;-0.402650;,
  -0.000000;-0.000000;-1.000000;,
  0.866025;-0.000000;-0.500000;,
  0.866025;-0.000000;0.500000;,
  -0.000000;-0.000000;1.000000;,
  -0.866025;-0.000000;0.500000;,
  -0.866025;-0.000000;-0.500000;,
  -0.000000;-0.592867;-0.805301;,
  0.697411;-0.592867;-0.402650;,
  0.697411;-0.592867;0.402650;,
  -0.000000;-0.592867;0.805300;,
  -0.697411;-0.592867;0.402650;,
  -0.697411;-0.592867;-0.402650;,
  -0.000000;-0.911231;-0.411895;,
  0.356712;-0.911231;-0.205948;,
  0.356712;-0.911231;0.205948;,
  -0.000000;-0.911231;0.411895;,
  -0.356712;-0.911231;0.205948;,
  -0.356712;-0.911231;-0.205948;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.885843;-0.463985;,
  0.401823;0.885843;-0.231992;,
  0.401823;0.885843;0.231992;,
  -0.000000;0.885843;0.463985;,
  -0.401823;0.885843;0.231993;,
  -0.401823;0.885843;-0.231993;,
  -0.000000;0.465471;-0.885063;,
  0.766487;0.465471;-0.442532;,
  0.766487;0.465471;0.442532;,
  -0.000000;0.465471;0.885063;,
  -0.766487;0.465471;0.442531;,
  -0.766487;0.465471;-0.442531;,
  -0.000000;-0.000001;-1.000000;,
  0.866025;-0.000001;-0.500000;,
  0.866025;-0.000001;0.500000;,
  -0.000000;-0.000001;1.000000;,
  -0.866025;-0.000001;0.500000;,
  -0.866025;-0.000001;-0.500000;,
  -0.000000;-0.465472;-0.885063;,
  0.766487;-0.465472;-0.442531;,
  0.766487;-0.465472;0.442531;,
  -0.000000;-0.465472;0.885063;,
  -0.766487;-0.465472;0.442531;,
  -0.766487;-0.465472;-0.442531;,
  -0.000000;-0.846760;-0.531975;,
  0.460704;-0.846760;-0.265987;,
  0.460704;-0.846760;0.265988;,
  0.000000;-0.846760;0.531975;,
  -0.460704;-0.846760;0.265988;,
  -0.460704;-0.846760;-0.265987;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.690555;-0.603472;0.398693;,
  0.000000;-0.603471;0.797385;,
  0.690555;-0.603472;0.398693;,
  0.690555;-0.603472;-0.398693;,
  0.000000;-0.603470;-0.797385;,
  -0.690555;-0.603472;-0.398693;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  96;
  4;0,0,2,2;,
  4;1,1,1,1;,
  4;78,78,79,79;,
  4;2,2,3,3;,
  4;4,4,4,4;,
  4;79,79,80,80;,
  4;3,3,5,5;,
  4;6,6,6,6;,
  4;80,80,81,81;,
  4;5,5,7,7;,
  4;8,8,8,8;,
  4;81,81,82,82;,
  4;7,7,9,9;,
  4;10,10,10,10;,
  4;82,82,83,83;,
  4;9,9,0,0;,
  4;76,76,76,76;,
  4;83,83,78,78;,
  3;11,13,12;,
  3;11,14,13;,
  3;11,15,14;,
  3;11,16,15;,
  3;11,17,16;,
  3;11,12,17;,
  4;12,13,19,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,12,18,23;,
  4;18,19,25,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,18,24,29;,
  4;24,25,31,30;,
  4;25,26,32,31;,
  4;26,27,33,32;,
  4;27,28,34,33;,
  4;28,29,35,34;,
  4;29,24,30,35;,
  4;30,31,37,36;,
  4;31,32,38,37;,
  4;32,33,39,38;,
  4;33,34,40,39;,
  4;34,35,41,40;,
  4;35,30,36,41;,
  3;36,37,42;,
  3;37,38,42;,
  3;38,39,42;,
  3;39,40,42;,
  3;40,41,42;,
  3;41,36,42;,
  3;43,45,44;,
  3;43,46,45;,
  3;43,47,46;,
  3;43,48,47;,
  3;43,49,48;,
  3;43,44,49;,
  4;44,45,51,50;,
  4;45,46,52,51;,
  4;46,47,53,52;,
  4;47,48,54,53;,
  4;48,49,55,54;,
  4;49,44,50,55;,
  4;50,51,57,56;,
  4;51,52,58,57;,
  4;52,53,59,58;,
  4;53,54,60,59;,
  4;54,55,61,60;,
  4;55,50,56,61;,
  4;56,57,63,62;,
  4;57,58,64,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,61,67,66;,
  4;61,56,62,67;,
  4;62,63,69,68;,
  4;63,64,70,69;,
  4;64,65,71,70;,
  4;65,66,72,71;,
  4;66,67,73,72;,
  4;67,62,68,73;,
  3;68,69,74;,
  3;69,70,74;,
  3;70,71,74;,
  3;71,72,74;,
  3;72,73,74;,
  3;73,68,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;6,6,6,6;,
  4;84,84,84,84;,
  4;85,85,85,85;;
 }
 MeshTextureCoords {
  142;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.166670;0.000000;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.666670;,
  0.500000;1.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  0.833330;0.333330;,
  0.833330;0.000000;,
  0.833330;0.666670;,
  0.833330;1.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
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
