//==================================================
// meshfield.h
// Author: Buriya Kota
//==================================================
#ifndef _PRECOMPILE_H_
#define _PRECOMPILE_H_

// 全てで使うヘッダのインクルード

//オンライン
#include <stdlib.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <functional>
#include <time.h>
#include <vector>
#include <stdarg.h>
#include <assert.h>

#include <d3dx9.h>
#include <Xinput.h>
#define	 DIRECTINPUT_VERSION (0x0800)	// ビルド時の警告対策用マクロ(この位置から動かさない)
#include <dinput.h>

#include <iostream>
#include <fstream>

#include <sstream> // 文字列ストリームを使用するために追加

#endif // _PRECOMPILE_H_