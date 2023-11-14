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
 17;
 0.01076;37.56501;0.98457;,
 12.61786;32.07427;-3.11172;,
 0.01076;32.07427;-12.27131;,
 7.80236;32.07427;11.70878;,
 -7.78084;32.07427;11.70878;,
 -12.59631;32.07427;-3.11172;,
 17.83987;18.81845;-4.80846;,
 0.01076;18.81845;-17.76205;,
 15.77153;18.81845;16.15091;,
 -16.51905;18.81845;16.15091;,
 -17.81834;18.81845;-4.80846;,
 12.61786;5.56257;-3.11172;,
 0.01076;5.56257;-12.27131;,
 7.80236;5.56257;11.70878;,
 -7.78084;5.56257;11.70878;,
 -12.59631;5.56257;-3.11172;,
 0.01076;0.07182;0.98457;;
 
 20;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,2,5;,
 4;2,1,6,7;,
 4;1,3,8,6;,
 4;3,4,9,8;,
 4;4,5,10,9;,
 4;5,2,7,10;,
 4;7,6,11,12;,
 4;6,8,13,11;,
 4;8,9,14,13;,
 4;9,10,15,14;,
 4;10,7,12,15;,
 3;12,11,16;,
 3;11,13,16;,
 3;13,14,16;,
 3;14,15,16;,
 3;15,12,16;;
 
 MeshMaterialList {
  7;
  20;
  2,
  2,
  2,
  2,
  2,
  3,
  2,
  1,
  2,
  3,
  3,
  2,
  1,
  2,
  3,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.784000;0.496000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.128800;0.344800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.244800;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.800000;0.210400;1.000000;;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.784000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  22;
  -0.000000;1.000000;0.000000;,
  -0.000000;0.728507;-0.685039;,
  0.620618;0.746833;-0.238902;,
  0.388968;0.764626;0.513858;,
  -0.386726;0.769941;0.507576;,
  -0.615935;0.749168;-0.243661;,
  0.587785;0.000001;-0.809017;,
  0.980118;0.000001;0.198414;,
  0.000000;0.000001;1.000000;,
  -0.804410;0.196024;-0.560802;,
  0.211017;-0.794346;-0.569637;,
  0.476549;-0.794346;-0.376717;,
  0.481323;-0.828754;0.285472;,
  -0.164108;-0.794345;0.584879;,
  -0.615936;-0.749168;-0.243661;,
  -0.000000;-1.000000;0.000000;,
  -0.984043;0.000001;0.177931;,
  -0.587785;0.000001;-0.809017;,
  0.869043;-0.462399;0.175928;,
  0.000000;-0.317740;0.948178;,
  -0.862321;-0.481758;0.155922;,
  -0.557325;-0.317740;-0.767092;;
  20;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,1,5;,
  4;1,2,6,6;,
  4;2,3,7,7;,
  4;3,4,8,8;,
  4;4,5,9,16;,
  4;5,1,17,9;,
  4;6,6,11,10;,
  4;7,7,12,18;,
  4;8,8,13,19;,
  4;16,20,14,20;,
  4;9,17,21,14;,
  3;10,11,15;,
  3;11,12,15;,
  3;12,13,15;,
  3;13,14,15;,
  3;14,10,15;;
 }
}
