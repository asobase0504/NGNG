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
 225;
 -11.77132;1.32267;-0.68381;,
 11.77132;1.32267;-0.68381;,
 11.77132;-0.04495;-0.68381;,
 -11.77132;-0.04495;-0.68381;,
 11.77132;1.32267;-0.68381;,
 11.77132;1.32267;0.68381;,
 11.77132;-0.04495;0.68381;,
 11.77132;-0.04495;-0.68381;,
 11.77132;1.32267;0.68381;,
 -11.77132;1.32267;0.68381;,
 -11.77132;-0.04495;0.68381;,
 11.77132;-0.04495;0.68381;,
 -11.77132;1.32267;0.68381;,
 -11.77132;1.32267;-0.68381;,
 -11.77132;-0.04495;-0.68381;,
 -11.77132;-0.04495;0.68381;,
 11.77132;1.32267;-0.68381;,
 -11.77132;1.32267;-0.68381;,
 -11.77132;-0.04495;-0.68381;,
 11.77132;-0.04495;-0.68381;,
 -11.77132;3.37767;-0.68381;,
 11.77132;3.37767;-0.68381;,
 11.77132;2.01005;-0.68381;,
 -11.77132;2.01005;-0.68381;,
 11.77132;3.37767;-0.68381;,
 11.77132;3.37767;0.68381;,
 11.77132;2.01005;0.68381;,
 11.77132;2.01005;-0.68381;,
 11.77132;3.37767;0.68381;,
 -11.77132;3.37767;0.68381;,
 -11.77132;2.01005;0.68381;,
 11.77132;2.01005;0.68381;,
 -11.77132;3.37767;0.68381;,
 -11.77132;3.37767;-0.68381;,
 -11.77132;2.01005;-0.68381;,
 -11.77132;2.01005;0.68381;,
 11.77132;3.37767;-0.68381;,
 -11.77132;3.37767;-0.68381;,
 -11.77132;2.01005;-0.68381;,
 11.77132;2.01005;-0.68381;,
 -11.77132;5.42270;-0.68381;,
 11.77132;5.42270;-0.68381;,
 11.77132;4.05508;-0.68381;,
 -11.77132;4.05508;-0.68381;,
 11.77132;5.42270;-0.68381;,
 11.77132;5.42270;0.68381;,
 11.77132;4.05508;0.68381;,
 11.77132;4.05508;-0.68381;,
 11.77132;5.42270;0.68381;,
 -11.77132;5.42270;0.68381;,
 -11.77132;4.05508;0.68381;,
 11.77132;4.05508;0.68381;,
 -11.77132;5.42270;0.68381;,
 -11.77132;5.42270;-0.68381;,
 -11.77132;4.05508;-0.68381;,
 -11.77132;4.05508;0.68381;,
 11.77132;5.42270;-0.68381;,
 -11.77132;5.42270;-0.68381;,
 -11.77132;4.05508;-0.68381;,
 11.77132;4.05508;-0.68381;,
 -11.77132;7.43834;-0.68381;,
 11.77132;7.43834;-0.68381;,
 11.77132;5.78619;-0.68381;,
 -11.77132;6.07071;-0.68381;,
 11.77132;7.43834;-0.68381;,
 11.77132;7.43834;0.68381;,
 11.77132;6.07071;0.68381;,
 11.77132;5.78619;-0.68381;,
 11.77132;7.43834;0.68381;,
 -11.77132;7.43834;0.68381;,
 -11.77132;6.07071;0.68381;,
 11.77132;6.07071;0.68381;,
 -11.77132;7.43834;0.68381;,
 -11.77132;7.43834;-0.68381;,
 -11.77132;6.07071;-0.68381;,
 -11.77132;6.07071;0.68381;,
 11.77132;7.43834;-0.68381;,
 -11.77132;7.43834;-0.68381;,
 -11.77132;6.07071;-0.68381;,
 11.77132;5.78619;-0.68381;,
 -11.77132;9.38885;-0.68381;,
 11.77132;9.38885;-0.68381;,
 11.77132;8.02123;-0.68381;,
 -11.77132;8.02123;-0.68381;,
 11.77132;9.38885;-0.68381;,
 11.77132;9.38885;0.68381;,
 11.77132;8.02123;0.68381;,
 11.77132;8.02123;-0.68381;,
 11.77132;9.38885;0.68381;,
 -11.77132;9.38885;0.68381;,
 -11.77132;8.02123;0.68381;,
 11.77132;8.02123;0.68381;,
 -11.77132;9.38885;0.68381;,
 -11.77132;9.38885;-0.68381;,
 -11.77132;8.02123;-0.68381;,
 -11.77132;8.02123;0.68381;,
 11.77132;9.38885;-0.68381;,
 -11.77132;9.38885;-0.68381;,
 -11.77132;8.02123;-0.68381;,
 11.77132;8.02123;-0.68381;,
 -11.77132;11.31203;-0.68381;,
 11.77132;11.31203;-0.68381;,
 11.77132;9.94440;-0.68381;,
 -11.77132;9.94440;-0.68381;,
 11.77132;11.31203;-0.68381;,
 11.77132;11.31203;0.68381;,
 11.77132;9.94440;0.68381;,
 11.77132;9.94440;-0.68381;,
 11.77132;11.31203;0.68381;,
 -11.77132;11.31203;0.68381;,
 -11.77132;9.94440;0.68381;,
 11.77132;9.94440;0.68381;,
 -11.77132;11.31203;0.68381;,
 -11.77132;11.31203;-0.68381;,
 -11.77132;9.94440;-0.68381;,
 -11.77132;9.94440;0.68381;,
 11.77132;11.31203;-0.68381;,
 -11.77132;11.31203;-0.68381;,
 -11.77132;9.94440;-0.68381;,
 11.77132;9.94440;-0.68381;,
 -11.77132;13.25175;-0.68381;,
 11.77132;13.25175;-0.68381;,
 11.77132;11.88412;-0.68381;,
 -11.77132;11.88412;-0.68381;,
 11.77132;13.25175;-0.68381;,
 11.77132;13.25175;0.68381;,
 11.77132;11.88412;0.68381;,
 11.77132;11.88412;-0.68381;,
 11.77132;13.25175;0.68381;,
 -11.77132;13.25175;0.68381;,
 -11.77132;11.88412;0.68381;,
 11.77132;11.88412;0.68381;,
 -11.77132;13.25175;0.68381;,
 -11.77132;13.25175;-0.68381;,
 -11.77132;11.88412;-0.68381;,
 -11.77132;11.88412;0.68381;,
 11.77132;13.25175;-0.68381;,
 -11.77132;13.25175;-0.68381;,
 -11.77132;11.88412;-0.68381;,
 11.77132;11.88412;-0.68381;,
 -11.77132;15.16868;-0.68381;,
 11.77132;15.16868;-0.68381;,
 11.77132;13.80105;-0.68381;,
 -11.77132;13.80105;-0.68381;,
 11.77132;15.16868;-0.68381;,
 11.77132;15.16868;0.68381;,
 11.77132;13.80105;0.68381;,
 11.77132;13.80105;-0.68381;,
 11.77132;15.16868;0.68381;,
 -11.77132;15.16868;0.68381;,
 -11.77132;13.80105;0.68381;,
 11.77132;13.80105;0.68381;,
 -11.77132;15.16868;0.68381;,
 -11.77132;15.16868;-0.68381;,
 -11.77132;13.80105;-0.68381;,
 -11.77132;13.80105;0.68381;,
 11.77132;15.16868;-0.68381;,
 -11.77132;15.16868;-0.68381;,
 -11.77132;13.80105;-0.68381;,
 11.77132;13.80105;-0.68381;,
 -11.77132;17.08475;-0.68381;,
 11.77132;17.08475;-0.68381;,
 11.77132;15.71712;-0.68381;,
 -11.77132;15.71712;-0.68381;,
 11.77132;17.08475;-0.68381;,
 11.77132;17.08475;0.68381;,
 11.77132;15.71712;0.68381;,
 11.77132;15.71712;-0.68381;,
 11.77132;17.08475;0.68381;,
 -11.77132;17.08475;0.68381;,
 -11.77132;15.71712;0.68381;,
 11.77132;15.71712;0.68381;,
 -11.77132;17.08475;0.68381;,
 -11.77132;17.08475;-0.68381;,
 -11.77132;15.71712;-0.68381;,
 -11.77132;15.71712;0.68381;,
 11.77132;17.08475;-0.68381;,
 -11.77132;17.08475;-0.68381;,
 -11.77132;15.71712;-0.68381;,
 11.77132;15.71712;-0.68381;,
 -11.77132;19.00510;-0.68381;,
 11.77132;19.00510;-0.68381;,
 11.77132;17.63747;-0.68381;,
 -11.77132;17.63747;-0.68381;,
 11.77132;19.00510;-0.68381;,
 11.77132;19.00510;0.68381;,
 11.77132;17.63747;0.68381;,
 11.77132;17.63747;-0.68381;,
 11.77132;19.00510;0.68381;,
 -11.77132;19.00510;0.68381;,
 -11.77132;17.63747;0.68381;,
 11.77132;17.63747;0.68381;,
 -11.77132;19.00510;0.68381;,
 -11.77132;19.00510;-0.68381;,
 -11.77132;17.63747;-0.68381;,
 -11.77132;17.63747;0.68381;,
 11.77132;19.00510;-0.68381;,
 -11.77132;19.00510;-0.68381;,
 -11.77132;17.63747;-0.68381;,
 11.77132;17.63747;-0.68381;,
 0.00000;0.30384;-0.88915;,
 0.43261;-0.09462;-1.00027;,
 0.43261;19.54828;-1.00027;,
 0.00000;19.19998;-0.88915;,
 0.00000;-0.49309;-1.11144;,
 0.00000;19.89649;-1.11144;,
 -0.43261;-0.09462;-1.00027;,
 -0.43261;19.54828;-1.00027;,
 0.00000;0.30384;-0.88915;,
 0.00000;19.19998;-0.88915;,
 0.43261;19.54828;1.00027;,
 0.00000;19.19998;0.88915;,
 0.00000;19.89649;1.11144;,
 -0.43261;19.54828;1.00027;,
 0.00000;19.19998;0.88915;,
 0.43261;-0.09462;1.00027;,
 0.00000;0.30384;0.88915;,
 0.00000;-0.49309;1.11144;,
 -0.43261;-0.09462;1.00027;,
 0.00000;0.30384;0.88915;,
 0.43261;-0.09462;-1.00027;,
 0.00000;0.30384;-0.88915;,
 0.00000;-0.49309;-1.11144;,
 -0.43261;-0.09462;-1.00027;,
 0.00000;0.30384;-0.88915;;
 
 76;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;201,204,205,202;,
 4;204,206,207,205;,
 4;206,208,209,207;,
 4;203,202,210,211;,
 4;202,205,212,210;,
 4;205,207,213,212;,
 4;207,209,214,213;,
 4;211,210,215,216;,
 4;210,212,217,215;,
 4;212,213,218,217;,
 4;213,214,219,218;,
 4;216,215,220,221;,
 4;215,217,222,220;,
 4;217,218,223,222;,
 4;218,219,224,223;;
 
 MeshMaterialList {
  2;
  76;
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
   0.800000;0.000000;0.072000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.548800;0.700000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  23;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.248784;0.000000;0.968559;,
  -0.248885;0.000000;-0.968533;,
  0.627126;-0.778918;-0.000000;,
  0.627019;0.779004;0.000000;,
  -0.627019;0.779004;0.000000;,
  0.248784;0.000000;-0.968559;,
  -0.248885;0.000000;0.968533;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.005947;-0.994729;0.102371;,
  0.248885;0.000000;-0.968533;,
  -0.248784;0.000000;0.968559;,
  -0.627126;-0.778918;0.000000;,
  0.248885;0.000000;0.968533;,
  -0.248784;0.000000;-0.968559;,
  0.677484;0.735538;0.000000;,
  0.677488;-0.735534;-0.000000;,
  -0.677488;-0.735534;0.000000;,
  -0.677484;0.735538;0.000000;;
  76;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;2,3,3,2;,
  4;14,0,0,14;,
  4;0,4,4,0;,
  4;15,2,2,15;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;16,16,16,16;,
  4;0,8,8,0;,
  4;17,2,2,17;,
  4;2,9,9,2;,
  4;18,0,0,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;;
 }
 MeshTextureCoords {
  225;
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
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  1.000000;1.000000;;
 }
}
