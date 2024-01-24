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
 223;
 67.26976;46.39658;0.38210;,
 66.16384;46.76062;6.50732;,
 61.59640;24.35098;8.13266;,
 61.74130;46.21756;-15.32208;,
 52.17638;6.37422;2.93110;,
 56.71994;13.65996;7.99218;,
 50.71706;8.81138;10.21210;,
 42.95418;3.97802;-20.52438;,
 55.76030;41.81632;-24.51120;,
 49.13568;35.96538;-36.30386;,
 19.95914;2.44410;20.16126;,
 21.84818;7.63546;26.51534;,
 31.34124;15.96216;-33.97962;,
 23.98280;46.76870;-55.00392;,
 15.87490;44.53866;-57.32022;,
 10.54782;2.43448;28.74384;,
 12.02214;5.52166;31.64316;,
 -0.65324;16.66798;43.16700;,
 28.31884;-0.57920;-6.17060;,
 45.48422;2.85234;-11.14210;,
 32.50838;-3.58034;-20.29594;,
 -30.01340;9.97144;28.25394;,
 -18.36244;25.46886;46.95168;,
 -27.55560;28.74338;49.25842;,
 -44.78562;21.47986;39.55300;,
 -35.58326;26.81952;46.37826;,
 -13.61518;-3.86084;17.74024;,
 -52.72376;23.75358;23.81648;,
 -57.78278;28.94154;32.73682;,
 -70.59600;33.83552;16.53148;,
 -41.82580;9.48820;-2.13540;,
 -62.22398;24.31802;0.03418;,
 -77.89058;35.14378;-5.18392;,
 -76.58258;32.18452;-13.79720;,
 -57.77302;16.14580;-19.78408;,
 -58.78030;28.63904;-26.37234;,
 -68.88636;37.87062;-23.28234;,
 -51.30710;48.02840;-41.47438;,
 -30.47850;44.12934;-56.96384;,
 -34.88416;19.63480;-40.02942;,
 -10.24410;46.35194;-59.09410;,
 -38.27638;0.01778;-25.38548;,
 -21.71594;-9.75654;-17.83156;,
 -31.93680;-3.01062;-24.04684;,
 8.03382;37.13180;-52.57076;,
 2.78814;47.02228;-60.09856;,
 -3.49246;7.20790;-31.99264;,
 24.34886;4.46028;-29.83320;,
 23.61292;-3.99954;-22.95668;,
 -9.80362;-9.89584;-18.22622;,
 -14.39354;-8.73844;-4.36218;,
 56.71994;13.65996;7.99218;,
 21.84818;7.63546;26.51534;,
 50.71706;8.81138;10.21210;,
 61.59640;24.35098;8.13266;,
 12.02214;5.52166;31.64316;,
 -0.65324;16.66798;43.16700;,
 36.62366;27.44260;25.14844;,
 14.09368;34.91480;40.09638;,
 49.83394;43.02726;21.48010;,
 62.48946;40.38460;12.79782;,
 66.16384;46.76062;6.50732;,
 -3.35402;42.61232;41.91408;,
 -18.36244;25.46886;46.95168;,
 25.35744;49.59406;37.65680;,
 -22.05390;39.74044;47.55682;,
 -27.55560;28.74338;49.25842;,
 19.89798;60.06616;35.58422;,
 41.60940;61.88706;18.65136;,
 65.00216;59.19028;-0.07632;,
 67.26976;46.39658;0.38210;,
 65.79442;50.00062;-6.92436;,
 61.74130;46.21756;-15.32208;,
 60.12022;65.26984;0.85324;,
 45.63182;64.64800;-18.91566;,
 35.14226;75.49808;15.12692;,
 43.63278;73.66492;-13.63890;,
 49.04272;48.05588;-25.51386;,
 55.76030;41.81632;-24.51120;,
 49.13568;35.96538;-36.30386;,
 23.98280;46.76870;-55.00392;,
 27.78770;61.99670;-38.09500;,
 31.38668;73.00456;-27.53214;,
 15.87490;44.53866;-57.32022;,
 2.78814;47.02228;-60.09856;,
 23.37060;80.66696;-18.81816;,
 12.87332;66.74288;-34.94018;,
 7.00340;86.68220;-16.39406;,
 17.73800;81.19888;5.41120;,
 25.69936;79.13550;20.94102;,
 -12.30660;94.62158;21.78476;,
 -32.37220;81.57382;-30.84112;,
 18.12048;66.98856;33.60516;,
 -21.96258;98.02778;-9.87820;,
 -1.92688;75.94740;38.38466;,
 14.07458;75.95822;28.45650;,
 -0.83574;89.59364;27.11858;,
 -4.33162;85.56184;32.23054;,
 -16.71616;94.88588;22.05510;,
 -19.00754;72.75438;31.39954;,
 -22.34488;98.03278;14.48406;,
 -23.44218;96.00288;17.46606;,
 -36.28848;80.78924;19.50212;,
 -31.86038;66.62072;29.64222;,
 -58.11112;68.63556;14.51452;,
 -46.89462;37.23076;36.57734;,
 -49.53104;58.01076;24.85522;,
 -56.08286;30.11936;34.92428;,
 -35.58326;26.81952;46.37826;,
 -44.78562;21.47986;39.55300;,
 -57.78278;28.94154;32.73682;,
 -65.63590;39.05836;24.79302;,
 -70.59600;33.83552;16.53148;,
 -61.65834;57.75592;18.51766;,
 -74.05246;44.72132;-2.58862;,
 -77.89058;35.14378;-5.18392;,
 -76.58258;32.18452;-13.79720;,
 -68.88636;37.87062;-23.28234;,
 -64.86174;61.36204;3.06294;,
 -48.45070;76.84924;-14.29296;,
 -62.12748;52.09118;-14.13432;,
 -34.80436;87.74254;-24.30872;,
 -52.87024;59.64028;-27.11500;,
 -46.18936;61.82862;-36.25292;,
 -51.30710;48.02840;-41.47438;,
 -18.90270;54.09360;-56.34534;,
 -30.47850;44.12934;-56.96384;,
 -16.01524;50.18174;-59.33806;,
 -10.24410;46.35194;-59.09410;,
 67.24300;49.38618;-2.90924;,
 64.57714;42.42838;10.32374;,
 60.34510;44.92924;-17.01198;,
 54.03502;8.29614;7.07778;,
 10.61862;2.63110;28.89088;,
 28.61478;-4.21858;-22.71578;,
 43.87604;1.42526;-11.83544;,
 14.82644;44.24096;-57.45180;,
 -18.68110;-10.91186;-16.88130;,
 -2.01554;47.66268;-60.09872;,
 -30.72408;44.02686;-56.70550;,
 -37.28400;-0.48946;-25.68416;,
 -49.57150;20.51336;18.69880;,
 -1.89180;18.22552;44.22386;,
 -27.92304;29.05026;49.33910;,
 -56.83746;29.07160;34.48538;,
 -67.84840;34.50900;23.50444;,
 -61.80044;19.59924;-18.49038;,
 -78.31578;36.47790;-5.63504;,
 -76.46810;32.13724;-14.08388;,
 -52.22004;48.99738;-40.78562;,
 -66.76952;38.91830;-25.17754;,
 -66.76952;38.91830;-25.17754;,
 -76.46810;32.13724;-14.08388;,
 -78.31578;36.47790;-5.63504;,
 -63.88170;63.16948;2.65584;,
 -52.22004;48.99738;-40.78562;,
 -58.99482;67.82846;14.61860;,
 -67.84840;34.50900;23.50444;,
 -34.61624;87.61082;-24.94614;,
 -49.82980;40.79652;33.41256;,
 -56.83746;29.07160;34.48538;,
 -27.92304;29.05026;49.33910;,
 -1.89180;18.22552;44.22386;,
 -35.09416;79.69506;21.11816;,
 -21.75582;97.32292;18.02274;,
 -4.30374;91.11244;27.33456;,
 17.37096;64.79784;34.98038;,
 14.58962;83.68672;-17.83410;,
 28.63154;77.87810;19.74330;,
 25.99754;48.44234;37.58430;,
 10.61862;2.63110;28.89088;,
 54.03502;8.29614;7.07778;,
 48.45494;43.01428;22.58982;,
 64.57714;42.42838;10.32374;,
 63.03976;62.87812;0.57810;,
 67.24300;49.38618;-2.90924;,
 60.34510;44.92924;-17.01198;,
 42.60008;73.76528;-15.13570;,
 28.28058;62.57740;-36.97628;,
 14.82644;44.24096;-57.45180;,
 -2.01554;47.66268;-60.09872;,
 -17.29516;50.91224;-59.18660;,
 -30.72408;44.02686;-56.70550;,
 68.83188;55.22460;-0.88260;,
 63.70712;39.85518;12.06634;,
 55.95592;9.99552;7.71292;,
 38.30146;-1.74596;-21.05328;,
 11.76976;3.67616;30.19532;,
 19.66248;45.62988;-57.59052;,
 -22.97930;-10.67870;-18.89578;,
 -23.55622;48.33860;-60.73934;,
 -49.58748;25.83876;40.62214;,
 -25.39090;28.17824;49.67256;,
 -78.86316;33.19908;-11.38544;,
 63.70712;39.85518;12.06634;,
 11.76976;3.67616;30.19532;,
 55.95592;9.99552;7.71292;,
 26.15538;51.63974;37.19588;,
 -25.39090;28.17824;49.67256;,
 28.20390;77.66326;20.13176;,
 68.83188;55.22460;-0.88260;,
 19.66248;45.62988;-57.59052;,
 -18.19080;97.21826;21.22438;,
 35.01028;76.22306;-21.30682;,
 -23.55622;48.33860;-60.73934;,
 -27.55356;94.90382;-18.35096;,
 -60.89408;67.78432;14.01630;,
 -78.86316;33.19908;-11.38544;,
 -49.58748;25.83876;40.62214;,
 37.23910;39.88938;-51.10770;,
 70.69156;53.01110;2.90568;,
 50.57948;-0.13818;-10.97594;,
 1.24468;0.84412;32.13560;,
 -31.71046;50.00888;-59.25358;,
 -46.50336;26.69658;47.91526;,
 70.69156;53.01110;2.90568;,
 1.24468;0.84412;32.13560;,
 50.57948;-0.13818;-10.97594;,
 -46.50336;26.69658;47.91526;,
 -8.24374;92.35930;32.83656;,
 37.23910;39.88938;-51.10770;,
 -31.71046;50.00888;-59.25358;,
 -33.77116;102.82708;3.71054;;
 
 362;
 3;0,1,2;,
 3;0,2,3;,
 3;4,3,2;,
 3;5,4,2;,
 3;4,5,6;,
 3;7,3,4;,
 3;8,3,7;,
 3;9,8,7;,
 3;10,4,6;,
 3;10,6,11;,
 3;12,9,7;,
 3;9,12,13;,
 3;13,12,14;,
 3;15,10,11;,
 3;16,15,11;,
 3;17,15,16;,
 3;18,4,10;,
 3;15,18,10;,
 3;4,19,7;,
 3;19,4,18;,
 3;19,20,7;,
 3;18,20,19;,
 3;20,12,7;,
 3;15,17,21;,
 3;21,17,22;,
 3;23,21,22;,
 3;24,23,25;,
 3;21,23,24;,
 3;21,26,15;,
 3;26,18,15;,
 3;27,21,24;,
 3;24,28,27;,
 3;29,27,28;,
 3;21,30,26;,
 3;27,30,21;,
 3;31,27,29;,
 3;31,29,32;,
 3;33,31,32;,
 3;34,27,31;,
 3;31,33,34;,
 3;30,27,34;,
 3;34,33,35;,
 3;33,36,35;,
 3;35,36,37;,
 3;38,35,37;,
 3;39,35,38;,
 3;35,39,34;,
 3;40,39,38;,
 3;34,41,30;,
 3;41,34,39;,
 3;30,41,42;,
 3;30,42,26;,
 3;41,39,43;,
 3;41,43,42;,
 3;40,44,39;,
 3;44,40,45;,
 3;14,44,45;,
 3;46,43,39;,
 3;44,46,39;,
 3;43,46,42;,
 3;47,44,14;,
 3;47,46,44;,
 3;12,47,14;,
 3;47,12,20;,
 3;48,46,47;,
 3;48,47,20;,
 3;48,49,46;,
 3;48,20,49;,
 3;42,46,49;,
 3;20,18,49;,
 3;42,49,50;,
 3;49,18,50;,
 3;26,42,50;,
 3;50,18,26;,
 3;51,52,53;,
 3;51,54,52;,
 3;55,52,56;,
 3;57,52,54;,
 3;52,58,56;,
 3;57,58,52;,
 3;59,57,54;,
 3;58,57,59;,
 3;59,54,60;,
 3;60,54,61;,
 3;61,59,60;,
 3;58,62,56;,
 3;56,62,63;,
 3;64,58,59;,
 3;62,65,63;,
 3;63,65,66;,
 3;67,62,58;,
 3;58,64,67;,
 3;64,59,68;,
 3;64,68,67;,
 3;69,59,61;,
 3;69,68,59;,
 3;69,61,70;,
 3;70,71,69;,
 3;70,72,71;,
 3;72,69,71;,
 3;73,68,69;,
 3;69,72,74;,
 3;69,74,73;,
 3;73,75,68;,
 3;67,68,75;,
 3;74,76,73;,
 3;73,76,75;,
 3;72,77,74;,
 3;78,77,72;,
 3;79,77,78;,
 3;77,79,80;,
 3;74,77,81;,
 3;81,77,80;,
 3;76,74,82;,
 3;82,74,81;,
 3;83,84,80;,
 3;84,81,80;,
 3;76,82,85;,
 3;76,85,75;,
 3;81,86,82;,
 3;86,81,84;,
 3;85,82,87;,
 3;82,86,87;,
 3;85,88,75;,
 3;85,87,88;,
 3;75,88,89;,
 3;89,67,75;,
 3;90,88,87;,
 3;89,88,90;,
 3;87,86,91;,
 3;67,89,92;,
 3;87,91,93;,
 3;90,87,93;,
 3;92,94,67;,
 3;94,62,67;,
 3;92,89,95;,
 3;92,95,94;,
 3;89,94,95;,
 3;94,65,62;,
 3;89,90,96;,
 3;89,97,94;,
 3;96,97,89;,
 3;96,98,97;,
 3;97,98,94;,
 3;98,96,90;,
 3;65,94,99;,
 3;98,99,94;,
 3;98,90,100;,
 3;90,93,100;,
 3;100,101,98;,
 3;93,101,100;,
 3;102,99,98;,
 3;102,98,101;,
 3;103,99,102;,
 3;99,103,65;,
 3;104,102,101;,
 3;103,102,104;,
 3;93,104,101;,
 3;103,105,65;,
 3;105,103,106;,
 3;104,106,103;,
 3;65,105,107;,
 3;105,106,107;,
 3;66,65,107;,
 3;108,66,107;,
 3;107,109,108;,
 3;109,107,110;,
 3;110,107,111;,
 3;107,106,111;,
 3;111,112,110;,
 3;111,106,113;,
 3;113,112,111;,
 3;104,113,106;,
 3;112,113,114;,
 3;112,114,115;,
 3;114,116,115;,
 3;117,116,114;,
 3;113,104,118;,
 3;114,113,118;,
 3;104,119,118;,
 3;119,104,93;,
 3;118,120,114;,
 3;118,119,120;,
 3;117,114,120;,
 3;121,119,93;,
 3;93,91,121;,
 3;122,120,119;,
 3;122,119,121;,
 3;117,120,122;,
 3;123,122,121;,
 3;123,117,122;,
 3;123,121,91;,
 3;124,117,123;,
 3;91,125,123;,
 3;123,125,124;,
 3;86,125,91;,
 3;124,125,126;,
 3;125,86,84;,
 3;125,127,126;,
 3;127,125,84;,
 3;127,128,126;,
 3;128,127,84;,
 3;129,130,2;,
 3;129,2,131;,
 3;132,131,2;,
 3;7,131,132;,
 3;9,131,7;,
 3;133,132,11;,
 3;134,9,7;,
 3;9,134,13;,
 3;132,135,7;,
 3;135,132,133;,
 3;135,134,7;,
 3;13,134,136;,
 3;26,135,133;,
 3;134,135,137;,
 3;137,135,26;,
 3;134,46,136;,
 3;134,137,46;,
 3;138,136,139;,
 3;136,46,139;,
 3;140,46,137;,
 3;46,140,139;,
 3;141,137,26;,
 3;141,140,137;,
 3;21,26,133;,
 3;21,141,26;,
 3;133,142,21;,
 3;21,142,143;,
 3;21,143,24;,
 3;141,21,24;,
 3;24,144,141;,
 3;145,141,144;,
 3;146,141,145;,
 3;146,140,141;,
 3;140,146,139;,
 3;146,145,147;,
 3;148,146,147;,
 3;148,139,146;,
 3;139,148,149;,
 3;148,150,149;,
 3;151,152,153;,
 3;154,151,153;,
 3;155,151,154;,
 3;153,156,154;,
 3;157,156,153;,
 3;155,154,158;,
 3;157,159,156;,
 3;160,159,157;,
 3;154,156,93;,
 3;158,154,93;,
 3;160,109,161;,
 3;161,65,160;,
 3;65,159,160;,
 3;162,65,161;,
 3;163,159,65;,
 3;156,159,163;,
 3;65,94,163;,
 3;94,65,162;,
 3;156,163,164;,
 3;164,163,94;,
 3;93,156,164;,
 3;165,164,94;,
 3;165,93,164;,
 3;94,162,166;,
 3;165,167,93;,
 3;167,158,93;,
 3;168,165,94;,
 3;168,94,166;,
 3;165,88,167;,
 3;168,88,165;,
 3;167,88,168;,
 3;166,162,169;,
 3;169,168,166;,
 3;170,52,162;,
 3;52,169,162;,
 3;171,54,52;,
 3;172,169,52;,
 3;172,52,54;,
 3;169,172,168;,
 3;172,54,173;,
 3;174,172,173;,
 3;174,168,172;,
 3;174,173,175;,
 3;176,174,175;,
 3;174,177,168;,
 3;174,176,177;,
 3;177,167,168;,
 3;176,79,80;,
 3;177,82,167;,
 3;177,176,178;,
 3;82,177,178;,
 3;82,178,167;,
 3;178,176,80;,
 3;167,178,158;,
 3;179,180,80;,
 3;180,178,80;,
 3;178,181,158;,
 3;181,178,180;,
 3;158,181,155;,
 3;181,180,182;,
 3;155,181,182;,
 3;183,184,185;,
 3;186,183,185;,
 3;9,183,186;,
 3;186,185,187;,
 3;9,186,188;,
 3;26,186,187;,
 3;186,189,188;,
 3;189,186,26;,
 3;188,189,190;,
 3;191,26,187;,
 3;191,189,26;,
 3;187,192,191;,
 3;189,193,190;,
 3;193,189,191;,
 3;190,193,149;,
 3;193,191,145;,
 3;194,195,196;,
 3;194,197,195;,
 3;195,197,198;,
 3;197,194,199;,
 3;200,199,194;,
 3;94,198,197;,
 3;199,94,197;,
 3;200,79,201;,
 3;199,202,94;,
 3;203,200,201;,
 3;200,203,199;,
 3;202,199,203;,
 3;204,203,201;,
 3;203,204,205;,
 3;202,203,205;,
 3;205,204,155;,
 3;202,206,94;,
 3;205,206,202;,
 3;155,206,205;,
 3;198,94,206;,
 3;155,207,206;,
 3;206,208,198;,
 3;157,206,207;,
 3;157,208,206;,
 3;209,210,211;,
 3;211,189,209;,
 3;189,211,212;,
 3;209,189,213;,
 3;214,189,212;,
 3;189,193,213;,
 3;193,189,214;,
 3;215,216,217;,
 3;215,197,216;,
 3;216,197,218;,
 3;197,215,219;,
 3;219,218,197;,
 3;215,203,219;,
 3;203,215,220;,
 3;221,203,220;,
 3;218,219,222;,
 3;219,203,222;,
 3;203,221,222;,
 3;218,222,207;,
 3;221,207,222;;
 
 MeshMaterialList {
  3;
  362;
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
  2,
  0,
  0,
  2,
  0,
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
  2,
  2,
  2,
  2,
  2,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  2,
  0,
  0,
  0,
  0,
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
  2,
  0,
  2,
  2,
  2,
  0,
  2,
  2,
  0,
  0;;
  Material {
   0.282353;0.282353;0.282353;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.765600;0.765600;0.765600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  213;
  0.992223;-0.093474;-0.082193;,
  0.870324;0.141248;0.471789;,
  0.951517;-0.307413;-0.010664;,
  0.862561;0.026708;-0.505247;,
  0.694992;-0.718804;-0.017527;,
  0.729666;-0.436237;0.526578;,
  0.476671;-0.678223;0.559284;,
  0.732264;-0.509917;-0.451413;,
  0.824619;0.112534;-0.554383;,
  0.694211;-0.126529;-0.708563;,
  0.292821;-0.889849;0.349892;,
  0.475185;-0.417112;0.774737;,
  0.375819;-0.484178;-0.790147;,
  0.434394;0.026392;-0.900336;,
  0.211283;-0.409802;-0.887368;,
  0.144622;-0.843778;0.516840;,
  0.339432;-0.595650;0.728003;,
  0.168940;-0.408199;0.897125;,
  0.196050;-0.962107;0.189512;,
  0.516772;-0.855474;-0.033336;,
  0.344869;-0.861532;-0.372596;,
  -0.288088;-0.798706;0.528275;,
  0.109018;-0.290230;0.950727;,
  0.008861;-0.595050;0.803640;,
  -0.438765;-0.699147;0.564516;,
  -0.300978;-0.510709;0.805350;,
  -0.165687;-0.928464;0.332418;,
  -0.546708;-0.815985;0.187824;,
  -0.710240;-0.504448;0.491012;,
  -0.659137;-0.691733;0.295033;,
  -0.557929;-0.797817;0.228480;,
  -0.580238;-0.793533;0.183382;,
  -0.597305;-0.784854;0.165020;,
  -0.673173;-0.676252;-0.299201;,
  -0.655744;-0.724636;-0.211902;,
  -0.575274;-0.388713;-0.719696;,
  -0.794710;0.285362;-0.535728;,
  -0.621074;0.169999;-0.765093;,
  -0.350741;-0.235277;-0.906436;,
  -0.241022;-0.535480;-0.809425;,
  -0.042129;-0.433047;-0.900386;,
  -0.520026;-0.853809;0.024142;,
  -0.288825;-0.938288;-0.190251;,
  -0.110978;-0.690579;-0.714692;,
  0.009241;-0.579073;-0.815223;,
  0.052635;-0.323164;-0.944878;,
  -0.003270;-0.603364;-0.797459;,
  0.168654;-0.572609;-0.802294;,
  0.098151;-0.736467;-0.669315;,
  0.081402;-0.962875;-0.257382;,
  0.027203;-0.985946;0.164833;,
  0.495592;-0.269394;0.825722;,
  0.330027;-0.093311;0.939348;,
  0.571453;0.075477;0.817157;,
  0.721549;-0.016070;0.692177;,
  0.215290;0.081605;0.973135;,
  0.425392;0.196612;0.883394;,
  -0.175922;0.287797;0.941395;,
  0.384257;0.306069;0.871016;,
  0.572262;0.404432;0.713408;,
  0.878291;0.469879;0.088428;,
  0.927244;0.131316;-0.350676;,
  0.574580;0.629178;0.523442;,
  0.654287;0.464437;-0.596831;,
  0.484426;0.799825;0.354416;,
  0.532687;0.789730;-0.304255;,
  0.622643;0.475683;-0.621322;,
  0.399939;0.603473;-0.689833;,
  0.357589;0.690266;-0.629017;,
  0.325744;0.932350;-0.156892;,
  0.116479;0.717390;-0.686866;,
  0.265789;0.882530;-0.387940;,
  0.346876;0.937869;0.008842;,
  0.493587;0.669218;0.555445;,
  0.297895;0.944815;0.136320;,
  -0.051102;0.688777;-0.723170;,
  0.436809;0.473118;0.765086;,
  -0.179241;0.968421;-0.173303;,
  0.076587;0.409134;0.909254;,
  0.441054;0.429636;0.787962;,
  0.240068;0.813515;0.529679;,
  0.130433;0.621669;0.772344;,
  -0.210404;0.674884;0.707292;,
  -0.375041;0.426370;0.823136;,
  0.067922;0.953779;0.292732;,
  -0.578179;0.677261;0.455002;,
  -0.407052;0.450694;0.794470;,
  -0.389468;0.431922;0.813485;,
  -0.630110;0.614209;0.475089;,
  -0.420527;0.383365;0.822306;,
  -0.437354;0.404570;0.803147;,
  -0.530241;0.153829;0.833775;,
  -0.715176;0.174015;0.676936;,
  -0.775304;0.385540;0.500262;,
  -0.885286;0.459021;-0.074624;,
  -0.849223;0.524975;-0.056762;,
  -0.746077;0.635237;-0.199608;,
  -0.782290;0.516635;-0.348010;,
  -0.678026;0.613974;-0.404124;,
  -0.776166;0.505259;-0.377199;,
  -0.615729;0.503349;-0.606232;,
  -0.182704;0.603039;-0.776507;,
  -0.105830;0.193234;-0.975428;,
  0.993013;0.019261;-0.116423;,
  0.846297;0.064794;0.528756;,
  0.848137;0.101117;-0.520038;,
  0.769667;-0.610370;-0.187246;,
  0.166343;-0.800628;0.575608;,
  0.289609;-0.600058;-0.745692;,
  0.371519;-0.926971;0.051954;,
  0.118206;-0.436023;-0.892139;,
  -0.202084;-0.948996;0.242008;,
  0.032776;-0.213104;-0.976480;,
  -0.282206;-0.461259;-0.841190;,
  -0.199470;-0.565485;-0.800274;,
  -0.557071;-0.805873;0.200599;,
  0.181357;-0.251190;0.950796;,
  -0.208482;-0.273462;0.939017;,
  -0.601384;-0.652720;0.460754;,
  -0.584652;-0.788403;0.191319;,
  -0.588973;-0.778912;0.215423;,
  -0.606241;-0.763282;0.223324;,
  -0.577657;-0.770500;0.269523;,
  -0.680176;0.383400;-0.624792;,
  0.510186;-0.856561;-0.077549;,
  -0.775561;0.608819;-0.166864;,
  -0.699667;0.554135;0.451000;,
  -0.658180;0.636682;-0.401789;,
  -0.467880;0.380278;0.797795;,
  -0.405524;0.429208;0.807051;,
  -0.454040;0.604572;0.654477;,
  0.279532;0.857200;0.432516;,
  0.320287;0.308257;0.895764;,
  0.267743;0.912335;-0.309773;,
  0.474689;0.746408;0.466417;,
  0.459748;0.089833;0.883494;,
  0.579562;0.071941;0.811747;,
  0.690206;0.521212;0.501950;,
  0.566702;0.726995;-0.387721;,
  0.332516;0.639799;-0.692885;,
  -0.146197;0.519781;-0.841697;,
  0.905139;-0.004645;-0.425090;,
  0.698737;0.008324;0.715330;,
  0.939345;-0.299259;-0.167555;,
  0.614505;-0.476762;-0.628555;,
  0.229377;-0.666366;0.709467;,
  0.172410;-0.548795;-0.817985;,
  -0.126088;-0.595479;-0.793415;,
  -0.337861;-0.537558;-0.772581;,
  -0.409420;-0.805840;0.427782;,
  -0.099377;-0.003827;0.995043;,
  -0.618741;-0.735619;-0.275726;,
  0.408181;0.079257;0.909454;,
  0.512441;0.686162;0.516320;,
  0.118629;0.977995;0.171620;,
  0.389569;0.834515;-0.389643;,
  -0.321520;0.850983;-0.415274;,
  -0.696265;0.563457;0.444670;,
  0.388020;-0.526125;-0.756725;,
  0.822676;0.154629;-0.547078;,
  0.569514;-0.479537;-0.667606;,
  -0.117206;-0.955319;0.271346;,
  -0.253645;-0.560674;-0.788232;,
  -0.469731;-0.830550;0.299233;,
  0.221868;0.748365;0.625080;,
  -0.682120;0.449139;0.577050;,
  -0.344442;-0.522619;-0.779890;,
  0.503683;-0.274590;0.819087;,
  0.675696;0.530468;-0.511896;,
  0.507614;0.587400;-0.630308;,
  0.122842;0.719091;-0.683972;,
  -0.888088;0.459460;-0.014031;,
  -0.401997;0.373699;0.835911;,
  -0.393507;0.410557;0.822554;,
  -0.895693;0.295125;0.332618;,
  -0.930179;0.366341;0.023696;,
  -0.833085;0.452528;-0.318100;,
  0.136712;0.745135;-0.652750;,
  -0.431689;0.546071;-0.717949;,
  0.465734;-0.460684;0.755554;,
  0.166647;-0.951211;0.259664;,
  -0.000777;-0.640089;-0.768301;,
  -0.568588;-0.793224;0.217953;,
  -0.559158;-0.413140;-0.718789;,
  -0.722697;-0.086183;-0.685771;,
  -0.771182;0.503902;-0.389050;,
  -0.884537;0.461610;-0.067161;,
  -0.718442;0.348611;0.601923;,
  -0.463960;0.365031;0.807151;,
  0.345189;0.938474;0.010594;,
  0.324995;0.945472;0.021477;,
  0.153530;0.725809;-0.670544;,
  0.733930;0.416005;-0.536923;,
  0.139220;0.739041;-0.659118;,
  -0.414066;0.544812;-0.729198;,
  0.195959;-0.961772;0.191300;,
  0.409046;-0.674821;0.614246;,
  -0.307772;-0.918873;0.246878;,
  0.594756;0.689016;0.414152;,
  0.469408;0.581533;-0.664436;,
  -0.068402;0.692382;-0.718281;,
  -0.398030;0.372127;0.838506;,
  -0.860786;0.508750;-0.014856;,
  -0.457212;0.385210;0.801605;,
  0.404179;-0.778453;0.480261;,
  0.620960;-0.093247;0.778276;,
  0.473689;-0.329089;0.816896;,
  -0.313217;0.257118;0.914213;,
  0.480144;0.868265;0.124810;,
  0.451570;0.582228;-0.676088;,
  -0.160478;0.710021;-0.685651;,
  0.230619;0.912912;-0.336760;,
  -0.684216;0.547546;-0.481708;;
  362;
  3;0,1,2;,
  3;0,2,3;,
  3;4,3,2;,
  3;5,4,2;,
  3;4,5,6;,
  3;7,3,4;,
  3;8,3,7;,
  3;9,8,7;,
  3;10,4,6;,
  3;10,6,11;,
  3;12,9,7;,
  3;9,12,13;,
  3;13,12,14;,
  3;15,10,11;,
  3;16,15,11;,
  3;17,15,16;,
  3;18,4,10;,
  3;15,18,10;,
  3;4,19,7;,
  3;19,4,18;,
  3;19,20,7;,
  3;18,20,19;,
  3;20,12,7;,
  3;15,17,21;,
  3;21,17,22;,
  3;23,21,22;,
  3;24,23,25;,
  3;21,23,24;,
  3;21,26,15;,
  3;26,18,15;,
  3;27,21,24;,
  3;24,28,27;,
  3;29,27,28;,
  3;21,30,26;,
  3;27,30,21;,
  3;31,27,29;,
  3;31,29,32;,
  3;33,31,32;,
  3;34,27,31;,
  3;31,33,34;,
  3;30,27,34;,
  3;34,33,35;,
  3;33,36,35;,
  3;35,36,37;,
  3;38,35,37;,
  3;39,35,38;,
  3;35,39,34;,
  3;40,39,38;,
  3;34,41,30;,
  3;166,34,39;,
  3;30,41,42;,
  3;30,42,26;,
  3;166,39,43;,
  3;41,43,42;,
  3;40,44,39;,
  3;44,40,45;,
  3;14,44,45;,
  3;46,43,39;,
  3;44,46,39;,
  3;43,46,42;,
  3;47,44,14;,
  3;47,46,44;,
  3;12,47,14;,
  3;47,12,20;,
  3;48,46,47;,
  3;48,47,20;,
  3;48,49,46;,
  3;48,20,49;,
  3;42,46,49;,
  3;20,18,49;,
  3;42,49,50;,
  3;49,18,50;,
  3;26,42,50;,
  3;50,18,26;,
  3;5,11,6;,
  3;5,167,11;,
  3;16,11,17;,
  3;51,11,167;,
  3;11,52,17;,
  3;51,52,11;,
  3;53,51,167;,
  3;52,51,53;,
  3;53,167,54;,
  3;54,2,1;,
  3;1,53,54;,
  3;52,55,17;,
  3;17,55,22;,
  3;56,52,53;,
  3;55,57,22;,
  3;22,57,23;,
  3;58,55,52;,
  3;52,56,58;,
  3;56,53,59;,
  3;56,59,58;,
  3;60,53,1;,
  3;60,59,53;,
  3;60,1,0;,
  3;0,61,60;,
  3;0,3,61;,
  3;3,60,61;,
  3;62,59,60;,
  3;60,3,63;,
  3;60,63,168;,
  3;62,64,59;,
  3;58,59,64;,
  3;63,65,168;,
  3;62,65,64;,
  3;3,66,63;,
  3;8,66,3;,
  3;9,66,8;,
  3;66,9,169;,
  3;63,66,67;,
  3;67,66,169;,
  3;65,63,68;,
  3;68,63,67;,
  3;14,45,13;,
  3;170,67,169;,
  3;65,68,69;,
  3;65,69,64;,
  3;67,70,68;,
  3;70,67,170;,
  3;69,68,71;,
  3;68,70,71;,
  3;69,72,64;,
  3;69,71,72;,
  3;64,72,73;,
  3;73,58,64;,
  3;74,72,71;,
  3;73,72,74;,
  3;71,70,75;,
  3;58,73,76;,
  3;71,75,77;,
  3;74,71,77;,
  3;76,78,58;,
  3;78,55,58;,
  3;76,73,79;,
  3;76,79,78;,
  3;73,78,79;,
  3;78,57,55;,
  3;73,74,80;,
  3;73,81,78;,
  3;80,81,73;,
  3;80,82,81;,
  3;81,82,78;,
  3;82,80,74;,
  3;57,78,83;,
  3;82,83,78;,
  3;82,74,84;,
  3;74,77,84;,
  3;84,85,82;,
  3;171,85,171;,
  3;86,83,82;,
  3;86,82,85;,
  3;87,83,86;,
  3;83,87,57;,
  3;88,86,85;,
  3;87,86,88;,
  3;77,88,85;,
  3;87,89,57;,
  3;89,87,90;,
  3;88,90,87;,
  3;57,89,91;,
  3;89,90,91;,
  3;172,57,91;,
  3;173,172,91;,
  3;91,24,25;,
  3;24,91,28;,
  3;28,91,92;,
  3;91,90,92;,
  3;92,29,28;,
  3;92,90,93;,
  3;93,174,92;,
  3;88,93,90;,
  3;174,93,94;,
  3;174,94,175;,
  3;94,176,175;,
  3;36,176,94;,
  3;93,88,95;,
  3;94,93,95;,
  3;88,96,95;,
  3;96,88,77;,
  3;95,97,94;,
  3;95,96,97;,
  3;36,94,97;,
  3;98,96,77;,
  3;77,75,177;,
  3;99,97,96;,
  3;99,96,98;,
  3;36,97,99;,
  3;100,99,98;,
  3;100,36,99;,
  3;100,98,75;,
  3;37,36,100;,
  3;75,101,100;,
  3;100,101,37;,
  3;70,101,75;,
  3;37,101,178;,
  3;101,70,170;,
  3;101,102,38;,
  3;102,101,170;,
  3;102,40,38;,
  3;40,102,45;,
  3;103,104,2;,
  3;103,2,105;,
  3;106,105,2;,
  3;7,105,106;,
  3;9,105,7;,
  3;107,179,11;,
  3;108,9,7;,
  3;9,108,13;,
  3;106,109,7;,
  3;109,106,107;,
  3;109,108,7;,
  3;13,108,110;,
  3;26,109,107;,
  3;180,109,111;,
  3;111,109,26;,
  3;108,46,110;,
  3;108,181,46;,
  3;112,110,113;,
  3;110,46,113;,
  3;114,46,181;,
  3;46,114,113;,
  3;115,111,26;,
  3;115,182,111;,
  3;21,26,107;,
  3;21,115,26;,
  3;107,116,21;,
  3;21,116,117;,
  3;21,117,24;,
  3;115,21,24;,
  3;24,118,115;,
  3;119,115,118;,
  3;120,115,119;,
  3;120,182,115;,
  3;114,183,113;,
  3;120,119,121;,
  3;122,120,121;,
  3;184,113,183;,
  3;113,184,123;,
  3;124,124,124;,
  3;185,184,186;,
  3;125,185,186;,
  3;123,185,125;,
  3;186,126,125;,
  3;187,126,186;,
  3;123,125,127;,
  3;187,128,126;,
  3;188,128,187;,
  3;125,126,77;,
  3;127,125,77;,
  3;118,24,117;,
  3;117,57,188;,
  3;57,128,188;,
  3;116,57,117;,
  3;129,128,57;,
  3;126,128,129;,
  3;57,78,129;,
  3;78,57,116;,
  3;126,129,130;,
  3;130,129,78;,
  3;77,126,130;,
  3;131,130,78;,
  3;189,77,190;,
  3;78,116,132;,
  3;189,133,77;,
  3;133,191,77;,
  3;134,131,78;,
  3;134,78,132;,
  3;131,72,133;,
  3;134,72,131;,
  3;133,72,134;,
  3;132,116,135;,
  3;135,134,132;,
  3;107,11,116;,
  3;11,135,116;,
  3;179,167,11;,
  3;136,135,11;,
  3;136,11,167;,
  3;135,136,134;,
  3;136,2,104;,
  3;137,136,104;,
  3;137,134,136;,
  3;137,104,103;,
  3;105,192,103;,
  3;137,138,134;,
  3;192,105,138;,
  3;138,133,134;,
  3;105,9,13;,
  3;138,68,133;,
  3;138,105,139;,
  3;68,138,139;,
  3;68,139,133;,
  3;139,105,13;,
  3;133,139,191;,
  3;110,112,13;,
  3;193,139,13;,
  3;139,140,191;,
  3;140,139,193;,
  3;127,140,123;,
  3;140,112,113;,
  3;123,140,194;,
  3;141,142,143;,
  3;144,141,143;,
  3;9,141,144;,
  3;195,196,145;,
  3;9,144,146;,
  3;26,195,145;,
  3;144,147,146;,
  3;197,195,26;,
  3;146,147,148;,
  3;149,26,145;,
  3;149,197,26;,
  3;145,150,149;,
  3;147,151,148;,
  3;151,197,149;,
  3;148,151,123;,
  3;151,149,119;,
  3;142,145,196;,
  3;142,152,145;,
  3;145,152,150;,
  3;152,142,153;,
  3;198,153,142;,
  3;78,150,152;,
  3;153,78,152;,
  3;141,9,199;,
  3;153,154,78;,
  3;155,141,199;,
  3;198,155,153;,
  3;154,153,155;,
  3;200,155,199;,
  3;155,200,156;,
  3;154,155,156;,
  3;156,200,123;,
  3;201,157,78;,
  3;156,157,154;,
  3;123,157,156;,
  3;150,78,157;,
  3;123,202,157;,
  3;157,203,150;,
  3;187,157,202;,
  3;187,203,157;,
  3;158,159,160;,
  3;160,147,158;,
  3;197,204,161;,
  3;158,147,162;,
  3;163,197,161;,
  3;147,151,162;,
  3;151,197,163;,
  3;205,206,204;,
  3;205,152,206;,
  3;206,152,207;,
  3;152,205,164;,
  3;164,207,152;,
  3;208,155,164;,
  3;155,159,209;,
  3;210,155,209;,
  3;207,164,165;,
  3;164,155,211;,
  3;155,210,211;,
  3;207,165,202;,
  3;210,202,212;;
 }
 MeshTextureCoords {
  223;
  0.674800;0.653320;,
  0.651370;0.657470;,
  0.625490;0.574220;,
  0.729490;0.637210;,
  0.638180;0.492680;,
  0.622070;0.523930;,
  0.610840;0.494140;,
  0.712890;0.460940;,
  0.774900;0.586670;,
  0.806640;0.539060;,
  0.578610;0.375000;,
  0.549800;0.381840;,
  0.780270;0.455570;,
  0.920900;0.477540;,
  0.936520;0.425290;,
  0.556150;0.337400;,
  0.539550;0.339840;,
  0.490480;0.282710;,
  0.668950;0.410650;,
  0.684570;0.467770;,
  0.710450;0.424320;,
  0.572750;0.187500;,
  0.473150;0.208500;,
  0.468510;0.181150;,
  0.535650;0.114750;,
  0.491210;0.141110;,
  0.613770;0.266110;,
  0.604490;0.092770;,
  0.574710;0.057130;,
  0.654300;0.014160;,
  0.691900;0.173340;,
  0.707030;0.080570;,
  0.752440;0.014650;,
  0.783690;0.034180;,
  0.768070;0.133300;,
  0.822270;0.116700;,
  0.847170;0.071290;,
  0.917970;0.125000;,
  0.951660;0.235840;,
  0.836910;0.227050;,
  0.961430;0.320310;,
  0.758300;0.220700;,
  0.724610;0.266110;,
  0.748530;0.241700;,
  0.908200;0.388670;,
  0.960940;0.358400;,
  0.788570;0.336430;,
  0.752930;0.409670;,
  0.721680;0.399900;,
  0.719730;0.299320;,
  0.681640;0.279300;,
  0.519530;0.359380;,
  0.331540;0.330570;,
  0.490230;0.335450;,
  0.537110;0.418950;,
  0.275880;0.331540;,
  0.208370;0.404300;,
  0.400880;0.423830;,
  0.291750;0.470210;,
  0.459720;0.491210;,
  0.519530;0.487300;,
  0.546880;0.523680;,
  0.232790;0.517330;,
  0.135010;0.483400;,
  0.342040;0.514890;,
  0.161380;0.543950;,
  0.115480;0.527590;,
  0.336430;0.557130;,
  0.428470;0.560300;,
  0.531250;0.578860;,
  0.574710;0.545900;,
  0.575680;0.585690;,
  0.601070;0.622070;,
  0.508300;0.597660;,
  0.524410;0.683350;,
  0.412350;0.609620;,
  0.486820;0.670410;,
  0.588870;0.694820;,
  0.632320;0.679440;,
  0.642580;0.764160;,
  0.551760;0.861940;,
  0.507320;0.780640;,
  0.480710;0.729740;,
  0.521480;0.900020;,
  0.481450;0.917170;,
  0.436770;0.717770;,
  0.443600;0.795290;,
  0.381350;0.746340;,
  0.384280;0.661130;,
  0.377200;0.616940;,
  0.293700;0.683840;,
  0.307620;0.825320;,
  0.337650;0.577390;,
  0.308840;0.754880;,
  0.285890;0.616210;,
  0.337400;0.610110;,
  0.309570;0.654780;,
  0.295650;0.644530;,
  0.284420;0.686030;,
  0.243650;0.643800;,
  0.283200;0.707270;,
  0.277590;0.702150;,
  0.230220;0.705320;,
  0.199590;0.657960;,
  0.169560;0.748530;,
  0.088130;0.631840;,
  0.141110;0.699950;,
  0.038360;0.646480;,
  0.083130;0.551760;,
  0.033170;0.581050;,
  0.026150;0.655270;,
  0.055910;0.718260;,
  0.028060;0.760130;,
  0.130980;0.740970;,
  0.089720;0.839970;,
  0.047820;0.864750;,
  0.050690;0.910650;,
  0.135010;0.941920;,
  0.155400;0.786740;,
  0.240840;0.810420;,
  0.161260;0.871700;,
  0.294190;0.803710;,
  0.227420;0.884030;,
  0.269040;0.898190;,
  0.251710;0.957700;,
  0.390140;0.931330;,
  0.361820;0.978900;,
  0.413090;0.943600;,
  0.437500;0.945500;,
  0.674800;0.653320;,
  0.651370;0.657470;,
  0.733400;0.633300;,
  0.622560;0.504640;,
  0.550780;0.337400;,
  0.716800;0.415530;,
  0.683590;0.462890;,
  0.934080;0.422850;,
  0.718260;0.281250;,
  0.960940;0.344240;,
  0.950680;0.235840;,
  0.756840;0.223630;,
  0.623530;0.109860;,
  0.490480;0.282710;,
  0.470700;0.178710;,
  0.574710;0.057130;,
  0.654300;0.014160;,
  0.758790;0.125490;,
  0.752440;0.014650;,
  0.784180;0.035160;,
  0.917970;0.125000;,
  0.847170;0.071290;,
  0.135860;0.939390;,
  0.050690;0.910650;,
  0.051510;0.862550;,
  0.160770;0.788330;,
  0.252440;0.955050;,
  0.166260;0.748050;,
  0.045380;0.734130;,
  0.295170;0.805050;,
  0.099120;0.646000;,
  0.033690;0.649900;,
  0.113340;0.527830;,
  0.209960;0.411130;,
  0.228640;0.696290;,
  0.281250;0.701660;,
  0.304930;0.660650;,
  0.337400;0.571780;,
  0.407470;0.732910;,
  0.385010;0.613770;,
  0.340580;0.513670;,
  0.275880;0.331540;,
  0.504400;0.347170;,
  0.456540;0.487790;,
  0.530270;0.501220;,
  0.519040;0.588870;,
  0.575200;0.566160;,
  0.602540;0.631350;,
  0.488280;0.670900;,
  0.507320;0.780640;,
  0.521480;0.900020;,
  0.465580;0.927430;,
  0.408200;0.940980;,
  0.361820;0.978900;,
  0.686520;0.649410;,
  0.651370;0.657470;,
  0.623050;0.513920;,
  0.705570;0.445800;,
  0.550780;0.341800;,
  0.927730;0.449710;,
  0.726070;0.270510;,
  0.956050;0.293460;,
  0.551270;0.092770;,
  0.472410;0.187990;,
  0.772950;0.029780;,
  0.523930;0.500240;,
  0.281250;0.331540;,
  0.508790;0.356930;,
  0.340090;0.522220;,
  0.124510;0.518070;,
  0.385010;0.613520;,
  0.553710;0.583250;,
  0.536620;0.881230;,
  0.286380;0.692870;,
  0.468990;0.690430;,
  0.390870;0.957790;,
  0.302250;0.778200;,
  0.169430;0.753420;,
  0.051420;0.894290;,
  0.034270;0.607670;,
  0.866700;0.494630;,
  0.680660;0.650640;,
  0.671390;0.473630;,
  0.570310;0.318360;,
  0.947750;0.256840;,
  0.539060;0.117680;,
  0.548830;0.569090;,
  0.281250;0.331540;,
  0.508790;0.356930;,
  0.077270;0.595950;,
  0.297610;0.648930;,
  0.589840;0.822390;,
  0.360840;0.957210;,
  0.270020;0.772220;;
 }
}
