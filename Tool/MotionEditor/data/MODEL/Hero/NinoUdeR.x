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
 63;
 4.70814;-17.19507;5.10909;,
 6.22923;-16.59335;3.92753;,
 3.07887;-2.86583;5.51217;,
 0.06921;-4.05757;6.35861;,
 -2.04185;-5.26661;6.53014;,
 3.11553;-17.82677;4.10250;,
 4.57128;-17.25432;-2.06646;,
 3.02040;-17.86793;-0.88325;,
 -1.77282;-4.95200;-3.25243;,
 -0.11623;-4.13807;-3.36857;,
 2.91688;-2.93609;-2.98368;,
 6.13413;-16.63453;-1.05821;,
 6.86588;-16.34307;1.41447;,
 2.99938;-2.90041;1.34347;,
 2.38451;-18.11795;1.66628;,
 -2.13425;-5.30656;1.68482;,
 4.64006;-17.22465;1.53953;,
 1.86110;-1.37610;5.34083;,
 2.49167;-3.09786;6.22249;,
 2.44033;-1.14692;4.63098;,
 1.70910;-1.44169;-2.62856;,
 2.02310;-1.31708;-2.09087;,
 2.30617;-3.17832;-3.50467;,
 -2.05258;-0.72352;2.94752;,
 -1.29237;-2.28946;5.57089;,
 0.05420;0.02347;2.84128;,
 -2.12357;-2.61857;4.64322;,
 -0.66171;-4.71995;6.45261;,
 -1.44434;-2.35513;-2.39848;,
 -2.12144;-0.74696;0.10623;,
 0.00000;0.00000;0.00000;,
 -0.84723;-4.80015;-3.27460;,
 -1.92727;-2.57397;-2.48628;,
 2.31871;-1.19979;-1.74724;,
 2.94051;-2.92580;-1.74488;,
 -2.25808;-2.67682;-1.43718;,
 -2.19313;-5.33218;-1.40355;,
 2.43622;-1.14870;4.41584;,
 3.05804;-2.87494;4.41818;,
 -2.14055;-2.62612;4.72588;,
 -2.07562;-5.28121;4.75950;,
 4.17892;-15.82354;1.36391;,
 3.87617;-16.42607;-0.47599;,
 2.84204;-16.64076;1.43542;,
 5.55209;-15.93744;0.20295;,
 5.55368;-15.85012;2.53396;,
 3.87865;-16.28462;3.29568;,
 4.01227;-17.60669;-1.54412;,
 2.33891;-17.95392;1.54860;,
 6.72391;-16.81623;-0.44556;,
 6.72636;-16.67479;3.32611;,
 4.01635;-17.37804;4.55855;,
 4.53522;-18.91486;-1.43246;,
 2.86199;-19.26197;1.66027;,
 7.24686;-18.12433;-0.33394;,
 7.24946;-17.98286;3.43775;,
 4.53943;-18.68602;4.67020;,
 5.24530;-19.85057;-0.18370;,
 4.21119;-20.06504;1.72775;,
 6.92127;-19.36193;0.49526;,
 6.92287;-19.27454;2.82627;,
 5.24782;-19.70910;3.58797;,
 5.87131;-20.05648;1.72521;;
 
 62;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;6,7,8,9;,
 4;6,9,10,11;,
 4;12,11,10,13;,
 4;12,13,2,1;,
 4;14,5,4,15;,
 4;14,15,8,7;,
 4;14,7,6,16;,
 4;14,16,0,5;,
 4;16,6,11,12;,
 4;16,12,1,0;,
 4;17,18,2,19;,
 4;20,21,10,22;,
 4;23,24,17,25;,
 4;24,26,4,27;,
 4;24,27,18,17;,
 4;28,29,30,20;,
 4;31,8,32,28;,
 4;31,28,20,22;,
 4;33,34,10,21;,
 4;35,32,8,36;,
 4;25,37,33,30;,
 4;37,19,2,38;,
 4;37,38,34,33;,
 4;39,23,29,35;,
 4;40,4,26,39;,
 4;40,39,35,36;,
 4;23,25,30,29;,
 3;30,21,20;,
 3;30,33,21;,
 3;25,17,19;,
 3;25,19,37;,
 3;23,26,24;,
 3;23,39,26;,
 3;29,28,32;,
 3;29,32,35;,
 3;41,42,43;,
 3;41,44,42;,
 3;41,45,44;,
 3;41,46,45;,
 3;41,43,46;,
 4;43,42,47,48;,
 4;42,44,49,47;,
 4;44,45,50,49;,
 4;45,46,51,50;,
 4;46,43,48,51;,
 4;48,47,52,53;,
 4;47,49,54,52;,
 4;49,50,55,54;,
 4;50,51,56,55;,
 4;51,48,53,56;,
 4;53,52,57,58;,
 4;52,54,59,57;,
 4;54,55,60,59;,
 4;55,56,61,60;,
 4;56,53,58,61;,
 3;58,57,62;,
 3;57,59,62;,
 3;59,60,62;,
 3;60,61,62;,
 3;61,58,62;;
 
 MeshMaterialList {
  11;
  62;
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
  80;
  0.045509;0.953802;-0.296968;,
  0.345538;-0.000666;-0.938405;,
  0.106516;0.972745;0.205964;,
  0.797227;0.165959;0.580420;,
  -0.466170;0.797951;0.382047;,
  -0.154516;-0.202635;0.966987;,
  -0.498961;0.771430;-0.394884;,
  -0.262715;-0.225908;-0.938054;,
  0.618497;0.351204;-0.702934;,
  0.822901;0.329524;0.462869;,
  -0.266330;0.259819;0.928204;,
  -0.152237;0.050122;-0.987072;,
  0.043777;-0.119760;-0.991837;,
  0.150447;-0.084952;0.984961;,
  0.967860;0.250628;-0.020784;,
  -0.935440;-0.353440;-0.005666;,
  0.368303;-0.929706;0.000649;,
  0.466596;0.744740;-0.477127;,
  0.591695;0.754621;0.283626;,
  -0.462371;0.487631;0.740560;,
  -0.470876;0.540542;-0.697202;,
  0.078148;0.719997;-0.689563;,
  0.109888;0.714030;0.691437;,
  0.259006;0.487590;0.833770;,
  0.179778;0.499528;-0.847438;,
  -0.396058;0.537825;0.744233;,
  -0.198434;0.578514;-0.791167;,
  -0.269615;0.383740;0.883205;,
  -0.112908;0.331338;-0.936732;,
  -0.992313;-0.017168;-0.122556;,
  0.665419;0.708357;-0.235473;,
  -0.989378;0.076441;-0.123641;,
  0.905056;0.374470;-0.201608;,
  0.748432;0.662917;-0.019766;,
  -0.999656;0.016692;0.020216;,
  0.940628;0.338804;-0.020745;,
  -0.139807;0.555066;0.819973;,
  -0.271978;0.961575;-0.037435;,
  -0.760259;0.649105;-0.025854;,
  -0.410060;0.783768;-0.466432;,
  0.159145;0.941295;-0.297720;,
  0.158416;0.963907;0.213982;,
  -0.400664;0.829352;0.389415;,
  -0.999998;0.001338;0.001342;,
  -0.877134;-0.037539;-0.478776;,
  0.610081;0.591319;-0.527393;,
  0.599489;0.655747;0.458921;,
  0.239555;0.517047;0.821752;,
  -0.754235;-0.655890;0.030640;,
  -0.663306;-0.614026;-0.427782;,
  0.428521;-0.273003;-0.861301;,
  0.997962;0.063739;-0.003069;,
  0.439010;-0.135159;0.888258;,
  -0.254274;-0.966305;0.039994;,
  -0.039337;-0.970467;-0.238005;,
  0.656063;-0.715224;-0.240907;,
  0.665885;-0.682093;0.302236;,
  0.299505;-0.846061;0.440997;,
  0.271955;-0.961581;0.037444;,
  0.955324;0.246552;-0.162997;,
  -0.920459;-0.353942;0.165768;,
  -0.958329;-0.178825;-0.222772;,
  -0.922718;-0.342471;-0.176933;,
  0.368314;-0.929701;0.000648;,
  0.368310;-0.929703;0.000667;,
  0.368302;-0.929706;0.000637;,
  0.368304;-0.929705;0.000661;,
  0.368318;-0.929700;0.000629;,
  0.368294;-0.929709;0.000607;,
  0.368292;-0.929710;0.000650;,
  0.368290;-0.929711;0.000692;,
  -0.965047;-0.009786;-0.261894;,
  -0.998118;0.057557;0.021139;,
  -0.999522;-0.024202;0.019259;,
  0.965029;0.153802;0.212284;,
  0.244483;0.393129;-0.886384;,
  -0.876048;0.039839;0.480576;,
  -0.678511;-0.552700;0.483886;,
  0.445561;-0.576249;-0.685137;,
  -0.480497;-0.772297;0.415549;;
  62;
  4;13,3,9,13;,
  4;13,13,10,5;,
  4;12,7,11,12;,
  4;12,12,8,1;,
  4;14,59,59,14;,
  4;14,14,9,3;,
  4;15,60,60,15;,
  4;15,15,61,62;,
  4;63,64,65,16;,
  4;63,16,66,67;,
  4;16,65,68,69;,
  4;16,69,70,66;,
  4;22,23,9,18;,
  4;21,17,8,24;,
  4;4,25,22,2;,
  4;25,19,10,27;,
  4;25,27,23,22;,
  4;26,6,0,21;,
  4;28,11,20,26;,
  4;28,26,21,24;,
  4;30,32,8,17;,
  4;31,71,61,29;,
  4;2,33,30,0;,
  4;33,18,9,35;,
  4;33,35,32,30;,
  4;34,72,72,31;,
  4;36,10,19,36;,
  4;73,34,31,29;,
  4;4,2,0,6;,
  3;0,17,21;,
  3;0,30,17;,
  3;2,22,18;,
  3;2,18,33;,
  3;4,19,25;,
  3;74,74,74;,
  3;6,26,20;,
  3;6,20,31;,
  3;37,39,38;,
  3;37,40,39;,
  3;37,41,40;,
  3;37,42,41;,
  3;37,38,42;,
  4;38,39,44,43;,
  4;39,40,45,75;,
  4;40,41,46,45;,
  4;41,42,47,46;,
  4;42,38,43,76;,
  4;43,44,49,48;,
  4;75,45,50,50;,
  4;45,46,51,51;,
  4;46,47,52,52;,
  4;76,43,48,77;,
  4;48,49,54,53;,
  4;50,50,55,78;,
  4;51,51,56,55;,
  4;52,52,57,56;,
  4;77,48,53,79;,
  3;53,54,58;,
  3;54,55,58;,
  3;55,56,58;,
  3;56,57,58;,
  3;57,53,58;;
 }
}