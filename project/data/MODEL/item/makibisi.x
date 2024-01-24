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
 186;
 -13.23749;0.16493;6.68013;,
 -6.78327;2.23846;5.92666;,
 -6.78327;1.24831;5.92666;,
 -13.23749;0.13235;6.68013;,
 -2.07396;4.08656;5.78773;,
 -2.07396;3.58657;5.78773;,
 -1.93503;2.23846;0.76255;,
 -1.93503;1.24831;0.76255;,
 -1.18155;0.16493;-5.37581;,
 -1.18155;0.13235;-5.37581;,
 -1.18155;0.16493;-5.37581;,
 -0.42807;2.23846;0.76255;,
 -0.42807;1.24831;0.76255;,
 -1.18155;0.13235;-5.37581;,
 -0.35345;4.08656;5.85203;,
 -0.35345;3.58657;5.85203;,
 4.42017;2.23846;5.92666;,
 4.42017;1.24831;5.92666;,
 10.87440;0.16493;6.68013;,
 10.87440;0.13235;6.68013;,
 10.87440;0.16493;6.68013;,
 4.42017;2.23846;7.43362;,
 4.42017;1.24831;7.43362;,
 10.87440;0.13235;6.68013;,
 -0.28915;4.08656;7.57254;,
 -0.28915;3.58657;7.57254;,
 -0.42807;2.23846;12.59773;,
 -0.42807;1.24831;12.59773;,
 -1.18155;0.16493;18.73608;,
 -1.18155;0.13235;18.73608;,
 -1.18155;0.16493;18.73608;,
 -1.93503;2.23846;12.59773;,
 -1.93503;1.24831;12.59773;,
 -1.18155;0.13235;18.73608;,
 -2.00965;4.08656;7.50824;,
 -2.00965;3.58657;7.50824;,
 -6.78327;2.23846;7.43362;,
 -6.78327;1.24831;7.43362;,
 -13.23749;0.16493;6.68013;,
 -13.23749;0.13235;6.68013;,
 -0.42807;2.23846;12.59773;,
 -1.18155;4.08656;8.23254;,
 -1.93503;2.23846;12.59773;,
 -0.31965;4.08656;7.54204;,
 4.42017;2.23846;7.43362;,
 0.37085;4.08656;6.68013;,
 4.42017;2.23846;5.92666;,
 -1.93864;4.08656;7.43722;,
 -2.00965;4.08656;7.50824;,
 -1.18155;13.91515;6.68013;,
 -0.42446;4.08656;5.92305;,
 -0.35345;4.08656;5.85203;,
 -2.73396;4.08656;6.68013;,
 -6.78327;2.23846;7.43362;,
 -2.04346;4.08656;5.81823;,
 -1.18155;4.08656;5.12773;,
 -0.42807;2.23846;0.76255;,
 -6.78327;2.23846;5.92666;,
 -13.23749;0.16493;6.68013;,
 -2.07396;4.08656;5.78773;,
 -1.93503;2.23846;0.76255;,
 -1.18155;0.16493;-5.37581;,
 -2.73718;0.16493;-10.43605;,
 2.98199;2.23846;-7.35126;,
 2.98199;1.24831;-7.35126;,
 -2.73718;0.13235;-10.43605;,
 6.91932;4.08656;-4.76391;,
 6.91932;3.58657;-4.76391;,
 9.91544;2.23846;-8.80063;,
 9.91544;1.24831;-8.80063;,
 14.05348;0.16493;-13.39668;,
 14.05348;0.13235;-13.39668;,
 14.05348;0.16493;-13.39668;,
 11.14988;2.23846;-7.93626;,
 11.14988;1.24831;-7.93626;,
 14.05348;0.13235;-13.39668;,
 8.29179;4.08656;-3.72440;,
 8.29179;3.58657;-3.72440;,
 12.15931;2.23846;-0.92524;,
 12.15931;1.24831;-0.92524;,
 17.01413;0.16493;3.39397;,
 17.01413;0.13235;3.39397;,
 17.01413;0.16493;3.39397;,
 11.29495;2.23846;0.30919;,
 11.29495;1.24831;0.30919;,
 17.01413;0.13235;3.39397;,
 7.35762;4.08656;-2.27816;,
 7.35762;3.58657;-2.27816;,
 4.36150;2.23846;1.75855;,
 4.36150;1.24831;1.75855;,
 0.22346;0.16493;6.35462;,
 0.22346;0.13235;6.35462;,
 0.22346;0.16493;6.35462;,
 3.12706;2.23846;0.89419;,
 3.12706;1.24831;0.89419;,
 0.22346;0.13235;6.35462;,
 5.98515;4.08656;-3.31768;,
 5.98515;3.58657;-3.31768;,
 2.11763;2.23846;-6.11684;,
 2.11763;1.24831;-6.11684;,
 -2.73718;0.16493;-10.43605;,
 -2.73718;0.13235;-10.43605;,
 4.36150;2.23846;1.75855;,
 6.24805;4.08656;-2.24938;,
 3.12706;2.23846;0.89419;,
 7.35013;4.08656;-2.32064;,
 11.29495;2.23846;0.30919;,
 8.41013;4.08656;-2.63061;,
 12.15931;2.23846;-0.92524;,
 6.08405;4.08656;-3.33511;,
 5.98515;4.08656;-3.31768;,
 7.13847;13.91515;-3.52104;,
 8.19288;4.08656;-3.70696;,
 8.29179;4.08656;-3.72440;,
 5.86681;4.08656;-4.41146;,
 2.11763;2.23846;-6.11684;,
 6.92681;4.08656;-4.72144;,
 8.02889;4.08656;-4.79269;,
 11.14988;2.23846;-7.93626;,
 2.98199;2.23846;-7.35126;,
 -2.73718;0.16493;-10.43605;,
 6.91932;4.08656;-4.76391;,
 9.91544;2.23846;-8.80063;,
 14.05348;0.16493;-13.39668;,
 -16.72547;0.16493;-10.52082;,
 -10.40278;2.23846;-9.02137;,
 -10.40278;1.24831;-9.02137;,
 -16.72547;0.13235;-10.52082;,
 -5.92995;4.08656;-7.54123;,
 -5.92995;3.58657;-7.54123;,
 -4.08071;2.23846;-12.21584;,
 -4.08071;1.24831;-12.21584;,
 -1.27322;0.16493;-17.72631;,
 -1.27322;0.13235;-17.72631;,
 -1.27322;0.16493;-17.72631;,
 -2.66462;2.23846;-11.70044;,
 -2.66462;1.24831;-11.70044;,
 -1.27322;0.13235;-17.72631;,
 -4.33521;4.08656;-6.89236;,
 -4.33521;3.58657;-6.89236;,
 0.12500;2.23846;-5.18957;,
 0.12500;1.24831;-5.18957;,
 5.93228;0.16493;-2.27405;,
 5.93228;0.13235;-2.27405;,
 5.93228;0.16493;-2.27405;,
 -0.39041;2.23846;-3.77349;,
 -0.39041;1.24831;-3.77349;,
 5.93228;0.13235;-2.27405;,
 -4.86323;4.08656;-5.25362;,
 -4.86323;3.58657;-5.25362;,
 -6.71248;2.23846;-0.57901;,
 -6.71248;1.24831;-0.57901;,
 -9.51997;0.16493;4.93145;,
 -9.51997;0.13235;4.93145;,
 -9.51997;0.16493;4.93145;,
 -8.12856;2.23846;-1.09443;,
 -8.12856;1.24831;-1.09443;,
 -9.51997;0.13235;4.93145;,
 -6.45797;4.08656;-5.90250;,
 -6.45797;3.58657;-5.90250;,
 -10.91818;2.23846;-7.60530;,
 -10.91818;1.24831;-7.60530;,
 -16.72547;0.16493;-10.52082;,
 -16.72547;0.13235;-10.52082;,
 -6.71248;2.23846;-0.57901;,
 -5.92754;4.08656;-4.93865;,
 -8.12856;2.23846;-1.09443;,
 -4.88146;4.08656;-5.29272;,
 -0.39041;2.23846;-3.77349;,
 -3.93782;4.08656;-5.86647;,
 0.12500;2.23846;-5.18957;,
 -6.36696;4.08656;-5.94494;,
 -6.45797;4.08656;-5.90250;,
 -5.39660;13.91515;-6.39743;,
 -4.42623;4.08656;-6.84992;,
 -4.33521;4.08656;-6.89236;,
 -6.85537;4.08656;-6.92839;,
 -10.91818;2.23846;-7.60530;,
 -5.91173;4.08656;-7.50214;,
 -4.86564;4.08656;-7.85620;,
 -2.66462;2.23846;-11.70044;,
 -10.40278;2.23846;-9.02137;,
 -16.72547;0.16493;-10.52082;,
 -5.92995;4.08656;-7.54123;,
 -4.08071;2.23846;-12.21584;,
 -1.27322;0.16493;-17.72631;;
 
 135;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;30,40,41,42;,
 4;40,24,43,41;,
 4;24,44,45,43;,
 4;44,18,46,45;,
 4;42,41,47,48;,
 4;41,43,49,47;,
 4;43,45,50,49;,
 4;45,46,51,50;,
 4;48,47,52,53;,
 4;47,49,54,52;,
 4;49,50,55,54;,
 4;50,51,56,55;,
 4;53,52,57,58;,
 4;52,54,59,57;,
 4;54,55,60,59;,
 4;55,56,61,60;,
 4;15,55,5,49;,
 4;49,54,52,47;,
 4;49,43,45,50;,
 3;51,61,59;,
 3;37,0,2;,
 4;37,2,5,35;,
 4;35,25,27,32;,
 3;27,28,32;,
 4;25,15,17,22;,
 3;22,17,19;,
 4;7,12,15,5;,
 3;8,12,7;,
 4;35,5,15,25;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;92,93,94,95;,
 4;93,96,97,94;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;92,102,103,104;,
 4;102,86,105,103;,
 4;86,106,107,105;,
 4;106,80,108,107;,
 4;104,103,109,110;,
 4;103,105,111,109;,
 4;105,107,112,111;,
 4;107,108,113,112;,
 4;110,109,114,115;,
 4;109,111,116,114;,
 4;111,112,117,116;,
 4;112,113,118,117;,
 4;115,114,119,120;,
 4;114,116,121,119;,
 4;116,117,122,121;,
 4;117,118,123,122;,
 4;77,117,67,111;,
 4;111,116,114,109;,
 4;111,105,107,112;,
 3;113,123,121;,
 3;99,62,64;,
 4;99,64,67,97;,
 4;97,87,89,94;,
 3;89,90,94;,
 4;87,77,79,84;,
 3;84,79,81;,
 4;69,74,77,67;,
 3;70,74,69;,
 4;97,67,77,87;,
 4;124,125,126,127;,
 4;125,128,129,126;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;134,135,136,137;,
 4;135,138,139,136;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;144,145,146,147;,
 4;145,148,149,146;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;154,155,156,157;,
 4;155,158,159,156;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;154,164,165,166;,
 4;164,148,167,165;,
 4;148,168,169,167;,
 4;168,142,170,169;,
 4;166,165,171,172;,
 4;165,167,173,171;,
 4;167,169,174,173;,
 4;169,170,175,174;,
 4;172,171,176,177;,
 4;171,173,178,176;,
 4;173,174,179,178;,
 4;174,175,180,179;,
 4;177,176,181,182;,
 4;176,178,183,181;,
 4;178,179,184,183;,
 4;179,180,185,184;,
 4;139,179,129,173;,
 4;173,178,176,171;,
 4;173,167,169,174;,
 3;175,185,183;,
 3;161,124,126;,
 4;161,126,129,159;,
 4;159,149,151,156;,
 3;151,152,156;,
 4;149,139,141,146;,
 3;146,141,143;,
 4;131,136,139,129;,
 3;132,136,131;,
 4;159,129,139,149;;
 
 MeshMaterialList {
  1;
  135;
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
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  195;
  -0.115955;0.000000;-0.993254;,
  -0.072789;0.000000;-0.997347;,
  -0.029487;0.000000;-0.999565;,
  -0.997197;0.000000;-0.074819;,
  0.004881;0.078233;-0.996923;,
  -0.992550;0.000000;-0.121835;,
  0.997662;0.000000;-0.068346;,
  0.999893;0.000000;-0.014660;,
  0.065876;0.000000;-0.997828;,
  0.115954;0.000000;-0.993255;,
  0.072790;0.000000;0.997347;,
  0.029488;0.000000;0.999565;,
  0.997197;0.000000;0.074819;,
  0.992550;0.000000;0.121835;,
  -0.997662;0.000000;0.068346;,
  -0.999893;0.000000;0.014660;,
  -0.065876;0.000000;0.997828;,
  -0.006564;0.971863;0.235457;,
  0.156719;0.975342;0.155394;,
  0.244259;0.969686;-0.006852;,
  -0.163779;0.972907;0.163180;,
  -0.067168;0.155662;0.985524;,
  0.985524;0.155661;-0.067170;,
  -0.244259;0.969686;0.006851;,
  -0.985524;0.155661;0.067167;,
  0.053196;0.155793;-0.986356;,
  -0.999618;0.000000;-0.027635;,
  0.992550;0.000000;-0.121835;,
  0.015630;0.000000;-0.999878;,
  0.027508;0.078192;-0.996559;,
  0.115955;0.000000;0.993254;,
  0.999618;0.000000;0.027635;,
  -0.992550;0.000000;0.121835;,
  -0.015631;0.000000;0.999878;,
  -0.115955;0.000000;0.993254;,
  0.000000;0.934791;0.355200;,
  0.064844;0.961673;0.266421;,
  -0.074716;0.961535;0.264326;,
  0.274554;0.959119;0.068634;,
  0.361155;0.932506;0.000000;,
  0.272182;0.959002;-0.078941;,
  0.113957;0.968767;-0.220239;,
  0.163779;0.972907;-0.163180;,
  -0.272182;0.959002;0.078941;,
  0.067169;0.155661;-0.985524;,
  0.074716;0.961535;-0.264326;,
  0.006564;0.971863;-0.235457;,
  -0.274554;0.959119;-0.068634;,
  -0.361156;0.932506;0.000000;,
  -0.156719;0.975342;-0.155394;,
  -0.101019;0.971322;-0.215241;,
  -0.064844;0.961673;-0.266421;,
  0.006177;0.939351;-0.342900;,
  0.307239;-0.951623;-0.004156;,
  0.165540;-0.986203;-0.000000;,
  0.151555;-0.977975;0.143515;,
  0.156735;-0.976336;-0.149001;,
  -0.151555;-0.977975;-0.143515;,
  0.003935;-0.954157;-0.299282;,
  0.000000;-0.984780;-0.173808;,
  -0.156735;-0.976336;0.149001;,
  -0.309572;-0.950867;0.004154;,
  -0.170376;-0.985379;0.000000;,
  -0.003935;-0.954157;0.299282;,
  0.000000;-0.984780;0.173808;,
  0.474724;0.000000;-0.880135;,
  0.512430;0.000000;-0.858729;,
  0.549172;0.000000;-0.835709;,
  -0.773942;0.000000;-0.633257;,
  0.575809;0.078233;-0.813832;,
  -0.743166;0.000000;-0.669107;,
  0.856438;0.000000;0.516250;,
  0.827472;0.000000;0.561506;,
  0.626293;0.000000;-0.779588;,
  0.664692;0.000000;-0.747118;,
  -0.512429;0.000000;0.858729;,
  -0.549173;0.000000;0.835709;,
  0.773942;0.000000;0.633256;,
  0.743168;0.000000;0.669105;,
  -0.856439;0.000000;-0.516249;,
  -0.827473;0.000000;-0.561506;,
  -0.626293;0.000000;0.779588;,
  -0.140429;0.971863;0.189110;,
  0.039247;0.975342;0.217182;,
  0.204015;0.969686;0.134489;,
  -0.227756;0.972907;0.039729;,
  -0.620294;0.155661;0.768769;,
  0.845821;0.155662;0.510251;,
  -0.204015;0.969686;-0.134489;,
  -0.845821;0.155661;-0.510252;,
  0.609327;0.155793;-0.777463;,
  -0.802989;0.000000;-0.595993;,
  0.882931;0.000000;0.469503;,
  0.586310;0.000000;-0.810087;,
  0.594136;0.078192;-0.800555;,
  -0.474723;0.000000;0.880135;,
  0.802989;0.000000;0.595994;,
  -0.882932;0.000000;-0.469502;,
  -0.586310;0.000000;0.810087;,
  -0.664692;0.000000;0.747117;,
  -0.203734;0.934790;0.290963;,
  -0.099696;0.961673;0.255432;,
  -0.212815;0.961535;0.173668;,
  0.185534;0.959119;0.213700;,
  0.295841;0.932506;0.207151;,
  0.268238;0.959002;0.091453;,
  0.219673;0.968766;-0.115046;,
  0.227757;0.972907;-0.039729;,
  -0.268237;0.959002;-0.091453;,
  0.620296;0.155662;-0.768767;,
  0.212815;0.961535;-0.173667;,
  0.140429;0.971863;-0.189110;,
  -0.185534;0.959119;-0.213699;,
  -0.295841;0.932506;-0.207151;,
  -0.039247;0.975342;-0.217182;,
  0.040707;0.971322;-0.234257;,
  0.099696;0.961673;-0.255433;,
  0.201740;0.939351;-0.277344;,
  0.254058;-0.951624;0.172821;,
  0.135602;-0.986203;0.094950;,
  0.041830;-0.977975;0.204489;,
  0.213853;-0.976337;-0.032154;,
  -0.041830;-0.977975;-0.204489;,
  0.174884;-0.954157;-0.242900;,
  0.099692;-0.984780;-0.142375;,
  -0.213853;-0.976336;0.032154;,
  -0.255969;-0.950867;-0.174160;,
  -0.139564;-0.985379;-0.097724;,
  -0.174884;-0.954157;0.242900;,
  -0.099692;-0.984780;0.142375;,
  0.230752;0.000000;-0.973013;,
  0.272714;0.000000;-0.962095;,
  0.314163;0.000000;-0.949369;,
  -0.911470;0.000000;-0.411367;,
  0.345555;0.078232;-0.935132;,
  -0.891022;0.000000;-0.453960;,
  0.960871;0.000000;0.276996;,
  0.944606;0.000000;0.328207;,
  0.403180;0.000000;-0.915121;,
  0.448675;0.000000;-0.893695;,
  -0.272714;0.000000;0.962095;,
  -0.314163;0.000000;0.949369;,
  0.911470;0.000000;0.411368;,
  0.891022;0.000000;0.453960;,
  -0.960871;0.000000;-0.276996;,
  -0.944606;0.000000;-0.328207;,
  -0.403180;0.000000;0.915121;,
  -0.086700;0.971863;0.219012;,
  0.094120;0.975342;0.199624;,
  0.231871;0.969686;0.077104;,
  -0.209714;0.972907;0.097323;,
  -0.400187;0.155661;0.903117;,
  0.949062;0.155661;0.273956;,
  -0.231872;0.969686;-0.077103;,
  -0.949062;0.155660;-0.273955;,
  0.387341;0.155792;-0.908678;,
  -0.929883;0.000000;-0.367856;,
  0.974362;0.000000;0.224986;,
  0.356666;0.000000;-0.934232;,
  0.366693;0.078192;-0.927051;,
  -0.230751;0.000000;0.973013;,
  0.929882;0.000000;0.367857;,
  -0.974362;0.000000;-0.224986;,
  -0.356666;0.000000;0.934232;,
  -0.448675;0.000000;0.893695;,
  -0.121486;0.934790;0.333778;,
  -0.030189;0.961673;0.272532;,
  -0.160616;0.961535;0.222830;,
  0.234522;0.959119;0.158398;,
  0.339375;0.932506;0.123523;,
  0.282767;0.959002;0.018912;,
  0.182411;0.968767;-0.167981;,
  0.209713;0.972907;-0.097323;,
  -0.282767;0.959002;-0.018911;,
  0.400185;0.155661;-0.903118;,
  0.160615;0.961535;-0.222831;,
  0.086699;0.971863;-0.219012;,
  -0.234522;0.959119;-0.158397;,
  -0.339375;0.932506;-0.123521;,
  -0.094120;0.975342;-0.199624;,
  -0.021310;0.971322;-0.236811;,
  0.030188;0.961673;-0.272532;,
  0.123084;0.939351;-0.320108;,
  0.290131;-0.951623;0.101175;,
  0.155557;-0.986203;0.056617;,
  0.093330;-0.977975;0.186695;,
  0.198245;-0.976336;-0.086408;,
  -0.093330;-0.977975;-0.186695;,
  0.106059;-0.954157;-0.279887;,
  0.059446;-0.984780;-0.163325;,
  -0.198244;-0.976336;0.086408;,
  -0.292323;-0.950867;-0.101976;,
  -0.160101;-0.985379;-0.058272;,
  -0.106058;-0.954157;0.279887;,
  -0.059445;-0.984780;0.163326;;
  135;
  4;0,1,1,0;,
  4;1,2,4,1;,
  4;26,3,3,26;,
  4;3,5,5,3;,
  4;27,6,6,27;,
  4;6,7,7,6;,
  4;28,8,8,29;,
  4;8,9,9,8;,
  4;30,10,10,30;,
  4;10,11,11,10;,
  4;31,12,12,31;,
  4;12,13,13,12;,
  4;32,14,14,32;,
  4;14,15,15,14;,
  4;33,16,16,33;,
  4;16,34,34,16;,
  4;35,36,17,37;,
  4;36,18,18,17;,
  4;18,38,19,18;,
  4;38,39,40,19;,
  4;37,17,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;19,40,41,42;,
  4;20,20,23,43;,
  4;24,24,24,24;,
  4;25,44,25,44;,
  4;42,41,45,46;,
  4;43,23,47,48;,
  4;23,49,50,47;,
  4;49,46,51,50;,
  4;46,45,52,51;,
  4;29,25,4,25;,
  4;24,24,24,24;,
  4;22,22,22,22;,
  3;41,52,50;,
  3;53,54,53;,
  4;53,53,55,56;,
  4;56,57,58,58;,
  3;58,59,58;,
  4;57,60,61,61;,
  3;61,61,62;,
  4;63,63,60,55;,
  3;64,63,63;,
  4;56,55,60,57;,
  4;65,66,66,65;,
  4;66,67,69,66;,
  4;91,68,68,91;,
  4;68,70,70,68;,
  4;92,71,71,92;,
  4;71,72,72,71;,
  4;93,73,73,94;,
  4;73,74,74,73;,
  4;95,75,75,95;,
  4;75,76,76,75;,
  4;96,77,77,96;,
  4;77,78,78,77;,
  4;97,79,79,97;,
  4;79,80,80,79;,
  4;98,81,81,98;,
  4;81,99,99,81;,
  4;100,101,82,102;,
  4;101,83,83,82;,
  4;83,103,84,83;,
  4;103,104,105,84;,
  4;102,82,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;84,105,106,107;,
  4;85,85,88,108;,
  4;89,89,89,89;,
  4;90,109,90,109;,
  4;107,106,110,111;,
  4;108,88,112,113;,
  4;88,114,115,112;,
  4;114,111,116,115;,
  4;111,110,117,116;,
  4;94,90,69,90;,
  4;89,89,89,89;,
  4;87,87,87,87;,
  3;106,117,115;,
  3;118,119,118;,
  4;118,118,120,121;,
  4;121,122,123,123;,
  3;123,124,123;,
  4;122,125,126,126;,
  3;126,126,127;,
  4;128,128,125,120;,
  3;129,128,128;,
  4;121,120,125,122;,
  4;130,131,131,130;,
  4;131,132,134,131;,
  4;156,133,133,156;,
  4;133,135,135,133;,
  4;157,136,136,157;,
  4;136,137,137,136;,
  4;158,138,138,159;,
  4;138,139,139,138;,
  4;160,140,140,160;,
  4;140,141,141,140;,
  4;161,142,142,161;,
  4;142,143,143,142;,
  4;162,144,144,162;,
  4;144,145,145,144;,
  4;163,146,146,163;,
  4;146,164,164,146;,
  4;165,166,147,167;,
  4;166,148,148,147;,
  4;148,168,149,148;,
  4;168,169,170,149;,
  4;167,147,150,150;,
  4;151,151,151,151;,
  4;152,152,152,152;,
  4;149,170,171,172;,
  4;150,150,153,173;,
  4;154,154,154,154;,
  4;155,174,155,174;,
  4;172,171,175,176;,
  4;173,153,177,178;,
  4;153,179,180,177;,
  4;179,176,181,180;,
  4;176,175,182,181;,
  4;159,155,134,155;,
  4;154,154,154,154;,
  4;152,152,152,152;,
  3;171,182,180;,
  3;183,184,183;,
  4;183,183,185,186;,
  4;186,187,188,188;,
  3;188,189,188;,
  4;187,190,191,191;,
  3;191,191,192;,
  4;193,193,190,185;,
  3;194,193,193;,
  4;186,185,190,187;;
 }
 MeshTextureCoords {
  186;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;;
 }
}
