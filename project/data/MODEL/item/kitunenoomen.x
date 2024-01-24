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
 283;
 -4.87969;14.62035;6.91867;,
 -2.35323;14.29551;6.34127;,
 -4.38284;13.97288;5.82495;,
 -4.87969;14.62035;6.91867;,
 -4.17046;16.56829;9.97849;,
 -4.87969;14.62035;6.91867;,
 -7.77856;17.53407;11.52406;,
 -4.87969;14.62035;6.91867;,
 -8.13959;15.91423;8.93177;,
 -4.87969;14.62035;6.91867;,
 -6.32236;13.64145;5.29456;,
 -4.87969;14.62035;6.91867;,
 -4.38284;13.97288;5.82495;,
 -3.11437;17.39148;11.10082;,
 -1.44588;14.51633;6.49961;,
 -8.57195;18.61399;13.05724;,
 -9.98907;16.25862;9.28787;,
 -7.29262;13.51344;4.89465;,
 -2.72781;15.90682;12.62761;,
 -0.72316;13.32775;8.50024;,
 -8.86235;17.22330;14.73443;,
 -10.66604;14.59871;10.53420;,
 -8.01075;12.37489;6.97535;,
 -8.56248;10.15810;-0.32505;,
 -9.26156;8.52686;0.87982;,
 -6.49814;4.27620;-5.92266;,
 -6.00942;6.23100;-6.60971;,
 -7.51645;13.35116;4.96282;,
 -8.27158;12.26483;6.86182;,
 -0.07767;14.66995;6.89542;,
 -0.07767;13.43564;8.73551;,
 8.51315;13.61150;5.20155;,
 9.26825;12.26482;6.86181;,
 8.40708;10.15809;-0.32507;,
 9.10616;8.52685;0.87980;,
 5.85403;6.23100;-6.60971;,
 6.34276;4.27620;-5.92266;,
 2.26494;3.66779;-10.71171;,
 2.45796;1.50182;-10.36261;,
 -2.42032;3.66779;-10.71171;,
 -2.61333;1.50182;-10.36261;,
 7.12659;13.81811;5.40944;,
 7.50364;12.50029;7.10708;,
 10.42103;14.54377;10.37735;,
 9.76075;16.16279;9.16172;,
 8.46633;17.42096;14.98181;,
 8.18308;18.77737;13.34592;,
 2.67832;15.81967;12.41920;,
 3.05536;17.26774;10.93001;,
 0.75822;13.37155;8.50140;,
 1.41852;14.57256;6.61680;,
 -8.01075;12.37489;6.97535;,
 -0.07768;7.19940;-10.64801;,
 -1.04081;7.74808;-8.40056;,
 -0.07768;7.25631;-8.79392;,
 -0.07768;7.19940;-10.64801;,
 -2.03850;7.05396;-8.62884;,
 -0.07768;7.19940;-10.64801;,
 -1.32456;6.22847;-9.94990;,
 -0.07768;7.19940;-10.64801;,
 -0.57010;5.68968;-10.81215;,
 -0.07768;7.19940;-10.64801;,
 0.41473;5.68968;-10.81215;,
 -0.07768;7.19940;-10.64801;,
 1.16919;6.22847;-9.94990;,
 -0.07768;7.19940;-10.64801;,
 1.88313;7.05396;-8.62884;,
 -0.07768;7.19940;-10.64801;,
 0.88545;7.74808;-8.40056;,
 -0.07768;7.19940;-10.64801;,
 -0.07768;7.25631;-8.79392;,
 -4.61766;6.78070;-6.72991;,
 -7.21719;9.20349;-1.55561;,
 -1.87067;4.28645;-10.72154;,
 1.71528;4.28645;-10.72154;,
 4.46227;6.71712;-6.96441;,
 7.06180;9.20348;-1.55562;,
 -0.07767;12.89045;4.34477;,
 -7.09221;11.84661;2.67428;,
 -7.51645;13.35116;4.96282;,
 -0.07767;14.66995;6.89542;,
 -8.56248;10.15810;-0.32505;,
 -6.00942;6.23100;-6.60971;,
 -2.42032;3.66779;-10.71171;,
 2.26494;3.66779;-10.71171;,
 5.85403;6.23100;-6.60971;,
 8.40708;10.15809;-0.32507;,
 6.36272;11.84661;2.67428;,
 8.51315;13.61150;5.20155;,
 -0.07767;12.89045;4.34477;,
 -0.07767;14.66995;6.89542;,
 -8.27158;12.26483;6.86182;,
 -0.07767;13.43564;8.73551;,
 -9.26156;8.52686;0.87982;,
 -6.49814;4.27620;-5.92266;,
 -2.61333;1.50182;-10.36261;,
 2.45796;1.50182;-10.36261;,
 6.34276;4.27620;-5.92266;,
 9.10616;8.52685;0.87980;,
 9.26825;12.26482;6.86181;,
 -0.07767;13.43564;8.73551;,
 -0.07768;8.44459;-2.95060;,
 -3.59142;8.43653;-3.08336;,
 3.30626;8.52048;-2.85650;,
 3.30680;8.52089;-2.85540;,
 4.79558;8.26284;-4.65090;,
 -4.96287;8.26778;-4.63463;,
 -3.61219;8.45059;-3.04534;,
 4.77719;14.74493;6.73836;,
 6.18433;13.93879;5.55599;,
 3.60114;14.31136;6.15223;,
 4.77719;14.74493;6.73836;,
 7.95682;15.93331;8.74790;,
 4.77719;14.74493;6.73836;,
 7.40923;17.83047;11.78400;,
 4.77719;14.74493;6.73836;,
 4.08545;16.57125;9.76882;,
 4.77719;14.74493;6.73836;,
 2.31296;14.45054;6.37496;,
 4.77719;14.74493;6.73836;,
 3.60114;14.31136;6.15223;,
 9.76075;16.16279;9.16172;,
 7.12659;13.81811;5.40944;,
 8.18308;18.77737;13.34592;,
 3.05536;17.26774;10.93001;,
 1.41852;14.57256;6.61680;,
 10.42103;14.54377;10.37735;,
 7.50364;12.17633;6.58864;,
 8.46633;17.42096;14.98181;,
 2.67832;15.81967;12.41920;,
 0.75822;13.37155;8.50140;,
 5.14960;12.61418;3.46170;,
 5.43195;11.93001;2.36678;,
 5.64240;11.45369;1.60451;,
 5.39480;11.65719;1.93019;,
 5.12984;10.88912;0.68143;,
 4.88817;11.19560;1.17681;,
 3.76879;10.59050;0.22173;,
 3.64402;10.87749;0.68413;,
 2.56113;10.39466;-0.07383;,
 2.32254;10.62518;0.29820;,
 2.01995;9.93735;-0.82214;,
 1.78299;10.12687;-0.51884;,
 1.80315;9.43940;-1.61902;,
 1.52772;8.78112;-2.67250;,
 5.15318;12.58497;3.41494;,
 5.81114;11.71941;2.02975;,
 5.89513;11.33228;1.41023;,
 5.62353;11.44658;1.59314;,
 5.35858;10.67852;0.34439;,
 5.13612;10.88820;0.68485;,
 3.99752;10.37990;-0.11531;,
 3.73518;10.59597;0.23361;,
 2.67603;10.12761;-0.50121;,
 2.55127;10.41459;-0.03883;,
 2.28330;9.80197;-1.03878;,
 2.01171;9.91627;-0.85587;,
 2.08857;9.22880;-1.95605;,
 1.52778;8.76051;-2.70548;,
 -4.99188;12.60214;3.44678;,
 -5.23709;11.64514;1.91526;,
 -5.48468;11.44163;1.58958;,
 -5.27423;11.91796;2.35186;,
 -4.73045;11.17037;1.17015;,
 -3.48630;10.86700;0.66823;,
 -3.61107;10.57721;0.20758;,
 -4.97212;10.85948;0.67751;,
 -2.16481;10.63073;0.27228;,
 -2.40341;10.39740;-0.09800;,
 -1.62526;10.11482;-0.53376;,
 -1.86223;9.92530;-0.83706;,
 -1.37000;8.76907;-2.68741;,
 -1.64543;9.42735;-1.63394;,
 -4.99546;12.58301;3.41617;,
 -5.46581;11.44462;1.59436;,
 -5.73741;11.33033;1.41145;,
 -5.65342;11.71745;2.03097;,
 -4.97840;10.87304;0.69432;,
 -5.20086;10.65896;0.35661;,
 -3.57746;10.59557;0.23385;,
 -3.83980;10.37669;-0.11331;,
 -2.39355;10.43023;-0.04860;,
 -2.51831;10.14044;-0.50923;,
 -1.85399;9.91431;-0.85464;,
 -2.12557;9.80001;-1.03756;,
 -1.37006;8.75855;-2.70426;,
 -1.93085;9.22684;-1.95483;,
 -5.46581;11.44462;1.59436;,
 -4.97840;10.87304;0.69432;,
 -5.20086;10.65896;0.35661;,
 -5.73741;11.33033;1.41145;,
 -3.57746;10.59557;0.23385;,
 -3.83980;10.37669;-0.11331;,
 -2.39355;10.43023;-0.04860;,
 -2.51831;10.14044;-0.50923;,
 -1.85399;9.91431;-0.85464;,
 -2.12557;9.80001;-1.03756;,
 -1.37006;8.75855;-2.70426;,
 -1.93085;9.22684;-1.95483;,
 -3.52513;11.27907;1.61691;,
 -1.80549;10.96631;1.11640;,
 -1.66625;10.58651;0.50860;,
 -1.86573;10.80728;0.86191;,
 -1.52809;10.89900;1.00868;,
 -1.38603;10.37481;0.16980;,
 -1.08480;10.67916;0.65686;,
 -1.18535;9.92596;-0.54851;,
 -0.70261;10.37690;0.17315;,
 -0.93497;9.54389;-1.15994;,
 -0.52816;9.98082;-0.46072;,
 -0.63456;9.42408;-1.35168;,
 -0.55152;9.63115;-1.02029;,
 -0.56029;9.46999;-1.27821;,
 3.36280;11.25010;1.57056;,
 1.70339;10.77832;0.81555;,
 1.50392;10.55755;0.46225;,
 1.64316;10.93735;1.07005;,
 1.22369;10.34584;0.12344;,
 1.36576;10.87003;0.96232;,
 1.02302;9.89699;-0.59486;,
 0.92247;10.65019;0.61051;,
 0.77264;9.51493;-1.20630;,
 0.54028;10.34793;0.12679;,
 0.47223;9.39512;-1.39803;,
 0.36582;9.95185;-0.50707;,
 0.39796;9.44102;-1.32457;,
 0.38918;9.60219;-1.06665;,
 -3.17072;8.20363;-5.38024;,
 -3.08588;8.13879;-5.59291;,
 -3.31348;8.13828;-5.59373;,
 -3.52905;8.13834;-5.48472;,
 -3.71985;8.17947;-5.30266;,
 -3.34449;8.23318;-5.21671;,
 -3.84167;8.22780;-5.13227;,
 -3.58903;8.24881;-5.09864;,
 -3.84661;8.21439;-4.94559;,
 -3.78862;8.28691;-4.82955;,
 -4.59008;8.46909;-4.03334;,
 -4.49951;8.54159;-3.91731;,
 -5.57625;8.93914;-3.33845;,
 -5.48567;9.01165;-3.22240;,
 -3.17072;7.80917;-6.71099;,
 -3.08588;7.74434;-6.92366;,
 -3.31348;7.74383;-6.92449;,
 -3.52905;7.74388;-6.81547;,
 -3.71985;7.78502;-6.63341;,
 -3.34449;7.83873;-6.54747;,
 -3.84167;7.83335;-6.46302;,
 -3.58903;7.85436;-6.42939;,
 -3.84661;7.81994;-6.27634;,
 -3.78862;7.89245;-6.16030;,
 -4.59008;8.07464;-5.36409;,
 -4.49951;8.14714;-5.24806;,
 -5.57625;8.25307;-4.48698;,
 -5.48567;8.32558;-4.37093;,
 2.74506;8.06939;-5.38379;,
 3.10339;8.00410;-5.48828;,
 2.88782;8.01414;-5.60360;,
 2.66022;7.95823;-5.56751;,
 2.91883;8.07329;-5.20424;,
 3.29419;8.01959;-5.29018;,
 3.16337;8.11460;-5.10220;,
 3.41601;8.10915;-5.14557;,
 3.36296;8.19139;-4.85729;,
 3.42095;8.11888;-4.97333;,
 4.07385;8.41156;-3.92350;,
 4.16443;8.33906;-4.03953;,
 5.06001;8.71707;-3.12575;,
 5.15059;8.64455;-3.24180;,
 2.74506;7.66782;-6.71009;,
 3.10339;7.60253;-6.81458;,
 2.88782;7.56100;-6.89768;,
 2.66022;7.56152;-6.89686;,
 2.91883;7.80184;-6.61186;,
 3.29419;7.71338;-6.67608;,
 3.16337;7.90111;-6.54603;,
 3.41601;7.75554;-6.50184;,
 3.36296;7.83872;-6.21414;,
 3.42095;7.76620;-6.33019;,
 4.07385;8.15606;-5.34107;,
 4.16443;8.08355;-5.45710;,
 5.06001;8.38811;-4.49743;,
 5.15059;8.31560;-4.61348;;
 
 158;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 4;1,4,13,14;,
 4;4,6,15,13;,
 4;6,8,16,15;,
 4;8,10,17,16;,
 4;14,13,18,19;,
 4;13,15,20,18;,
 4;15,16,21,20;,
 4;16,17,22,21;,
 4;23,24,25,26;,
 4;23,27,28,24;,
 4;27,29,30,28;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;33,35,36,34;,
 4;35,37,38,36;,
 4;37,39,40,38;,
 4;39,26,25,40;,
 4;37,35,33,31;,
 4;31,29,39,37;,
 4;29,27,26,39;,
 3;27,23,26;,
 4;41,42,43,44;,
 4;44,43,45,46;,
 4;46,45,47,48;,
 4;48,47,49,50;,
 4;16,21,51,17;,
 4;15,20,21,16;,
 4;13,18,20,15;,
 4;14,19,18,13;,
 4;41,44,46,48;,
 3;50,41,48;,
 4;13,16,17,14;,
 3;13,15,16;,
 3;52,53,54;,
 3;55,56,53;,
 3;57,58,56;,
 3;59,60,58;,
 3;61,62,60;,
 3;63,64,62;,
 3;65,66,64;,
 3;67,68,66;,
 3;69,70,68;,
 4;56,58,71,72;,
 4;58,60,73,71;,
 4;60,62,74,73;,
 4;62,64,75,74;,
 4;64,66,76,75;,
 4;77,78,79,80;,
 4;78,72,81,79;,
 4;72,71,82,81;,
 4;71,73,83,82;,
 4;73,74,84,83;,
 4;74,75,85,84;,
 4;75,76,86,85;,
 4;76,87,88,86;,
 4;87,89,90,88;,
 4;80,79,91,92;,
 4;79,81,93,91;,
 4;81,82,94,93;,
 4;82,83,95,94;,
 4;83,84,96,95;,
 4;84,85,97,96;,
 4;85,86,98,97;,
 4;86,88,99,98;,
 4;88,90,100,99;,
 4;101,54,53,102;,
 4;101,102,78,77;,
 4;103,68,54,101;,
 4;103,101,77,87;,
 4;104,87,76,105;,
 4;104,105,66,68;,
 4;106,72,78,107;,
 4;106,107,53,56;,
 3;108,109,110;,
 3;111,112,109;,
 3;113,114,112;,
 3;115,116,114;,
 3;117,118,116;,
 3;119,120,118;,
 4;109,112,121,122;,
 4;112,114,123,121;,
 4;114,116,124,123;,
 4;116,118,125,124;,
 4;122,121,126,127;,
 4;121,123,128,126;,
 4;123,124,129,128;,
 4;124,125,130,129;,
 4;131,132,133,134;,
 4;134,133,135,136;,
 4;136,135,137,138;,
 4;138,137,139,140;,
 4;140,139,141,142;,
 4;142,141,143,144;,
 4;145,146,147,148;,
 4;148,147,149,150;,
 4;150,149,151,152;,
 4;152,151,153,154;,
 4;154,153,155,156;,
 4;156,155,157,158;,
 4;159,160,161,162;,
 4;163,164,165,166;,
 4;164,167,168,165;,
 4;167,169,170,168;,
 4;169,171,172,170;,
 4;173,174,175,176;,
 4;174,177,178,175;,
 4;177,179,180,178;,
 4;179,181,182,180;,
 4;181,183,184,182;,
 4;183,185,186,184;,
 4;187,188,189,190;,
 4;188,191,192,189;,
 4;191,193,194,192;,
 4;193,195,196,194;,
 4;195,197,198,196;,
 4;163,177,174,160;,
 4;199,200,201,202;,
 4;200,203,204,201;,
 4;203,205,206,204;,
 4;205,207,208,206;,
 4;207,209,210,208;,
 4;209,211,212,210;,
 4;213,214,215,216;,
 4;216,215,217,218;,
 4;218,217,219,220;,
 4;220,219,221,222;,
 4;222,221,223,224;,
 4;224,223,225,226;,
 4;227,228,229,230;,
 4;227,230,231,232;,
 4;231,233,234,232;,
 4;234,233,235,236;,
 4;236,235,237,238;,
 4;238,237,239,240;,
 4;241,242,243,244;,
 4;241,244,245,246;,
 4;245,247,248,246;,
 4;248,247,249,250;,
 4;250,249,251,252;,
 4;252,251,253,254;,
 4;255,256,257,258;,
 4;255,259,260,256;,
 4;260,259,261,262;,
 4;261,263,264,262;,
 4;263,265,266,264;,
 4;265,267,268,266;,
 4;269,270,271,272;,
 4;269,273,274,270;,
 4;274,273,275,276;,
 4;275,277,278,276;,
 4;277,279,280,278;,
 4;279,281,282,280;;
 
 MeshMaterialList {
  5;
  158;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
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
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
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
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.012800;1.000000;;
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
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  187;
  -0.001429;0.851048;-0.525087;,
  -0.006658;0.859173;-0.511642;,
  -0.035181;0.844605;-0.534232;,
  -0.032677;0.833251;-0.551928;,
  0.010292;0.836670;-0.547611;,
  0.040923;0.850713;-0.524035;,
  0.028014;0.858653;-0.511792;,
  -0.085438;0.827464;-0.554980;,
  -0.056616;0.821245;-0.567760;,
  0.018219;0.827301;-0.561464;,
  0.070730;0.851406;-0.519716;,
  0.077285;0.863973;-0.497572;,
  0.881509;0.464512;0.084682;,
  0.677693;0.630285;0.378778;,
  0.368487;0.698040;0.613968;,
  -0.968375;0.140586;-0.206122;,
  -0.858838;-0.144933;-0.491316;,
  0.843224;-0.022035;0.537111;,
  0.935625;-0.244712;0.254406;,
  0.667394;-0.708719;-0.228696;,
  0.021443;-0.848738;-0.528378;,
  -0.209827;-0.808177;-0.550293;,
  -0.934225;-0.178740;0.308667;,
  -0.843224;-0.022038;0.537111;,
  -0.421022;0.107642;0.900641;,
  0.421022;0.107644;0.900641;,
  -0.968895;-0.101559;0.225671;,
  -0.826637;0.218518;0.518576;,
  -0.909159;-0.400463;-0.114281;,
  0.712822;-0.600353;-0.362575;,
  0.882672;-0.459832;-0.097186;,
  -0.908586;0.401522;0.115114;,
  -0.942218;-0.273868;0.192926;,
  0.000000;-0.848048;0.529919;,
  0.000000;-0.848048;0.529919;,
  0.003588;-0.848750;0.528782;,
  -0.011258;-0.851395;0.524404;,
  -0.029687;-0.853050;0.520985;,
  0.458129;-0.669416;-0.584808;,
  0.968375;-0.140586;0.206122;,
  0.858838;0.144933;0.491316;,
  0.908586;-0.401522;-0.115114;,
  -0.677693;-0.630285;-0.378778;,
  -0.368487;-0.698040;-0.613968;,
  -0.881509;-0.464512;-0.084682;,
  -0.000000;-0.848048;0.529919;,
  -0.000000;-0.848048;0.529919;,
  -0.000000;-0.848048;0.529919;,
  -0.000000;-0.848048;0.529919;,
  -0.000000;-0.848048;0.529919;,
  -0.000000;-0.848048;0.529919;,
  -0.239326;0.773076;-0.587433;,
  -0.002104;0.995002;-0.099830;,
  -0.006674;0.968449;-0.249122;,
  -0.480172;0.714929;-0.508244;,
  -0.596177;0.443074;-0.669521;,
  -0.319920;0.206420;-0.924685;,
  0.316331;0.206229;-0.925961;,
  0.585086;0.454115;-0.671903;,
  0.470820;0.722124;-0.506819;,
  0.006550;0.967828;-0.251528;,
  -0.000561;0.840726;-0.541460;,
  0.041133;0.866371;-0.497703;,
  -0.113655;0.842281;-0.526920;,
  -0.409814;0.640459;-0.649511;,
  -0.272657;0.254282;-0.927900;,
  0.275248;0.242108;-0.930388;,
  0.408953;0.637192;-0.653256;,
  0.116638;0.843999;-0.523509;,
  -0.034354;0.863981;-0.502351;,
  -0.004060;0.825130;-0.564928;,
  0.060077;0.835688;-0.545909;,
  0.016132;0.849495;-0.527349;,
  -0.629361;0.421355;-0.652966;,
  -0.338622;0.101996;-0.935378;,
  0.344023;0.090029;-0.934635;,
  0.639314;0.405251;-0.653490;,
  0.010508;0.847453;-0.530766;,
  -0.050231;0.832427;-0.551853;,
  -0.021443;0.848738;0.528378;,
  -0.667394;0.708719;0.228696;,
  -0.935625;0.244712;-0.254406;,
  -0.843224;0.022035;-0.537111;,
  -0.421022;-0.107644;-0.900641;,
  0.421022;-0.107642;-0.900641;,
  0.843224;0.022038;-0.537111;,
  0.934225;0.178740;-0.308667;,
  0.942218;0.273868;-0.192926;,
  -0.000513;0.937408;-0.348232;,
  0.104534;0.932681;-0.345223;,
  -0.105642;0.931753;-0.347385;,
  0.089000;0.926069;-0.366709;,
  -0.084493;0.928664;-0.361169;,
  0.649953;0.349431;-0.674877;,
  0.209827;0.808177;0.550293;,
  -0.003111;0.839225;-0.543775;,
  -0.013419;0.816562;-0.577102;,
  0.010897;0.833961;-0.551716;,
  0.019826;0.845622;-0.533414;,
  0.003139;0.852684;-0.522417;,
  -0.016275;0.854258;-0.519595;,
  -0.019301;0.840806;-0.540992;,
  0.020069;0.842288;-0.538653;,
  0.017866;0.846173;-0.532608;,
  0.003267;0.852948;-0.521985;,
  -0.014856;0.853950;-0.520143;,
  -0.020583;0.852132;-0.522922;,
  0.835555;-0.128269;-0.534223;,
  0.961240;0.149963;-0.231364;,
  0.909159;0.400463;0.114281;,
  -0.712822;0.600353;0.362575;,
  -0.882672;0.459832;0.097186;,
  -0.458129;0.669416;0.584808;,
  0.000007;0.848049;-0.529918;,
  0.003254;0.849566;-0.527472;,
  -0.000554;0.849915;-0.526920;,
  -0.007627;0.848511;-0.529124;,
  -0.000286;0.849826;-0.527063;,
  0.003537;0.849680;-0.527287;,
  0.000002;0.848048;-0.529920;,
  -0.000001;0.848048;-0.529919;,
  0.001519;0.849748;-0.527187;,
  -0.002021;0.850031;-0.526729;,
  -0.007365;0.848403;-0.529300;,
  0.000475;0.850063;-0.526681;,
  0.004301;0.849963;-0.526824;,
  0.000000;0.848048;-0.529919;,
  0.000001;0.848048;-0.529920;,
  0.003899;0.846966;-0.531633;,
  0.000097;0.846630;-0.532183;,
  -0.007623;0.847540;-0.530677;,
  -0.000290;0.846258;-0.532773;,
  0.003533;0.846395;-0.532544;,
  0.000001;0.848048;-0.529919;,
  -0.007601;0.847339;-0.530997;,
  0.000002;0.848048;-0.529920;,
  0.003615;0.846186;-0.532875;,
  0.001257;0.846003;-0.533177;,
  -0.007361;0.847653;-0.530500;,
  0.000473;0.846019;-0.533153;,
  0.004299;0.846104;-0.533001;,
  0.000001;0.848048;-0.529919;,
  0.001525;0.846339;-0.532642;,
  -0.002012;0.846057;-0.533089;,
  0.003047;0.844620;-0.535357;,
  0.000002;0.848049;-0.529918;,
  0.000001;0.848049;-0.529919;,
  0.000000;0.848048;-0.529919;,
  0.000000;0.848048;-0.529919;,
  0.000000;0.848048;-0.529919;,
  0.000001;0.848048;-0.529919;,
  0.000002;0.848048;-0.529919;,
  0.000000;0.848048;-0.529920;,
  -0.000001;0.848048;-0.529920;,
  0.000004;0.848047;-0.529920;,
  0.000005;0.848048;-0.529920;,
  0.000001;0.848048;-0.529919;,
  -0.000000;0.848048;-0.529919;,
  -0.000001;0.848048;-0.529919;,
  0.019714;0.840897;-0.540836;,
  -0.097914;0.869902;-0.483408;,
  -0.219894;0.931460;-0.289877;,
  -0.139949;0.964460;-0.224125;,
  -0.069459;0.955979;-0.285094;,
  -0.069553;0.960484;-0.269504;,
  -0.056590;0.964635;-0.257444;,
  -0.197612;0.893209;-0.403890;,
  -0.205707;0.888300;-0.410620;,
  -0.219899;0.931463;-0.289865;,
  -0.139959;0.964461;-0.224113;,
  -0.069455;0.955974;-0.285115;,
  -0.069554;0.960485;-0.269501;,
  -0.056601;0.964645;-0.257401;,
  0.105340;0.878208;-0.466534;,
  0.175173;0.883754;-0.433928;,
  0.179018;0.927152;-0.329152;,
  0.047615;0.931238;-0.361288;,
  0.050623;0.947348;-0.316180;,
  0.021098;0.973622;-0.227191;,
  -0.075516;0.954358;-0.288960;,
  0.159392;0.888327;-0.430662;,
  0.158172;0.883681;-0.440555;,
  0.363324;0.881149;-0.302608;,
  0.424257;0.789425;-0.443638;,
  0.119677;0.691180;-0.712704;,
  -0.004414;0.796048;-0.605217;,
  0.009170;0.871942;-0.489523;;
  158;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;4,5,10,9;,
  4;5,6,11,10;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;31,15,15,31;,
  4;15,16,16,15;,
  4;18,18,17,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;32,22,22,32;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,17,17,25;,
  4;33,34,34,33;,
  4;33,35,35,33;,
  4;35,36,36,35;,
  3;36,37,36;,
  4;27,27,26,26;,
  4;26,26,28,28;,
  4;38,38,29,29;,
  4;29,29,30,30;,
  4;39,39,40,40;,
  4;41,41,39,39;,
  4;42,42,43,43;,
  4;44,44,42,42;,
  4;45,46,46,45;,
  3;47,45,45;,
  4;48,48,49,49;,
  3;48,50,48;,
  3;51,53,52;,
  3;51,54,53;,
  3;51,55,54;,
  3;51,56,55;,
  3;51,57,56;,
  3;93,58,57;,
  3;93,59,58;,
  3;51,60,59;,
  3;51,52,60;,
  4;54,55,64,63;,
  4;55,56,65,64;,
  4;56,57,66,65;,
  4;57,58,67,66;,
  4;58,59,68,67;,
  4;61,62,71,70;,
  4;62,63,72,71;,
  4;63,64,73,72;,
  4;64,65,74,73;,
  4;65,66,75,74;,
  4;66,67,76,75;,
  4;67,68,77,76;,
  4;68,69,78,77;,
  4;69,61,70,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,73,82,81;,
  4;73,74,83,82;,
  4;74,75,84,83;,
  4;75,76,85,84;,
  4;76,86,86,85;,
  4;86,87,87,86;,
  4;94,79,79,94;,
  4;88,52,53,89;,
  4;88,89,62,61;,
  4;90,60,52,88;,
  4;90,88,61,69;,
  4;91,69,68,91;,
  4;91,91,59,60;,
  4;92,63,62,92;,
  4;92,92,53,54;,
  3;95,97,96;,
  3;95,98,97;,
  3;95,99,98;,
  3;95,100,99;,
  3;95,101,100;,
  3;95,96,101;,
  4;97,98,103,102;,
  4;98,99,104,103;,
  4;99,100,105,104;,
  4;100,101,106,105;,
  4;107,108,108,107;,
  4;108,109,109,108;,
  4;112,110,110,112;,
  4;110,111,111,110;,
  4;113,113,114,114;,
  4;114,114,115,115;,
  4;115,115,116,116;,
  4;116,116,117,117;,
  4;117,117,118,118;,
  4;118,118,119,119;,
  4;120,120,121,121;,
  4;121,121,122,122;,
  4;122,122,123,123;,
  4;123,123,124,124;,
  4;124,124,125,125;,
  4;125,125,126,126;,
  4;127,128,127,127;,
  4;129,130,130,134;,
  4;130,131,131,130;,
  4;131,132,132,131;,
  4;132,133,133,132;,
  4;135,136,142,135;,
  4;136,137,143,142;,
  4;137,138,138,143;,
  4;138,139,139,138;,
  4;139,140,140,139;,
  4;140,141,141,140;,
  4;144,143,143,144;,
  4;143,138,138,143;,
  4;138,139,139,138;,
  4;139,140,140,139;,
  4;140,141,141,140;,
  4;129,137,136,128;,
  4;145,146,146,145;,
  4;146,147,147,146;,
  4;147,148,148,147;,
  4;148,149,149,148;,
  4;149,150,150,149;,
  4;150,151,151,150;,
  4;152,152,153,153;,
  4;153,153,154,154;,
  4;154,154,155,155;,
  4;155,155,156,156;,
  4;156,156,157,157;,
  4;157,157,158,158;,
  4;164,165,165,164;,
  4;164,164,163,163;,
  4;163,162,162,163;,
  4;162,162,161,161;,
  4;161,161,160,160;,
  4;160,160,159,159;,
  4;171,172,172,171;,
  4;171,171,170,170;,
  4;170,169,169,170;,
  4;169,169,168,168;,
  4;168,168,167,167;,
  4;167,167,166,166;,
  4;178,178,179,179;,
  4;178,177,177,178;,
  4;177,177,176,176;,
  4;176,175,175,176;,
  4;175,174,174,175;,
  4;174,173,173,174;,
  4;185,185,186,186;,
  4;185,184,184,185;,
  4;184,184,183,183;,
  4;183,182,182,183;,
  4;182,181,181,182;,
  4;181,180,180,181;;
 }
 MeshTextureCoords {
  283;
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.333330;0.333330;,
  0.166670;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  0.333330;0.500000;,
  0.166670;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
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
  0.055560;0.000000;,
  0.111110;0.125000;,
  0.000000;0.125000;,
  0.166670;0.000000;,
  0.222220;0.125000;,
  0.277780;0.000000;,
  0.333330;0.125000;,
  0.388890;0.000000;,
  0.444440;0.125000;,
  0.500000;0.000000;,
  0.555560;0.125000;,
  0.611110;0.000000;,
  0.666670;0.125000;,
  0.722220;0.000000;,
  0.777780;0.125000;,
  0.833330;0.000000;,
  0.888890;0.125000;,
  0.944440;0.000000;,
  1.000000;0.125000;,
  0.333330;0.250000;,
  0.222220;0.250000;,
  0.444440;0.250000;,
  0.555560;0.250000;,
  0.666670;0.250000;,
  0.777780;0.250000;,
  0.000000;0.250000;,
  0.111110;0.250000;,
  0.111110;0.375000;,
  0.000000;0.375000;,
  0.222220;0.375000;,
  0.333330;0.375000;,
  0.444440;0.375000;,
  0.555560;0.375000;,
  0.666670;0.375000;,
  0.777780;0.375000;,
  0.888890;0.250000;,
  0.888890;0.375000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  0.111110;0.500000;,
  0.000000;0.500000;,
  0.222220;0.500000;,
  0.333330;0.500000;,
  0.444440;0.500000;,
  0.555560;0.500000;,
  0.666670;0.500000;,
  0.777780;0.500000;,
  0.888890;0.500000;,
  1.000000;0.500000;,
  0.000000;0.174420;,
  0.111110;0.177690;,
  0.888890;0.180250;,
  0.888890;0.180260;,
  0.777780;0.195300;,
  0.222220;0.195590;,
  0.111110;0.178120;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.333330;0.333330;,
  0.166670;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  0.333330;0.500000;,
  0.166670;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.333330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.166670;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.833330;1.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.833330;1.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.833330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.500000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.833330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.500000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;;
 }
}
