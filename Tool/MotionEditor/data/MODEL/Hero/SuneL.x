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
 65;
 2.17427;-26.53414;1.85285;,
 4.78530;-12.53007;3.36297;,
 4.07062;-12.65656;4.93337;,
 1.50825;-26.50343;2.52961;,
 4.85859;-12.05192;-1.43811;,
 2.19350;-26.47731;-0.06693;,
 4.01750;-3.74243;-0.03211;,
 2.99758;-3.56144;3.54693;,
 2.08427;-4.46883;-4.92452;,
 1.82933;-3.59380;4.78418;,
 0.32986;-11.58305;-3.88285;,
 0.37014;-26.29634;-1.12677;,
 2.19394;-26.47601;-0.11738;,
 -1.89439;-26.25241;1.61784;,
 -0.99029;-26.30932;2.02298;,
 -0.38440;-9.79331;4.88799;,
 -4.13116;-11.89497;4.29773;,
 1.54918;-26.45917;1.04039;,
 2.02323;-26.48281;0.62594;,
 1.53453;-26.50244;2.41751;,
 -0.39996;-26.36190;2.40432;,
 -1.67982;-3.69588;4.84074;,
 1.34755;-26.44921;1.21659;,
 -3.48130;-4.03405;3.02512;,
 -2.55140;-3.49770;3.52734;,
 -0.78570;-4.31464;-5.22352;,
 -1.87469;-26.19411;-0.69580;,
 -3.18289;-3.47039;-4.63572;,
 -2.78047;-3.22610;3.95156;,
 -4.06374;-11.20645;-1.99798;,
 -1.88791;-26.23338;0.85741;,
 -5.35690;-11.49611;-0.15342;,
 -4.56235;-3.81653;-0.12688;,
 -0.28891;0.27433;-0.05511;,
 1.98813;-0.23297;-0.05511;,
 0.84960;-0.23297;-2.24483;,
 -1.42742;-0.23297;-2.24483;,
 -2.56591;-0.23297;-0.05511;,
 -1.42742;-0.23297;2.13460;,
 0.84960;-0.23297;2.13460;,
 3.65504;-1.61893;-0.05511;,
 1.68304;-1.61893;-3.84781;,
 -2.26088;-1.61893;-3.84781;,
 -4.23281;-1.61893;-0.05511;,
 -2.26088;-1.61893;3.73758;,
 1.68304;-1.61893;3.73758;,
 4.26516;-3.51233;-0.05511;,
 1.98813;-3.51233;-4.43453;,
 -2.56591;-3.51233;-4.43453;,
 -4.84295;-3.51233;-0.05511;,
 -2.56591;-3.51233;4.32431;,
 1.98813;-3.51233;4.32431;,
 3.65504;-5.40562;-0.05511;,
 1.68304;-5.40562;-3.84781;,
 -2.26088;-5.40562;-3.84781;,
 -4.23281;-5.40562;-0.05511;,
 -2.26088;-5.40562;3.73758;,
 1.68304;-5.40562;3.73758;,
 1.98813;-6.79163;-0.05511;,
 0.84960;-6.79163;-2.24483;,
 -1.42742;-6.79163;-2.24483;,
 -2.56591;-6.79163;-0.05511;,
 -1.42742;-6.79163;2.13460;,
 0.84960;-6.79163;2.13460;,
 -0.28891;-7.29895;-0.05511;;
 
 72;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,7,1,4;,
 4;8,9,7,6;,
 4;10,8,6,4;,
 4;11,10,4,12;,
 4;13,14,15,16;,
 4;17,18,3,19;,
 4;17,11,12,18;,
 4;20,19,2,15;,
 4;15,2,9,21;,
 3;20,22,19;,
 3;20,14,13;,
 3;22,17,19;,
 3;23,16,15;,
 3;2,7,9;,
 3;2,19,3;,
 3;7,2,1;,
 3;4,5,12;,
 4;24,9,8,25;,
 3;10,11,26;,
 3;25,10,27;,
 3;15,28,23;,
 3;28,24,23;,
 4;28,21,9,24;,
 3;10,26,29;,
 3;10,29,27;,
 3;10,25,8;,
 3;15,14,20;,
 3;15,21,28;,
 4;30,31,29,26;,
 4;30,13,16,31;,
 4;31,32,27,29;,
 4;31,16,23,32;,
 4;24,27,32,23;,
 3;25,27,24;,
 3;33,34,35;,
 3;33,35,36;,
 3;33,36,37;,
 3;33,37,38;,
 3;33,38,39;,
 3;33,39,34;,
 4;34,40,41,35;,
 4;35,41,42,36;,
 4;36,42,43,37;,
 4;37,43,44,38;,
 4;38,44,45,39;,
 4;39,45,40,34;,
 4;40,46,47,41;,
 4;41,47,48,42;,
 4;42,48,49,43;,
 4;43,49,50,44;,
 4;44,50,51,45;,
 4;45,51,46,40;,
 4;46,52,53,47;,
 4;47,53,54,48;,
 4;48,54,55,49;,
 4;49,55,56,50;,
 4;50,56,57,51;,
 4;51,57,52,46;,
 4;52,58,59,53;,
 4;53,59,60,54;,
 4;54,60,61,55;,
 4;55,61,62,56;,
 4;56,62,63,57;,
 4;57,63,58,52;,
 3;58,64,59;,
 3;59,64,60;,
 3;60,64,61;,
 3;61,64,62;,
 3;62,64,63;,
 3;63,64,58;;
 
 MeshMaterialList {
  11;
  72;
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
  2;;
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
  88;
  0.888152;0.171074;0.426520;,
  0.804212;-0.231414;0.547440;,
  0.953379;0.054738;-0.296770;,
  0.460323;-0.164118;-0.872449;,
  -0.575330;-0.151977;-0.803678;,
  -0.560587;-0.194060;-0.805036;,
  -0.701342;0.044620;0.711427;,
  -0.398558;-0.165246;0.902134;,
  0.544196;-0.005250;0.838942;,
  0.942675;-0.097871;-0.319039;,
  -0.711878;-0.149355;-0.686238;,
  -0.370125;-0.089662;0.924645;,
  0.933417;-0.216346;0.286230;,
  0.956461;-0.027161;0.290593;,
  0.983280;-0.182086;0.002278;,
  0.065184;0.995320;-0.071337;,
  -0.039680;0.995307;-0.088255;,
  -0.001512;-0.184315;-0.982866;,
  -0.053551;-0.998217;-0.026366;,
  0.141407;-0.182892;-0.972910;,
  -0.239381;-0.202030;0.949674;,
  -0.545288;0.031321;0.837663;,
  -0.045720;-0.998709;-0.022125;,
  -0.348174;-0.064381;0.935217;,
  -0.314573;-0.147454;0.937711;,
  -0.056262;-0.998091;-0.025466;,
  -0.074755;-0.996671;-0.032541;,
  0.192846;0.979751;-0.053835;,
  0.024329;0.991625;-0.126836;,
  -0.685621;-0.148535;0.712644;,
  -0.993859;0.085244;-0.070554;,
  -0.971186;-0.215907;-0.100909;,
  -0.993746;-0.069855;-0.087114;,
  -0.000001;1.000000;0.000000;,
  0.435732;0.900076;0.000000;,
  0.218703;0.911796;-0.347559;,
  -0.218705;0.911797;-0.347556;,
  -0.435736;0.900075;0.000000;,
  -0.218705;0.911796;0.347556;,
  0.218702;0.911796;0.347559;,
  0.823781;0.566908;0.000000;,
  0.421909;0.594537;-0.684484;,
  -0.421913;0.594536;-0.684483;,
  -0.823786;0.566902;0.000000;,
  -0.421913;0.594537;0.684482;,
  0.421909;0.594538;0.684483;,
  1.000000;-0.000009;0.000000;,
  0.887238;-0.000008;-0.461312;,
  0.000000;-0.000008;-1.000000;,
  -1.000000;-0.000009;0.000000;,
  -0.887240;-0.000008;0.461308;,
  0.000000;-0.000008;1.000000;,
  0.823781;-0.566907;0.000000;,
  0.542935;-0.654985;-0.525562;,
  -0.225349;-0.661933;-0.714886;,
  -0.823786;-0.566901;0.000000;,
  -0.542939;-0.654984;0.525560;,
  0.225347;-0.661933;0.714887;,
  0.435745;-0.900070;0.000000;,
  0.218709;-0.911791;-0.347569;,
  -0.218711;-0.911791;-0.347566;,
  -0.435748;-0.900069;0.000000;,
  -0.218711;-0.911791;0.347566;,
  0.218709;-0.911791;0.347569;,
  -0.000001;-1.000000;0.000000;,
  -0.133523;0.986831;-0.091306;,
  0.443572;-0.112307;-0.889174;,
  -0.011065;-0.999841;-0.013976;,
  -0.080317;-0.996310;-0.030246;,
  -0.062141;-0.161477;0.984918;,
  0.392132;0.109491;0.913370;,
  -0.072199;-0.996846;-0.032947;,
  0.003767;0.991395;0.130852;,
  -0.951374;0.214441;-0.221141;,
  0.983417;-0.181315;0.003908;,
  -0.107614;-0.196286;-0.974624;,
  0.069127;0.940450;-0.332830;,
  -0.293429;0.924653;-0.242726;,
  0.271778;0.961714;-0.035241;,
  -0.969981;-0.213663;0.116125;,
  -0.038139;0.997256;0.063456;,
  -0.398063;0.906619;0.139956;,
  -0.887240;-0.000008;-0.461308;,
  0.887238;-0.000008;0.461312;,
  0.000000;-0.296009;-0.955185;,
  -0.853058;-0.274896;-0.443535;,
  0.000000;-0.296014;0.955184;,
  0.853053;-0.274909;0.443538;;
  72;
  4;12,13,8,1;,
  4;9,13,12,14;,
  4;2,0,13,9;,
  4;16,15,65,65;,
  4;17,66,2,9;,
  4;19,17,9,3;,
  4;20,7,11,21;,
  4;25,22,67,18;,
  4;25,68,68,22;,
  4;24,69,8,11;,
  4;11,8,70,23;,
  3;71,26,18;,
  3;72,72,72;,
  3;26,25,18;,
  3;6,21,11;,
  3;8,0,70;,
  3;73,73,73;,
  3;0,8,13;,
  3;9,14,74;,
  4;28,15,16,27;,
  3;17,19,5;,
  3;75,17,4;,
  3;11,29,6;,
  3;76,28,77;,
  4;76,78,15,28;,
  3;17,5,10;,
  3;17,10,4;,
  3;17,75,66;,
  3;11,7,24;,
  3;11,23,29;,
  4;31,32,10,5;,
  4;31,79,79,32;,
  4;32,30,4,10;,
  4;32,21,6,30;,
  4;28,80,81,77;,
  3;27,80,28;,
  3;33,34,35;,
  3;33,35,36;,
  3;33,36,37;,
  3;33,37,38;,
  3;33,38,39;,
  3;33,39,34;,
  4;34,40,41,35;,
  4;35,41,42,36;,
  4;36,42,43,37;,
  4;37,43,44,38;,
  4;38,44,45,39;,
  4;39,45,40,34;,
  4;40,46,47,41;,
  4;41,48,48,42;,
  4;42,82,49,43;,
  4;43,49,50,44;,
  4;44,51,51,45;,
  4;45,83,46,40;,
  4;46,52,53,47;,
  4;48,84,54,48;,
  4;82,85,55,49;,
  4;49,55,56,50;,
  4;51,86,57,51;,
  4;83,87,52,46;,
  4;52,58,59,53;,
  4;53,59,60,54;,
  4;54,60,61,55;,
  4;55,61,62,56;,
  4;56,62,63,57;,
  4;57,63,58,52;,
  3;58,64,59;,
  3;59,64,60;,
  3;60,64,61;,
  3;61,64,62;,
  3;62,64,63;,
  3;63,64,58;;
 }
}