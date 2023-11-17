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
 114;
 -0.40289;-0.00435;-0.18561;,
 -14.24017;-0.00435;-0.18561;,
 -10.18732;-0.00435;-10.57353;,
 -0.40289;-0.00435;-14.87635;,
 -0.40289;-0.00435;13.20018;,
 -10.18732;-0.00435;8.89736;,
 -0.01970;17.49627;1.63114;,
 -0.01970;17.55911;0.12456;,
 -1.68704;17.49627;0.89788;,
 -2.37768;17.49627;0.12456;,
 -0.77377;17.53913;0.12456;,
 -0.77577;17.53079;-0.67817;,
 -1.68704;17.49627;-1.64564;,
 -0.78405;17.49627;-2.04273;,
 -0.30991;17.55145;0.12456;,
 -0.31005;17.54825;-0.18369;,
 -0.01970;17.49627;-2.37886;,
 -0.31211;17.49627;-2.25027;,
 -0.43901;17.54333;-0.32061;,
 -0.43829;17.54800;0.12456;,
 -0.44645;17.49627;-2.19119;,
 -0.40289;10.59402;-7.28279;,
 -1.06168;10.59402;-6.99308;,
 -3.05910;10.59402;-6.11470;,
 -2.04882;10.59402;-6.55899;,
 -0.40289;9.32229;-8.07328;,
 -1.11263;9.32229;-7.76116;,
 -2.24943;9.32224;-7.26126;,
 -3.36457;9.32224;-6.77087;,
 -0.40289;7.66187;-9.10531;,
 -1.17909;7.66187;-8.76396;,
 -2.51135;7.66187;-8.17811;,
 -3.76338;7.66187;-7.62750;,
 -0.40289;6.28415;-9.96165;,
 -1.23427;6.28415;-9.59604;,
 -2.72867;6.28415;-8.93888;,
 -4.09431;6.28415;-8.33832;,
 -0.40289;4.83575;-10.86193;,
 -1.29228;4.83575;-10.47083;,
 -2.95713;4.83575;-9.73868;,
 -4.44224;4.83575;-9.08559;,
 -0.40289;3.70533;-11.56461;,
 -1.33752;3.70527;-11.15359;,
 -3.13544;3.70527;-10.36291;,
 -4.71372;3.70527;-9.66884;,
 -9.54851;0.66728;-9.43108;,
 -13.33672;0.66728;0.27861;,
 -9.54851;0.66728;8.68334;,
 -0.40289;0.66728;12.70524;,
 -5.44353;0.66728;-11.23629;,
 -5.81418;-0.00435;-12.49669;,
 -0.40289;0.66728;-13.45298;,
 -1.52095;-0.00435;-14.38467;,
 -1.45919;0.66728;-12.98847;,
 -3.61470;0.66728;-12.04055;,
 -3.85811;-0.00435;-13.35688;,
 -5.44353;0.66728;-11.23629;,
 10.18732;-0.00435;-10.57353;,
 14.24017;-0.00435;-0.18561;,
 0.40289;-0.00435;-0.18561;,
 0.40289;-0.00435;-14.87635;,
 10.18732;-0.00435;8.89736;,
 0.40289;-0.00435;13.20018;,
 1.68704;17.49627;0.89788;,
 0.01970;17.55911;0.12456;,
 0.01970;17.49627;1.63114;,
 2.37768;17.49627;0.12456;,
 1.68704;17.49627;-1.64564;,
 0.77577;17.53079;-0.67817;,
 0.77377;17.53913;0.12456;,
 0.78405;17.49627;-2.04273;,
 0.31005;17.54825;-0.18369;,
 0.30991;17.55145;0.12456;,
 0.31211;17.49627;-2.25027;,
 0.01970;17.49627;-2.37886;,
 0.43829;17.54800;0.12456;,
 0.43901;17.54333;-0.32061;,
 0.44645;17.49627;-2.19119;,
 1.06168;10.59402;-6.99308;,
 0.40289;10.59402;-7.28279;,
 2.04882;10.59402;-6.55899;,
 3.05910;10.59402;-6.11470;,
 1.11263;9.32229;-7.76116;,
 0.40289;9.32229;-8.07328;,
 3.36457;9.32224;-6.77087;,
 2.24943;9.32224;-7.26126;,
 1.17909;7.66187;-8.76396;,
 0.40289;7.66187;-9.10531;,
 3.76338;7.66187;-7.62750;,
 2.51135;7.66187;-8.17811;,
 1.23427;6.28415;-9.59604;,
 0.40289;6.28415;-9.96165;,
 4.09431;6.28415;-8.33832;,
 2.72867;6.28415;-8.93888;,
 1.29228;4.83575;-10.47083;,
 0.40289;4.83575;-10.86193;,
 4.44224;4.83575;-9.08559;,
 2.95713;4.83575;-9.73868;,
 1.33752;3.70527;-11.15359;,
 0.40289;3.70533;-11.56461;,
 4.71372;3.70527;-9.66884;,
 3.13544;3.70527;-10.36291;,
 13.33672;0.66728;0.27861;,
 9.54851;0.66728;-9.43108;,
 0.40289;0.66728;12.70524;,
 9.54851;0.66728;8.68334;,
 5.81418;-0.00435;-12.49669;,
 5.44353;0.66728;-11.23629;,
 1.45919;0.66728;-12.98847;,
 1.52095;-0.00435;-14.38467;,
 0.40289;0.66728;-13.45298;,
 5.44353;0.66728;-11.23629;,
 3.85811;-0.00435;-13.35688;,
 3.61470;0.66728;-12.04055;;
 
 126;
 3;0,1,2;,
 3;0,2,3;,
 3;0,4,5;,
 3;0,5,1;,
 3;6,7,8;,
 3;8,7,9;,
 4;10,11,12,9;,
 3;13,12,11;,
 3;14,7,15;,
 4;15,7,16,17;,
 4;18,11,10,19;,
 4;18,19,14,15;,
 4;20,13,11,18;,
 4;20,18,15,17;,
 4;21,22,17,16;,
 4;23,13,20,24;,
 4;24,20,17,22;,
 4;25,26,22,21;,
 4;27,28,23,24;,
 4;26,27,24,22;,
 4;29,30,26,25;,
 4;31,32,28,27;,
 4;30,31,27,26;,
 4;33,34,30,29;,
 4;35,36,32,31;,
 4;34,35,31,30;,
 4;37,38,34,33;,
 4;39,40,36,35;,
 4;38,39,35,34;,
 4;41,42,38,37;,
 4;43,44,40,39;,
 4;42,43,39,38;,
 4;45,2,1,46;,
 4;45,46,9,12;,
 4;47,5,4,48;,
 4;47,48,6,8;,
 4;46,1,5,47;,
 4;46,47,8,9;,
 4;49,50,2,45;,
 4;49,45,12,13;,
 4;51,3,52,53;,
 4;51,53,42,41;,
 4;54,55,50,56;,
 4;54,56,44,43;,
 4;53,52,55,54;,
 4;53,54,43,42;,
 3;57,58,59;,
 3;60,57,59;,
 3;61,62,59;,
 3;58,61,59;,
 3;63,64,65;,
 3;66,64,63;,
 4;66,67,68,69;,
 3;68,67,70;,
 3;71,64,72;,
 4;73,74,64,71;,
 4;75,69,68,76;,
 4;71,72,75,76;,
 4;76,68,70,77;,
 4;73,71,76,77;,
 4;74,73,78,79;,
 4;80,77,70,81;,
 4;78,73,77,80;,
 4;79,78,82,83;,
 4;80,81,84,85;,
 4;78,80,85,82;,
 4;83,82,86,87;,
 4;85,84,88,89;,
 4;82,85,89,86;,
 4;87,86,90,91;,
 4;89,88,92,93;,
 4;86,89,93,90;,
 4;91,90,94,95;,
 4;93,92,96,97;,
 4;90,93,97,94;,
 4;95,94,98,99;,
 4;97,96,100,101;,
 4;94,97,101,98;,
 4;102,58,57,103;,
 4;67,66,102,103;,
 4;104,62,61,105;,
 4;63,65,104,105;,
 4;105,61,58,102;,
 4;66,63,105,102;,
 4;103,57,106,107;,
 4;70,67,103,107;,
 4;108,109,60,110;,
 4;99,98,108,110;,
 4;111,106,112,113;,
 4;101,100,111,113;,
 4;113,112,109,108;,
 4;98,101,113,108;,
 4;2,57,60,3;,
 4;3,60,59,0;,
 4;0,59,62,4;,
 4;6,65,64,7;,
 4;7,64,66,9;,
 4;9,66,69,10;,
 4;14,72,64,7;,
 4;7,64,74,16;,
 4;10,69,75,19;,
 4;19,75,72,14;,
 4;16,74,79,21;,
 4;23,81,70,13;,
 4;21,79,83,25;,
 4;28,84,81,23;,
 4;25,83,87,29;,
 4;32,88,84,28;,
 4;29,87,91,33;,
 4;36,92,88,32;,
 4;33,91,95,37;,
 4;40,96,92,36;,
 4;37,95,99,41;,
 4;44,100,96,40;,
 4;4,62,104,48;,
 4;48,104,65,6;,
 4;49,107,106,50;,
 4;50,106,57,2;,
 4;13,70,107,49;,
 4;51,110,60,3;,
 4;3,60,109,52;,
 4;41,99,110,51;,
 4;55,112,106,50;,
 4;50,106,111,56;,
 4;56,111,100,44;,
 4;52,109,112,55;;
 
 MeshMaterialList {
  11;
  126;
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
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
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
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
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
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
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
  0;;
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
  124;
  0.000000;-1.000000;-0.000000;,
  -0.013714;0.999876;0.007764;,
  -0.454805;0.889355;0.046908;,
  -0.341940;0.880964;-0.327079;,
  -0.097176;0.883725;-0.457807;,
  -0.102561;0.870225;0.481860;,
  -0.313656;0.873215;0.372982;,
  -0.123466;0.890380;-0.438155;,
  -0.026578;0.999593;-0.010379;,
  -0.159397;0.811165;-0.562676;,
  -0.018749;0.999666;-0.017786;,
  -0.184444;0.888857;-0.419420;,
  -0.026661;0.999591;-0.010381;,
  -0.194083;0.876125;-0.441290;,
  -0.018868;0.999665;-0.017749;,
  -0.184444;0.888859;-0.419416;,
  -0.026642;0.999591;-0.010395;,
  -0.194038;0.876127;-0.441306;,
  -0.018820;0.999665;-0.017768;,
  -0.173717;0.548617;-0.817828;,
  -0.342186;0.526722;-0.778121;,
  -0.342190;0.526725;-0.778118;,
  -0.342189;0.526723;-0.778119;,
  -0.177775;0.519491;-0.835778;,
  -0.349885;0.494532;-0.795624;,
  -0.349885;0.494532;-0.795624;,
  -0.349886;0.494532;-0.795624;,
  -0.177777;0.519486;-0.835781;,
  -0.349884;0.494530;-0.795626;,
  -0.349884;0.494532;-0.795625;,
  -0.349889;0.494532;-0.795622;,
  -0.177774;0.519492;-0.835778;,
  -0.349881;0.494535;-0.795625;,
  -0.349883;0.494533;-0.795625;,
  -0.349888;0.494531;-0.795624;,
  -0.177775;0.519500;-0.835773;,
  -0.349887;0.494533;-0.795623;,
  -0.349888;0.494526;-0.795627;,
  -0.349888;0.494524;-0.795629;,
  -0.177779;0.519503;-0.835770;,
  -0.349893;0.494537;-0.795618;,
  -0.349888;0.494534;-0.795622;,
  -0.349887;0.494533;-0.795623;,
  -0.718265;0.692791;0.064317;,
  -0.493135;0.739182;-0.458725;,
  -0.140718;0.741506;-0.656024;,
  -0.171899;0.564538;0.807308;,
  -0.530980;0.601980;0.596389;,
  -0.138822;0.729131;-0.670147;,
  -0.278708;0.721577;-0.633757;,
  -0.278704;0.721580;-0.633755;,
  -0.278703;0.721581;-0.633755;,
  0.013714;0.999876;0.007764;,
  0.454805;0.889355;0.046908;,
  0.341940;0.880964;-0.327079;,
  0.097176;0.883725;-0.457807;,
  0.102561;0.870225;0.481860;,
  0.313656;0.873215;0.372982;,
  0.123466;0.890380;-0.438155;,
  0.026578;0.999593;-0.010379;,
  0.159397;0.811165;-0.562676;,
  0.018749;0.999666;-0.017786;,
  0.184444;0.888857;-0.419420;,
  0.026661;0.999591;-0.010381;,
  0.194083;0.876125;-0.441290;,
  0.018868;0.999665;-0.017749;,
  0.184444;0.888859;-0.419416;,
  0.026642;0.999591;-0.010395;,
  0.194038;0.876127;-0.441306;,
  0.018820;0.999665;-0.017768;,
  0.173717;0.548617;-0.817828;,
  0.342186;0.526722;-0.778121;,
  0.342190;0.526725;-0.778118;,
  0.342189;0.526723;-0.778119;,
  0.177775;0.519491;-0.835778;,
  0.349885;0.494532;-0.795624;,
  0.349885;0.494532;-0.795624;,
  0.349886;0.494532;-0.795624;,
  0.177777;0.519486;-0.835781;,
  0.349884;0.494530;-0.795626;,
  0.349884;0.494532;-0.795625;,
  0.349889;0.494532;-0.795622;,
  0.177774;0.519492;-0.835778;,
  0.349881;0.494535;-0.795625;,
  0.349883;0.494533;-0.795625;,
  0.349888;0.494531;-0.795624;,
  0.177775;0.519500;-0.835773;,
  0.349887;0.494533;-0.795623;,
  0.349888;0.494526;-0.795627;,
  0.349888;0.494524;-0.795629;,
  0.177779;0.519503;-0.835770;,
  0.349893;0.494537;-0.795618;,
  0.349888;0.494534;-0.795622;,
  0.349887;0.494533;-0.795623;,
  0.718265;0.692791;0.064317;,
  0.493135;0.739182;-0.458725;,
  0.140718;0.741506;-0.656024;,
  0.171899;0.564538;0.807308;,
  0.530980;0.601980;0.596389;,
  0.138822;0.729131;-0.670147;,
  0.278708;0.721577;-0.633757;,
  0.278704;0.721580;-0.633755;,
  0.278703;0.721581;-0.633755;,
  -0.243285;0.945679;-0.215646;,
  -0.606800;0.793415;0.047811;,
  -0.516321;0.656513;0.549912;,
  -0.169306;0.584672;0.793407;,
  -0.063070;0.955145;-0.289346;,
  0.606800;0.793415;0.047811;,
  0.243285;0.945679;-0.215646;,
  0.169306;0.584672;0.793407;,
  0.516321;0.656513;0.549912;,
  0.063070;0.955145;-0.289346;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.483507;0.875340;,
  0.000000;-0.508117;0.861288;,
  0.000000;-0.458507;0.888691;,
  0.000000;-0.458507;0.888691;,
  0.000000;-0.458505;0.888692;,
  0.000000;-0.458503;0.888693;,
  0.000000;-0.458511;0.888689;,
  0.000000;-0.986951;0.161018;,
  0.000000;-0.702398;0.711785;;
  126;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;5,1,6;,
  3;6,1,2;,
  4;8,10,3,2;,
  3;9,3,10;,
  3;12,1,14;,
  4;14,1,4,13;,
  4;18,10,8,16;,
  4;18,16,12,14;,
  4;17,9,10,18;,
  4;17,18,14,13;,
  4;19,21,13,4;,
  4;20,9,17,22;,
  4;22,17,13,21;,
  4;23,24,21,19;,
  4;25,26,20,22;,
  4;24,25,22,21;,
  4;27,28,24,23;,
  4;29,30,26,25;,
  4;28,29,25,24;,
  4;31,32,28,27;,
  4;33,34,30,29;,
  4;32,33,29,28;,
  4;35,36,32,31;,
  4;37,38,34,33;,
  4;36,37,33,32;,
  4;39,40,36,35;,
  4;41,42,38,37;,
  4;40,41,37,36;,
  4;44,103,104,43;,
  4;44,43,2,3;,
  4;47,105,106,46;,
  4;47,46,5,6;,
  4;43,104,105,47;,
  4;43,47,6,2;,
  4;48,7,103,44;,
  4;48,44,3,9;,
  4;45,107,11,49;,
  4;45,49,40,39;,
  4;50,15,7,51;,
  4;50,51,42,41;,
  4;49,11,15,50;,
  4;49,50,41,40;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;57,52,56;,
  3;53,52,57;,
  4;53,54,61,59;,
  3;61,54,60;,
  3;65,52,63;,
  4;64,55,52,65;,
  4;67,59,61,69;,
  4;65,63,67,69;,
  4;69,61,60,68;,
  4;64,65,69,68;,
  4;55,64,72,70;,
  4;73,68,60,71;,
  4;72,64,68,73;,
  4;70,72,75,74;,
  4;73,71,77,76;,
  4;72,73,76,75;,
  4;74,75,79,78;,
  4;76,77,81,80;,
  4;75,76,80,79;,
  4;78,79,83,82;,
  4;80,81,85,84;,
  4;79,80,84,83;,
  4;82,83,87,86;,
  4;84,85,89,88;,
  4;83,84,88,87;,
  4;86,87,91,90;,
  4;88,89,93,92;,
  4;87,88,92,91;,
  4;94,108,109,95;,
  4;54,53,94,95;,
  4;97,110,111,98;,
  4;57,56,97,98;,
  4;98,111,108,94;,
  4;53,57,98,94;,
  4;95,109,58,99;,
  4;60,54,95,99;,
  4;100,62,112,96;,
  4;90,91,100,96;,
  4;102,58,66,101;,
  4;92,93,102,101;,
  4;101,66,62,100;,
  4;91,92,101,100;,
  4;103,109,112,107;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,56,52,1;,
  4;113,113,113,113;,
  4;114,114,114,114;,
  4;114,114,114,114;,
  4;1,52,55,4;,
  4;114,114,114,114;,
  4;114,114,114,114;,
  4;4,55,70,19;,
  4;115,115,116,116;,
  4;19,70,74,23;,
  4;117,117,115,115;,
  4;23,74,78,27;,
  4;118,118,117,117;,
  4;27,78,82,31;,
  4;119,119,118,118;,
  4;31,82,86,35;,
  4;120,120,119,119;,
  4;35,86,90,39;,
  4;121,121,120,120;,
  4;106,110,97,46;,
  4;46,97,56,5;,
  4;48,99,58,7;,
  4;122,122,0,0;,
  4;9,60,99,48;,
  4;45,96,112,107;,
  4;0,0,0,0;,
  4;39,90,96,45;,
  4;0,0,122,122;,
  4;122,122,123,123;,
  4;123,123,121,121;,
  4;0,0,0,0;;
 }
}