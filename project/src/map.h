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
class CStatue;
class CEnemy;

//==============================================================
// �}�b�v�N���X
//==============================================================
class CMap : public CTask
{
private:
public:
	CMap();
	~CMap();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	// �ÓI�����o�֐�
	static CMap *Create(std::string);			// �}�b�v�̐���

	void Load(std::string path);

	static CMap* GetMap() { return m_map; }

	CMapModel* GetMapModel(int inNum) { return m_model[inNum]; }
	int GetNumModel() { return m_model.size(); }

	CMesh* GetMapMesh(int inNum) { return m_mesh[inNum]; }
	int GetNumMesh() { return m_mesh.size(); }

	const std::list<CStatue*> GetStatueList() const { return m_statue; }

	void InEnemyList(CEnemy* inEnemy) { m_enemy.push_back(inEnemy); }
	void InEnemyList(D3DXVECTOR3,int);
	void InEnemyList(int);

	const std::list<CEnemy*> GetEnemyList() const { return m_enemy; }

	std::string GetNextMapPath() { return m_nextMapPath; }
private:
	static CMap* m_map;

	std::string m_nextMapPath;	//���̃}�b�v

	int m_SpawnCnt;	// �G�l�~�[�̏o���^�C��

	// ���݂���Object
	std::vector<CMapModel*> m_model;
	std::vector<CMesh*> m_mesh;
	std::list<CEnemy*> m_enemy;
	std::list<CStatue*> m_statue;
};
#endif