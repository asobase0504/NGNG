//**************************************************************
//
// �}�b�v�̃w�b�_�[
// Author:Tomidokoro Tomoki
//
//**************************************************************
#ifndef _MAP_H_		//���̃}�N������`����ĂȂ�������
#define _MAP_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// �}�N���錾
//==============================================================

//==============================================================
// �O���錾
//==============================================================
class CMesh;
class CMapModel;

//==============================================================
// �}�b�v�N���X
//==============================================================
class CMap : public CTask
{
public:
	CMap();
	~CMap();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	// �ÓI�����o�֐�
	static CMap *Create();			// �}�b�v�̐���

	void Load(std::string path);

	static CMap* GetMap() { return m_map; }

	CMapModel* GetMapModel(int inNum) { return m_mapModel[inNum]; }
	int GetNumModel() { return m_mapModel.size(); }

	CMesh* GetMapMesh(int inNum) { return m_mesh[inNum]; }
	int GetNumMesh() { return m_mesh.size(); }

private:
	static CMap* m_map;
	std::vector<CMapModel*> m_mapModel;
	std::vector<CMesh*> m_mesh;
};
#endif