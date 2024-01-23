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
 134;
 -28.02657;354.69048;-183.47001;,
 -15.79498;369.55879;-187.00235;,
 31.37018;358.51900;-148.86647;,
 41.79809;360.44854;-148.86647;,
 -68.68136;12.99346;-323.55872;,
 31.13151;23.57942;-231.19466;,
 88.28016;-0.25291;-231.19466;,
 -45.91617;-1.24163;-288.23211;,
 -101.48162;-7.25924;346.71451;,
 -108.06801;-5.91135;355.02110;,
 54.96184;-0.91075;287.59146;,
 39.18769;19.01608;287.59146;,
 77.56093;32.67694;-235.93269;,
 102.76920;5.69457;-209.52129;,
 42.32862;42.10199;284.62769;,
 54.96184;22.02864;287.59146;,
 54.96184;29.36576;275.33365;,
 123.59706;1.84661;-122.73999;,
 -167.51286;-10.02741;-205.71514;,
 -45.91617;-1.24163;-288.23211;,
 88.28016;-0.25291;-231.19466;,
 -72.24127;369.51373;-94.22434;,
 -58.28471;380.56539;-110.43220;,
 -15.79498;369.55879;-187.00235;,
 -28.02657;354.69048;-183.47001;,
 -19.27405;380.56539;-111.26094;,
 31.37018;358.51900;-148.86647;,
 -15.79498;369.55879;-187.00235;,
 -58.28471;380.56539;-110.43220;,
 123.59706;1.84661;-122.73999;,
 88.28016;-0.25291;-231.19466;,
 102.76920;5.69457;-209.52129;,
 119.13351;11.82032;-119.43994;,
 41.60125;376.55040;-84.00565;,
 41.79809;360.44854;-148.86647;,
 -167.51286;-10.02741;-205.71514;,
 -146.97051;30.55891;-193.97554;,
 -68.68136;12.99346;-323.55872;,
 -45.91617;-1.24163;-288.23211;,
 123.59706;-0.90815;162.60236;,
 54.96184;-0.91075;287.59146;,
 -108.06801;-5.91135;355.02110;,
 -163.08814;-8.78063;252.46441;,
 -72.24127;368.95635;132.65908;,
 -58.28471;380.56539;148.96492;,
 -58.28471;380.56539;148.96492;,
 -40.04006;367.31890;216.91048;,
 -19.92236;367.31890;216.91048;,
 -18.59086;380.56539;150.12624;,
 119.13351;10.01860;159.00092;,
 54.96184;22.02864;287.59146;,
 123.59706;-0.90815;162.60236;,
 39.60086;376.55040;119.78716;,
 -163.08814;-8.78063;252.46441;,
 -101.48162;-7.25924;346.71451;,
 -119.09164;22.79696;240.05877;,
 104.01511;35.24672;156.34901;,
 76.20665;42.91265;233.62334;,
 54.96184;29.36576;275.33365;,
 119.13351;23.61194;157.81038;,
 119.13351;26.89320;-118.28092;,
 104.01511;35.24672;-117.31776;,
 102.76920;5.69457;-209.52129;,
 42.32862;42.10199;284.62769;,
 76.20665;42.91265;233.62334;,
 -48.23129;123.83036;321.42566;,
 -92.34260;-4.52271;330.30367;,
 -53.43988;123.98567;321.43125;,
 -34.75187;115.58245;-288.23211;,
 -31.83622;116.07736;-268.78418;,
 -7.40551;124.22958;310.62276;,
 80.60868;117.95928;-195.05708;,
 -114.94895;120.91470;-193.91386;,
 -34.75187;115.58245;-288.23211;,
 80.60868;117.95928;-195.05708;,
 102.76920;5.69457;-209.52129;,
 -96.46717;144.64558;226.28780;,
 -92.34260;-4.52271;330.30367;,
 -48.23129;123.83036;321.42566;,
 78.79680;122.96568;166.51627;,
 50.24638;123.56375;227.16961;,
 42.32862;42.10199;284.62769;,
 104.01511;35.24672;156.34901;,
 104.01511;35.24672;-117.31776;,
 80.60868;117.95928;-195.05708;,
 -1.81903;124.23078;307.27156;,
 -105.64901;131.86000;250.29888;,
 -1.81903;124.23078;307.27156;,
 -11.92107;260.71787;269.07347;,
 -19.92236;367.31890;216.91048;,
 -46.39147;257.87862;285.49134;,
 54.12990;268.33919;-285.84366;,
 53.88026;352.67007;-146.14080;,
 70.40776;269.52574;-267.79361;,
 -26.84555;262.06202;-326.38082;,
 70.40776;269.52574;-267.79361;,
 53.88026;352.67007;-146.14080;,
 81.88156;268.67408;-123.29380;,
 -123.74324;246.84341;-162.70650;,
 -26.84555;262.06202;-326.38082;,
 -46.39147;257.87862;285.49134;,
 -106.46172;244.35078;240.77571;,
 62.54457;267.19820;132.88611;,
 44.49016;265.55884;172.11646;,
 81.88156;268.67408;-123.29380;,
 -11.92107;260.71787;269.07347;,
 -106.46172;244.35078;240.77571;,
 81.88156;268.67408;-123.29380;,
 80.60868;117.95928;-195.05708;,
 102.76920;5.69457;-209.52129;,
 80.60868;117.95928;-195.05708;,
 80.60868;117.95928;-195.05708;,
 -11.92107;260.71787;269.07347;,
 -46.39147;257.87862;285.49134;,
 -40.04006;367.31890;216.91048;,
 -106.46172;244.35078;240.77571;,
 -51.44528;156.01748;311.26075;,
 -8.61550;155.25608;299.48919;,
 -24.62377;176.13775;-306.59854;,
 -77.96213;172.53908;-176.24583;,
 -76.44232;152.79437;226.94212;,
 -47.71047;155.91682;311.25332;,
 -85.85590;152.61564;253.52740;,
 -4.52342;155.22761;297.04566;,
 -11.92107;260.71787;269.07347;,
 -8.61550;155.25608;299.48919;,
 -51.44528;156.01748;311.26075;,
 -47.71047;155.91682;311.25332;,
 -76.44232;152.79437;226.94212;,
 -106.46172;244.35078;240.77571;,
 -85.85590;152.61564;253.52740;,
 -24.62377;176.13775;-306.59854;,
 -26.84555;262.06202;-326.38082;,
 -23.07454;175.74546;-296.21534;;
 
 83;
 3;0,1,2;,
 3;3,0,2;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,6,5;,
 3;14,15,16;,
 4;14,11,10,15;,
 4;17,18,19,20;,
 4;21,22,23,24;,
 4;25,26,27,28;,
 4;29,30,31,32;,
 4;33,34,26,25;,
 4;35,36,37,38;,
 4;39,40,41,42;,
 4;39,42,18,17;,
 4;43,44,22,21;,
 4;45,46,47,48;,
 4;45,48,25,28;,
 4;49,50,40,51;,
 4;49,51,29,32;,
 4;48,52,33,25;,
 4;53,41,54,55;,
 4;53,55,36,35;,
 4;56,57,58,59;,
 4;56,59,60,61;,
 4;59,58,50,49;,
 4;59,49,32,60;,
 3;62,60,32;,
 3;63,16,64;,
 3;65,66,67;,
 4;68,69,5,4;,
 4;70,67,66,8;,
 3;70,8,11;,
 4;69,71,12,5;,
 4;72,73,37,36;,
 3;74,60,75;,
 3;76,77,78;,
 4;79,80,81,57;,
 3;79,57,82;,
 4;79,82,83,84;,
 3;85,81,80;,
 4;76,86,55,54;,
 3;76,54,77;,
 4;86,72,36,55;,
 4;87,70,11,63;,
 3;88,89,90;,
 4;91,3,92,93;,
 4;94,0,3,91;,
 4;94,91,71,69;,
 4;95,96,34,97;,
 4;98,21,24,99;,
 4;100,46,44,101;,
 3;102,52,103;,
 4;102,103,80,79;,
 4;104,33,52,102;,
 4;104,102,79,84;,
 4;103,52,48,105;,
 4;103,105,85,80;,
 4;106,43,21,98;,
 3;107,34,33;,
 3;108,109,12;,
 3;108,91,93;,
 3;110,61,60;,
 3;111,95,97;,
 3;112,48,47;,
 3;113,89,114;,
 3;115,44,43;,
 4;116,67,70,117;,
 4;116,117,88,90;,
 4;118,73,72,119;,
 4;118,119,98,99;,
 4;120,76,78,121;,
 4;120,121,100,101;,
 4;119,72,86,122;,
 4;119,122,106,98;,
 3;123,124,125;,
 4;123,125,70,87;,
 3;126,113,127;,
 4;126,127,65,67;,
 3;128,129,130;,
 4;128,130,86,76;,
 3;131,132,133;,
 4;131,133,69,68;;
 
 MeshMaterialList {
  1;
  83;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.345098;0.320000;0.345098;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  0.449647;-0.539101;-0.712171;,
  0.569808;0.104357;-0.815125;,
  0.510047;0.738124;-0.441615;,
  0.702783;-0.039055;-0.710331;,
  0.840236;0.353599;0.411060;,
  0.408068;0.481053;0.775931;,
  -0.274676;0.761205;0.587469;,
  -0.037857;0.952618;0.301806;,
  0.130810;0.714738;0.687051;,
  -0.003097;-0.067944;-0.997684;,
  0.890830;0.053574;-0.451166;,
  0.843063;0.363557;0.396321;,
  0.341014;0.901947;-0.264957;,
  0.765846;0.322561;0.556268;,
  0.747167;0.021397;-0.664292;,
  0.549557;0.080200;-0.831598;,
  0.808110;0.431457;0.401003;,
  0.292564;0.270364;0.917229;,
  -0.245832;0.793985;0.556016;,
  0.507258;0.173271;-0.844195;,
  -0.530546;0.828941;-0.177139;,
  0.035724;-0.999252;-0.014799;,
  0.712905;0.664325;0.224586;,
  0.059212;0.993048;-0.101732;,
  -0.803769;0.550739;-0.225038;,
  0.993114;0.048544;-0.106626;,
  0.037828;0.990029;-0.135688;,
  -0.898115;0.092841;-0.429849;,
  0.911316;0.408897;0.048037;,
  0.858607;0.482860;0.172164;,
  0.034853;-0.999380;0.005101;,
  -0.484791;0.843816;0.230112;,
  0.187190;0.954207;0.233344;,
  -0.819155;0.560713;0.120770;,
  0.944389;0.242260;0.222351;,
  0.067132;0.997744;0.000232;,
  0.872760;0.442321;0.206502;,
  -0.639270;0.709926;0.295532;,
  0.730657;-0.023532;-0.682340;,
  -0.006612;-0.186321;-0.982467;,
  -0.629485;0.501333;0.593644;,
  0.939166;-0.137346;-0.314807;,
  0.839455;0.252783;0.481057;,
  -0.870942;0.414709;-0.263583;,
  0.942504;0.218283;0.253057;,
  -0.567878;0.678638;0.465795;,
  0.726010;-0.107649;-0.679207;,
  0.048594;0.424468;0.904138;,
  0.680254;0.221614;0.698672;,
  0.851622;0.433754;-0.294275;,
  0.234563;0.411599;0.880663;,
  -0.296769;0.788641;-0.538492;,
  0.359974;0.791244;-0.494318;,
  -0.969376;0.075659;-0.233635;,
  0.963438;0.239566;0.119984;,
  -0.927817;0.187129;0.322704;,
  0.658652;0.309804;0.685711;,
  0.952938;0.193577;0.233318;,
  0.814953;0.281638;0.506489;,
  -0.815888;0.236093;0.527813;,
  0.283909;0.278074;0.917644;,
  -0.872311;0.047086;-0.486679;,
  -0.960120;0.098697;-0.261588;,
  -0.771044;0.636693;0.010672;,
  0.983085;-0.108344;-0.147668;,
  0.391179;0.282544;0.875870;,
  0.493140;0.283265;0.822541;,
  -0.273007;0.916966;-0.290931;,
  -0.003630;0.997529;-0.070165;,
  -0.012502;0.065462;0.997777;,
  0.035586;-0.999028;-0.025998;,
  -0.775391;0.421234;-0.470459;,
  0.159931;0.977887;-0.134758;,
  0.988012;0.092319;-0.123733;,
  -0.696601;-0.338243;-0.632723;,
  -0.768931;0.011210;-0.639233;,
  0.033845;-0.999332;0.013800;,
  0.919657;0.321750;0.225184;,
  -0.510539;0.856040;0.080901;,
  -0.755932;0.653947;0.030334;,
  -0.202462;0.448517;0.870541;,
  -0.716850;0.408037;0.565360;,
  0.454207;0.006129;0.890875;,
  0.627710;0.182198;0.756825;,
  -0.774921;0.351556;-0.525268;,
  0.980786;0.185425;-0.060630;,
  -0.784692;0.436516;0.440127;,
  0.784399;0.369220;0.498392;,
  -0.972645;0.228402;0.042355;,
  0.821418;-0.206091;-0.531789;,
  0.609409;-0.312245;-0.728782;,
  0.648408;0.393433;0.651750;,
  -0.792150;0.197561;0.577466;,
  0.859064;0.335923;0.386219;,
  0.946014;0.323174;-0.024813;,
  0.725985;-0.257217;-0.637798;,
  0.415470;0.682612;0.601187;,
  0.994884;0.093450;0.038371;,
  -0.859709;-0.253136;-0.443647;,
  -0.924509;-0.381153;0.002453;,
  -0.009283;-0.273568;-0.961808;,
  -0.008526;-0.244852;-0.969523;,
  0.912180;0.250028;0.324675;,
  0.565451;-0.824515;0.020972;;
  83;
  3;0,0,0;,
  3;12,67,68;,
  4;14,15,3,1;,
  4;18,7,5,17;,
  4;19,10,3,15;,
  3;13,11,16;,
  4;69,17,5,69;,
  4;21,21,70,70;,
  4;24,20,71,71;,
  4;23,68,72,72;,
  4;73,3,10,25;,
  4;26,12,68,23;,
  4;74,27,75,74;,
  4;30,76,76,30;,
  4;30,30,21,21;,
  4;33,31,20,24;,
  4;31,6,8,32;,
  4;31,32,23,20;,
  4;34,11,5,77;,
  4;34,77,73,25;,
  4;32,35,26,23;,
  4;78,7,18,37;,
  4;78,37,79,79;,
  4;29,4,16,36;,
  4;29,36,28,22;,
  4;36,16,11,34;,
  4;36,34,25,28;,
  3;10,28,25;,
  3;13,16,4;,
  3;39,9,39;,
  4;41,46,15,14;,
  4;47,80,81,18;,
  3;82,83,17;,
  4;46,38,19,15;,
  4;43,84,75,27;,
  3;85,28,10;,
  3;40,81,86;,
  4;44,42,13,4;,
  3;44,4,29;,
  4;44,29,22,85;,
  3;48,13,42;,
  4;40,45,37,18;,
  3;87,83,87;,
  4;88,43,27,37;,
  4;48,82,17,13;,
  3;56,8,50;,
  4;52,12,2,49;,
  4;51,67,12,52;,
  4;89,90,38,46;,
  4;91,91,91,54;,
  4;53,24,67,51;,
  4;92,6,31,55;,
  3;57,93,58;,
  4;57,58,42,44;,
  4;54,94,93,57;,
  4;54,57,44,85;,
  4;58,93,32,56;,
  4;58,56,48,42;,
  4;55,33,24,53;,
  3;54,12,94;,
  3;38,10,19;,
  3;38,90,95;,
  3;96,22,28;,
  3;38,49,54;,
  3;56,97,97;,
  3;50,8,6;,
  3;55,31,33;,
  4;60,80,47,65;,
  4;60,65,56,50;,
  4;61,84,43,62;,
  4;61,62,53,98;,
  4;59,40,86,59;,
  4;59,59,92,55;,
  4;62,43,45,63;,
  4;62,99,55,53;,
  3;66,56,65;,
  4;66,65,47,48;,
  3;100,101,100;,
  4;100,100,39,39;,
  3;102,102,102;,
  4;103,103,103,103;,
  3;64,89,64;,
  4;64,64,46,41;;
 }
 MeshTextureCoords {
  134;
  0.000000;0.414770;,
  0.000000;0.000000;,
  0.209870;0.000000;,
  0.746180;0.000000;,
  0.000000;0.650070;,
  0.221530;0.544410;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.723820;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.429130;0.451540;,
  0.904080;0.218860;,
  1.000000;0.351810;,
  0.077880;0.284010;,
  0.000000;0.391960;,
  0.000000;0.246870;,
  1.000000;0.258460;,
  0.000000;0.265660;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.727150;0.418930;,
  0.723550;0.000000;,
  1.000000;0.000000;,
  1.000000;0.414770;,
  0.211990;0.725080;,
  0.209870;1.000000;,
  0.000000;1.000000;,
  0.000000;0.723550;,
  0.258460;1.000000;,
  0.000000;1.000000;,
  0.000000;0.351810;,
  0.264440;0.362430;,
  0.738270;0.727210;,
  0.746180;1.000000;,
  0.734340;1.000000;,
  0.730260;0.669970;,
  1.000000;0.650070;,
  1.000000;1.000000;,
  1.000000;0.776010;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.766100;,
  0.242000;0.426320;,
  0.245960;0.000000;,
  0.000000;0.245960;,
  0.000000;0.000000;,
  0.217580;0.000000;,
  0.215700;0.243820;,
  0.769480;0.382710;,
  1.000000;0.391960;,
  0.776010;1.000000;,
  0.724180;0.240900;,
  0.233900;1.000000;,
  0.000000;0.723820;,
  0.238050;0.706270;,
  0.764670;0.000000;,
  1.000000;0.000000;,
  1.000000;0.246870;,
  0.767320;0.229710;,
  0.266550;0.192770;,
  0.268290;0.000000;,
  0.000000;0.262465;,
  0.180335;0.142005;,
  0.000000;0.000000;,
  1.000000;0.176889;,
  1.000000;0.430010;,
  0.871690;0.176426;,
  0.000000;0.497215;,
  0.075535;0.458973;,
  0.655487;0.162232;,
  0.808693;0.086647;,
  0.728588;0.535042;,
  1.000000;0.497215;,
  0.000000;0.048270;,
  0.000000;0.173120;,
  0.137943;0.427907;,
  0.000000;0.430010;,
  0.000000;0.176889;,
  0.850731;0.238344;,
  0.720868;0.126418;,
  0.717210;0.000000;,
  1.000000;0.235330;,
  1.000000;0.731710;,
  0.864903;0.729387;,
  0.426451;0.000000;,
  0.240359;0.542651;,
  0.530717;0.059365;,
  0.700046;0.105282;,
  0.782420;0.000000;,
  0.840971;0.115716;,
  0.783938;0.052335;,
  1.000000;0.000000;,
  1.000000;0.028541;,
  0.046374;0.441908;,
  1.000000;0.945876;,
  1.000000;1.000000;,
  0.818114;0.836037;,
  0.728082;0.494189;,
  1.000000;0.465331;,
  0.000000;0.116116;,
  0.173365;0.287583;,
  0.804698;0.239274;,
  0.722053;0.167379;,
  0.817356;0.728570;,
  0.355042;0.082613;,
  0.240914;0.503285;,
  0.817735;0.782303;,
  0.904346;0.067459;,
  1.000000;0.173120;,
  0.045701;0.024135;,
  0.932452;0.818993;,
  0.353991;0.041307;,
  0.920486;0.115916;,
  1.000000;0.000000;,
  0.173259;0.357477;,
  0.862997;0.159246;,
  0.667427;0.146972;,
  1.000000;0.481865;,
  0.728352;0.515966;,
  0.149585;0.381788;,
  0.000000;0.159685;,
  0.240551;0.529023;,
  0.565240;0.062715;,
  0.659675;0.071877;,
  0.656610;0.138021;,
  0.885498;0.159303;,
  0.977491;0.159629;,
  0.160651;0.440205;,
  0.207034;0.465327;,
  0.228822;0.515883;,
  0.011163;0.476227;,
  0.023187;0.453620;,
  0.050603;0.456424;;
 }
}
