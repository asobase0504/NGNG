//**************************************************************
//
// 言語設定
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _LETTER_H_			// このマクロ定義がされてなかったら
#define _LETTER_H_			// 二重インクルード防止のマクロ定義

//--------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------
std::string WStringToString(std::wstring oWString);
std::wstring StringToWString(std::string oString);
std::string UTF8toSjis(std::string srcUTF8);
std::string SjistoUTF8(std::string srcSjis);

#endif