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
 2.13311;13.69915;1.83332;,
 1.96302;13.69915;3.61630;,
 1.96105;12.36851;5.43599;,
 3.99176;13.09713;1.97922;,
 -1.96708;13.69915;3.35462;,
 -1.98753;13.69915;1.50987;,
 -3.84618;13.09713;1.36397;,
 -2.18892;12.36851;5.41428;,
 -1.12462;13.09713;-2.19194;,
 1.73076;13.09713;-2.00182;,
 2.35479;10.88481;-4.06719;,
 -1.57530;10.88481;-4.32887;,
 3.95286;13.09713;0.28432;,
 5.41325;10.88481;-0.92059;,
 5.46679;10.88481;2.09500;,
 2.71230;10.44454;6.06456;,
 -5.32121;10.88481;1.24819;,
 -2.69412;10.44454;6.03468;,
 -3.52263;13.09713;-0.21342;,
 -4.87589;10.88481;-1.60568;,
 -1.12462;13.09713;-2.19194;,
 -1.57530;10.88481;-4.32887;,
 0.98234;8.09003;-5.58708;,
 -0.57426;8.09713;-5.62490;,
 3.98790;8.09003;-4.07851;,
 5.78326;8.09713;2.16934;,
 2.88419;8.02021;6.74548;,
 -5.63768;8.09713;1.17385;,
 -2.91730;8.02021;6.71035;,
 -3.98658;8.09713;-4.44640;,
 -0.57426;8.09713;-5.62490;,
 1.02001;4.99986;-6.03957;,
 -0.60858;5.00696;-6.09766;,
 6.07714;5.00696;2.19495;,
 4.16816;4.99986;-4.34508;,
 3.03386;5.33280;6.29616;,
 -5.93156;5.00696;1.14823;,
 -3.07883;5.33280;6.19464;,
 -4.18746;5.00696;-4.75442;,
 4.18155;1.91678;-1.69419;,
 1.82849;1.91678;-5.39325;,
 4.22275;1.91678;2.16934;,
 2.11592;2.64540;5.64081;,
 -4.07717;1.91678;1.17385;,
 -2.27865;2.64540;5.51100;,
 -3.73455;1.91678;-2.49956;,
 -0.60858;5.00696;-6.09766;,
 -1.19520;1.91678;-5.70087;,
 -1.19520;1.91678;-5.70087;,
 1.84545;0.82692;-5.42203;,
 -1.27054;0.82692;-5.68371;,
 4.26213;7.60261;0.85709;,
 0.38879;7.60261;-2.84196;,
 4.55310;4.51245;-1.41855;,
 0.71415;4.50534;-3.67414;,
 -0.26064;7.60261;-3.28618;,
 -3.77948;7.60261;-1.34620;,
 -0.29023;4.51245;-3.75894;,
 -3.24317;4.51245;-2.00115;,
 1.79164;2.03443;-4.70799;,
 0.94102;4.88166;-5.35876;,
 -1.23205;2.03443;-5.01561;,
 -0.52735;4.88259;-5.44062;,
 0.20859;3.76381;-5.08043;,
 0.21826;3.88504;-5.74900;,
 1.70234;0.99545;-5.63020;,
 1.19069;0.99545;-5.63020;,
 1.19069;0.20974;-5.63020;,
 1.70234;0.20974;-5.63020;,
 -0.66695;0.99545;-5.63020;,
 -1.17860;0.99545;-5.63020;,
 -1.17860;0.20974;-5.63020;,
 -0.66695;0.20974;-5.63020;,
 -0.07499;0.99545;-5.63020;,
 -0.58664;0.99545;-5.63020;,
 -0.58664;0.20974;-5.63020;,
 -0.07499;0.20974;-5.63020;,
 0.53259;0.99545;-5.63020;,
 0.02094;0.99545;-5.63020;,
 0.02094;0.20974;-5.63020;,
 0.53259;0.20974;-5.63020;,
 1.13496;0.99545;-5.63020;,
 0.62331;0.99545;-5.63020;,
 0.62331;0.20974;-5.63020;,
 1.13496;0.20974;-5.63020;,
 -0.66695;0.20974;-5.63020;,
 -1.17860;0.20974;-5.63020;,
 -1.17860;0.99545;-5.63020;,
 -0.58664;0.99545;-5.63020;,
 -0.07499;0.20974;-5.63020;,
 -0.58664;0.20974;-5.63020;,
 0.02094;0.99545;-5.63020;,
 0.53259;0.20974;-5.63020;,
 0.02094;0.20974;-5.63020;,
 0.62331;0.99545;-5.63020;,
 1.13496;0.20974;-5.63020;,
 0.62331;0.20974;-5.63020;,
 1.19069;0.99545;-5.63020;,
 1.70234;0.20974;-5.63020;,
 1.19069;0.20974;-5.63020;;
 
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
  79;
  0.186525;0.982435;0.005367;,
  0.157233;0.942584;0.294640;,
  -0.178239;0.946138;0.270283;,
  -0.182130;0.983011;-0.022778;,
  -0.175425;0.886817;-0.427529;,
  0.228416;0.885872;-0.403804;,
  0.582499;0.779963;-0.228808;,
  0.609467;0.770391;0.187211;,
  0.321537;0.688360;0.650211;,
  -0.372211;0.692289;0.618219;,
  -0.633210;0.767624;0.098986;,
  -0.544679;0.780840;-0.305965;,
  -0.217239;0.577752;-0.786772;,
  0.314317;0.556207;-0.769310;,
  0.812976;0.417348;-0.406068;,
  0.915146;0.315777;0.250586;,
  0.424299;0.338972;0.839684;,
  -0.482445;0.331573;0.810744;,
  -0.935743;0.321419;0.145173;,
  -0.744712;0.463531;-0.480149;,
  -0.127002;0.347219;-0.929145;,
  0.218339;0.319287;-0.922162;,
  0.894750;0.135851;-0.425403;,
  0.980122;0.062434;0.188318;,
  0.468182;0.077554;0.880222;,
  -0.882117;0.084263;0.463433;,
  -0.990020;0.082739;0.114085;,
  -0.859094;0.200680;-0.470835;,
  -0.078357;-0.153713;-0.985004;,
  0.176956;-0.158401;-0.971388;,
  0.894260;-0.193434;-0.403588;,
  0.962000;-0.192179;0.193965;,
  0.432772;-0.229874;0.871703;,
  -0.652138;-0.242733;0.718190;,
  -0.972008;-0.199623;0.123898;,
  -0.864814;-0.225567;-0.448570;,
  -0.295135;-0.113754;-0.948660;,
  0.426883;-0.121487;-0.896109;,
  0.845360;-0.211514;-0.490539;,
  0.880177;-0.422246;0.216787;,
  0.393542;-0.362611;0.844771;,
  -0.341948;-0.674794;0.654006;,
  -0.886094;-0.441828;0.140087;,
  -0.790982;-0.239227;-0.563132;,
  -0.392536;0.027021;-0.919339;,
  0.521180;0.016972;-0.853278;,
  -0.075918;-0.981703;-0.174628;,
  0.088894;-0.987455;-0.130498;,
  -0.991223;-0.009918;0.131827;,
  -0.104225;0.977413;0.183852;,
  -0.992032;-0.096541;0.080946;,
  0.080676;0.981809;0.171877;,
  0.975646;-0.216736;-0.033763;,
  -0.955135;-0.284959;-0.080724;,
  0.017122;0.985588;-0.168294;,
  -0.906494;-0.417335;-0.064030;,
  -0.782228;-0.621314;-0.045696;,
  0.000000;0.000000;1.000000;,
  0.984752;0.018625;0.172962;,
  0.953619;-0.293753;0.065723;,
  0.547549;0.399106;-0.735462;,
  -0.948957;-0.313406;0.035465;,
  0.979955;0.083482;-0.180884;,
  -0.493703;0.118234;-0.861555;,
  0.905604;-0.424112;-0.003045;,
  0.077101;-0.177096;-0.981169;,
  -0.008576;0.047774;0.998821;,
  -0.011143;-0.176369;0.984261;,
  -0.007024;-0.995891;0.090288;,
  -0.013990;-0.983597;0.179834;,
  -0.009432;-0.994770;0.101706;,
  0.000000;-1.000000;-0.000000;,
  -0.092452;-0.003184;0.995712;,
  -0.028000;-0.952926;0.301908;,
  -0.808779;-0.584559;-0.064555;,
  0.805228;-0.592873;-0.010474;,
  0.817541;-0.573803;-0.048748;,
  0.058016;-0.218817;-0.974040;,
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
  4;33,41,40,32;,
  4;41,68,68,69;,
  4;68,70,70,68;,
  4;70,71,71,70;,
  4;72,72,72,72;,
  4;70,73,73,70;,
  3;38,45,37;,
  3;36,44,43;,
  4;1,0,3,2;,
  4;4,11,10,3;,
  4;3,0,5,4;,
  4;0,7,6,5;,
  4;56,74,61,56;,
  4;75,75,59,76;,
  3;36,28,77;,
  4;75,75,64,64;,
  4;53,53,55,55;,
  3;77,29,37;,
  4;56,56,55,55;,
  3;28,29,77;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;;
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
}
