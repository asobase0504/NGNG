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
 132;
 4.20866;25.47155;-1.45949;,
 4.09475;25.40596;2.00570;,
 4.07535;24.21305;2.05206;,
 4.18916;24.27854;-1.41314;,
 -0.29077;25.61072;2.17173;,
 -0.31036;24.41776;2.21809;,
 -2.88724;25.80279;-1.19088;,
 -2.90675;24.60985;-1.14452;,
 -0.10638;25.71677;-3.43510;,
 -0.12596;24.52385;-3.38874;,
 1.00380;25.60159;-0.38161;,
 0.98427;24.40858;-0.33520;,
 4.84246;24.23460;-1.63224;,
 4.70534;24.15569;2.53957;,
 4.67888;22.54169;2.60235;,
 4.81602;22.62062;-1.56952;,
 -0.57450;24.40213;2.73946;,
 -0.60106;22.78815;2.80218;,
 -3.70055;24.63343;-1.30891;,
 -3.72695;23.01943;-1.24613;,
 -0.35261;24.52985;-4.01076;,
 -0.37904;22.91586;-3.94802;,
 0.98399;24.39115;-0.33457;,
 0.95760;22.77715;-0.27183;,
 4.21182;22.70540;-1.36831;,
 4.09620;22.63884;2.14922;,
 4.07434;21.30557;2.20103;,
 4.19007;21.37207;-1.31650;,
 -0.35558;22.84672;2.31771;,
 -0.37741;21.51341;2.36954;,
 -2.99125;23.04171;-1.09569;,
 -3.01305;21.70839;-1.04385;,
 -0.16842;22.95431;-3.37377;,
 -0.19030;21.62102;-3.32194;,
 0.95855;22.83738;-0.27419;,
 0.93674;21.50412;-0.22233;,
 2.21812;21.49295;-1.80041;,
 1.44160;21.53678;-2.17258;,
 -0.90677;21.67501;-2.81083;,
 -1.03892;21.69909;-1.43197;,
 1.66349;0.00689;-1.11952;,
 -1.41383;0.19811;-1.08104;,
 -0.21889;0.11382;-1.96516;,
 1.60793;0.00681;-1.42452;,
 -0.81714;21.70598;0.35493;,
 -0.93856;21.72812;1.62272;,
 1.41683;21.57900;1.35370;,
 2.04766;21.52400;-0.02149;,
 1.51824;0.03336;0.39700;,
 0.98045;0.08023;1.56930;,
 -1.23789;0.21729;1.52472;,
 -1.38390;0.21377;0.43893;,
 1.81665;2.25195;-1.69228;,
 -0.35263;2.37911;-2.32705;,
 -1.39851;2.49163;1.81042;,
 1.17205;2.33245;1.82143;,
 1.97332;2.24640;-1.33264;,
 -1.59119;2.46829;-1.24608;,
 1.80293;2.27753;0.44629;,
 -1.53212;2.48523;0.53754;,
 -0.39900;95.46492;-2.50672;,
 -0.36198;95.45821;-2.89272;,
 -0.57913;95.46937;-3.09045;,
 -0.63418;95.47943;-2.51139;,
 -0.68897;95.48956;-1.93356;,
 -0.43305;95.47117;-2.14970;,
 2.64637;25.58106;-0.73450;,
 2.56241;25.59632;0.14171;,
 1.97860;25.63868;0.67301;,
 2.11332;25.61398;-0.74517;,
 2.24837;25.58919;-2.16630;,
 2.73706;25.56449;-1.68179;,
 -0.43115;25.77111;-0.79633;,
 -0.29603;25.74632;-2.21733;,
 -1.27066;95.52549;-1.94524;,
 -1.18931;95.51370;-2.52257;,
 -1.10777;95.50203;-3.10110;,
 1.14007;92.09491;-3.34397;,
 0.65143;92.11950;-3.82842;,
 0.38159;92.16908;-0.98913;,
 0.96550;92.12675;-1.52044;,
 1.04934;92.11143;-2.39662;,
 -0.93635;92.25053;-1.01565;,
 -3.04634;95.62841;-2.55985;,
 -2.81118;95.61384;-2.55517;,
 -2.75516;95.60377;-3.13418;,
 -3.00941;95.62171;-2.94591;,
 -3.08065;95.63470;-2.20288;,
 -2.86696;95.62411;-1.97732;,
 -1.03457;25.80841;-0.80845;,
 -0.50157;25.77546;-0.79773;,
 -0.63854;25.80028;0.62038;,
 -1.11853;25.82368;0.06773;,
 -0.94377;25.79180;-1.75576;,
 -0.36430;25.75056;-2.21874;,
 2.04287;25.61835;-0.74666;,
 2.18011;25.59342;-2.16765;,
 -2.28534;95.58818;-1.96563;,
 -2.25603;95.57957;-2.54400;,
 -2.22663;95.57110;-3.12358;,
 -2.54073;92.32217;-3.41786;,
 -1.96129;92.28078;-3.88089;,
 -2.23552;92.33067;-1.04171;,
 -2.71540;92.35408;-1.59443;,
 -2.63153;92.33881;-2.47057;,
 -0.91751;92.24934;-1.01523;,
 2.25409;64.43121;-2.64445;,
 1.76653;64.54639;-3.13113;,
 1.48798;63.89910;-0.27493;,
 2.07370;64.01548;-0.81016;,
 2.16031;64.21525;-1.69147;,
 0.16914;63.91684;-0.29990;,
 -0.84779;64.58172;-3.18060;,
 -1.42908;64.48084;-2.71405;,
 -1.60942;64.06511;-0.87974;,
 -1.13087;63.93442;-0.32444;,
 -1.52286;64.26491;-1.76108;,
 0.18793;63.91665;-0.29950;,
 2.57695;48.34375;-2.24367;,
 2.08916;48.39851;-2.72889;,
 1.81148;48.25071;0.11506;,
 2.39714;48.24895;-0.41724;,
 2.48362;48.29454;-1.29482;,
 0.49267;48.32488;0.08874;,
 0.66066;25.72006;0.64650;,
 -0.52537;48.54558;-2.78107;,
 -1.10638;48.55103;-2.31721;,
 -1.28618;48.45617;-0.49073;,
 -0.80738;48.39801;0.06278;,
 -1.19977;48.50171;-1.36827;,
 0.67938;25.71890;0.64693;,
 0.51150;48.32386;0.08912;;
 
 127;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,0,3,9;,
 3;10,1,0;,
 3;10,4,1;,
 3;10,6,4;,
 3;10,8,6;,
 3;10,0,8;,
 3;11,3,2;,
 3;11,2,5;,
 3;11,5,7;,
 3;11,7,9;,
 3;11,9,3;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,12,15,21;,
 3;22,13,12;,
 3;22,16,13;,
 3;22,18,16;,
 3;22,20,18;,
 3;22,12,20;,
 3;23,15,14;,
 3;23,14,17;,
 3;23,17,19;,
 3;23,19,21;,
 3;23,21,15;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,24,27,33;,
 3;34,25,24;,
 3;34,28,25;,
 3;34,30,28;,
 3;34,32,30;,
 3;34,24,32;,
 3;35,27,26;,
 3;35,26,29;,
 3;35,29,31;,
 3;35,31,33;,
 3;35,33,27;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;44,47,36,39;,
 4;48,49,50,51;,
 4;48,51,41,40;,
 4;52,43,42,53;,
 4;52,53,38,37;,
 4;54,50,49,55;,
 4;54,55,46,45;,
 4;56,40,43,52;,
 4;56,52,37,36;,
 4;53,42,41,57;,
 4;53,57,39,38;,
 4;55,49,48,58;,
 4;55,58,47,46;,
 4;58,48,40,56;,
 4;58,56,36,47;,
 4;54,45,44,59;,
 4;54,59,51,50;,
 4;59,44,39,57;,
 4;59,57,41,51;,
 4;60,61,62,63;,
 4;60,63,64,65;,
 4;66,67,68,69;,
 4;66,69,70,71;,
 4;72,73,70,69;,
 4;74,64,63,75;,
 4;75,63,62,76;,
 4;77,78,62,61;,
 4;79,80,65,64;,
 4;80,81,60,65;,
 4;81,77,61,60;,
 4;79,64,74,82;,
 4;83,84,85,86;,
 4;83,87,88,84;,
 4;89,90,91,92;,
 4;89,93,94,90;,
 4;95,90,94,96;,
 4;97,98,84,88;,
 4;98,99,85,84;,
 4;100,86,85,101;,
 4;102,88,87,103;,
 4;103,87,83,104;,
 4;104,83,86,100;,
 4;102,105,97,88;,
 4;85,62,78,101;,
 3;82,74,97;,
 4;99,97,74,76;,
 4;106,107,78,77;,
 4;108,109,80,79;,
 4;109,110,81,80;,
 4;110,106,77,81;,
 4;111,108,79,82;,
 4;112,113,100,101;,
 4;114,115,102,103;,
 4;116,114,103,104;,
 4;113,116,104,100;,
 4;115,117,105,102;,
 4;107,112,101,78;,
 4;118,71,70,119;,
 4;118,119,107,106;,
 4;120,68,67,121;,
 4;120,121,109,108;,
 4;121,67,66,122;,
 4;121,122,110,109;,
 4;122,66,71,118;,
 4;122,118,106,110;,
 4;123,124,68,120;,
 4;123,120,108,111;,
 4;125,94,93,126;,
 4;125,126,113,112;,
 4;127,92,91,128;,
 4;127,128,115,114;,
 4;129,89,92,127;,
 4;129,127,114,116;,
 4;126,93,89,129;,
 4;126,129,116,113;,
 4;128,91,130,131;,
 4;128,131,117,115;,
 4;119,70,94,125;,
 4;119,125,112,107;;
 
 MeshMaterialList {
  11;
  127;
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  10,
  10,
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
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10;;
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
  180;
  0.047396;0.998667;0.020451;,
  0.999357;-0.015024;0.032553;,
  -0.421950;0.042113;0.905641;,
  -0.789957;0.036735;0.612061;,
  -0.628275;-0.019928;-0.777736;,
  -0.047399;-0.998667;-0.020449;,
  0.047394;0.998667;0.020453;,
  0.999355;-0.015114;0.032563;,
  -0.421946;0.042132;0.905641;,
  -0.789950;0.036757;0.612068;,
  -0.628272;-0.019958;-0.777738;,
  -0.047394;-0.998667;-0.020452;,
  0.047402;0.998667;0.020443;,
  0.999355;-0.015077;0.032579;,
  -0.421953;0.042106;0.905640;,
  -0.789956;0.036719;0.612063;,
  -0.628275;-0.019943;-0.777735;,
  -0.047401;-0.998667;-0.020440;,
  0.061866;0.998018;-0.011512;,
  -0.061871;-0.998017;0.011538;,
  0.061875;0.998017;-0.011519;,
  -0.061884;-0.998017;0.011531;,
  0.061870;0.998018;-0.011511;,
  -0.061872;-0.998018;0.011518;,
  0.061874;0.998018;-0.011515;,
  -0.061878;-0.998017;0.011514;,
  -0.031192;-0.106923;-0.993778;,
  0.603778;-0.086565;-0.792439;,
  0.018204;-0.050922;0.998537;,
  -0.951711;-0.047707;-0.303265;,
  0.974144;-0.079881;-0.211333;,
  0.963058;-0.066669;0.260911;,
  -0.998148;-0.020860;0.057143;,
  0.061783;0.998024;-0.011440;,
  -0.061863;-0.998018;0.011529;,
  0.061858;0.998017;-0.011612;,
  -0.061932;-0.998014;0.011473;,
  0.061822;0.998022;-0.011435;,
  -0.061864;-0.998018;0.011529;,
  0.061856;0.998017;-0.011632;,
  -0.061865;-0.998018;0.011529;,
  0.061820;0.998021;-0.011526;,
  -0.061898;-0.998016;0.011501;,
  0.061839;0.998020;-0.011533;,
  -0.061887;-0.998017;0.011510;,
  0.061862;0.998019;-0.011496;,
  0.061859;0.998017;-0.011607;,
  -0.018579;0.024525;0.999527;,
  0.061858;0.998018;-0.011541;,
  0.913806;0.233091;-0.332607;,
  0.869062;0.237787;0.433806;,
  0.382494;0.161775;-0.909685;,
  0.345465;0.199249;0.917036;,
  0.970322;0.223532;0.092237;,
  -0.007907;0.191411;0.981478;,
  0.061990;0.998012;-0.011378;,
  -0.061854;-0.998018;0.011543;,
  0.061901;0.998014;-0.011699;,
  -0.061892;-0.998017;0.011474;,
  0.061941;0.998015;-0.011393;,
  -0.061857;-0.998018;0.011534;,
  0.061888;0.998014;-0.011721;,
  -0.061861;-0.998018;0.011525;,
  0.061945;0.998013;-0.011539;,
  -0.061873;-0.998018;0.011508;,
  0.061915;0.998015;-0.011557;,
  -0.061869;-0.998018;0.011514;,
  0.061878;0.998018;-0.011485;,
  0.061869;0.998016;-0.011652;,
  -0.018598;0.024526;0.999526;,
  0.061884;0.998016;-0.011575;,
  -0.875073;-0.050377;-0.481362;,
  -0.950216;-0.037495;0.309328;,
  -0.315081;0.049793;-0.947758;,
  -0.417369;0.090448;0.904225;,
  -0.991717;-0.084516;-0.096717;,
  -0.010613;0.149868;0.988649;,
  0.941508;0.019940;-0.336402;,
  0.892077;0.038047;0.450278;,
  0.390416;-0.011318;-0.920569;,
  0.351229;0.033994;0.935672;,
  0.994363;0.032429;0.100944;,
  -0.018587;0.024526;0.999527;,
  -0.877246;-0.038390;-0.478504;,
  -0.953463;-0.020979;0.300779;,
  -0.321255;-0.033429;-0.946403;,
  -0.424768;0.010021;0.905247;,
  -0.994367;-0.032357;-0.100935;,
  -0.018575;0.024525;0.999527;,
  0.941135;0.004413;-0.338003;,
  0.893089;0.023533;0.449264;,
  0.389763;-0.017554;-0.920748;,
  0.351699;0.028113;0.935691;,
  0.994965;0.016113;0.098924;,
  -0.018580;0.024526;0.999527;,
  -0.878292;-0.023900;-0.477526;,
  -0.953157;-0.005874;0.302420;,
  -0.321658;-0.027850;-0.946446;,
  -0.424067;0.016472;0.905481;,
  -0.994961;-0.016265;-0.098939;,
  -0.018588;0.024525;0.999526;,
  0.039581;0.038157;0.998488;,
  0.413934;-0.042110;-0.909332;,
  0.047404;0.998666;0.020462;,
  0.047400;0.998667;0.020449;,
  0.047395;0.998667;0.020458;,
  0.047388;0.998667;0.020447;,
  0.047393;0.998667;0.020438;,
  -0.047399;-0.998667;-0.020447;,
  -0.047391;-0.998667;-0.020435;,
  -0.047397;-0.998667;-0.020443;,
  -0.047403;-0.998666;-0.020455;,
  -0.047403;-0.998666;-0.020463;,
  0.039578;0.038169;0.998487;,
  0.413935;-0.042121;-0.909331;,
  0.047391;0.998667;0.020452;,
  0.047395;0.998667;0.020448;,
  0.047390;0.998667;0.020460;,
  0.047396;0.998667;0.020455;,
  0.047397;0.998667;0.020448;,
  -0.047392;-0.998667;-0.020452;,
  -0.047392;-0.998667;-0.020454;,
  -0.047394;-0.998667;-0.020455;,
  -0.047396;-0.998667;-0.020452;,
  -0.047394;-0.998667;-0.020450;,
  0.039574;0.038160;0.998488;,
  0.413930;-0.042113;-0.909334;,
  0.047399;0.998667;0.020446;,
  0.047390;0.998667;0.020451;,
  0.047409;0.998667;0.020437;,
  0.047412;0.998666;0.020438;,
  0.047400;0.998667;0.020442;,
  -0.047408;-0.998667;-0.020432;,
  -0.047404;-0.998667;-0.020446;,
  -0.047396;-0.998667;-0.020452;,
  -0.047396;-0.998667;-0.020440;,
  -0.047402;-0.998667;-0.020428;,
  0.691591;-0.158976;-0.704576;,
  -0.199655;-0.152530;-0.967922;,
  0.270570;-0.017579;-0.962540;,
  0.512723;-0.018902;-0.858346;,
  -0.019363;-0.117224;0.992917;,
  0.055665;0.015677;0.998326;,
  0.985618;-0.137581;-0.098126;,
  0.943935;-0.016101;-0.329740;,
  -0.903990;-0.113624;-0.412179;,
  -0.889946;-0.005440;-0.456034;,
  -0.980393;0.014638;-0.196508;,
  0.906193;-0.062507;0.418218;,
  0.900098;-0.123358;0.417859;,
  0.956944;-0.127128;0.260953;,
  0.965616;-0.005963;0.259905;,
  0.908900;-0.001424;0.417012;,
  -0.997825;-0.023146;0.061718;,
  -0.999524;0.030563;0.004234;,
  -0.998638;0.032106;0.041115;,
  -0.994599;-0.073783;0.073001;,
  -0.989948;-0.076712;0.118820;,
  0.363591;0.324988;-0.873032;,
  0.849143;0.423687;-0.315349;,
  0.814552;0.418350;0.401856;,
  0.330658;0.354477;0.874649;,
  0.914096;0.397421;0.080527;,
  -0.002481;0.272828;0.962060;,
  -0.873127;-0.053748;-0.484520;,
  -0.306462;0.136292;-0.942075;,
  -0.406845;0.174100;0.896753;,
  -0.947011;-0.045304;0.317990;,
  -0.987579;-0.127062;-0.092423;,
  -0.002481;0.272827;0.962060;,
  0.940622;-0.001733;-0.339451;,
  0.389277;-0.019989;-0.920904;,
  0.352202;0.025671;0.935572;,
  0.893888;0.017557;0.447947;,
  0.995257;0.009518;0.096819;,
  -0.322101;-0.025634;-0.946358;,
  -0.879108;-0.018054;-0.476281;,
  -0.952679;0.000465;0.303978;,
  -0.423494;0.019198;0.905695;,
  -0.995253;-0.009633;-0.096844;;
  127;
  4;1,1,1,1;,
  4;101,2,2,101;,
  4;2,3,3,2;,
  4;4,4,4,4;,
  4;102,102,102,102;,
  3;0,103,104;,
  3;0,105,103;,
  3;0,106,105;,
  3;0,107,106;,
  3;0,104,107;,
  3;5,108,109;,
  3;5,109,110;,
  3;5,110,111;,
  3;5,111,112;,
  3;5,112,108;,
  4;7,7,7,7;,
  4;113,8,8,113;,
  4;8,9,9,8;,
  4;10,10,10,10;,
  4;114,114,114,114;,
  3;6,115,116;,
  3;6,117,115;,
  3;6,118,117;,
  3;6,119,118;,
  3;6,116,119;,
  3;11,120,121;,
  3;11,121,122;,
  3;11,122,123;,
  3;11,123,124;,
  3;11,124,120;,
  4;13,13,13,13;,
  4;125,14,14,125;,
  4;14,15,15,14;,
  4;16,16,16,16;,
  4;126,126,126,126;,
  3;12,127,128;,
  3;12,129,127;,
  3;12,130,129;,
  3;12,131,130;,
  3;12,128,131;,
  3;17,132,133;,
  3;17,133,134;,
  3;17,134,135;,
  3;17,135,136;,
  3;17,136,132;,
  4;22,18,18,22;,
  4;23,23,19,19;,
  4;24,20,20,24;,
  4;24,24,22,22;,
  4;25,21,21,25;,
  4;25,25,23,23;,
  4;27,137,138,26;,
  4;27,26,139,140;,
  4;28,141,141,28;,
  4;28,28,142,142;,
  4;30,143,137,27;,
  4;30,27,140,144;,
  4;26,138,145,29;,
  4;146,29,147,146;,
  4;148,149,150,31;,
  4;148,31,151,152;,
  4;31,150,143,30;,
  4;31,30,144,151;,
  4;153,154,155,32;,
  4;153,32,156,157;,
  4;32,155,147,29;,
  4;32,29,145,156;,
  4;41,33,37,43;,
  4;41,43,39,35;,
  4;42,36,36,44;,
  4;42,44,38,34;,
  4;40,40,38,44;,
  4;46,39,43,48;,
  4;48,43,37,45;,
  4;49,51,158,159;,
  4;52,50,160,161;,
  4;50,53,162,160;,
  4;53,49,159,162;,
  4;52,161,163,54;,
  4;63,65,59,55;,
  4;63,57,61,65;,
  4;64,66,58,58;,
  4;64,56,60,66;,
  4;62,66,60,62;,
  4;68,70,65,61;,
  4;70,67,59,65;,
  4;71,164,165,73;,
  4;74,166,167,72;,
  4;72,167,168,75;,
  4;75,168,164,71;,
  4;74,76,169,166;,
  4;165,158,51,73;,
  3;54,163,169;,
  4;67,68,46,45;,
  4;77,79,51,49;,
  4;80,78,50,52;,
  4;78,81,53,50;,
  4;81,77,49,53;,
  4;82,80,52,54;,
  4;85,83,71,73;,
  4;84,86,74,72;,
  4;87,84,72,75;,
  4;83,87,75,71;,
  4;86,88,76,74;,
  4;79,85,73,51;,
  4;89,170,171,91;,
  4;89,91,79,77;,
  4;92,172,173,90;,
  4;92,90,78,80;,
  4;90,173,174,93;,
  4;90,93,81,78;,
  4;93,174,170,89;,
  4;93,89,77,81;,
  4;94,47,172,92;,
  4;94,92,80,82;,
  4;97,175,176,95;,
  4;97,95,83,85;,
  4;96,177,178,98;,
  4;96,98,86,84;,
  4;99,179,177,96;,
  4;99,96,84,87;,
  4;95,176,179,99;,
  4;95,99,87,83;,
  4;98,178,69,100;,
  4;98,100,88,86;,
  4;91,171,175,97;,
  4;91,97,85,79;;
 }
}
