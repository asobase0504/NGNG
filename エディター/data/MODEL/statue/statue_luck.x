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
 188;
 -21.98796;4.12024;-17.22058;,
 21.98796;4.12024;-17.22058;,
 21.98796;0.64738;-17.22058;,
 -21.98796;0.64738;-17.22058;,
 21.98796;4.12024;-17.22058;,
 21.98796;4.12024;17.22058;,
 21.98796;0.64738;17.22058;,
 21.98796;0.64738;-17.22058;,
 21.98796;4.12024;17.22058;,
 -21.98796;4.12024;17.22058;,
 -21.98796;0.64738;17.22058;,
 21.98796;0.64738;17.22058;,
 -21.98796;4.12024;17.22058;,
 -21.98796;4.12024;-17.22058;,
 -21.98796;0.64738;-17.22058;,
 -21.98796;0.64738;17.22058;,
 21.98796;4.12024;-17.22058;,
 -21.98796;4.12024;-17.22058;,
 -21.98796;0.64738;-17.22058;,
 21.98796;0.64738;-17.22058;,
 -12.95934;30.04422;-12.95934;,
 0.00000;30.04422;-12.95934;,
 0.00000;4.12556;-7.12764;,
 -7.12764;4.12556;-7.12764;,
 12.95934;30.04422;-12.95934;,
 7.12764;4.12556;-7.12764;,
 12.95934;30.04422;-12.95934;,
 12.95934;30.04422;0.00000;,
 7.12764;4.12556;0.00000;,
 7.12764;4.12556;-7.12764;,
 12.95934;30.04422;12.95934;,
 7.12764;4.12556;7.12764;,
 12.95934;30.04422;12.95934;,
 0.00000;30.04422;12.95934;,
 0.00000;4.12556;7.12764;,
 7.12764;4.12556;7.12764;,
 -12.95934;30.04422;12.95934;,
 -7.12764;4.12556;7.12764;,
 -12.95934;30.04422;12.95934;,
 -12.95934;30.04422;0.00000;,
 -7.12764;4.12556;0.00000;,
 -7.12764;4.12556;7.12764;,
 -12.95934;30.04422;-12.95934;,
 -7.12764;4.12556;-7.12764;,
 0.00000;30.04422;0.00000;,
 -12.95934;30.04422;0.00000;,
 12.95934;30.04422;0.00000;,
 0.00000;30.04422;-12.95934;,
 -12.95934;30.04422;-12.95934;,
 12.95934;30.04422;-12.95934;,
 -7.12764;4.12556;0.00000;,
 0.00000;4.12556;0.00000;,
 7.12764;4.12556;0.00000;,
 -7.12764;4.12556;-7.12764;,
 0.00000;4.12556;-7.12764;,
 7.12764;4.12556;-7.12764;,
 -14.39028;31.71188;-14.39028;,
 14.39028;31.71188;-14.39028;,
 14.39028;29.01898;-14.39028;,
 -14.39028;29.01898;-14.39028;,
 14.39028;31.71188;-14.39028;,
 14.39028;31.71188;14.39028;,
 14.39028;29.01898;14.39028;,
 14.39028;29.01898;-14.39028;,
 14.39028;31.71188;14.39028;,
 -14.39028;31.71188;14.39028;,
 -14.39028;29.01898;14.39028;,
 14.39028;29.01898;14.39028;,
 -14.39028;31.71188;14.39028;,
 -14.39028;31.71188;-14.39028;,
 -14.39028;29.01898;-14.39028;,
 -14.39028;29.01898;14.39028;,
 14.39028;31.71188;-14.39028;,
 -14.39028;31.71188;-14.39028;,
 -14.39028;29.01898;-14.39028;,
 14.39028;29.01898;-14.39028;,
 0.04238;47.24356;-23.19424;,
 1.71368;47.24356;-20.29950;,
 1.55260;56.37564;-15.68460;,
 -0.15896;58.65866;-17.42564;,
 5.40196;60.15828;-6.99022;,
 4.65274;63.38696;-6.55766;,
 11.00684;56.37564;0.69062;,
 11.65884;58.65866;3.04338;,
 15.08398;47.24356;2.85856;,
 16.75528;47.24356;5.75332;,
 15.24506;38.11146;-1.75632;,
 16.95662;35.82844;-0.01528;,
 11.39570;34.32882;-10.45070;,
 12.14492;31.10014;-10.88326;,
 5.79082;38.11146;-18.13154;,
 5.13882;35.82844;-20.48430;,
 13.34604;59.71108;-22.22180;,
 21.90110;51.42118;-16.51600;,
 13.49194;50.86428;-26.69134;,
 -0.15896;58.65866;-17.42564;,
 16.97428;63.40374;-13.74360;,
 21.90110;51.42118;-16.51600;,
 13.34604;59.71108;-22.22180;,
 4.65274;63.38696;-6.55766;,
 22.31238;59.74308;-6.13352;,
 21.90110;51.42118;-16.51600;,
 16.97428;63.40374;-13.74360;,
 11.65884;58.65866;3.04338;,
 26.23920;50.76816;-3.89510;,
 21.90110;51.42118;-16.51600;,
 22.31238;59.74308;-6.13352;,
 16.75528;47.24356;5.75332;,
 26.39268;41.77282;-8.43080;,
 21.90110;51.42118;-16.51600;,
 26.23920;50.76816;-3.89510;,
 16.95662;35.82844;-0.01528;,
 22.67762;38.13264;-17.03644;,
 21.90110;51.42118;-16.51600;,
 26.39268;41.77282;-8.43080;,
 12.14492;31.10014;-10.88326;,
 17.33194;41.94174;-24.58036;,
 21.90110;51.42118;-16.51600;,
 22.67762;38.13264;-17.03644;,
 5.13882;35.82844;-20.48430;,
 13.49194;50.86428;-26.69134;,
 21.90110;51.42118;-16.51600;,
 17.33194;41.94174;-24.58036;,
 0.04238;47.24356;-23.19424;,
 14.74850;50.85476;-24.44408;,
 14.63106;57.94396;-20.86318;,
 1.55260;56.37564;-15.68460;,
 14.63106;57.94396;-20.86318;,
 17.54066;60.89406;-14.07062;,
 5.40196;60.15828;-6.99022;,
 17.54066;60.89406;-14.07062;,
 21.81168;57.95366;-7.98780;,
 11.00684;56.37564;0.69062;,
 21.81168;57.95366;-7.98780;,
 24.94626;50.77796;-6.20766;,
 15.08398;47.24356;2.85856;,
 24.94626;50.77796;-6.20766;,
 25.06840;43.59378;-9.83078;,
 15.24506;38.11146;-1.75632;,
 25.06840;43.59378;-9.83078;,
 22.10332;40.67726;-16.70488;,
 11.39570;34.32882;-10.45070;,
 22.10332;40.67726;-16.70488;,
 17.82758;43.71272;-22.74530;,
 5.79082;38.11146;-18.13154;,
 17.82758;43.71272;-22.74530;,
 14.74850;50.85476;-24.44408;,
 1.71368;47.24356;-20.29950;,
 3.84706;40.72266;-6.17684;,
 10.73480;40.72266;-1.17260;,
 10.73480;32.20896;-1.17260;,
 3.84706;32.20896;-6.17684;,
 10.73480;40.72266;-1.17260;,
 5.73056;40.72266;5.71516;,
 5.73056;32.20896;5.71516;,
 10.73480;32.20896;-1.17260;,
 5.73056;40.72266;5.71516;,
 -1.15720;40.72266;0.71092;,
 -1.15720;32.20896;0.71092;,
 5.73056;32.20896;5.71516;,
 -1.15720;40.72266;0.71092;,
 3.84706;40.72266;-6.17684;,
 3.84706;32.20896;-6.17684;,
 -1.15720;32.20896;0.71092;,
 10.73480;40.72266;-1.17260;,
 3.84706;40.72266;-6.17684;,
 3.84706;32.20896;-6.17684;,
 10.73480;32.20896;-1.17260;,
 -10.69482;31.80976;-2.07860;,
 -10.64556;40.32300;-2.16042;,
 -2.20896;40.26326;-3.30148;,
 -2.25814;31.75002;-3.21966;,
 -10.64556;40.32300;-2.16042;,
 -9.50404;40.39740;6.27610;,
 -1.06734;40.33764;5.13506;,
 -2.20896;40.26326;-3.30148;,
 -9.50404;40.39740;6.27610;,
 -9.55320;31.88422;6.35792;,
 -1.11658;31.82446;5.21686;,
 -1.06734;40.33764;5.13506;,
 -9.55320;31.88422;6.35792;,
 -10.69482;31.80976;-2.07860;,
 -2.25814;31.75002;-3.21966;,
 -1.11658;31.82446;5.21686;,
 -10.64556;40.32300;-2.16042;,
 -10.69482;31.80976;-2.07860;,
 -2.25814;31.75002;-3.21966;,
 -2.20896;40.26326;-3.30148;;
 
 80;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;38,33,44,45;,
 4;33,30,46,44;,
 4;45,44,47,48;,
 4;44,46,49,47;,
 4;50,51,34,41;,
 4;51,52,31,34;,
 4;53,54,51,50;,
 4;54,55,52,51;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;68,61,72,73;,
 4;74,75,62,71;,
 4;76,77,78,79;,
 4;79,78,80,81;,
 4;81,80,82,83;,
 4;83,82,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,77,76;,
 3;92,93,94;,
 4;92,94,76,95;,
 3;96,97,98;,
 4;96,98,95,99;,
 3;100,101,102;,
 4;100,102,99,103;,
 3;104,105,106;,
 4;104,106,103,107;,
 3;108,109,110;,
 4;108,110,107,111;,
 3;112,113,114;,
 4;112,114,111,115;,
 3;116,117,118;,
 4;116,118,115,119;,
 3;120,121,122;,
 4;120,122,119,123;,
 3;124,93,125;,
 4;124,125,126,77;,
 3;127,97,128;,
 4;127,128,129,126;,
 3;130,101,131;,
 4;130,131,132,129;,
 3;133,105,134;,
 4;133,134,135,132;,
 3;136,109,137;,
 4;136,137,138,135;,
 3;139,113,140;,
 4;139,140,141,138;,
 3;142,117,143;,
 4;142,143,144,141;,
 3;145,121,146;,
 4;145,146,147,144;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;160,153,164,165;,
 4;166,167,154,163;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;180,173,184,185;,
 4;186,187,174,183;;
 
 MeshMaterialList {
  7;
  80;
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
  4,
  5,
  2,
  3,
  1,
  6,
  4,
  5,
  2,
  3,
  1,
  6;;
  Material {
   0.263200;0.263200;0.263200;1.000000;;
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
    "C:\\Users\\student\\Pictures\\さいころ１.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\さいころ２.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\さいころ３.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\さいころ５.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\さいころ４.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\さいころ６.png";
   }
  }
 }
 MeshNormals {
  68;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.219512;-0.975610;,
  0.000000;-0.219512;-0.975610;,
  0.975610;-0.219512;-0.000000;,
  0.975610;-0.219512;-0.000000;,
  0.000000;-0.219512;0.975610;,
  0.000000;-0.219512;0.975610;,
  -0.975610;-0.219512;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.975610;-0.219512;0.000000;,
  -0.836515;-0.258819;0.482965;,
  -0.836515;-0.258820;0.482964;,
  -0.836516;-0.258819;0.482963;,
  -0.836516;-0.258819;0.482963;,
  -0.836516;-0.258819;0.482964;,
  -0.836516;-0.258819;0.482964;,
  -0.836516;-0.258819;0.482963;,
  -0.836516;-0.258818;0.482964;,
  0.844326;0.252731;-0.472482;,
  0.739800;0.249084;-0.625022;,
  0.737696;0.374783;-0.561554;,
  0.789460;0.426688;-0.441237;,
  0.864986;0.374267;-0.334251;,
  0.920052;0.247873;-0.303418;,
  0.922187;0.121673;-0.367107;,
  0.870116;0.069952;-0.487858;,
  0.794560;0.122875;-0.594623;,
  -0.708055;-0.402462;0.580243;,
  -0.710660;-0.246905;0.658787;,
  -0.772093;-0.466740;0.431308;,
  -0.865568;-0.401901;0.298775;,
  -0.933766;-0.245366;0.260531;,
  -0.936412;-0.089017;0.339424;,
  -0.871927;-0.025008;0.488997;,
  -0.778408;-0.090636;0.621181;,
  -0.280178;0.726134;-0.627878;,
  -0.268539;0.067302;-0.960915;,
  -0.002000;0.999998;-0.000855;,
  0.403765;0.727948;0.554135;,
  0.699529;0.067886;0.711372;,
  0.711262;-0.593007;0.377424;,
  0.432023;-0.866105;-0.251433;,
  0.026164;-0.592000;-0.805513;,
  -0.844401;-0.252676;0.472379;,
  0.316509;-0.054162;0.947042;,
  0.328354;-0.721374;0.609757;,
  0.046078;-0.998627;-0.024927;,
  -0.365472;-0.723147;-0.586080;,
  -0.665262;-0.055339;-0.744557;,
  -0.677169;0.613243;-0.406663;,
  -0.394173;0.889987;0.229241;,
  0.017437;0.613139;0.789783;,
  0.587786;0.000000;-0.809017;,
  0.809018;0.000000;0.587784;,
  -0.587784;0.000000;0.809018;,
  -0.809016;0.000000;-0.587786;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.134086;-0.008749;-0.990931;,
  0.005783;0.999937;-0.009600;,
  0.134084;0.008748;0.990931;,
  -0.005782;-0.999937;0.009607;,
  -0.990953;0.007016;0.134027;,
  0.990953;-0.007016;-0.134029;;
  80;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;12,12,12,12;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;3,4,4,3;,
  4;4,3,3,4;,
  4;6,5,5,6;,
  4;5,6,6,5;,
  4;8,7,7,8;,
  4;7,8,8,7;,
  4;13,9,9,13;,
  4;9,13,13,9;,
  4;10,10,10,10;,
  4;10,10,10,10;,
  4;10,10,10,10;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;12,12,12,12;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,18,18;,
  4;18,18,19,19;,
  4;19,19,20,20;,
  4;20,20,21,21;,
  4;21,21,14,14;,
  3;24,22,23;,
  4;39,40,40,39;,
  3;25,22,24;,
  4;41,39,39,41;,
  3;26,22,25;,
  4;42,41,41,42;,
  3;27,22,26;,
  4;43,42,42,43;,
  3;28,22,27;,
  4;44,43,43,44;,
  3;29,22,28;,
  4;45,44,44,45;,
  3;30,22,29;,
  4;46,45,45,46;,
  3;23,22,30;,
  4;40,46,46,40;,
  3;32,47,31;,
  4;48,49,49,48;,
  3;31,47,33;,
  4;49,50,50,49;,
  3;33,47,34;,
  4;50,51,51,50;,
  3;34,47,35;,
  4;51,52,52,51;,
  3;35,47,36;,
  4;52,53,53,52;,
  3;36,47,37;,
  4;53,54,54,53;,
  3;37,47,38;,
  4;54,55,55,54;,
  3;38,47,32;,
  4;55,48,48,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;;
 }
 MeshTextureCoords {
  188;
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
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
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
  0.081750;0.692060;,
  0.062500;1.000000;,
  0.043250;0.691940;,
  0.125000;0.000000;,
  0.206830;0.690680;,
  0.187500;1.000000;,
  0.168250;0.692060;,
  0.250000;0.000000;,
  0.331960;0.688590;,
  0.312500;1.000000;,
  0.293170;0.690680;,
  0.375000;0.000000;,
  0.457060;0.687010;,
  0.437500;1.000000;,
  0.418040;0.688590;,
  0.500000;0.000000;,
  0.582070;0.686890;,
  0.562500;1.000000;,
  0.542940;0.687010;,
  0.625000;0.000000;,
  0.706980;0.688300;,
  0.687500;1.000000;,
  0.667930;0.686890;,
  0.750000;0.000000;,
  0.831850;0.690390;,
  0.812500;1.000000;,
  0.793020;0.688300;,
  0.875000;0.000000;,
  0.956750;0.691940;,
  0.937500;1.000000;,
  0.918150;0.690390;,
  1.000000;0.000000;,
  0.043220;0.691450;,
  0.081780;0.691550;,
  0.125000;0.000000;,
  0.168220;0.691550;,
  0.206850;0.690440;,
  0.250000;0.000000;,
  0.293150;0.690440;,
  0.331950;0.688770;,
  0.375000;0.000000;,
  0.418050;0.688770;,
  0.457030;0.687510;,
  0.500000;0.000000;,
  0.542970;0.687510;,
  0.582040;0.687410;,
  0.625000;0.000000;,
  0.667960;0.687410;,
  0.706970;0.688540;,
  0.750000;0.000000;,
  0.793030;0.688540;,
  0.831860;0.690210;,
  0.875000;0.000000;,
  0.918140;0.690210;,
  0.956780;0.691450;,
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
  1.000000;0.000000;;
 }
}
