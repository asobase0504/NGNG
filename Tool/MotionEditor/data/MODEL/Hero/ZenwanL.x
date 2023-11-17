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
 18;
 2.85930;0.10149;-0.70732;,
 -1.73507;-10.23544;-0.00365;,
 -2.42807;-10.09852;-1.34558;,
 1.71248;0.32836;-2.92803;,
 -4.03049;-10.67083;-1.57115;,
 -0.53814;0.06354;-3.42123;,
 -4.66400;-9.56813;-0.76654;,
 -1.98781;1.20586;-1.96979;,
 -4.89716;-9.48553;0.81523;,
 -2.37363;1.34257;0.64785;,
 -4.20409;-9.62254;2.15712;,
 -1.22672;1.11587;2.86858;,
 -3.38016;-10.74771;2.56353;,
 0.53813;-0.06357;3.42123;,
 -1.96821;-10.15282;1.57808;,
 2.47347;0.23829;1.91033;,
 0.00000;0.00000;0.00000;,
 -3.70533;-10.70929;0.49619;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 3;16,0,3;,
 3;16,3,5;,
 3;16,5,7;,
 3;16,7,9;,
 3;16,9,11;,
 3;16,11,13;,
 3;16,13,15;,
 3;16,15,0;,
 3;17,2,1;,
 3;17,4,2;,
 3;17,6,4;,
 3;17,8,6;,
 3;17,10,8;,
 3;17,12,10;,
 3;17,14,12;,
 3;17,1,14;;
 
 MeshMaterialList {
  11;
  24;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
  Material {
   0.800000;0.659200;0.367200;1.000000;;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.216800;0.216800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\���炵.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.737600;0.520800;0.360800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\�Ẵz�b�g�p���c\\�ăz�b�g�p���c_�f�j����.png";
   }
  }
  Material {
   0.571200;0.401600;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\2260175.jpg";
   }
  }
  Material {
   0.075200;0.075200;0.075200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.545600;0.545600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  31;
  0.235888;0.971594;-0.019038;,
  0.898366;-0.410013;-0.157567;,
  0.557332;-0.337518;-0.758593;,
  0.225710;-0.235081;-0.945406;,
  -0.871369;0.168015;-0.460963;,
  -0.960102;0.226293;0.164307;,
  -0.640015;0.132773;0.756804;,
  -0.330763;0.039401;0.942891;,
  0.808090;-0.359526;0.466617;,
  0.616956;-0.778343;-0.116395;,
  0.457642;-0.742251;-0.489518;,
  -0.932191;-0.270294;-0.240750;,
  -0.946719;-0.285009;0.149978;,
  -0.791089;-0.302097;0.531898;,
  0.614374;-0.745076;0.259626;,
  0.283517;-0.956927;-0.062524;,
  -0.687659;0.096224;-0.719629;,
  0.621806;-0.287548;0.728473;,
  -0.029667;0.999285;0.023459;,
  -0.067159;0.995118;0.072318;,
  0.238819;0.970868;-0.019533;,
  0.535245;0.844377;-0.023232;,
  0.479154;0.875728;-0.059265;,
  0.514699;0.850204;-0.110622;,
  0.238846;0.970861;-0.019529;,
  -0.087676;0.996091;-0.010729;,
  0.344403;-0.936089;-0.071584;,
  -0.764474;-0.635284;0.109515;,
  -0.821058;-0.558356;0.118752;,
  -0.821064;-0.558344;0.118769;,
  0.344439;-0.936077;-0.071572;;
  24;
  4;1,9,10,2;,
  4;2,10,3,3;,
  4;16,16,11,4;,
  4;4,11,12,5;,
  4;5,12,13,6;,
  4;6,13,7,7;,
  4;17,17,14,8;,
  4;8,14,9,1;,
  3;0,18,19;,
  3;0,19,20;,
  3;0,20,21;,
  3;0,21,22;,
  3;0,22,23;,
  3;0,23,24;,
  3;0,24,25;,
  3;0,25,18;,
  3;15,10,9;,
  3;15,26,10;,
  3;27,11,28;,
  3;27,12,11;,
  3;27,13,12;,
  3;27,29,13;,
  3;15,14,30;,
  3;15,9,14;;
 }
}