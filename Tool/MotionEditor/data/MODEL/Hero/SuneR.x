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
 -2.17427;-26.53414;1.85285;,
 -1.50825;-26.50343;2.52961;,
 -4.07062;-12.65656;4.93337;,
 -4.78530;-12.53007;3.36297;,
 -4.85859;-12.05192;-1.43811;,
 -2.19350;-26.47731;-0.06693;,
 -4.01750;-3.74243;-0.03211;,
 -2.99758;-3.56144;3.54693;,
 -2.08427;-4.46883;-4.92452;,
 -1.82933;-3.59380;4.78418;,
 -0.32986;-11.58305;-3.88285;,
 -0.37014;-26.29634;-1.12677;,
 -2.19394;-26.47601;-0.11738;,
 1.89439;-26.25241;1.61784;,
 4.13116;-11.89497;4.29773;,
 0.38440;-9.79331;4.88799;,
 0.99029;-26.30932;2.02298;,
 -1.54918;-26.45917;1.04039;,
 -1.53453;-26.50244;2.41751;,
 -2.02323;-26.48281;0.62594;,
 0.39996;-26.36190;2.40432;,
 1.67982;-3.69588;4.84074;,
 -1.34755;-26.44921;1.21659;,
 3.48130;-4.03405;3.02512;,
 2.55140;-3.49770;3.52734;,
 0.78570;-4.31464;-5.22352;,
 1.87469;-26.19411;-0.69580;,
 3.18289;-3.47039;-4.63572;,
 2.78047;-3.22610;3.95156;,
 4.06374;-11.20645;-1.99798;,
 1.88791;-26.23338;0.85741;,
 5.35690;-11.49611;-0.15342;,
 4.56235;-3.81653;-0.12688;,
 0.28891;0.27433;-0.05511;,
 -0.84960;-0.23297;-2.24483;,
 -1.98813;-0.23297;-0.05511;,
 1.42742;-0.23297;-2.24483;,
 2.56591;-0.23297;-0.05511;,
 1.42742;-0.23297;2.13460;,
 -0.84960;-0.23297;2.13460;,
 -1.68304;-1.61893;-3.84781;,
 -3.65504;-1.61893;-0.05511;,
 2.26088;-1.61893;-3.84781;,
 4.23281;-1.61893;-0.05511;,
 2.26088;-1.61893;3.73758;,
 -1.68304;-1.61893;3.73758;,
 -1.98813;-3.51233;-4.43453;,
 -4.26516;-3.51233;-0.05511;,
 2.56591;-3.51233;-4.43453;,
 4.84295;-3.51233;-0.05511;,
 2.56591;-3.51233;4.32431;,
 -1.98813;-3.51233;4.32431;,
 -1.68304;-5.40562;-3.84781;,
 -3.65504;-5.40562;-0.05511;,
 2.26088;-5.40562;-3.84781;,
 4.23281;-5.40562;-0.05511;,
 2.26088;-5.40562;3.73758;,
 -1.68304;-5.40562;3.73758;,
 -0.84960;-6.79163;-2.24483;,
 -1.98813;-6.79163;-0.05511;,
 1.42742;-6.79163;-2.24483;,
 2.56591;-6.79163;-0.05511;,
 1.42742;-6.79163;2.13460;,
 -0.84960;-6.79163;2.13460;,
 0.28891;-7.29895;-0.05511;;
 
 72;
 4;0,1,2,3;,
 4;4,5,0,3;,
 4;6,4,3,7;,
 4;8,6,7,9;,
 4;10,4,6,8;,
 4;11,12,4,10;,
 4;13,14,15,16;,
 4;17,18,1,19;,
 4;17,19,12,11;,
 4;20,15,2,18;,
 4;15,21,9,2;,
 3;20,18,22;,
 3;20,13,16;,
 3;22,18,17;,
 3;23,15,14;,
 3;2,9,7;,
 3;2,1,18;,
 3;7,3,2;,
 3;4,12,5;,
 4;24,25,8,9;,
 3;10,26,11;,
 3;25,27,10;,
 3;15,23,28;,
 3;28,23,24;,
 4;28,24,9,21;,
 3;10,29,26;,
 3;10,27,29;,
 3;10,8,25;,
 3;15,20,16;,
 3;15,28,21;,
 4;30,26,29,31;,
 4;30,31,14,13;,
 4;31,29,27,32;,
 4;31,32,23,14;,
 4;24,23,32,27;,
 3;25,24,27;,
 3;33,34,35;,
 3;33,36,34;,
 3;33,37,36;,
 3;33,38,37;,
 3;33,39,38;,
 3;33,35,39;,
 4;35,34,40,41;,
 4;34,36,42,40;,
 4;36,37,43,42;,
 4;37,38,44,43;,
 4;38,39,45,44;,
 4;39,35,41,45;,
 4;41,40,46,47;,
 4;40,42,48,46;,
 4;42,43,49,48;,
 4;43,44,50,49;,
 4;44,45,51,50;,
 4;45,41,47,51;,
 4;47,46,52,53;,
 4;46,48,54,52;,
 4;48,49,55,54;,
 4;49,50,56,55;,
 4;50,51,57,56;,
 4;51,47,53,57;,
 4;53,52,58,59;,
 4;52,54,60,58;,
 4;54,55,61,60;,
 4;55,56,62,61;,
 4;56,57,63,62;,
 4;57,53,59,63;,
 3;59,58,64;,
 3;58,60,64;,
 3;60,61,64;,
 3;61,62,64;,
 3;62,63,64;,
 3;63,59,64;;
 
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
    "C:\\Users\\student\\Desktop\\さらし.png";
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
    "C:\\Users\\student\\Desktop\\夏のホットパンツ\\夏ホットパンツ_デニム風.png";
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
  -0.888152;0.171074;0.426520;,
  -0.804212;-0.231414;0.547440;,
  -0.953379;0.054738;-0.296770;,
  -0.460323;-0.164118;-0.872449;,
  0.575330;-0.151977;-0.803678;,
  0.560587;-0.194060;-0.805036;,
  0.701342;0.044620;0.711427;,
  0.398558;-0.165246;0.902134;,
  -0.544196;-0.005250;0.838942;,
  -0.942675;-0.097871;-0.319039;,
  0.711878;-0.149355;-0.686238;,
  0.370125;-0.089662;0.924645;,
  -0.933417;-0.216346;0.286230;,
  -0.956461;-0.027161;0.290593;,
  -0.983280;-0.182086;0.002278;,
  -0.065184;0.995320;-0.071337;,
  0.039680;0.995307;-0.088255;,
  0.001512;-0.184315;-0.982866;,
  0.053551;-0.998217;-0.026366;,
  -0.141407;-0.182892;-0.972910;,
  0.239381;-0.202030;0.949674;,
  0.545288;0.031321;0.837663;,
  0.045720;-0.998709;-0.022125;,
  0.348174;-0.064381;0.935217;,
  0.314573;-0.147454;0.937711;,
  0.056262;-0.998091;-0.025466;,
  0.074755;-0.996671;-0.032541;,
  -0.192846;0.979751;-0.053835;,
  -0.024329;0.991625;-0.126836;,
  0.685621;-0.148535;0.712644;,
  0.993859;0.085244;-0.070554;,
  0.971186;-0.215907;-0.100909;,
  0.993746;-0.069855;-0.087114;,
  0.000001;1.000000;0.000000;,
  -0.435732;0.900076;0.000000;,
  -0.218703;0.911796;-0.347559;,
  0.218705;0.911797;-0.347556;,
  0.435736;0.900075;0.000000;,
  0.218705;0.911796;0.347556;,
  -0.218702;0.911796;0.347559;,
  -0.823781;0.566908;0.000000;,
  -0.421909;0.594537;-0.684484;,
  0.421913;0.594536;-0.684483;,
  0.823786;0.566902;0.000000;,
  0.421913;0.594537;0.684482;,
  -0.421909;0.594538;0.684483;,
  -1.000000;-0.000009;0.000000;,
  -0.887238;-0.000008;-0.461312;,
  0.000000;-0.000008;-1.000000;,
  1.000000;-0.000009;0.000000;,
  0.887240;-0.000008;0.461308;,
  0.000000;-0.000008;1.000000;,
  -0.823781;-0.566907;0.000000;,
  -0.542935;-0.654985;-0.525562;,
  0.225349;-0.661933;-0.714886;,
  0.823786;-0.566901;0.000000;,
  0.542939;-0.654984;0.525560;,
  -0.225347;-0.661933;0.714887;,
  -0.435745;-0.900070;0.000000;,
  -0.218709;-0.911791;-0.347569;,
  0.218711;-0.911791;-0.347566;,
  0.435748;-0.900069;0.000000;,
  0.218711;-0.911791;0.347566;,
  -0.218709;-0.911791;0.347569;,
  0.000001;-1.000000;0.000000;,
  0.133523;0.986831;-0.091306;,
  -0.443572;-0.112307;-0.889174;,
  0.011065;-0.999841;-0.013976;,
  0.080317;-0.996310;-0.030246;,
  0.062141;-0.161477;0.984918;,
  -0.392132;0.109491;0.913370;,
  0.072199;-0.996846;-0.032947;,
  -0.003767;0.991395;0.130852;,
  0.951374;0.214441;-0.221141;,
  -0.983417;-0.181315;0.003908;,
  0.107614;-0.196286;-0.974624;,
  -0.069127;0.940450;-0.332830;,
  0.293429;0.924653;-0.242726;,
  -0.271778;0.961714;-0.035241;,
  0.969981;-0.213663;0.116125;,
  0.398063;0.906619;0.139956;,
  0.038139;0.997256;0.063456;,
  0.887240;-0.000008;-0.461308;,
  -0.887238;-0.000008;0.461312;,
  0.000000;-0.296009;-0.955185;,
  0.853058;-0.274896;-0.443535;,
  0.000000;-0.296014;0.955184;,
  -0.853053;-0.274909;0.443538;;
  72;
  4;12,1,8,13;,
  4;9,14,12,13;,
  4;2,9,13,0;,
  4;16,65,65,15;,
  4;17,9,2,66;,
  4;19,3,9,17;,
  4;20,21,11,7;,
  4;25,18,67,22;,
  4;25,22,68,68;,
  4;24,11,8,69;,
  4;11,23,70,8;,
  3;71,18,26;,
  3;72,72,72;,
  3;26,18,25;,
  3;6,11,21;,
  3;8,70,0;,
  3;73,73,73;,
  3;0,13,8;,
  3;9,74,14;,
  4;28,27,16,15;,
  3;17,5,19;,
  3;75,4,17;,
  3;11,6,29;,
  3;76,77,28;,
  4;76,28,15,78;,
  3;17,10,5;,
  3;17,4,10;,
  3;17,66,75;,
  3;11,24,7;,
  3;11,29,23;,
  4;31,5,10,32;,
  4;31,32,79,79;,
  4;32,10,4,30;,
  4;32,30,6,21;,
  4;28,77,80,81;,
  3;27,28,81;,
  3;33,35,34;,
  3;33,36,35;,
  3;33,37,36;,
  3;33,38,37;,
  3;33,39,38;,
  3;33,34,39;,
  4;34,35,41,40;,
  4;35,36,42,41;,
  4;36,37,43,42;,
  4;37,38,44,43;,
  4;38,39,45,44;,
  4;39,34,40,45;,
  4;40,41,47,46;,
  4;41,42,48,48;,
  4;42,43,49,82;,
  4;43,44,50,49;,
  4;44,45,51,51;,
  4;45,40,46,83;,
  4;46,47,53,52;,
  4;48,48,54,84;,
  4;82,49,55,85;,
  4;49,50,56,55;,
  4;51,51,57,86;,
  4;83,46,52,87;,
  4;52,53,59,58;,
  4;53,54,60,59;,
  4;54,55,61,60;,
  4;55,56,62,61;,
  4;56,57,63,62;,
  4;57,52,58,63;,
  3;58,59,64;,
  3;59,60,64;,
  3;60,61,64;,
  3;61,62,64;,
  3;62,63,64;,
  3;63,58,64;;
 }
}
