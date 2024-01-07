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
 284;
 -22.90079;22.26307;-30.41666;,
 23.32969;22.26307;-30.41666;,
 23.32969;0.05468;-30.41666;,
 -22.90079;0.05468;-30.41666;,
 23.32969;22.26307;-30.41666;,
 23.32969;22.26307;15.81371;,
 23.32969;0.05468;15.81371;,
 23.32969;0.05468;-30.41666;,
 23.32969;22.26307;15.81371;,
 -22.90079;22.26307;15.81371;,
 -22.90079;0.05468;15.81371;,
 23.32969;0.05468;15.81371;,
 -22.90079;22.26307;15.81371;,
 -22.90079;22.26307;-30.41666;,
 -22.90079;0.05468;-30.41666;,
 -22.90079;0.05468;15.81371;,
 23.32969;22.26307;-30.41666;,
 -22.90079;22.26307;-30.41666;,
 -22.90079;0.05468;-30.41666;,
 23.32969;0.05468;-30.41666;,
 0.21445;137.59082;-51.12592;,
 31.20306;137.59082;-38.29015;,
 36.08260;131.05690;-43.16964;,
 0.21445;131.05690;-58.02665;,
 44.03893;137.83438;-7.30148;,
 50.93967;131.05690;-7.30148;,
 31.20306;137.83438;23.68710;,
 36.08260;131.05690;28.56669;,
 0.21445;137.83438;36.52293;,
 0.21445;131.05690;43.42369;,
 -30.77420;137.59082;23.68710;,
 -35.65373;131.05690;28.56664;,
 -43.61001;137.59082;-7.30153;,
 -50.51076;131.05690;-7.30153;,
 -30.77420;137.59082;-38.29015;,
 -35.65373;131.05690;-43.16964;,
 36.68111;127.50901;-43.76812;,
 0.21445;127.50901;-58.87309;,
 51.78611;127.50901;-7.30148;,
 36.68111;127.50901;29.16517;,
 0.21445;127.50901;44.27012;,
 -36.25221;127.50901;29.16517;,
 -51.35717;127.50901;-7.30153;,
 -36.25221;127.50901;-43.76812;,
 41.32376;112.92805;-48.41074;,
 0.21445;112.92805;-65.43870;,
 58.35178;112.92805;-7.30148;,
 41.32376;112.92805;33.80779;,
 0.21445;112.92805;50.83575;,
 -40.89485;112.92805;33.80779;,
 -57.92286;112.92805;-7.30153;,
 -40.89485;112.92805;-48.41074;,
 41.95931;107.33645;-49.04638;,
 0.21445;107.33645;-66.33758;,
 59.25057;107.33645;-7.30148;,
 41.95931;107.33645;34.44334;,
 0.21444;107.33645;51.73458;,
 -41.53041;107.33645;34.44329;,
 -58.82165;107.33645;-7.30153;,
 -41.53041;107.33645;-49.04638;,
 43.87585;94.06462;-50.96288;,
 0.21445;94.06462;-69.04796;,
 61.96095;94.06462;-7.30148;,
 43.87585;94.06462;36.35984;,
 0.21444;94.06462;54.44497;,
 -43.44694;94.06462;36.35980;,
 -61.53203;94.06462;-7.30153;,
 -43.44694;94.06462;-50.96288;,
 43.87585;87.37208;-50.96288;,
 0.21445;87.37208;-69.04796;,
 61.96095;87.37208;-7.30148;,
 43.87585;87.37208;36.35984;,
 0.21444;87.37208;54.44497;,
 -43.44694;87.37208;36.35980;,
 -61.53203;87.37208;-7.30153;,
 -43.44694;87.37208;-50.96288;,
 43.87585;71.23934;-50.96288;,
 0.21445;71.23934;-69.04796;,
 61.96095;71.23934;-7.30148;,
 43.87585;71.23934;36.35984;,
 0.21444;71.23934;54.44497;,
 -43.44694;71.23934;36.35980;,
 -61.53203;71.23934;-7.30153;,
 -43.44694;71.23934;-50.96288;,
 43.87585;64.79055;-50.96288;,
 0.21445;64.79055;-69.04796;,
 61.96095;64.79055;-7.30148;,
 43.87585;64.72764;36.35984;,
 0.21444;64.79055;54.44497;,
 -43.44694;64.79055;36.35980;,
 -61.53203;64.79055;-7.30153;,
 -43.44694;64.79055;-50.96288;,
 42.37781;52.32157;-49.46484;,
 0.21445;52.32157;-66.92943;,
 59.84241;52.32157;-7.30148;,
 42.37781;52.32157;34.86185;,
 0.21444;52.32157;52.32642;,
 -41.94890;52.32157;34.86180;,
 -59.41349;52.32157;-7.30153;,
 -41.94890;52.32157;-49.46484;,
 42.37781;45.33786;-49.46484;,
 0.21445;45.33786;-66.92943;,
 59.84241;45.33786;-7.30148;,
 42.37781;45.33786;34.86185;,
 0.21444;45.33786;52.32642;,
 -41.94890;45.33786;34.86180;,
 -59.41349;45.33786;-7.30153;,
 -41.94890;45.33786;-49.46484;,
 40.11179;32.08433;-47.19877;,
 0.21445;32.08433;-63.72480;,
 56.63777;32.08433;-7.30148;,
 40.11179;32.08433;32.59583;,
 0.21445;32.08433;49.12178;,
 -39.68288;32.08433;32.59583;,
 -56.20885;32.08433;-7.30153;,
 -39.68288;32.08433;-47.19877;,
 37.97674;24.64491;-45.06376;,
 0.21445;24.64491;-60.70541;,
 53.61840;24.64491;-7.30148;,
 37.97674;24.64491;30.46078;,
 0.21445;24.64491;46.10245;,
 -37.54784;24.64491;30.46078;,
 -53.18945;24.64491;-7.30153;,
 -37.54784;24.64491;-45.06376;,
 31.56356;16.00412;-38.65064;,
 0.21445;16.00412;-51.63578;,
 44.54878;16.00412;-7.30148;,
 31.56356;16.00412;24.04760;,
 0.21445;16.00412;37.03279;,
 -31.13467;16.00412;24.04760;,
 -44.11987;16.00412;-7.30153;,
 -31.13467;16.00412;-38.65064;,
 -0.81892;132.67648;-63.53891;,
 11.84395;129.75359;-65.44754;,
 5.58407;129.75359;-74.62919;,
 -0.81892;132.67648;-63.53891;,
 8.56848;129.75359;-54.82890;,
 -0.81892;132.67648;-63.53891;,
 -1.77600;129.75359;-50.76870;,
 -0.81892;132.67648;-63.53891;,
 -11.39967;129.75359;-56.32490;,
 -0.81892;132.67648;-63.53891;,
 -13.05568;129.75359;-67.31356;,
 -0.81892;132.67648;-63.53891;,
 -5.49739;129.75359;-75.45953;,
 -0.81892;132.67648;-63.53891;,
 5.58407;129.75359;-74.62919;,
 21.99872;121.56392;-66.97820;,
 10.71884;121.56392;-83.52287;,
 16.09657;121.56392;-47.84365;,
 -2.54339;121.56392;-40.52798;,
 -19.88472;121.56392;-50.53994;,
 -22.86917;121.56392;-70.34056;,
 -9.24917;121.56392;-85.01916;,
 10.71884;121.56392;-83.52287;,
 27.63430;109.72958;-67.82757;,
 13.56837;109.72958;-88.45842;,
 20.27419;109.72958;-43.96729;,
 -2.96933;109.72958;-34.84484;,
 -24.59351;109.72958;-47.32949;,
 -28.31496;109.72958;-72.02033;,
 -11.33147;109.72958;-90.32444;,
 13.56837;109.72958;-88.45842;,
 27.63430;96.59430;-67.82757;,
 13.56837;96.59430;-88.45842;,
 20.27419;96.59430;-43.96729;,
 -2.96933;96.59430;-34.84484;,
 -24.59351;96.59430;-47.32949;,
 -28.31496;96.59430;-72.02033;,
 -11.33147;96.59430;-90.32444;,
 13.56837;96.59430;-88.45842;,
 21.99872;84.75996;-66.97820;,
 10.71884;84.75996;-83.52287;,
 16.09657;84.75996;-47.84365;,
 -2.54339;84.75996;-40.52798;,
 -19.88472;84.75996;-50.53994;,
 -22.86917;84.75996;-70.34056;,
 -9.24917;84.75996;-85.01916;,
 10.71884;84.75996;-83.52287;,
 11.84395;76.57029;-65.44754;,
 5.58407;76.57029;-74.62919;,
 8.56848;76.57029;-54.82890;,
 -1.77600;76.57029;-50.76870;,
 -11.39967;76.57029;-56.32490;,
 -13.05568;76.57029;-67.31356;,
 -5.49739;76.57029;-75.45953;,
 5.58407;76.57029;-74.62919;,
 -0.81892;73.64745;-63.53891;,
 -0.81892;73.64745;-63.53891;,
 -0.81892;73.64745;-63.53891;,
 -0.81892;73.64745;-63.53891;,
 -0.81892;73.64745;-63.53891;,
 -0.81892;73.64745;-63.53891;,
 -0.81892;73.64745;-63.53891;,
 -28.92514;69.67394;-41.11085;,
 -14.38685;69.67394;-41.11085;,
 -14.38685;69.25878;-72.40217;,
 -22.42296;69.25878;-72.40217;,
 0.15104;69.67394;-41.11085;,
 0.15104;69.25878;-72.40217;,
 14.68884;69.67394;-41.11085;,
 14.68884;69.25878;-72.40217;,
 29.22722;69.67394;-41.11085;,
 23.59813;69.25878;-72.40217;,
 -14.38685;45.63854;-84.26901;,
 -22.42296;45.63854;-84.26901;,
 0.15104;45.63854;-84.26901;,
 14.68884;45.63854;-84.26901;,
 23.59813;45.63854;-84.26901;,
 -14.38685;10.98424;-81.33312;,
 -23.11087;28.62464;-81.33312;,
 0.15104;6.11319;-81.33312;,
 14.68884;10.98424;-81.33312;,
 24.18905;29.77291;-81.33312;,
 29.22722;69.67394;-41.11085;,
 29.22722;62.77446;-41.15836;,
 23.59813;61.91116;-67.36185;,
 23.59813;69.25878;-72.40217;,
 23.59813;45.63854;-78.16364;,
 23.59813;45.63854;-84.26901;,
 18.55983;29.77291;-75.22779;,
 24.18905;29.77291;-81.33312;,
 29.22722;62.77446;-41.15836;,
 14.68884;62.77446;-41.15836;,
 14.68884;61.91116;-67.36185;,
 23.59813;61.91116;-67.36185;,
 0.15104;62.77446;-41.15836;,
 0.15104;61.91116;-67.36185;,
 -14.38685;62.77446;-41.15836;,
 -14.38685;61.91116;-67.36185;,
 -28.92514;62.77446;-41.15836;,
 -22.42296;61.91116;-67.36185;,
 14.68884;45.63854;-78.16364;,
 23.59813;45.63854;-78.16364;,
 0.15104;45.63854;-78.16364;,
 -14.38685;45.63854;-78.16364;,
 -22.42296;45.63854;-78.16364;,
 14.68884;10.98424;-75.22779;,
 18.55983;29.77291;-75.22779;,
 0.15104;6.11319;-75.22779;,
 -14.38685;10.98424;-75.22779;,
 -23.11087;28.62464;-75.22779;,
 -28.92514;62.77446;-41.15836;,
 -28.92514;69.67394;-41.11085;,
 -22.42296;69.25878;-72.40217;,
 -22.42296;61.91116;-67.36185;,
 -22.42296;45.63854;-84.26901;,
 -22.42296;45.63854;-78.16364;,
 -23.11087;28.62464;-81.33312;,
 -23.11087;28.62464;-75.22779;,
 -14.38685;62.77446;-41.15836;,
 -14.38685;69.67394;-41.11085;,
 -28.92514;69.67394;-41.11085;,
 0.15104;69.67394;-41.11085;,
 14.68884;62.77446;-41.15836;,
 14.68884;69.67394;-41.11085;,
 29.22722;69.67394;-41.11085;,
 -23.11087;28.62464;-81.33312;,
 -14.38685;10.98424;-81.33312;,
 -14.38685;10.98424;-75.22779;,
 0.15104;6.11319;-81.33312;,
 14.68884;10.98424;-81.33312;,
 14.68884;10.98424;-75.22779;,
 24.18905;29.77291;-81.33312;,
 -22.90079;157.23177;-30.41666;,
 23.32969;157.23177;-30.41666;,
 23.32969;135.02338;-30.41666;,
 -22.90079;135.02338;-30.41666;,
 23.32969;157.23177;-30.41666;,
 23.32969;157.23177;15.81371;,
 23.32969;135.02338;15.81371;,
 23.32969;135.02338;-30.41666;,
 23.32969;157.23177;15.81371;,
 -22.90079;157.23177;15.81371;,
 -22.90079;135.02338;15.81371;,
 23.32969;135.02338;15.81371;,
 -22.90079;157.23177;15.81371;,
 -22.90079;157.23177;-30.41666;,
 -22.90079;135.02338;-30.41666;,
 -22.90079;135.02338;15.81371;,
 23.32969;157.23177;-30.41666;,
 -22.90079;157.23177;-30.41666;,
 -22.90079;135.02338;-30.41666;,
 23.32969;135.02338;-30.41666;;
 
 217;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,20,23,35;,
 4;23,22,36,37;,
 4;22,25,38,36;,
 4;25,27,39,38;,
 4;27,29,40,39;,
 4;29,31,41,40;,
 4;31,33,42,41;,
 4;33,35,43,42;,
 4;35,23,37,43;,
 4;37,36,44,45;,
 4;36,38,46,44;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,41,49,48;,
 4;41,42,50,49;,
 4;42,43,51,50;,
 4;43,37,45,51;,
 4;45,44,52,53;,
 4;44,46,54,52;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,49,57,56;,
 4;49,50,58,57;,
 4;50,51,59,58;,
 4;51,45,53,59;,
 4;53,52,60,61;,
 4;52,54,62,60;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,57,65,64;,
 4;57,58,66,65;,
 4;58,59,67,66;,
 4;59,53,61,67;,
 4;61,60,68,69;,
 4;60,62,70,68;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,65,73,72;,
 4;65,66,74,73;,
 4;66,67,75,74;,
 4;67,61,69,75;,
 4;69,68,76,77;,
 4;68,70,78,76;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,73,81,80;,
 4;73,74,82,81;,
 4;74,75,83,82;,
 4;75,69,77,83;,
 4;77,76,84,85;,
 4;76,78,86,84;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,81,89,88;,
 4;81,82,90,89;,
 4;82,83,91,90;,
 4;83,77,85,91;,
 4;85,84,92,93;,
 4;84,86,94,92;,
 4;86,87,95,94;,
 4;87,88,96,95;,
 4;88,89,97,96;,
 4;89,90,98,97;,
 4;90,91,99,98;,
 4;91,85,93,99;,
 4;93,92,100,101;,
 4;92,94,102,100;,
 4;94,95,103,102;,
 4;95,96,104,103;,
 4;96,97,105,104;,
 4;97,98,106,105;,
 4;98,99,107,106;,
 4;99,93,101,107;,
 4;101,100,108,109;,
 4;100,102,110,108;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,106,114,113;,
 4;106,107,115,114;,
 4;107,101,109,115;,
 4;109,108,116,117;,
 4;108,110,118,116;,
 4;110,111,119,118;,
 4;111,112,120,119;,
 4;112,113,121,120;,
 4;113,114,122,121;,
 4;114,115,123,122;,
 4;115,109,117,123;,
 4;117,116,124,125;,
 4;116,118,126,124;,
 4;118,119,127,126;,
 4;119,120,128,127;,
 4;120,121,129,128;,
 4;121,122,130,129;,
 4;122,123,131,130;,
 4;123,117,125,131;,
 4;26,24,30,28;,
 4;24,21,32,30;,
 4;21,20,34,32;,
 4;53,52,44,45;,
 4;52,54,46,44;,
 4;54,55,47,46;,
 4;55,56,48,47;,
 4;56,57,49,48;,
 4;57,58,50,49;,
 4;58,59,51,50;,
 4;59,53,45,51;,
 4;127,128,129,130;,
 4;130,131,126,127;,
 4;131,125,124,126;,
 3;132,133,134;,
 3;135,136,133;,
 3;137,138,136;,
 3;139,140,138;,
 3;141,142,140;,
 3;143,144,142;,
 3;145,146,144;,
 4;134,133,147,148;,
 4;133,136,149,147;,
 4;136,138,150,149;,
 4;138,140,151,150;,
 4;140,142,152,151;,
 4;142,144,153,152;,
 4;144,146,154,153;,
 4;148,147,155,156;,
 4;147,149,157,155;,
 4;149,150,158,157;,
 4;150,151,159,158;,
 4;151,152,160,159;,
 4;152,153,161,160;,
 4;153,154,162,161;,
 4;156,155,163,164;,
 4;155,157,165,163;,
 4;157,158,166,165;,
 4;158,159,167,166;,
 4;159,160,168,167;,
 4;160,161,169,168;,
 4;161,162,170,169;,
 4;164,163,171,172;,
 4;163,165,173,171;,
 4;165,166,174,173;,
 4;166,167,175,174;,
 4;167,168,176,175;,
 4;168,169,177,176;,
 4;169,170,178,177;,
 4;172,171,179,180;,
 4;171,173,181,179;,
 4;173,174,182,181;,
 4;174,175,183,182;,
 4;175,176,184,183;,
 4;176,177,185,184;,
 4;177,178,186,185;,
 3;180,179,187;,
 3;179,181,188;,
 3;181,182,189;,
 3;182,183,190;,
 3;183,184,191;,
 3;184,185,192;,
 3;185,186,193;,
 4;194,195,196,197;,
 4;195,198,199,196;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;197,196,204,205;,
 4;196,199,206,204;,
 4;199,201,207,206;,
 4;201,203,208,207;,
 4;205,204,209,210;,
 4;204,206,211,209;,
 4;206,207,212,211;,
 4;207,208,213,212;,
 4;214,215,216,217;,
 4;217,216,218,219;,
 4;219,218,220,221;,
 4;222,223,224,225;,
 4;223,226,227,224;,
 4;226,228,229,227;,
 4;228,230,231,229;,
 4;225,224,232,233;,
 4;224,227,234,232;,
 4;227,229,235,234;,
 4;229,231,236,235;,
 4;233,232,237,238;,
 4;232,234,239,237;,
 4;234,235,240,239;,
 4;235,236,241,240;,
 4;242,243,244,245;,
 4;245,244,246,247;,
 4;247,246,248,249;,
 4;242,250,251,252;,
 4;250,226,253,251;,
 4;226,254,255,253;,
 4;254,215,256,255;,
 4;257,258,259,249;,
 4;258,260,239,259;,
 4;260,261,262,239;,
 4;261,263,220,262;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;276,269,280,281;,
 4;282,283,270,279;;
 
 MeshMaterialList {
  4;
  217;
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.332800;1.000000;;
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
  217;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.875552;-0.483124;,
  0.257539;0.930926;-0.258940;,
  0.367176;0.930148;-0.002316;,
  0.348120;0.870655;0.347522;,
  -0.001469;0.872006;0.489493;,
  -0.260049;0.931030;0.256042;,
  -0.363478;0.931603;-0.000762;,
  -0.341619;0.875553;-0.341620;,
  0.000000;0.504524;-0.863398;,
  0.611537;0.502193;-0.611412;,
  0.867007;0.498295;-0.000020;,
  0.613885;0.496275;0.613886;,
  -0.000020;0.498295;0.867007;,
  -0.611412;0.502194;0.611537;,
  -0.863398;0.504523;-0.000000;,
  -0.610514;0.504523;-0.610515;,
  -0.000000;0.323141;-0.946351;,
  0.669170;0.323143;-0.669171;,
  0.946350;0.323144;-0.000000;,
  0.669170;0.323142;0.669171;,
  -0.000000;0.323142;0.946351;,
  -0.669171;0.323142;0.669171;,
  -0.946351;0.323141;-0.000000;,
  -0.669171;0.323140;-0.669172;,
  -0.000000;0.287820;-0.957685;,
  0.677185;0.287818;-0.677186;,
  0.957686;0.287814;0.000000;,
  0.677186;0.287814;0.677187;,
  -0.000000;0.287813;0.957687;,
  -0.677187;0.287813;0.677187;,
  -0.957686;0.287814;-0.000000;,
  -0.677185;0.287818;-0.677186;,
  -0.000000;0.179455;-0.983766;,
  0.695628;0.179452;-0.695628;,
  0.983767;0.179449;0.000000;,
  0.695628;0.179449;0.695629;,
  -0.000000;0.179448;0.983767;,
  -0.695629;0.179448;0.695628;,
  -0.983767;0.179449;0.000000;,
  -0.695628;0.179453;-0.695628;,
  -0.000000;0.100702;-0.994917;,
  0.703512;0.100703;-0.703512;,
  0.994917;0.100703;0.000000;,
  0.703512;0.100703;0.703512;,
  -0.000001;0.100703;0.994917;,
  -0.703513;0.100703;0.703512;,
  -0.994917;0.100703;0.000000;,
  -0.703512;0.100703;-0.703513;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000001;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000001;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  -1.000000;0.000000;0.000000;,
  -0.000000;-0.084136;-0.996454;,
  0.704599;-0.084136;-0.704600;,
  0.996446;-0.084238;-0.000032;,
  0.704587;-0.084347;0.704587;,
  -0.000033;-0.084241;0.996445;,
  -0.704600;-0.084136;0.704599;,
  -0.996454;-0.084136;0.000000;,
  -0.704599;-0.084136;-0.704600;,
  0.996446;-0.084238;-0.000032;,
  0.704587;-0.084347;0.704587;,
  -0.000033;-0.084241;0.996445;,
  -0.704600;-0.084136;0.704599;,
  -0.996454;-0.084136;-0.000000;,
  -0.704599;-0.084136;-0.704600;,
  -0.000000;-0.118584;-0.992944;,
  0.702118;-0.118584;-0.702117;,
  0.992944;-0.118583;0.000000;,
  0.702117;-0.118583;0.702118;,
  -0.000000;-0.118583;0.992944;,
  -0.702118;-0.118583;0.702117;,
  -0.992944;-0.118583;-0.000000;,
  -0.702117;-0.118584;-0.702118;,
  -0.000000;-0.306615;-0.951834;,
  0.673048;-0.306615;-0.673048;,
  0.951834;-0.306614;-0.000000;,
  0.673048;-0.306614;0.673048;,
  -0.000000;-0.306613;0.951834;,
  -0.673048;-0.306614;0.673048;,
  -0.951834;-0.306615;-0.000000;,
  -0.673048;-0.306615;-0.673048;,
  0.000000;-0.565261;-0.824912;,
  0.583301;-0.565261;-0.583301;,
  0.824912;-0.565262;0.000000;,
  0.583300;-0.565262;0.583301;,
  -0.000000;-0.565261;0.824912;,
  -0.583301;-0.565262;0.583300;,
  -0.824912;-0.565261;-0.000000;,
  -0.583301;-0.565261;-0.583301;,
  0.000000;-0.874557;-0.484923;,
  0.342892;-0.874557;-0.342892;,
  0.364175;-0.931331;0.000000;,
  0.257510;-0.931331;0.257510;,
  0.000000;-0.874558;0.484922;,
  -0.342892;-0.874557;0.342892;,
  -0.364176;-0.931330;-0.000000;,
  -0.257511;-0.931330;-0.257511;,
  0.000000;1.000000;-0.000001;,
  0.215014;0.902815;-0.372417;,
  0.425228;0.902814;-0.064091;,
  0.315238;0.902813;0.292494;,
  -0.032132;0.902815;0.428828;,
  -0.355307;0.902815;0.242242;,
  -0.410925;0.902814;-0.126758;,
  -0.157110;0.902814;-0.400304;,
  0.389377;0.627327;-0.674423;,
  0.770059;0.627325;-0.116066;,
  0.570872;0.627324;0.529689;,
  -0.058194;0.627324;0.776581;,
  -0.643440;0.627326;0.438689;,
  -0.744157;0.627326;-0.229546;,
  -0.284512;0.627327;-0.724923;,
  0.487233;0.224529;-0.843914;,
  0.963584;0.224528;-0.145235;,
  0.714335;0.224526;0.662808;,
  -0.072820;0.224526;0.971743;,
  -0.805144;0.224526;0.548937;,
  -0.931175;0.224527;-0.287229;,
  -0.356014;0.224530;-0.907105;,
  0.487233;-0.224529;-0.843914;,
  0.963584;-0.224528;-0.145235;,
  0.714335;-0.224526;0.662808;,
  -0.072820;-0.224526;0.971743;,
  -0.805144;-0.224526;0.548937;,
  -0.931175;-0.224527;-0.287229;,
  -0.356014;-0.224530;-0.907105;,
  0.389377;-0.627327;-0.674423;,
  0.770060;-0.627325;-0.116066;,
  0.570872;-0.627324;0.529689;,
  -0.058194;-0.627324;0.776581;,
  -0.643440;-0.627326;0.438689;,
  -0.744157;-0.627326;-0.229546;,
  -0.284512;-0.627327;-0.724923;,
  0.215013;-0.902816;-0.372415;,
  0.425226;-0.902815;-0.064091;,
  0.315237;-0.902814;0.292493;,
  -0.032132;-0.902815;0.428826;,
  -0.355306;-0.902816;0.242241;,
  -0.410923;-0.902815;-0.126757;,
  -0.157109;-0.902815;-0.400303;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-0.158719;0.987324;,
  -0.698144;-0.158712;0.698144;,
  -0.987326;-0.158705;-0.000000;,
  -0.698145;-0.158705;-0.698145;,
  0.000000;-0.158705;-0.987326;,
  0.698145;-0.158703;-0.698145;,
  0.987326;-0.158705;0.000000;,
  0.698144;-0.158713;0.698144;,
  0.000000;0.999912;-0.013266;,
  -0.044223;0.168355;-0.984734;,
  -0.025264;0.180232;-0.983300;,
  0.000000;0.191930;-0.981409;,
  0.024808;0.178743;-0.983583;,
  -0.084511;-0.127201;-0.988270;,
  -0.048505;-0.103319;-0.993465;,
  0.000000;-0.079248;-0.996855;,
  0.047610;-0.106340;-0.993189;,
  0.000000;0.999912;-0.013266;,
  0.043324;0.165350;-0.985283;,
  0.082719;-0.133227;-0.987628;,
  0.979503;-0.059159;-0.192544;,
  0.000000;-0.999458;0.032928;,
  0.994863;-0.029732;-0.096769;,
  0.000000;-0.873302;0.487179;,
  0.982636;-0.019220;0.184547;,
  -0.054903;-0.238496;0.969590;,
  -0.000000;-0.250655;0.968077;,
  0.025763;-0.239155;0.970639;,
  0.919955;-0.167570;0.354405;,
  -0.103391;0.106447;0.988928;,
  -0.000000;0.079247;0.996855;,
  0.048504;0.103318;0.993465;,
  0.000000;-0.999458;0.032928;,
  0.000000;-0.873302;0.487179;,
  0.045133;-0.227428;0.972748;,
  0.084509;0.127199;0.988271;,
  0.000000;0.448929;-0.893567;,
  0.000000;0.448929;-0.893567;,
  0.000000;0.448929;-0.893567;,
  0.000000;0.448929;-0.893567;,
  0.000000;-0.873302;0.487179;,
  -0.103796;-0.225562;0.968684;,
  -0.193436;0.132686;0.972099;,
  -0.972928;-0.067873;-0.220916;,
  -0.993209;-0.034169;-0.111213;,
  -0.999796;0.020204;0.000000;,
  -0.978149;-0.207905;0.000000;,
  0.000000;-0.006886;0.999976;,
  0.000000;-0.006886;0.999976;,
  0.000000;-0.006886;0.999976;,
  -0.657436;-0.753510;0.000000;,
  0.000001;-1.000000;-0.000000;,
  0.684819;-0.702868;0.192351;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  217;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,6,14,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,14,22,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,22,30,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,30,38,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,38,46,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,46,54,61;,
  4;54,55,55,62;,
  4;55,56,63,55;,
  4;56,57,64,63;,
  4;57,58,65,64;,
  4;58,59,66,65;,
  4;59,60,67,66;,
  4;60,61,61,67;,
  4;61,54,62,61;,
  4;62,55,69,68;,
  4;55,63,70,69;,
  4;63,64,71,70;,
  4;64,65,72,71;,
  4;65,66,73,72;,
  4;66,67,74,73;,
  4;67,61,75,74;,
  4;61,62,68,75;,
  4;68,69,69,68;,
  4;69,70,76,69;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,73,79,78;,
  4;73,74,80,79;,
  4;74,75,81,80;,
  4;75,68,68,81;,
  4;68,69,83,82;,
  4;69,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,68,82,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,82,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,98,106,113;,
  4;9,8,11,10;,
  4;8,7,12,11;,
  4;7,6,13,12;,
  4;158,159,159,158;,
  4;159,160,160,159;,
  4;160,161,161,160;,
  4;161,162,162,161;,
  4;162,163,163,162;,
  4;163,164,164,163;,
  4;164,165,165,164;,
  4;165,158,158,165;,
  4;109,110,111,112;,
  4;112,113,108,109;,
  4;113,106,107,108;,
  3;114,116,115;,
  3;114,117,116;,
  3;114,118,117;,
  3;114,119,118;,
  3;114,120,119;,
  3;114,121,120;,
  3;114,115,121;,
  4;115,116,123,122;,
  4;116,117,124,123;,
  4;117,118,125,124;,
  4;118,119,126,125;,
  4;119,120,127,126;,
  4;120,121,128,127;,
  4;121,115,122,128;,
  4;122,123,130,129;,
  4;123,124,131,130;,
  4;124,125,132,131;,
  4;125,126,133,132;,
  4;126,127,134,133;,
  4;127,128,135,134;,
  4;128,122,129,135;,
  4;129,130,137,136;,
  4;130,131,138,137;,
  4;131,132,139,138;,
  4;132,133,140,139;,
  4;133,134,141,140;,
  4;134,135,142,141;,
  4;135,129,136,142;,
  4;136,137,144,143;,
  4;137,138,145,144;,
  4;138,139,146,145;,
  4;139,140,147,146;,
  4;140,141,148,147;,
  4;141,142,149,148;,
  4;142,136,143,149;,
  4;143,144,151,150;,
  4;144,145,152,151;,
  4;145,146,153,152;,
  4;146,147,154,153;,
  4;147,148,155,154;,
  4;148,149,156,155;,
  4;149,143,150,156;,
  3;150,151,157;,
  3;151,152,157;,
  3;152,153,157;,
  3;153,154,157;,
  3;154,155,157;,
  3;155,156,157;,
  3;156,150,157;,
  4;166,166,166,166;,
  4;166,166,166,166;,
  4;166,166,166,166;,
  4;166,175,175,166;,
  4;194,195,168,167;,
  4;195,195,169,168;,
  4;195,196,170,169;,
  4;196,197,176,170;,
  4;167,168,172,171;,
  4;168,169,173,172;,
  4;169,170,174,173;,
  4;170,176,177,174;,
  4;178,178,180,180;,
  4;180,180,182,182;,
  4;182,182,186,186;,
  4;179,179,181,198;,
  4;179,179,181,181;,
  4;179,179,181,181;,
  4;179,190,191,181;,
  4;198,181,183,199;,
  4;181,181,184,183;,
  4;181,181,185,184;,
  4;181,191,192,185;,
  4;199,183,187,200;,
  4;183,184,188,187;,
  4;184,185,189,188;,
  4;185,192,193,189;,
  4;201,201,202,202;,
  4;202,202,203,203;,
  4;203,203,204,204;,
  4;205,206,206,205;,
  4;206,206,206,206;,
  4;206,206,206,206;,
  4;206,207,207,206;,
  4;204,208,208,204;,
  4;208,209,209,208;,
  4;209,210,210,209;,
  4;210,186,186,210;,
  4;211,211,211,211;,
  4;212,212,212,212;,
  4;213,213,213,213;,
  4;214,214,214,214;,
  4;215,215,215,215;,
  4;216,216,216,216;;
 }
 MeshTextureCoords {
  284;
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
  0.071430;0.000000;,
  0.142860;0.142860;,
  0.000000;0.142860;,
  0.214290;0.000000;,
  0.285710;0.142860;,
  0.357140;0.000000;,
  0.428570;0.142860;,
  0.500000;0.000000;,
  0.571430;0.142860;,
  0.642860;0.000000;,
  0.714290;0.142860;,
  0.785710;0.000000;,
  0.857140;0.142860;,
  0.928570;0.000000;,
  1.000000;0.142860;,
  0.142860;0.285710;,
  0.000000;0.285710;,
  0.285710;0.285710;,
  0.428570;0.285710;,
  0.571430;0.285710;,
  0.714290;0.285710;,
  0.857140;0.285710;,
  1.000000;0.285710;,
  0.142860;0.428570;,
  0.000000;0.428570;,
  0.285710;0.428570;,
  0.428570;0.428570;,
  0.571430;0.428570;,
  0.714290;0.428570;,
  0.857140;0.428570;,
  1.000000;0.428570;,
  0.142860;0.571430;,
  0.000000;0.571430;,
  0.285710;0.571430;,
  0.428570;0.571430;,
  0.571430;0.571430;,
  0.714290;0.571430;,
  0.857140;0.571430;,
  1.000000;0.571430;,
  0.142860;0.714290;,
  0.000000;0.714290;,
  0.285710;0.714290;,
  0.428570;0.714290;,
  0.571430;0.714290;,
  0.714290;0.714290;,
  0.857140;0.714290;,
  1.000000;0.714290;,
  0.142860;0.857140;,
  0.000000;0.857140;,
  0.285710;0.857140;,
  0.428570;0.857140;,
  0.571430;0.857140;,
  0.714290;0.857140;,
  0.857140;0.857140;,
  1.000000;0.857140;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.000000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.250000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.750000;0.666670;,
  1.000000;0.666670;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.000000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.250000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.750000;0.666670;,
  1.000000;0.666670;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
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
