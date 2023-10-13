//**************************************************************
//
// precompile
// Author : Yuda Kaito
// Author : Katsuki Mizuki
// Author : Hamada Ryuuga
//
//**************************************************************
#ifndef PRECOMPILE_H_	// ���̃}�N����`������ĂȂ�������
#define PRECOMPILE_H_	// ��d�C���N���[�h�h�~�̃}�N����`

// �������[���[�N�̃`�F�b�N
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG:

// ���i�g�p�֎~
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
//#define new new
#endif // CHECK_MEM_LEAK

// ���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

// ��{
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <assert.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <locale.h>
#include <math.h>

// STL
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <functional>
#include <chrono>
#include <string>

// new�f�o�b�O�p
#pragma push_macro("new")
#undef new

// DirectX9
#include <d3dx9.h>

#pragma pop_macro("new")

// Input
#define	 DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <xinput.h>

// Json
#include "nlohmann/json.hpp"

// Debug
#include "debug_proc.h"

// Input
#include "input.h"

#endif
