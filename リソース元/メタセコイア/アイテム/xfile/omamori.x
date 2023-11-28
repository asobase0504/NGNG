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
 200;
 0.01478;1.65926;-0.35206;,
 0.13993;1.65926;-0.35206;,
 0.13993;1.36137;-0.53527;,
 0.01478;1.36137;-0.53527;,
 0.13993;0.02350;-0.53527;,
 0.01478;0.02350;-0.53527;,
 0.13993;1.65926;-0.35206;,
 0.13993;1.65926;0.35206;,
 0.13993;1.36137;0.53527;,
 0.13993;1.36137;-0.53527;,
 0.13993;0.02350;0.53527;,
 0.13993;0.02350;-0.53527;,
 0.13993;1.65926;0.35206;,
 0.01478;1.65926;0.35206;,
 0.01478;1.36137;0.53527;,
 0.13993;1.36137;0.53527;,
 0.01478;0.02350;0.53527;,
 0.13993;0.02350;0.53527;,
 0.01478;1.65926;0.35206;,
 0.01478;1.65926;-0.35206;,
 0.01478;1.36137;-0.53527;,
 0.01478;1.36137;0.53527;,
 0.01478;0.02350;-0.53527;,
 0.01478;0.02350;0.53527;,
 0.13993;1.65926;-0.35206;,
 0.01478;1.65926;-0.35206;,
 0.01478;0.02350;-0.53527;,
 0.13993;0.02350;-0.53527;,
 0.14602;1.02644;-0.12529;,
 0.15889;1.01901;-0.12529;,
 0.15889;1.08215;-0.23464;,
 0.14602;1.08587;-0.22821;,
 0.15889;1.00415;-0.12529;,
 0.15889;1.07472;-0.24751;,
 0.14602;0.99673;-0.12529;,
 0.14602;1.07101;-0.25394;,
 0.13315;1.00415;-0.12529;,
 0.13315;1.07472;-0.24751;,
 0.13315;1.01901;-0.12529;,
 0.13315;1.08215;-0.23464;,
 0.14602;1.02644;-0.12529;,
 0.14602;1.08587;-0.22821;,
 0.15889;1.20843;-0.23464;,
 0.14602;1.20471;-0.22821;,
 0.15889;1.21585;-0.24751;,
 0.14602;1.21957;-0.25394;,
 0.13315;1.21585;-0.24751;,
 0.13315;1.20843;-0.23464;,
 0.14602;1.20471;-0.22821;,
 0.15889;1.27156;-0.12529;,
 0.14602;1.26413;-0.12529;,
 0.15889;1.28642;-0.12529;,
 0.14602;1.29385;-0.12529;,
 0.13315;1.28642;-0.12529;,
 0.13315;1.27156;-0.12529;,
 0.14602;1.26413;-0.12529;,
 0.15889;1.20843;-0.01593;,
 0.14602;1.20471;-0.02236;,
 0.15889;1.21585;-0.00306;,
 0.14602;1.21957;0.00337;,
 0.13315;1.21585;-0.00306;,
 0.13315;1.20843;-0.01593;,
 0.14602;1.20471;-0.02236;,
 0.15889;1.08215;-0.01593;,
 0.14602;1.08587;-0.02236;,
 0.15889;1.07472;-0.00306;,
 0.14602;1.07101;0.00337;,
 0.13315;1.07472;-0.00306;,
 0.13315;1.08215;-0.01593;,
 0.14602;1.08587;-0.02236;,
 0.15889;1.01901;-0.12529;,
 0.14602;1.02644;-0.12529;,
 0.15889;1.00415;-0.12529;,
 0.14602;0.99673;-0.12529;,
 0.13315;1.00415;-0.12529;,
 0.13315;1.01901;-0.12529;,
 0.14602;1.02644;-0.12529;,
 0.14602;1.02644;0.13233;,
 0.15889;1.01901;0.13233;,
 0.15889;1.08215;0.02297;,
 0.14602;1.08587;0.02940;,
 0.15889;1.00415;0.13233;,
 0.15889;1.07472;0.01010;,
 0.14602;0.99673;0.13233;,
 0.14602;1.07101;0.00367;,
 0.13315;1.00415;0.13233;,
 0.13315;1.07472;0.01010;,
 0.13315;1.01901;0.13233;,
 0.13315;1.08215;0.02297;,
 0.14602;1.02644;0.13233;,
 0.14602;1.08587;0.02940;,
 0.15889;1.20843;0.02297;,
 0.14602;1.20471;0.02940;,
 0.15889;1.21585;0.01010;,
 0.14602;1.21957;0.00367;,
 0.13315;1.21585;0.01010;,
 0.13315;1.20843;0.02297;,
 0.14602;1.20471;0.02940;,
 0.15889;1.27156;0.13233;,
 0.14602;1.26413;0.13233;,
 0.15889;1.28642;0.13233;,
 0.14602;1.29385;0.13233;,
 0.13315;1.28642;0.13233;,
 0.13315;1.27156;0.13233;,
 0.14602;1.26413;0.13233;,
 0.15889;1.20843;0.24168;,
 0.14602;1.20471;0.23525;,
 0.15889;1.21585;0.25455;,
 0.14602;1.21957;0.26098;,
 0.13315;1.21585;0.25455;,
 0.13315;1.20843;0.24168;,
 0.14602;1.20471;0.23525;,
 0.15889;1.08215;0.24168;,
 0.14602;1.08587;0.23525;,
 0.15889;1.07472;0.25455;,
 0.14602;1.07101;0.26098;,
 0.13315;1.07472;0.25455;,
 0.13315;1.08215;0.24168;,
 0.14602;1.08587;0.23525;,
 0.15889;1.01901;0.13233;,
 0.14602;1.02644;0.13233;,
 0.15889;1.00415;0.13233;,
 0.14602;0.99673;0.13233;,
 0.13315;1.00415;0.13233;,
 0.13315;1.01901;0.13233;,
 0.14602;1.02644;0.13233;,
 0.14602;1.21918;0.00452;,
 0.17046;1.18223;0.00452;,
 0.14602;1.18223;-0.06012;,
 0.14602;1.21918;0.00452;,
 0.14602;1.18223;0.06916;,
 0.14602;1.21918;0.00452;,
 0.08138;1.18223;0.00452;,
 0.14602;1.21918;0.00452;,
 0.14602;1.18223;-0.06012;,
 0.17046;1.10834;0.00452;,
 0.14602;1.10834;-0.06012;,
 0.14602;1.10834;0.06916;,
 0.08138;1.10834;0.00452;,
 0.14602;1.10834;-0.06012;,
 0.14602;1.07139;0.00452;,
 0.14602;1.07139;0.00452;,
 0.14602;1.07139;0.00452;,
 0.14602;1.07139;0.00452;,
 0.14288;1.08765;-0.02244;,
 0.15574;1.08481;-0.01673;,
 0.15574;0.82999;-0.16131;,
 0.14288;0.83378;-0.16662;,
 0.15574;1.07913;-0.00531;,
 0.15574;0.82243;-0.15066;,
 0.14288;1.07628;0.00041;,
 0.14288;0.81865;-0.14535;,
 0.13001;1.07913;-0.00531;,
 0.13001;0.82243;-0.15066;,
 0.13001;1.08481;-0.01673;,
 0.13001;0.82999;-0.16131;,
 0.14288;1.08765;-0.02244;,
 0.14288;0.83378;-0.16662;,
 0.14288;1.08765;0.02271;,
 0.13001;1.08481;0.01699;,
 0.13001;0.82999;0.16157;,
 0.14288;0.83378;0.16688;,
 0.13001;1.07913;0.00557;,
 0.13001;0.82243;0.15093;,
 0.14288;1.07628;-0.00014;,
 0.14288;0.81865;0.14562;,
 0.15574;1.07913;0.00557;,
 0.15574;0.82243;0.15093;,
 0.15574;1.08481;0.01699;,
 0.15574;0.82999;0.16157;,
 0.14288;1.08765;0.02271;,
 0.14288;0.83378;0.16688;,
 0.14063;0.70388;0.24688;,
 0.14063;0.66529;0.24824;,
 0.14063;0.66529;0.17433;,
 0.14063;0.70388;0.03038;,
 0.14063;0.62672;0.24824;,
 0.14063;0.62672;0.17433;,
 0.14063;0.77100;0.03038;,
 0.14063;0.70388;-0.04835;,
 0.14063;0.77100;-0.04835;,
 0.14063;0.66529;-0.19433;,
 0.14063;0.66529;-0.26861;,
 0.14063;0.70388;-0.26484;,
 0.14063;0.62672;-0.19433;,
 0.14063;0.62672;-0.26861;,
 0.14063;0.32753;-0.09140;,
 0.14063;0.40928;-0.15999;,
 0.14063;0.44561;-0.11669;,
 0.14063;0.36387;-0.04810;,
 0.14063;0.54654;-0.20837;,
 0.14063;0.54654;0.19041;,
 0.14063;0.50369;0.19041;,
 0.14063;0.50369;-0.20837;,
 0.14063;0.58649;0.09585;,
 0.14063;0.20464;0.09585;,
 0.14063;0.20464;0.04701;,
 0.14063;0.58649;0.04570;,
 0.14063;0.27018;-0.01484;,
 0.14063;0.31015;0.02513;;
 
 124;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;9,8,10,11;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;18,19,20,21;,
 4;21,20,22,23;,
 4;18,7,24,25;,
 4;26,27,10,23;,
 4;28,29,30,31;,
 4;29,32,33,30;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;31,30,42,43;,
 4;30,33,44,42;,
 4;33,35,45,44;,
 4;35,37,46,45;,
 4;37,39,47,46;,
 4;39,41,48,47;,
 4;43,42,49,50;,
 4;42,44,51,49;,
 4;44,45,52,51;,
 4;45,46,53,52;,
 4;46,47,54,53;,
 4;47,48,55,54;,
 4;50,49,56,57;,
 4;49,51,58,56;,
 4;51,52,59,58;,
 4;52,53,60,59;,
 4;53,54,61,60;,
 4;54,55,62,61;,
 4;57,56,63,64;,
 4;56,58,65,63;,
 4;58,59,66,65;,
 4;59,60,67,66;,
 4;60,61,68,67;,
 4;61,62,69,68;,
 4;64,63,70,71;,
 4;63,65,72,70;,
 4;65,66,73,72;,
 4;66,67,74,73;,
 4;67,68,75,74;,
 4;68,69,76,75;,
 4;77,78,79,80;,
 4;78,81,82,79;,
 4;81,83,84,82;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;80,79,91,92;,
 4;79,82,93,91;,
 4;82,84,94,93;,
 4;84,86,95,94;,
 4;86,88,96,95;,
 4;88,90,97,96;,
 4;92,91,98,99;,
 4;91,93,100,98;,
 4;93,94,101,100;,
 4;94,95,102,101;,
 4;95,96,103,102;,
 4;96,97,104,103;,
 4;99,98,105,106;,
 4;98,100,107,105;,
 4;100,101,108,107;,
 4;101,102,109,108;,
 4;102,103,110,109;,
 4;103,104,111,110;,
 4;106,105,112,113;,
 4;105,107,114,112;,
 4;107,108,115,114;,
 4;108,109,116,115;,
 4;109,110,117,116;,
 4;110,111,118,117;,
 4;113,112,119,120;,
 4;112,114,121,119;,
 4;114,115,122,121;,
 4;115,116,123,122;,
 4;116,117,124,123;,
 4;117,118,125,124;,
 3;126,127,128;,
 3;129,130,127;,
 3;131,132,130;,
 3;133,134,132;,
 4;128,127,135,136;,
 4;127,130,137,135;,
 4;130,132,138,137;,
 4;132,134,139,138;,
 3;136,135,140;,
 3;135,137,141;,
 3;137,138,142;,
 3;138,139,143;,
 4;144,145,146,147;,
 4;145,148,149,146;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;150,148,145,144;,
 4;144,154,152,150;,
 4;151,153,155,157;,
 4;157,146,149,151;,
 4;158,159,160,161;,
 4;159,162,163,160;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;164,162,159,158;,
 4;158,168,166,164;,
 4;165,167,169,171;,
 4;171,160,163,165;,
 4;172,173,174,175;,
 4;173,176,177,174;,
 4;178,175,179,180;,
 4;175,174,181,179;,
 4;179,181,182,183;,
 4;181,184,185,182;,
 4;186,187,188,189;,
 4;190,191,192,193;,
 4;194,195,196,197;,
 4;195,196,198,199;;
 
 MeshMaterialList {
  2;
  124;
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
   0.800000;0.000000;0.100000;1.000000;;
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
 }
 MeshNormals {
  120;
  0.000000;0.872888;-0.487921;,
  0.000000;0.272212;-0.962237;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.872888;0.487921;,
  0.000000;0.272212;0.962237;,
  0.000000;0.000000;1.000000;,
  -0.000080;0.866016;0.500015;,
  0.499913;0.866076;0.000000;,
  -0.000080;-0.866026;-0.499998;,
  -0.499837;-0.866119;-0.000006;,
  -1.000000;0.000000;0.000000;,
  0.499806;0.433039;0.750114;,
  -0.499828;-0.433069;-0.750082;,
  -0.000078;0.000000;1.000000;,
  0.499745;-0.433078;0.750132;,
  -0.000078;0.000000;-1.000000;,
  -0.499954;0.433004;-0.750036;,
  -0.000078;-0.866025;0.500000;,
  0.499784;-0.866150;0.000000;,
  -0.000076;0.866027;-0.499998;,
  -0.500091;0.865973;-0.000006;,
  -0.000078;-0.866025;-0.500000;,
  0.499747;-0.433077;-0.750132;,
  -0.000078;0.866022;0.500006;,
  -0.500136;0.432973;0.749932;,
  -0.000078;0.000000;-1.000000;,
  0.499808;0.433038;-0.750114;,
  -0.000078;0.000000;1.000000;,
  -0.500008;-0.433039;0.749979;,
  -0.000078;0.866016;0.500016;,
  0.499913;0.866076;-0.000000;,
  -0.000078;-0.866022;-0.500006;,
  -0.499874;-0.866098;0.000000;,
  0.499808;0.433038;0.750114;,
  -0.500008;-0.433039;-0.749979;,
  -0.000078;0.000000;1.000000;,
  0.499747;-0.433077;0.750132;,
  -0.000078;0.000000;-1.000000;,
  -0.500136;0.432973;-0.749932;,
  -0.000078;-0.866025;0.500000;,
  0.499784;-0.866150;-0.000000;,
  -0.000078;0.866022;-0.500006;,
  -0.500129;0.865951;0.000000;,
  -0.000078;-0.866025;-0.500000;,
  0.499745;-0.433078;-0.750132;,
  -0.000078;0.866022;0.500006;,
  -0.500136;0.432973;0.749932;,
  0.499806;0.433039;-0.750114;,
  -0.000078;0.000000;1.000000;,
  -0.500009;-0.433039;0.749979;,
  0.834059;0.551675;-0.000011;,
  0.899712;0.273494;-0.340176;,
  0.956772;0.290839;-0.000012;,
  0.899720;0.273496;0.340153;,
  -0.496269;0.868169;-0.000015;,
  0.899712;-0.273494;-0.340176;,
  0.956772;-0.290839;-0.000012;,
  0.899720;-0.273496;0.340153;,
  -0.638119;-0.430896;0.638070;,
  0.834059;-0.551675;-0.000011;,
  0.000000;0.493653;-0.869659;,
  0.447020;0.441585;-0.777931;,
  0.000000;-0.492576;0.870270;,
  -0.447008;-0.440624;0.778482;,
  0.000000;0.493653;0.869659;,
  -0.447019;0.441585;0.777931;,
  0.000000;-0.492576;-0.870270;,
  0.447009;-0.440624;-0.778482;,
  0.000000;-1.000000;-0.000000;,
  0.499690;-0.866204;-0.000006;,
  0.499681;-0.433112;-0.750155;,
  -0.500060;0.865991;0.000000;,
  -0.499954;0.432996;0.750041;,
  0.499810;0.433045;-0.750108;,
  -0.499891;-0.433036;0.750059;,
  0.499946;0.866056;-0.000006;,
  -0.499930;-0.866066;0.000000;,
  0.499990;0.433015;0.750005;,
  -0.499893;-0.433035;-0.750059;,
  0.499863;-0.433081;0.750052;,
  -0.499954;0.432996;-0.750041;,
  -0.000078;0.866016;-0.500016;,
  -0.000078;-0.866022;0.500006;,
  0.499728;-0.866182;-0.000000;,
  0.499863;-0.433081;-0.750052;,
  -0.500060;0.865991;-0.000000;,
  -0.499954;0.432996;0.750041;,
  0.499990;0.433015;-0.750005;,
  -0.499893;-0.433035;0.750059;,
  0.499983;0.866035;-0.000000;,
  -0.499930;-0.866066;-0.000000;,
  0.499990;0.433015;0.750005;,
  -0.499891;-0.433036;-0.750059;,
  0.499863;-0.433081;0.750052;,
  -0.499954;0.432996;-0.750041;,
  -0.000080;0.866016;-0.500015;,
  -0.000078;-0.866022;0.500006;,
  -0.638119;0.430896;0.638070;,
  -0.638097;0.430888;-0.638097;,
  -0.707134;0.000000;0.707079;,
  -0.707107;0.000000;-0.707107;,
  -0.638097;-0.430888;-0.638097;,
  -0.496269;-0.868169;-0.000015;,
  0.447009;-0.440624;0.778482;,
  -0.447020;0.441585;-0.777931;,
  0.000000;0.895308;0.445448;,
  0.000021;0.895308;0.445448;,
  -0.000021;0.895308;0.445448;,
  0.000000;-0.815026;-0.579425;,
  -0.000137;-0.815026;-0.579425;,
  0.000137;-0.815026;-0.579425;,
  -0.447008;-0.440624;-0.778482;,
  0.447020;0.441585;0.777931;,
  -0.000000;0.895308;-0.445448;,
  0.000021;0.895308;-0.445448;,
  -0.000021;0.895308;-0.445448;,
  -0.000136;-0.815026;0.579425;,
  -0.000136;-0.815026;0.579425;,
  -0.000136;-0.815026;0.579425;;
  124;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;4,4,0,0;,
  4;69,69,69,69;,
  4;7,8,12,7;,
  4;3,3,3,3;,
  4;70,9,9,71;,
  4;9,10,13,9;,
  4;11,11,11,11;,
  4;72,7,7,73;,
  4;14,12,15,14;,
  4;3,3,3,3;,
  4;71,16,16,74;,
  4;16,13,17,16;,
  4;11,11,11,11;,
  4;73,14,14,75;,
  4;18,15,19,18;,
  4;3,3,3,3;,
  4;74,20,20,76;,
  4;20,17,21,20;,
  4;11,11,11,11;,
  4;75,18,18,77;,
  4;22,19,23,22;,
  4;3,3,3,3;,
  4;76,24,24,78;,
  4;24,21,25,24;,
  4;11,11,11,11;,
  4;77,22,22,79;,
  4;26,23,27,26;,
  4;3,3,3,3;,
  4;78,28,28,80;,
  4;28,25,29,28;,
  4;11,11,11,11;,
  4;79,26,26,81;,
  4;82,27,8,82;,
  4;3,3,3,3;,
  4;80,83,83,70;,
  4;83,29,10,83;,
  4;11,11,11,11;,
  4;81,82,82,72;,
  4;30,31,34,30;,
  4;3,3,3,3;,
  4;84,32,32,85;,
  4;32,33,35,32;,
  4;11,11,11,11;,
  4;86,30,30,87;,
  4;36,34,37,36;,
  4;3,3,3,3;,
  4;85,38,38,88;,
  4;38,35,39,38;,
  4;11,11,11,11;,
  4;87,36,36,89;,
  4;40,37,41,40;,
  4;3,3,3,3;,
  4;88,42,42,90;,
  4;42,39,43,42;,
  4;11,11,11,11;,
  4;89,40,40,91;,
  4;44,41,45,44;,
  4;3,3,3,3;,
  4;90,46,46,92;,
  4;46,43,47,46;,
  4;11,11,11,11;,
  4;91,44,44,93;,
  4;16,45,48,16;,
  4;3,3,3,3;,
  4;92,49,49,94;,
  4;49,47,50,49;,
  4;11,11,11,11;,
  4;93,16,16,95;,
  4;96,48,31,96;,
  4;3,3,3,3;,
  4;94,97,97,84;,
  4;97,50,33,97;,
  4;11,11,11,11;,
  4;95,96,96,86;,
  3;51,53,52;,
  3;51,54,53;,
  3;55,55,98;,
  3;55,99,55;,
  4;52,53,57,56;,
  4;53,54,58,57;,
  4;98,100,59,59;,
  4;101,99,102,102;,
  3;56,57,60;,
  3;57,58,60;,
  3;59,59,103;,
  3;102,102,103;,
  4;61,62,62,61;,
  4;3,3,3,3;,
  4;104,63,63,104;,
  4;63,64,64,63;,
  4;11,11,11,11;,
  4;105,61,61,105;,
  4;106,107,107,106;,
  4;106,108,108,106;,
  4;109,110,110,109;,
  4;109,111,111,109;,
  4;65,66,66,65;,
  4;11,11,11,11;,
  4;112,67,67,112;,
  4;67,68,68,67;,
  4;3,3,3,3;,
  4;113,65,65,113;,
  4;114,115,115,114;,
  4;114,116,116,114;,
  4;117,118,118,117;,
  4;117,119,119,117;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;;
 }
 MeshTextureCoords {
  200;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.166670;,
  0.166670;0.166670;,
  0.166670;0.000000;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.333330;0.166670;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.333330;0.833330;,
  0.333330;1.000000;,
  0.500000;0.166670;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.500000;0.833330;,
  0.500000;1.000000;,
  0.666670;0.166670;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.666670;0.833330;,
  0.666670;1.000000;,
  0.833330;0.166670;,
  0.833330;0.000000;,
  0.833330;0.333330;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  0.833330;0.833330;,
  0.833330;1.000000;,
  1.000000;0.166670;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.833330;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.166670;,
  0.166670;0.166670;,
  0.166670;0.000000;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.333330;0.166670;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.333330;0.833330;,
  0.333330;1.000000;,
  0.500000;0.166670;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.500000;0.833330;,
  0.500000;1.000000;,
  0.666670;0.166670;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.666670;0.833330;,
  0.666670;1.000000;,
  0.833330;0.166670;,
  0.833330;0.000000;,
  0.833330;0.333330;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  0.833330;0.833330;,
  0.833330;1.000000;,
  1.000000;0.166670;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.833330;,
  1.000000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.333330;,
  0.000000;0.333330;,
  0.375000;0.000000;,
  0.500000;0.333330;,
  0.625000;0.000000;,
  0.750000;0.333330;,
  0.875000;0.000000;,
  1.000000;0.333330;,
  0.250000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.750000;0.666670;,
  1.000000;0.666670;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.166670;,
  1.000000;0.000000;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.166670;,
  1.000000;0.000000;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  0.333330;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  0.333330;1.000000;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;0.200000;,
  0.333330;0.200000;,
  0.333330;0.400000;,
  0.000000;0.400000;,
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
