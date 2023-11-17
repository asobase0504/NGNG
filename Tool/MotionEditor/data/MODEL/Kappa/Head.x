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
 88;
 11.26808;26.27578;7.90586;,
 -0.04135;26.27578;14.43538;,
 -0.04135;20.28427;18.43877;,
 14.73514;20.28427;9.90759;,
 -11.35078;26.27578;7.90586;,
 -14.81784;20.28427;9.90759;,
 -11.35078;26.27578;-5.15313;,
 -14.81784;20.28427;-7.15485;,
 -0.04135;26.27578;-11.68265;,
 -0.04135;20.28427;-15.68604;,
 14.73514;20.28427;-7.15485;,
 15.95261;13.21677;10.61050;,
 15.95261;13.21677;-7.85774;,
 -0.04135;13.21677;19.84460;,
 -16.03529;13.21677;10.61050;,
 -16.03529;13.21677;-7.85774;,
 -0.04135;13.21677;-17.09186;,
 14.73514;6.14929;9.90759;,
 14.73514;6.14929;-7.15485;,
 -0.04135;6.14929;18.43877;,
 -14.81784;6.14929;9.90759;,
 -14.81784;6.14929;-7.15485;,
 -0.04135;6.14929;-15.68604;,
 11.26808;0.15777;7.90586;,
 11.26808;0.15777;-5.15313;,
 -0.04135;0.15777;14.43538;,
 -11.35078;0.15777;7.90586;,
 -11.35078;0.15777;-5.15313;,
 -0.04135;0.15777;-11.68265;,
 11.26808;26.27578;7.89562;,
 11.26808;26.27578;-5.15313;,
 11.26808;26.27578;-5.12485;,
 -10.67215;26.22980;-5.42621;,
 -11.27158;26.22980;7.59652;,
 0.46681;26.22980;14.37370;,
 11.39591;26.22980;7.39740;,
 0.80822;26.22980;-10.98821;,
 -10.75580;26.22980;-4.31174;,
 -11.65026;26.22980;-19.21402;,
 11.00307;26.22980;-4.56271;,
 -0.56093;26.22980;-11.23921;,
 11.89758;26.22980;-19.46500;,
 -0.33664;26.22980;13.98589;,
 11.22738;26.22980;7.30938;,
 12.12189;26.22980;22.21171;,
 10.61057;26.22980;7.80885;,
 10.61057;26.22980;-5.54415;,
 23.96360;26.22980;1.13239;,
 -11.10345;26.22980;7.50556;,
 0.46058;26.22980;14.18205;,
 -11.99796;26.22980;22.40790;,
 -10.51293;26.22980;-5.32376;,
 -10.51293;26.22980;8.02923;,
 -23.86594;26.22980;1.35272;,
 -7.52765;11.36463;-14.06590;,
 -12.25017;13.84290;-10.55815;,
 -12.10616;20.00883;-8.91228;,
 -7.23966;23.69647;-10.77417;,
 -2.51713;21.21819;-14.28191;,
 -2.66112;15.05227;-15.92776;,
 9.40999;11.36463;-13.36769;,
 4.01095;13.84290;-15.70363;,
 2.65757;20.00883;-14.75596;,
 6.70327;23.69647;-11.47239;,
 12.10231;21.21819;-9.13644;,
 13.45567;15.05227;-10.08407;,
 -7.51903;12.65309;-13.73797;,
 -11.25470;14.61351;-10.96323;,
 -11.14079;19.49094;-9.66127;,
 -7.29122;22.40802;-11.13407;,
 -3.55553;20.44760;-13.90881;,
 -3.66945;15.57016;-15.21074;,
 9.34322;12.65309;-13.12522;,
 5.07238;14.61351;-14.97304;,
 4.00182;19.49094;-14.22342;,
 7.20210;22.40802;-11.62599;,
 11.47292;20.44760;-9.77819;,
 12.54348;15.57016;-10.52780;,
 -0.18816;10.95086;-16.83155;,
 -0.18816;5.52494;-25.65855;,
 -8.02622;6.84862;-11.21000;,
 7.64993;6.84862;-11.36880;,
 -0.18816;8.21603;-20.18890;,
 -0.18814;2.95663;-13.65914;,
 -0.18814;5.45138;-24.98210;,
 7.64993;7.05887;-11.28613;,
 -8.02622;7.05887;-11.26632;,
 -0.18814;5.69144;-19.51247;;
 
 71;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;10,3,11,12;,
 4;3,2,13,11;,
 4;2,5,14,13;,
 4;5,7,15,14;,
 4;7,9,16,15;,
 4;12,11,17,18;,
 4;11,13,19,17;,
 4;13,14,20,19;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 4;18,17,23,24;,
 4;17,19,25,23;,
 4;19,20,26,25;,
 4;20,21,27,26;,
 4;21,22,28,27;,
 3;29,1,0;,
 4;12,16,9,10;,
 4;18,22,16,12;,
 4;24,28,22,18;,
 4;30,10,9,8;,
 4;31,29,3,10;,
 4;30,8,32,33;,
 4;33,34,35,30;,
 3;36,37,38;,
 3;38,37,36;,
 3;39,40,41;,
 3;41,40,39;,
 3;42,43,44;,
 3;44,43,42;,
 3;45,46,47;,
 3;47,46,45;,
 3;48,49,50;,
 3;50,49,48;,
 3;51,52,53;,
 3;53,52,51;,
 4;54,55,56,57;,
 4;57,58,59,54;,
 4;54,59,58,57;,
 4;57,56,55,54;,
 4;60,61,62,63;,
 4;63,64,65,60;,
 4;60,65,64,63;,
 4;63,62,61,60;,
 4;66,67,68,69;,
 4;69,70,71,66;,
 4;66,71,70,69;,
 4;69,68,67,66;,
 4;72,73,74,75;,
 4;75,76,77,72;,
 4;72,77,76,75;,
 4;75,74,73,72;,
 3;78,79,80;,
 3;80,79,81;,
 3;81,79,78;,
 3;82,78,80;,
 3;82,80,81;,
 3;82,81,78;,
 3;83,84,85;,
 3;85,84,86;,
 3;86,84,83;,
 3;87,83,85;,
 3;87,85,86;,
 3;87,86,83;,
 3;86,85,78;,
 3;81,80,83;,
 4;28,24,23,25;,
 4;25,26,27,28;;
 
 MeshMaterialList {
  7;
  71;
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
  2,
  2,
  2,
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
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
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
  2;;
  Material {
   0.800000;0.784000;0.496000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.128800;0.344800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.244800;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.800000;0.210400;1.000000;;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.784000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  83;
  -0.000847;0.800754;-0.598993;,
  0.432767;0.500851;-0.749574;,
  0.432767;0.500851;0.749574;,
  0.000000;0.800408;0.599455;,
  -0.720073;0.555572;0.415734;,
  -0.720073;0.555572;-0.415734;,
  -0.000000;0.385931;-0.922528;,
  0.798932;0.385931;-0.461264;,
  0.798932;0.385932;0.461264;,
  0.000000;0.385932;0.922527;,
  -0.798932;0.385931;0.461264;,
  -0.798932;0.385931;-0.461264;,
  -0.500000;-0.000000;-0.866026;,
  1.000000;-0.000000;-0.000000;,
  0.866025;-0.000000;0.500000;,
  -0.000000;-0.000000;1.000000;,
  -0.866025;-0.000000;0.500000;,
  -0.866025;-0.000000;-0.500000;,
  0.000000;-0.385931;-0.922528;,
  0.798932;-0.385931;-0.461264;,
  0.798932;-0.385932;0.461264;,
  -0.000000;-0.385932;0.922527;,
  -0.798932;-0.385931;0.461264;,
  -0.798932;-0.385931;-0.461264;,
  0.000000;-0.894630;-0.446808;,
  0.519144;-0.800408;-0.299728;,
  0.519143;-0.800408;0.299728;,
  0.000000;-0.894630;0.446808;,
  -0.519143;-0.800408;0.299728;,
  -0.519143;-0.800408;-0.299728;,
  0.865533;0.500852;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.001051;0.999998;0.001819;,
  -0.002118;0.999996;0.001807;,
  0.000016;0.999998;0.001832;,
  0.000000;-1.000000;-0.000000;,
  -0.497309;0.234569;-0.835261;,
  -0.497306;0.234569;-0.835263;,
  -0.497312;0.234569;-0.835259;,
  0.474702;0.234571;-0.848313;,
  0.474704;0.234570;-0.848312;,
  0.474700;0.234572;-0.848314;,
  -0.497307;0.234572;-0.835262;,
  -0.497305;0.234571;-0.835263;,
  -0.497309;0.234572;-0.835260;,
  0.474702;0.234570;-0.848313;,
  0.474703;0.234570;-0.848313;,
  0.474701;0.234571;-0.848314;,
  -0.634752;0.658292;-0.404650;,
  -0.355287;0.923934;-0.141832;,
  -0.242459;-0.803185;0.544159;,
  0.651494;-0.588202;0.479139;,
  0.499290;-0.846141;-0.186427;,
  0.262945;-0.964737;-0.011920;,
  0.187160;0.936473;0.296631;,
  -0.515961;0.776082;0.362603;,
  0.499999;-0.000000;-0.866026;,
  0.497309;-0.234569;0.835261;,
  0.497306;-0.234569;0.835263;,
  0.497312;-0.234569;0.835259;,
  -0.474702;-0.234571;0.848313;,
  -0.474704;-0.234570;0.848312;,
  -0.474700;-0.234572;0.848314;,
  0.497307;-0.234572;0.835262;,
  0.497305;-0.234571;0.835263;,
  0.497309;-0.234572;0.835260;,
  -0.474702;-0.234570;0.848313;,
  -0.474703;-0.234570;0.848313;,
  -0.474701;-0.234571;0.848314;,
  0.251768;-0.801309;0.542693;,
  0.000929;-0.995783;0.091731;,
  0.353687;0.924401;-0.142790;,
  0.629818;0.661723;-0.406758;,
  0.001538;0.988400;0.151867;,
  -0.645852;-0.591930;0.482176;,
  -0.186495;0.936588;0.296687;,
  -0.000147;0.993192;-0.116487;,
  -0.262942;-0.964738;-0.011898;,
  -0.499643;-0.845942;-0.186383;,
  0.000207;-0.986496;0.163784;,
  0.516632;0.775716;0.362431;,
  0.000725;0.819006;0.573785;,
  0.008652;-0.520039;0.854098;;
  71;
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,0,6,11;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,6,12,17;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,12,18,23;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,18,24,29;,
  3;31,3,31;,
  4;56,56,6,7;,
  4;19,18,56,56;,
  4;25,24,18,19;,
  4;1,7,6,0;,
  4;30,30,8,7;,
  4;32,0,33,32;,
  4;32,34,34,32;,
  3;35,35,35;,
  3;31,31,31;,
  3;35,35,35;,
  3;31,31,31;,
  3;35,35,35;,
  3;31,31,31;,
  3;35,35,35;,
  3;31,31,31;,
  3;35,35,35;,
  3;31,31,31;,
  3;35,35,35;,
  3;31,31,31;,
  4;36,38,38,36;,
  4;36,37,37,36;,
  4;57,58,58,57;,
  4;57,59,59,57;,
  4;39,41,41,39;,
  4;39,40,40,39;,
  4;60,61,61,60;,
  4;60,62,62,60;,
  4;42,44,44,42;,
  4;42,43,43,42;,
  4;63,64,64,63;,
  4;63,65,65,63;,
  4;45,47,47,45;,
  4;45,46,46,45;,
  4;66,67,67,66;,
  4;66,68,68,66;,
  3;48,48,49;,
  3;69,70,50;,
  3;71,72,72;,
  3;51,51,69;,
  3;73,49,71;,
  3;74,50,74;,
  3;52,52,53;,
  3;75,76,54;,
  3;77,78,78;,
  3;55,55,75;,
  3;79,53,77;,
  3;80,54,80;,
  3;54,75,81;,
  3;50,69,82;,
  4;24,25,26,27;,
  4;27,28,29,24;;
 }
}