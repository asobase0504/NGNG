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
 100;
 4.39326;26.27399;5.78790;,
 4.02844;26.27399;9.61221;,
 4.02421;23.41994;13.51525;,
 8.37987;24.98271;6.10085;,
 -4.40122;26.27399;9.05094;,
 -4.44509;26.27399;5.09413;,
 -8.43169;24.98271;4.78120;,
 -4.87705;23.41994;13.46869;,
 -2.59424;24.98271;-2.84586;,
 3.53026;24.98271;-2.43807;,
 4.86874;20.23752;-6.86808;,
 -3.56089;20.23752;-7.42935;,
 8.29643;24.98271;2.46546;,
 11.42881;20.23752;-0.11895;,
 11.54365;20.23752;6.34917;,
 5.63556;19.29316;15.08372;,
 -11.59548;20.23752;4.53286;,
 -5.96064;19.29316;15.01964;,
 -7.73771;24.98271;1.39786;,
 -10.64032;20.23752;-1.58840;,
 -2.59424;24.98271;-2.84586;,
 -3.56089;20.23752;-7.42935;,
 1.92498;14.24298;-10.12809;,
 -1.41377;14.25826;-10.20919;,
 8.37159;14.24298;-6.89236;,
 12.22246;14.25826;6.50863;,
 6.00425;14.09324;16.99968;,
 -12.27429;14.25826;4.37341;,
 -6.96604;14.09324;16.92432;,
 -8.73284;14.25826;-7.68144;,
 -1.41377;14.25826;-10.20919;,
 2.00578;7.61491;-11.09862;,
 -1.48738;7.63015;-11.22323;,
 12.14075;7.63015;6.56357;,
 8.75823;7.61491;-7.46413;,
 5.61324;8.32902;16.22695;,
 -12.90463;7.63015;4.31846;,
 -7.31251;8.32902;16.00920;,
 -9.16371;7.63015;-8.34212;,
 8.78695;1.00202;-1.77824;,
 3.73988;1.00202;-9.71234;,
 8.16328;1.00202;6.50863;,
 3.64435;2.56482;14.36581;,
 -8.92715;1.00202;4.37341;,
 -5.06950;2.56482;14.08739;,
 -8.19226;1.00202;-3.50567;,
 -1.48738;7.63015;-11.22323;,
 -2.74562;1.00202;-10.37215;,
 -2.74562;1.00202;-10.37215;,
 3.77626;-1.33564;-9.77406;,
 -2.90721;-1.33564;-10.33534;,
 8.95978;13.19752;3.69399;,
 0.65188;13.19752;-4.24008;,
 9.58388;6.56945;-1.18702;,
 1.34974;6.55421;-6.02502;,
 -0.74109;13.19752;-5.19289;,
 -8.28863;13.19752;-1.03184;,
 -0.80455;6.56945;-6.20691;,
 -7.13830;6.56945;-2.43663;,
 3.66084;1.25436;-8.24252;,
 1.83635;7.36137;-9.63836;,
 -2.82466;1.25436;-8.90234;,
 -1.31315;7.36337;-9.81394;,
 0.26537;4.96372;-9.04137;,
 0.28611;5.22372;-10.47538;,
 3.46930;-0.97411;-10.22058;,
 2.37187;-0.97411;-10.22058;,
 2.37187;-2.65938;-10.22058;,
 3.46930;-2.65938;-10.22058;,
 -1.61258;-0.97411;-10.22058;,
 -2.71001;-0.97411;-10.22058;,
 -2.71001;-2.65938;-10.22058;,
 -1.61258;-2.65938;-10.22058;,
 -0.34288;-0.97411;-10.22058;,
 -1.44032;-0.97411;-10.22058;,
 -1.44032;-2.65938;-10.22058;,
 -0.34288;-2.65938;-10.22058;,
 0.96031;-0.97411;-10.22058;,
 -0.13712;-0.97411;-10.22058;,
 -0.13712;-2.65938;-10.22058;,
 0.96031;-2.65938;-10.22058;,
 2.25233;-0.97411;-10.22058;,
 1.15490;-0.97411;-10.22058;,
 1.15490;-2.65938;-10.22058;,
 2.25233;-2.65938;-10.22058;,
 -1.61258;-2.65938;-10.22058;,
 -2.71001;-2.65938;-10.22058;,
 -2.71001;-0.97411;-10.22058;,
 -1.44032;-0.97411;-10.22058;,
 -0.34288;-2.65938;-10.22058;,
 -1.44032;-2.65938;-10.22058;,
 -0.13712;-0.97411;-10.22058;,
 0.96031;-2.65938;-10.22058;,
 -0.13712;-2.65938;-10.22058;,
 1.15490;-0.97411;-10.22058;,
 2.25233;-2.65938;-10.22058;,
 1.15490;-2.65938;-10.22058;,
 2.37187;-0.97411;-10.22058;,
 3.46930;-2.65938;-10.22058;,
 2.37187;-2.65938;-10.22058;;
 
 76;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,3,14,13;,
 4;3,2,15,14;,
 4;7,6,16,17;,
 4;6,18,19,16;,
 4;18,20,21,19;,
 4;11,10,22,23;,
 4;10,13,24,22;,
 4;13,14,25,24;,
 4;14,15,26,25;,
 4;17,16,27,28;,
 4;16,19,29,27;,
 4;19,21,30,29;,
 4;23,22,31,32;,
 4;24,25,33,34;,
 4;25,26,35,33;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;31,34,39,40;,
 4;34,33,41,39;,
 4;33,35,42,41;,
 4;37,36,43,44;,
 4;36,38,45,43;,
 4;38,46,47,45;,
 4;48,40,49,50;,
 4;51,52,22,24;,
 4;53,51,24,34;,
 4;54,53,34,31;,
 4;52,54,31,22;,
 4;52,51,53,54;,
 4;55,56,29,30;,
 4;57,55,30,46;,
 4;58,57,46,38;,
 4;56,58,38,29;,
 4;56,55,57,58;,
 4;59,60,31,40;,
 4;61,59,40,48;,
 4;62,61,48,32;,
 4;62,60,59,61;,
 4;4,7,2,1;,
 4;7,17,15,2;,
 4;17,28,26,15;,
 4;28,37,35,26;,
 4;37,44,42,35;,
 4;44,43,41,42;,
 4;43,45,39,41;,
 4;45,48,40,39;,
 4;48,50,49,40;,
 4;45,50,49,39;,
 3;39,49,40;,
 3;47,50,45;,
 4;1,0,5,4;,
 4;20,18,6,5;,
 4;5,0,9,20;,
 4;0,3,12,9;,
 4;63,62,32,64;,
 4;63,64,31,60;,
 3;48,32,64;,
 4;64,63,61,48;,
 4;60,31,40,59;,
 3;64,31,40;,
 4;63,64,40,59;,
 3;32,31,64;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,86,87,69;,
 4;88,73,89,90;,
 4;91,77,92,93;,
 4;94,81,95,96;,
 4;97,65,98,99;;
 
 MeshMaterialList {
  3;
  76;
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
  2,
  0,
  2,
  0,
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
  0,
  2,
  2,
  0,
  2,
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
   0.620800;0.608800;0.618400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  78;
  0.186525;0.982436;0.005366;,
  0.157233;0.942585;0.294637;,
  -0.178239;0.946139;0.270281;,
  -0.182130;0.983011;-0.022779;,
  -0.175426;0.886817;-0.427530;,
  0.228416;0.885871;-0.403804;,
  0.582500;0.779962;-0.228808;,
  0.607930;0.772139;0.184993;,
  0.318871;0.699445;0.639608;,
  -0.368904;0.703093;0.607923;,
  -0.631578;0.769175;0.097362;,
  -0.544679;0.780839;-0.305965;,
  -0.217239;0.577752;-0.786772;,
  0.314318;0.556207;-0.769310;,
  0.812976;0.417347;-0.406068;,
  0.914655;0.323061;0.242975;,
  0.425911;0.380791;0.820730;,
  -0.482469;0.384001;0.787252;,
  -0.931863;0.336981;0.134447;,
  -0.744712;0.463531;-0.480149;,
  -0.127002;0.347219;-0.929144;,
  0.218339;0.319287;-0.922163;,
  0.900538;0.117208;-0.418682;,
  0.983241;0.029564;0.179895;,
  0.481683;0.090514;0.871658;,
  -0.899746;0.118283;0.420079;,
  -0.990919;0.100071;0.089811;,
  -0.859094;0.200681;-0.470835;,
  -0.078355;-0.153713;-0.985004;,
  0.176957;-0.158401;-0.971388;,
  0.903596;-0.206431;-0.375367;,
  0.953735;-0.228158;0.195789;,
  0.441290;-0.272359;0.855034;,
  -0.882265;-0.217655;0.417414;,
  -0.973655;-0.206772;0.096133;,
  -0.864814;-0.225567;-0.448571;,
  -0.295135;-0.113756;-0.948660;,
  0.426883;-0.121489;-0.896109;,
  0.856296;-0.206980;-0.473199;,
  0.877897;-0.420277;0.229485;,
  0.281256;-0.695784;0.660894;,
  -0.337088;-0.711205;0.616895;,
  -0.879282;-0.461734;0.116896;,
  -0.790982;-0.239228;-0.563132;,
  -0.392536;0.027018;-0.919340;,
  0.521180;0.016968;-0.853278;,
  -0.075921;-0.981702;-0.174634;,
  0.088893;-0.987456;-0.130496;,
  -0.991223;-0.009918;0.131827;,
  -0.104225;0.977412;0.183854;,
  -0.992032;-0.096541;0.080945;,
  0.080678;0.981809;0.171881;,
  0.975646;-0.216736;-0.033763;,
  -0.955135;-0.284958;-0.080726;,
  0.017121;0.985590;-0.168284;,
  -0.906495;-0.417334;-0.064031;,
  -0.782229;-0.621313;-0.045694;,
  0.000000;0.000000;1.000000;,
  0.984752;0.018625;0.172962;,
  0.953619;-0.293753;0.065724;,
  0.547550;0.399106;-0.735462;,
  -0.948957;-0.313406;0.035466;,
  0.979955;0.083482;-0.180884;,
  -0.493703;0.118233;-0.861555;,
  0.905605;-0.424112;-0.003044;,
  0.077101;-0.177095;-0.981169;,
  -0.008521;0.103679;0.994574;,
  -0.017273;-0.227798;0.973555;,
  -0.007009;-0.996258;0.086139;,
  -0.009433;-0.994770;0.101707;,
  0.000000;-1.000000;-0.000000;,
  -0.092452;-0.003180;0.995712;,
  -0.028000;-0.952925;0.301911;,
  -0.808780;-0.584557;-0.064553;,
  0.805228;-0.592873;-0.010472;,
  0.817541;-0.573803;-0.048746;,
  0.058018;-0.218817;-0.974039;,
  0.000000;0.000000;-1.000000;;
  76;
  4;0,1,8,7;,
  4;2,3,10,9;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,4,12,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,12,20,27;,
  4;20,21,29,28;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,28,36,43;,
  4;36,37,45,44;,
  4;47,47,47,47;,
  4;50,50,50,50;,
  4;49,49,49,49;,
  4;58,58,59,58;,
  4;60,60,60,60;,
  4;46,46,46,46;,
  4;48,48,48,61;,
  4;51,51,51,51;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;55,53,53,55;,
  4;54,54,54,54;,
  4;52,64,64,52;,
  4;65,65,65,65;,
  4;2,9,8,1;,
  4;9,17,16,8;,
  4;17,66,24,16;,
  4;66,67,32,24;,
  4;67,41,40,32;,
  4;41,68,68,40;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;71,71,71,71;,
  4;69,72,72,69;,
  3;38,45,37;,
  3;36,44,43;,
  4;1,0,3,2;,
  4;4,11,10,3;,
  4;3,0,5,4;,
  4;0,7,6,5;,
  4;56,73,61,56;,
  4;74,74,59,75;,
  3;36,28,76;,
  4;74,74,64,64;,
  4;53,53,55,55;,
  3;76,29,37;,
  4;56,56,55,55;,
  3;28,29,76;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;;
 }
 MeshTextureCoords {
  100;
  0.300000;0.100000;,
  0.400000;0.100000;,
  0.400000;0.200000;,
  0.300000;0.200000;,
  0.700000;0.100000;,
  0.800000;0.100000;,
  0.800000;0.200000;,
  0.700000;0.200000;,
  0.000000;0.200000;,
  0.100000;0.200000;,
  0.100000;0.300000;,
  0.000000;0.300000;,
  0.200000;0.200000;,
  0.200000;0.300000;,
  0.300000;0.300000;,
  0.400000;0.300000;,
  0.800000;0.300000;,
  0.700000;0.300000;,
  0.900000;0.200000;,
  0.900000;0.300000;,
  1.000000;0.200000;,
  1.000000;0.300000;,
  0.100000;0.400000;,
  0.000000;0.400000;,
  0.200000;0.400000;,
  0.300000;0.400000;,
  0.400000;0.400000;,
  0.800000;0.400000;,
  0.700000;0.400000;,
  0.900000;0.400000;,
  1.000000;0.400000;,
  0.100000;0.500000;,
  0.000000;0.500000;,
  0.300000;0.500000;,
  0.200000;0.500000;,
  0.400000;0.500000;,
  0.800000;0.500000;,
  0.700000;0.500000;,
  0.900000;0.500000;,
  0.200000;0.600000;,
  0.100000;0.600000;,
  0.300000;0.600000;,
  0.400000;0.600000;,
  0.800000;0.600000;,
  0.700000;0.600000;,
  0.900000;0.600000;,
  1.000000;0.500000;,
  1.000000;0.600000;,
  0.000000;0.600000;,
  0.100000;0.700000;,
  0.000000;0.700000;,
  0.200000;0.400000;,
  0.100000;0.400000;,
  0.200000;0.500000;,
  0.100000;0.500000;,
  1.000000;0.400000;,
  0.900000;0.400000;,
  1.000000;0.500000;,
  0.900000;0.500000;,
  0.100000;0.600000;,
  0.100000;0.500000;,
  0.000000;0.600000;,
  0.000000;0.500000;,
  0.050120;0.500000;,
  0.050770;0.500000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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
 MeshVertexColors {
  100;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;;
 }
}
