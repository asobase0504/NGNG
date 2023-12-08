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
 144;
 0.25808;12.75493;0.25445;,
 0.00000;12.75493;0.84661;,
 0.00000;12.99505;0.00282;,
 0.84661;12.75493;0.00000;,
 0.00000;15.01256;0.00000;,
 0.00000;12.75493;0.84661;,
 -0.25225;12.75493;0.26184;,
 -0.84661;12.75493;0.00000;,
 -0.26093;12.75493;-0.25316;,
 0.00000;12.75493;-0.84661;,
 0.25069;12.75493;-0.26184;,
 0.84661;12.75493;0.00000;,
 -0.12414;12.93506;-0.13378;,
 0.12414;12.93506;-0.13378;,
 0.12414;4.99510;-0.13378;,
 -0.12414;4.99510;-0.13378;,
 0.12414;12.93506;-0.13378;,
 0.12414;12.93506;0.13378;,
 0.12414;4.99510;0.13378;,
 0.12414;4.99510;-0.13378;,
 0.12414;12.93506;0.13378;,
 -0.12414;12.93506;0.13378;,
 -0.12414;4.99510;0.13378;,
 0.12414;4.99510;0.13378;,
 -0.12414;12.93506;0.13378;,
 -0.12414;12.93506;-0.13378;,
 -0.12414;4.99510;-0.13378;,
 -0.12414;4.99510;0.13378;,
 0.12414;12.93506;-0.13378;,
 -0.12414;12.93506;-0.13378;,
 -0.12414;4.99510;-0.13378;,
 0.12414;4.99510;-0.13378;,
 -0.10269;7.21398;0.11571;,
 -0.73348;6.95123;0.11571;,
 -0.95920;6.66156;0.11571;,
 -1.24970;5.70958;0.11571;,
 -1.01728;5.00831;0.11571;,
 -0.65428;3.84860;0.11571;,
 -0.10269;5.00677;0.11571;,
 -0.10269;7.21398;-0.10260;,
 -1.24970;5.70958;-0.10260;,
 -0.95920;6.66156;-0.10260;,
 -0.73348;6.95123;-0.10260;,
 -0.10269;5.00677;-0.10260;,
 -0.65428;3.84860;-0.10260;,
 -1.01728;5.00831;-0.10260;,
 -0.73348;6.95123;0.11571;,
 -0.10269;7.21398;0.11571;,
 -0.95920;6.66156;0.11571;,
 -0.73348;6.95123;0.11571;,
 -0.95920;6.66156;0.11571;,
 -1.24970;5.70958;0.11571;,
 -1.24970;5.70958;0.11571;,
 -1.01728;5.00831;0.11571;,
 -0.65428;3.84860;0.11571;,
 -1.01728;5.00831;0.11571;,
 -0.10269;5.00677;0.11571;,
 -0.65428;3.84860;0.11571;,
 -0.10269;7.21398;0.11571;,
 -0.10269;5.00677;0.11571;,
 0.09397;7.21398;0.12947;,
 0.09397;6.95123;0.76027;,
 0.09397;6.66156;0.98599;,
 0.09397;5.70958;1.27648;,
 0.09397;5.00831;1.04407;,
 0.09397;3.84860;0.68106;,
 0.09397;5.00677;0.12947;,
 -0.12326;7.21398;0.12947;,
 -0.12326;5.70958;1.27648;,
 -0.12326;6.66156;0.98599;,
 -0.12326;6.95123;0.76027;,
 -0.12326;5.00677;0.12947;,
 -0.12326;3.84860;0.68106;,
 -0.12326;5.00831;1.04407;,
 0.09397;6.95123;0.76027;,
 0.09397;7.21398;0.12947;,
 0.09397;6.66156;0.98599;,
 0.09397;6.95123;0.76027;,
 0.09397;6.66156;0.98599;,
 0.09397;5.70958;1.27648;,
 0.09397;5.70958;1.27648;,
 0.09397;5.00831;1.04407;,
 0.09397;3.84860;0.68106;,
 0.09397;5.00831;1.04407;,
 0.09397;5.00677;0.12947;,
 0.09397;3.84860;0.68106;,
 0.09397;7.21398;0.12947;,
 0.09397;5.00677;0.12947;,
 -0.12271;7.21398;-0.15240;,
 -0.12271;6.95123;-0.78320;,
 -0.12271;6.66156;-1.00892;,
 -0.12271;5.70958;-1.29941;,
 -0.12271;5.00831;-1.06700;,
 -0.12271;3.84860;-0.70400;,
 -0.12271;5.00677;-0.15240;,
 0.09343;7.21398;-0.15240;,
 0.09343;5.70958;-1.29941;,
 0.09343;6.66156;-1.00892;,
 0.09343;6.95123;-0.78320;,
 0.09343;5.00677;-0.15240;,
 0.09343;3.84860;-0.70400;,
 0.09343;5.00831;-1.06700;,
 -0.12271;6.95123;-0.78320;,
 -0.12271;7.21398;-0.15240;,
 -0.12271;6.66156;-1.00892;,
 -0.12271;6.95123;-0.78320;,
 -0.12271;6.66156;-1.00892;,
 -0.12271;5.70958;-1.29941;,
 -0.12271;5.70958;-1.29941;,
 -0.12271;5.00831;-1.06700;,
 -0.12271;3.84860;-0.70400;,
 -0.12271;5.00831;-1.06700;,
 -0.12271;5.00677;-0.15240;,
 -0.12271;3.84860;-0.70400;,
 -0.12271;7.21398;-0.15240;,
 -0.12271;5.00677;-0.15240;,
 0.09228;7.21398;-0.10207;,
 0.72308;6.95123;-0.10207;,
 0.94880;6.66156;-0.10207;,
 1.23929;5.70958;-0.10207;,
 1.00688;5.00831;-0.10207;,
 0.64387;3.84860;-0.10207;,
 0.09228;5.00677;-0.10207;,
 0.09228;7.21398;0.11516;,
 1.23929;5.70958;0.11516;,
 0.94880;6.66156;0.11516;,
 0.72308;6.95123;0.11516;,
 0.09228;5.00677;0.11516;,
 0.64387;3.84860;0.11516;,
 1.00688;5.00831;0.11516;,
 0.72308;6.95123;-0.10207;,
 0.09228;7.21398;-0.10207;,
 0.94880;6.66156;-0.10207;,
 0.72308;6.95123;-0.10207;,
 0.94880;6.66156;-0.10207;,
 1.23929;5.70958;-0.10207;,
 1.23929;5.70958;-0.10207;,
 1.00688;5.00831;-0.10207;,
 0.64387;3.84860;-0.10207;,
 1.00688;5.00831;-0.10207;,
 0.09228;5.00677;-0.10207;,
 0.64387;3.84860;-0.10207;,
 0.09228;7.21398;-0.10207;,
 0.09228;5.00677;-0.10207;;
 
 74;
 3;0,1,2;,
 3;0,3,4;,
 3;4,5,0;,
 3;6,1,4;,
 3;4,7,6;,
 3;8,7,4;,
 3;4,9,8;,
 3;4,10,9;,
 3;4,11,10;,
 3;2,5,6;,
 3;6,7,2;,
 3;7,8,2;,
 3;2,8,9;,
 3;9,10,2;,
 3;2,10,3;,
 3;11,0,2;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;24,17,28,29;,
 4;30,31,18,27;,
 4;32,33,34,35;,
 4;32,36,37,38;,
 3;32,35,36;,
 4;39,40,41,42;,
 4;39,43,44,45;,
 3;39,45,40;,
 4;42,46,47,39;,
 4;42,41,48,49;,
 4;50,41,40,51;,
 4;52,40,45,53;,
 4;45,44,54,55;,
 4;43,56,57,44;,
 4;39,58,59,43;,
 4;60,61,62,63;,
 4;60,64,65,66;,
 3;60,63,64;,
 4;67,68,69,70;,
 4;67,71,72,73;,
 3;67,73,68;,
 4;70,74,75,67;,
 4;70,69,76,77;,
 4;78,69,68,79;,
 4;80,68,73,81;,
 4;73,72,82,83;,
 4;71,84,85,72;,
 4;67,86,87,71;,
 4;88,89,90,91;,
 4;88,92,93,94;,
 3;88,91,92;,
 4;95,96,97,98;,
 4;95,99,100,101;,
 3;95,101,96;,
 4;98,102,103,95;,
 4;98,97,104,105;,
 4;106,97,96,107;,
 4;108,96,101,109;,
 4;101,100,110,111;,
 4;99,112,113,100;,
 4;95,114,115,99;,
 4;116,117,118,119;,
 4;116,120,121,122;,
 3;116,119,120;,
 4;123,124,125,126;,
 4;123,127,128,129;,
 3;123,129,124;,
 4;126,130,131,123;,
 4;126,125,132,133;,
 4;134,125,124,135;,
 4;136,124,129,137;,
 4;129,128,138,139;,
 4;127,140,141,128;,
 4;123,142,143,127;;
 
 MeshMaterialList {
  2;
  74;
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
  1;;
  Material {
   0.304000;0.304000;0.304000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.385882;0.313726;0.169412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  92;
  -0.905169;0.149246;-0.397988;,
  0.392530;0.147199;0.907884;,
  -0.531830;-0.814513;-0.231788;,
  -0.398624;0.149484;0.904850;,
  0.697127;0.158499;0.699209;,
  0.701366;0.158484;-0.694959;,
  -0.700855;0.158957;0.695367;,
  -0.695889;0.158961;-0.700336;,
  -0.390916;-0.832212;-0.393201;,
  -0.155355;-0.985861;-0.062786;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.906599;0.148172;0.395125;,
  -0.908249;0.146921;0.391788;,
  -0.392450;0.147169;-0.907923;,
  0.909230;0.146171;-0.389789;,
  0.397775;0.149166;-0.905276;,
  0.419692;-0.892635;0.164504;,
  0.535761;-0.812126;-0.231109;,
  0.393432;-0.832978;-0.389048;,
  0.233149;-0.815815;-0.529232;,
  0.229563;-0.815626;0.531089;,
  0.386535;-0.835769;0.389976;,
  0.526129;-0.818336;0.231330;,
  -0.535772;-0.812522;0.229687;,
  -0.392143;-0.834960;0.386089;,
  -0.230634;-0.819329;0.524888;,
  -0.231933;-0.811444;-0.536438;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.384517;0.923118;0.000000;,
  -0.788796;0.614655;0.000000;,
  -0.956462;0.291858;0.000000;,
  -0.949228;-0.314589;0.000000;,
  -0.954341;-0.298720;0.000000;,
  0.902834;-0.429989;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.606592;0.795014;0.000000;,
  -0.887429;0.460944;0.000000;,
  -0.999929;-0.011927;0.000000;,
  -0.951818;-0.306665;0.000000;,
  0.975406;-0.220416;-0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.923118;0.384517;,
  0.000000;0.614647;0.788803;,
  0.000000;0.291862;0.956460;,
  0.000000;-0.314589;0.949228;,
  0.000000;-0.298720;0.954341;,
  0.000000;-0.429989;-0.902834;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.795010;0.606596;,
  0.000000;0.460941;0.887431;,
  0.000000;-0.011925;0.999929;,
  0.000000;-0.306665;0.951818;,
  0.000000;-0.220416;-0.975406;,
  -1.000000;0.000001;0.000005;,
  -1.000000;0.000001;0.000004;,
  -1.000000;-0.000001;0.000006;,
  -1.000000;-0.000002;0.000006;,
  -1.000000;-0.000006;0.000009;,
  1.000000;0.000000;0.000000;,
  0.000000;0.923119;-0.384515;,
  0.000000;0.614647;-0.788803;,
  0.000000;0.291857;-0.956462;,
  0.000000;-0.314589;-0.949228;,
  0.000000;-0.298717;-0.954342;,
  0.000000;-0.429993;0.902832;,
  0.000000;0.000000;1.000000;,
  0.000000;0.795011;-0.606595;,
  0.000000;0.460939;-0.887432;,
  0.000000;-0.011927;-0.999929;,
  0.000000;-0.306663;-0.951818;,
  0.000000;-0.220417;0.975406;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.384517;0.923118;0.000000;,
  0.788796;0.614655;0.000000;,
  0.956462;0.291858;0.000000;,
  0.949228;-0.314589;-0.000000;,
  0.954341;-0.298720;-0.000000;,
  -0.902834;-0.429989;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.606592;0.795014;0.000000;,
  0.887429;0.460944;0.000000;,
  0.999929;-0.011927;-0.000000;,
  0.951818;-0.306665;-0.000000;,
  -0.975406;-0.220416;0.000000;;
  74;
  3;8,2,9;,
  3;4,1,4;,
  3;4,13,4;,
  3;6,14,6;,
  3;6,3,6;,
  3;7,15,7;,
  3;7,0,7;,
  3;5,5,16;,
  3;5,17,5;,
  3;18,19,20;,
  3;20,21,9;,
  3;22,23,18;,
  3;9,23,24;,
  3;25,26,9;,
  3;9,26,27;,
  3;28,8,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;32,32,32,32;,
  3;32,32,32;,
  4;33,33,33,33;,
  4;33,33,33,33;,
  3;33,33,33;,
  4;41,34,34,34;,
  4;41,42,35,35;,
  4;36,42,43,36;,
  4;37,43,44,37;,
  4;44,38,38,38;,
  4;45,39,39,39;,
  4;40,40,40,45;,
  4;46,46,46,46;,
  4;46,46,46,46;,
  3;46,46,46;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  3;47,47,47;,
  4;55,48,48,48;,
  4;55,56,49,49;,
  4;50,56,57,50;,
  4;51,57,58,51;,
  4;58,52,52,52;,
  4;59,53,53,53;,
  4;54,54,54,59;,
  4;62,64,64,63;,
  4;62,61,60,60;,
  3;62,63,61;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  3;65,65,65;,
  4;73,66,66,66;,
  4;73,74,67,67;,
  4;68,74,75,68;,
  4;69,75,76,69;,
  4;76,70,70,70;,
  4;77,71,71,71;,
  4;72,72,72,77;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  3;78,78,78;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  3;79,79,79;,
  4;87,80,80,80;,
  4;87,88,81,81;,
  4;82,88,89,82;,
  4;83,89,90,83;,
  4;90,84,84,84;,
  4;91,85,85,85;,
  4;86,86,86,91;;
 }
 MeshTextureCoords {
  144;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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
  1.000000;0.000000;,
  0.750000;0.500000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
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
  0.750000;0.500000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
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
  0.750000;0.500000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
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
  0.750000;0.500000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
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