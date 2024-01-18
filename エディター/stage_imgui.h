//**************************************************
// 
// particle_imgui.h
// Author  : katsuki mizuki
// Author  : Yuda Kaito
// 
//**************************************************
#ifndef _STAGE_IMGUI_H_	// ���̃}�N������`����ĂȂ�������
#define _STAGE_IMGUI_H_	// 2�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "imgui_property.h"


class CMapModel;
//--------------------------------------------------
// �p�[�e�B�N���p��Imgui�\���N���X
//--------------------------------------------------
class CStageImgui : public CImguiProperty
{
public:
	enum DATATYPE
	{
		ENEMY = 0,		// Enemy
		MODEL,			// ���f��
		MESH,			// Mesh
		MAX			//���񂽂����H
	};

private:	
	

	// ��`
	struct Pendulum
	{
		int type;
		float coefficient;
		D3DXVECTOR3 destRot;
	};

	struct Ball
	{
		int rotType;
		float radius;
		float  rotSpeed;
	};

	struct Wood
	{
		int coolTime;
		float rot;
		float rotSpeed;
		float move;
	};

	static const int D3DXyz = 3;//XYZ�������p
public:
	CStageImgui();
	~CStageImgui();

	HWND Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice) override;
	void Uninit(HWND hWnd, WNDCLASSEX wcex) override;
	bool Update() override;
	void Draw() override;

	int GetMesh() const { return m_sliderIntmesh; }
	int GetModel() const { return m_sliderIntmodel; }
	int GetEnemy() const { return m_sliderIntEnemy; }

	int GetModelEnemy() const { return m_indexEnemy; }
	
	Ball GetBall() const { return m_Ball; }
	Wood GetWood() const { return m_Wood; }
	Pendulum GetPendulum() const { return m_Pendulum; }

	void Imguigold();
	void ImguiEnemy();
	void ImguiChangenumber(std::string number,int Number);

	int selectModel();
	bool GetAnimati();

	const D3DXVECTOR3& GetRot() { return D3DXVECTOR3(m_sliderRot3[0], m_sliderRot3[1], m_sliderRot3[2]); }
	const D3DXVECTOR3& GetPosV() { return D3DXVECTOR3(m_PosVSet[0], m_PosVSet[1], m_PosVSet[2]); }
	const D3DXVECTOR3& GetPosR() { return D3DXVECTOR3(m_PosRSet[0], m_PosRSet[1], m_PosRSet[2]); }


	const D3DXVECTOR3& GetposRDest() { return D3DXVECTOR3(m_posRDest[0], m_posRDest[1], m_posRDest[2]); }
	const D3DXVECTOR3& GetposVDest() { return D3DXVECTOR3(m_posVDest[0], m_posVDest[1], m_posVDest[2]); }
	const D3DXVECTOR3& GetDistance() { return D3DXVECTOR3(m_fDistance[0], m_fDistance[1], m_fDistance[2]); }

	std::string GetPass() { return m_CameraAnimationPass; }

	std::string Getfile() { return m_SavefileNeme; }
	

	void SetVtx(int inx,int Llst) { m_Vtx[Llst] = inx; }
	
private: // �v���C�x�[�g�֐�
	void TaskBarUpdate();
	void EditMesh();
	void EditModel();
	void EditCamera();
	void EditEnemy();

	void EditPlayer();
	void ImguiCreate();
	void Imguifilecord();
	void ImguiPlarer();


	void funcFileSave(HWND hWnd);
	void funcFileLoad(HWND hWnd, CStageImgui::DATATYPE Mode);
private: // �����o�[�ϐ�

	const int MeshMax = 100;
	static const int	MAX_TEXT = 1024;		// �e�L�X�g�̍ő啶����
	const char*	WINDOW_NAME = "test";	// �E�C���h�E�̖��O (�L���v�V�����ɕ\��)

	D3DXVECTOR3 sliderRot;			// mesh�̉�]��肽������....

	bool m_Gura = false;			// �d��
	bool m_MoveIron = false;		// �S���������Ȃ��ݒ�i�X�N���[���o�[�j
	Ball m_Ball;					// �ݒu����Ball�̕\�����i�󂯎�锠�j
	Pendulum m_Pendulum;			// �ݒu����Pendulum�̕\�����i�󂯎�锠�j
	Wood m_Wood;					// �ݒu����Wood�̕\�����i�󂯎�锠�j	

	int m_sliderIntmodel;

	int m_indexBuilding = 0;			// �ҏW���������f���̕\��ID�i�R���{�{�b�N�X�j
	int m_indexEmemy = 0;			// �ҏW���������f���̕\��ID�i�R���{�{�b�N�X�j

	std::string m_NowModelName;		// �ݒu�������f���̕\�����i�R���{�{�b�N�X�j
	float m_sliderPos3[3];			// ��]����^�}�̍��W�i�󂯎�锠�j	
	float m_sliderRot3[3];			// ��]����^�}�̉�]�i�󂯎�锠�j	
	float m_sliderNowRot3[3];			// ��]����^�}�̉�]�i�󂯎�锠�j	
	float m_PosVSet[3];			// ���R�̎����W�ݒ肷��悤	
	float m_PosRSet[3];			// ���R�̎����W�ݒ肷��悤	
	float m_sliderPlayerPos[3];			// �v���C���[�̈ʒu�i�󂯎�锠�j	


	int m_sliderIntmesh;					// mesh��Type�I���i�X�N���[���o�[�j
	int m_sliderIntEnemy = 0;				// Enemy��Type�I���i�X�N���[���o�[�j
	signed int m_indexModel = 0;			// �ҏW���������f���̕\��ID�i�R���{�{�b�N�X�j
	signed int m_indexTex = 0;				// �ҏW�������e�N�X�`���̕\��ID�i�R���{�{�b�N�X�j
	signed int m_indexNouEnemy;				//�ҏW�������G�l�~�[�̕\��ID�i�R���{�{�b�N�X�j
	signed int m_indexmeshAnimation = 0;	// �ҏW���������b�V���̃A�j���[�V�����ԍ��\��ID�i�R���{�{�b�N�X�j
	signed int m_indexmeshNumber = 0;		// �ҏW���������b�V���̔ԍ��̕\��ID�i�R���{�{�b�N�X�j

	signed int m_indexCamera = 0;			// �ҏW�������J����Animation�̔ԍ��̕\��ID�i�R���{�{�b�N�X�j
	signed int m_indexCameraAnimation = 0;	// �ҏW�������J����Animation�̒��̍��W�ԍ��̕\��ID�i�R���{�{�b�N�X�j

	signed int m_indexEnemy = 0;				// �ҏW������teki�̕\��ID�i�R���{�{�b�N�X�j

	signed int m_indexEnemyBoss = 0;				// �ҏW������BOSS�A�j���[�V�����̕\��ID�i�R���{�{�b�N�X�j
	std::string m_NowMeshName;				// �ҏW������mesh�̕\�����i�R���{�{�b�N�X�j
	std::string m_NowEnemyName;				// �ҏW�������G�l�~�[�̕\�����i�R���{�{�b�N�X�j
	std::string m_NowMeshNumberName;			// �ҏW�������A�j���[�V����Number�̕\�����i�R���{�{�b�N�X�j
	std::string m_NowCameraNumberName;		// �ҏW������CameraNumber�̕\�����i�R���{�{�b�N�X�j
	std::string m_NowCameraAnimationNumberName;	// �ҏW������Camera�A�j���[�V����Number�̕\�����i�R���{�{�b�N�X�j
	std::string m_CameraAnimationPass;		// �ҏW������Camera�A�j���[�V����Number�̕\�����i�j

	std::string m_BossAnime;
	std::string m_SavefileNeme;		// Save������file���i�j

	bool m_Animation = false;					// �A�j���[�V�������邩���Ȃ���
	bool m_Izing = false;
	
	int m_KeySet;


	//�J�����̃v���C���[�Ǐ]�@�\�̕ҏW
	float m_posRDest[3];			// ���R�̎����W�ݒ肷��悤	
	float m_posVDest[3];			// ���R�̎����W�ݒ肷��悤	
	float m_fDistance[3];			//�Ȃ񂱂�

	int m_BossAnimation;
	int m_BossAnimationType = 0;

	int m_BossKeySet = 0;

	int m_Vtx[3];

	std::vector<bool> m_list;
	D3DXVECTOR3 m_PlayerPos;

	
	CMapModel*m_model;
	
};

#endif // !_IMGUI_PROPERTY_H_
