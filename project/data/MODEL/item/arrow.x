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
 1.38621;13.47904;4.88212;,
 0.93688;12.68736;5.79884;,
 0.90986;14.20184;4.91330;,
 2.52544;13.76580;4.36796;,
 1.42376;17.10659;7.66637;,
 0.93688;12.68736;5.79884;,
 0.37605;13.52589;5.02122;,
 -0.82872;13.95520;4.79422;,
 0.30501;14.24050;4.28264;,
 0.75985;15.03364;3.36332;,
 1.31759;14.19530;4.14135;,
 2.52544;13.76580;4.36796;,
 0.63437;14.31876;4.66607;,
 1.12620;14.29099;4.60357;,
 -0.89744;2.87463;-6.24741;,
 -1.38927;2.90240;-6.18490;,
 1.12620;14.29099;4.60357;,
 1.15417;13.92023;4.98844;,
 -0.86947;2.50386;-5.86254;,
 -0.89744;2.87463;-6.24741;,
 1.15417;13.92023;4.98844;,
 0.66235;13.94800;5.05094;,
 -1.36129;2.53162;-5.80003;,
 -0.86947;2.50386;-5.86254;,
 0.66235;13.94800;5.05094;,
 0.63437;14.31876;4.66607;,
 -1.38927;2.90240;-6.18490;,
 -1.36129;2.53162;-5.80003;,
 1.12620;14.29099;4.60357;,
 0.63437;14.31876;4.66607;,
 -1.38927;2.90240;-6.18490;,
 -0.89744;2.87463;-6.24741;,
 -0.75516;5.74467;-2.79905;,
 -2.07170;5.43744;-2.99935;,
 -2.59267;5.04620;-3.33837;,
 -3.41074;3.70990;-4.56622;,
 -3.12908;2.67558;-5.58313;,
 -2.70556;0.96750;-7.25942;,
 -1.31771;2.57105;-5.81550;,
 -0.77798;6.04719;-3.11306;,
 -3.43356;4.01239;-4.88023;,
 -2.61549;5.34869;-3.65239;,
 -2.09453;5.73995;-3.31334;,
 -1.34053;2.87356;-6.12952;,
 -2.72839;1.27000;-7.57344;,
 -3.15190;2.97809;-5.89714;,
 -2.07170;5.43744;-2.99935;,
 -0.75516;5.74467;-2.79905;,
 -2.59267;5.04620;-3.33837;,
 -2.07170;5.43744;-2.99935;,
 -2.59267;5.04620;-3.33837;,
 -3.41074;3.70990;-4.56622;,
 -3.41074;3.70990;-4.56622;,
 -3.12908;2.67558;-5.58313;,
 -2.70556;0.96750;-7.25942;,
 -3.12908;2.67558;-5.58313;,
 -1.31771;2.57105;-5.81550;,
 -2.70556;0.96750;-7.25942;,
 -0.75516;5.74467;-2.79905;,
 -1.31771;2.57105;-5.81550;,
 -0.36416;5.70360;-2.82878;,
 -0.36518;4.45174;-2.28051;,
 -0.41541;3.72247;-2.35172;,
 -0.62767;1.95113;-3.23490;,
 -0.83069;1.26486;-4.52754;,
 -1.16422;0.10038;-6.63459;,
 -0.92671;2.52998;-5.84521;,
 -0.79447;5.72791;-2.77405;,
 -1.05798;1.97542;-3.18020;,
 -0.84572;3.74677;-2.29704;,
 -0.79549;4.47603;-2.22583;,
 -1.35702;2.55427;-5.79052;,
 -1.59453;0.12469;-6.57989;,
 -1.26100;1.28917;-4.47286;,
 -0.36518;4.45174;-2.28051;,
 -0.36416;5.70360;-2.82878;,
 -0.41541;3.72247;-2.35172;,
 -0.36518;4.45174;-2.28051;,
 -0.41541;3.72247;-2.35172;,
 -0.62767;1.95113;-3.23490;,
 -0.62767;1.95113;-3.23490;,
 -0.83069;1.26486;-4.52754;,
 -1.16422;0.10038;-6.63459;,
 -0.83069;1.26486;-4.52754;,
 -0.92671;2.52998;-5.84521;,
 -1.16422;0.10038;-6.63459;,
 -0.36416;5.70360;-2.82878;,
 -0.92671;2.52998;-5.84521;,
 -0.82286;6.11842;-3.17964;,
 -0.95579;6.61471;-4.44604;,
 -1.05321;6.51098;-5.16657;,
 -1.32621;5.54471;-6.88545;,
 -1.48064;4.21436;-7.50952;,
 -1.73827;2.04389;-8.57230;,
 -1.38541;2.94480;-6.19610;,
 -0.39470;6.09425;-3.23406;,
 -0.89804;5.52054;-6.93986;,
 -0.62504;6.48681;-5.22101;,
 -0.52762;6.59053;-4.50045;,
 -0.95725;2.92062;-6.25050;,
 -1.31009;2.01971;-8.62673;,
 -1.05247;4.19019;-7.56395;,
 -0.95579;6.61471;-4.44604;,
 -0.82286;6.11842;-3.17964;,
 -1.05321;6.51098;-5.16657;,
 -0.95579;6.61471;-4.44604;,
 -1.05321;6.51098;-5.16657;,
 -1.32621;5.54471;-6.88545;,
 -1.32621;5.54471;-6.88545;,
 -1.48064;4.21436;-7.50952;,
 -1.73827;2.04389;-8.57230;,
 -1.48064;4.21436;-7.50952;,
 -1.38541;2.94480;-6.19610;,
 -1.73827;2.04389;-8.57230;,
 -0.82286;6.11842;-3.17964;,
 -1.38541;2.94480;-6.19610;,
 -0.39172;6.02463;-3.16136;,
 0.79089;5.57628;-3.67925;,
 1.16420;5.13453;-4.13193;,
 1.49701;3.73323;-5.50608;,
 0.85789;2.75092;-6.40595;,
 -0.15677;1.12404;-7.89946;,
 -0.95426;2.85100;-6.17781;,
 -0.36900;5.72362;-2.84892;,
 1.51972;3.43223;-5.19363;,
 1.18691;4.83353;-3.81949;,
 0.81360;5.27527;-3.36681;,
 -0.93155;2.55000;-5.86535;,
 -0.13405;0.82303;-7.58702;,
 0.88061;2.44991;-6.09349;,
 0.79089;5.57628;-3.67925;,
 -0.39172;6.02463;-3.16136;,
 1.16420;5.13453;-4.13193;,
 0.79089;5.57628;-3.67925;,
 1.16420;5.13453;-4.13193;,
 1.49701;3.73323;-5.50608;,
 1.49701;3.73323;-5.50608;,
 0.85789;2.75092;-6.40595;,
 -0.15677;1.12404;-7.89946;,
 0.85789;2.75092;-6.40595;,
 -0.95426;2.85100;-6.17781;,
 -0.15677;1.12404;-7.89946;,
 -0.39172;6.02463;-3.16136;,
 -0.95426;2.85100;-6.17781;;
 
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
   0.385600;0.313600;0.169600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  120;
  -0.898328;0.433663;-0.070311;,
  0.455009;-0.545143;0.704121;,
  -0.642672;-0.395228;-0.656328;,
  -0.328476;-0.497147;0.803086;,
  0.747232;-0.409477;0.523423;,
  0.678551;0.556202;-0.479800;,
  -0.637568;-0.328296;0.696943;,
  -0.705610;0.638420;-0.307463;,
  -0.513796;-0.304001;-0.802245;,
  -0.282788;-0.656562;-0.699255;,
  -0.052281;0.692842;-0.719192;,
  0.990469;-0.055932;-0.125870;,
  0.052282;-0.692841;0.719192;,
  0.937495;-0.217939;0.271305;,
  -0.860387;-0.115022;0.496492;,
  -0.417420;0.756795;-0.503012;,
  0.898817;0.324289;-0.294899;,
  0.365670;0.712200;-0.599214;,
  0.310538;-0.779173;-0.544478;,
  0.415079;-0.453692;-0.788589;,
  0.263196;-0.351298;-0.898508;,
  0.099302;-0.232873;-0.967424;,
  0.151201;-0.967163;-0.204289;,
  0.296723;-0.892658;-0.339290;,
  0.428907;-0.778025;-0.459038;,
  -0.622191;-0.713314;-0.322585;,
  -0.474619;-0.845834;-0.243517;,
  -0.305409;-0.939792;-0.153348;,
  -0.361170;-0.198723;-0.911079;,
  -0.990468;0.055928;0.125875;,
  0.127429;0.718927;0.683305;,
  -0.127429;-0.718911;-0.683322;,
  0.052275;-0.692841;0.719193;,
  0.052281;-0.692843;0.719191;,
  0.052282;-0.692840;0.719193;,
  0.052285;-0.692840;0.719194;,
  0.052284;-0.692835;0.719198;,
  -0.052281;0.692843;-0.719191;,
  -0.052289;0.692846;-0.719188;,
  -0.052284;0.692842;-0.719191;,
  -0.052286;0.692842;-0.719192;,
  -0.052275;0.692835;-0.719199;,
  -0.263213;0.685129;0.679203;,
  -0.702946;0.486009;0.519290;,
  -0.910152;0.263335;0.319811;,
  -0.980270;-0.173073;-0.095482;,
  -0.983312;-0.161380;-0.083992;,
  0.839434;-0.359627;-0.407455;,
  0.990469;-0.055928;-0.125873;,
  -0.499494;0.605467;0.619609;,
  -0.820228;0.381027;0.426666;,
  -0.991918;0.047361;0.117707;,
  -0.981825;-0.167233;-0.089740;,
  0.938021;-0.213016;-0.273387;,
  0.990468;-0.055928;-0.125874;,
  0.990469;-0.055929;-0.125873;,
  0.990469;-0.055929;-0.125871;,
  0.990469;-0.055930;-0.125869;,
  0.990469;-0.055930;-0.125866;,
  -0.990469;0.055931;0.125869;,
  -0.990469;0.055930;0.125871;,
  -0.990469;0.055930;0.125870;,
  -0.990469;0.055929;0.125871;,
  -0.990469;0.055929;0.125869;,
  0.137773;0.397234;0.907317;,
  0.119558;-0.104635;0.987298;,
  0.087207;-0.452851;0.887311;,
  0.009526;-0.883825;0.467721;,
  0.011812;-0.875961;0.482238;,
  -0.102016;0.316396;-0.943126;,
  -0.052311;0.692842;-0.719189;,
  0.133038;0.151271;0.979499;,
  0.105136;-0.283470;0.953201;,
  0.050757;-0.701363;0.710995;,
  0.010669;-0.879923;0.474996;,
  -0.079109;0.517342;-0.852114;,
  -0.990468;0.055927;0.125876;,
  -0.990468;0.055928;0.125875;,
  -0.990469;0.055923;0.125875;,
  -0.990469;0.055922;0.125875;,
  -0.990469;0.055914;0.125876;,
  0.990469;-0.055932;-0.125870;,
  0.990469;-0.055930;-0.125871;,
  0.990469;-0.055928;-0.125871;,
  0.990469;-0.055926;-0.125872;,
  0.990469;-0.055925;-0.125872;,
  0.097537;0.930054;0.354241;,
  0.037098;0.988396;-0.147301;,
  -0.012820;0.872501;-0.488445;,
  -0.089723;0.431506;-0.897637;,
  -0.087985;0.446461;-0.890467;,
  -0.007601;-0.934649;0.355491;,
  0.052271;-0.692841;0.719193;,
  0.069605;0.991821;0.106986;,
  0.012345;0.946228;-0.323264;,
  -0.053805;0.684221;-0.727287;,
  -0.088857;0.438999;-0.894083;,
  0.022898;-0.834263;0.550891;,
  -0.052280;0.692840;-0.719193;,
  -0.052276;0.692841;-0.719193;,
  -0.052277;0.692837;-0.719197;,
  -0.052276;0.692835;-0.719199;,
  -0.052280;0.692829;-0.719204;,
  0.052279;-0.692841;0.719193;,
  0.052278;-0.692840;0.719194;,
  0.052279;-0.692839;0.719195;,
  0.052278;-0.692838;0.719196;,
  0.052281;-0.692836;0.719198;,
  0.498487;0.642129;0.582393;,
  0.859602;0.397768;0.320725;,
  0.984538;0.156325;0.079039;,
  0.900092;-0.279251;-0.334446;,
  0.907178;-0.268122;-0.324251;,
  -0.949024;-0.258630;-0.180176;,
  -0.990469;0.055930;0.125873;,
  0.702119;0.537616;0.466903;,
  0.937710;0.281745;0.203272;,
  0.988878;-0.064500;-0.134014;,
  0.903666;-0.273696;-0.329360;,
  -0.994197;-0.103905;-0.027836;;
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
  4;34,36,36,35;,
  4;34,33,32,32;,
  3;34,35,33;,
  4;39,40,41,41;,
  4;39,37,37,38;,
  3;39,38,40;,
  4;49,42,42,42;,
  4;49,50,43,43;,
  4;44,50,51,44;,
  4;45,51,52,45;,
  4;52,46,46,46;,
  4;53,47,47,47;,
  4;48,48,48,53;,
  4;56,58,58,57;,
  4;56,55,54,54;,
  3;56,57,55;,
  4;61,62,63,63;,
  4;61,59,59,60;,
  3;61,60,62;,
  4;71,64,64,64;,
  4;71,72,65,65;,
  4;66,72,73,66;,
  4;67,73,74,67;,
  4;74,68,68,68;,
  4;75,69,69,69;,
  4;70,70,70,75;,
  4;78,80,80,79;,
  4;78,77,76,76;,
  3;78,79,77;,
  4;83,84,85,85;,
  4;83,81,81,82;,
  3;83,82,84;,
  4;93,86,86,86;,
  4;93,94,87,87;,
  4;88,94,95,88;,
  4;89,95,96,89;,
  4;96,90,90,90;,
  4;97,91,91,91;,
  4;92,92,92,97;,
  4;100,102,102,101;,
  4;100,99,98,98;,
  3;100,101,99;,
  4;105,106,107,107;,
  4;105,103,103,104;,
  3;105,104,106;,
  4;115,108,108,108;,
  4;115,116,109,109;,
  4;110,116,117,110;,
  4;111,117,118,111;,
  4;118,112,112,112;,
  4;119,113,113,113;,
  4;114,114,114,119;;
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
