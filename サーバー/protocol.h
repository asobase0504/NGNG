//=============================================================================
//
// �v���g�R��
// Author : �l�c����
//
//=============================================================================

#ifndef _PROTOCOL_H_			// ���̃}�N����`������ĂȂ�������
#define _PROTOCOL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

typedef enum
{
	COMMAND_TYPE_NONE = 0,

	COMMAND_TYPE_MOVEID,

	COMMAND_TYPE_MOVE,

	COMMAND_TYPE_GET,

	COMMAND_TYPE_POPENEMY,

	COMMAND_TYPE_GETENEMY,

	COMMAND_TYPE_SETMOVE,
	COMMAND_TYPE_MAX
}COMMAND_TYPE;

typedef enum
{
	MOVE_TYPE_NONE = 0,
	
	MOVE_TYPE_MOVEUP,
	MOVE_TYPE_MOVEDOWN,
	MOVE_TYPE_MOVELEFT,
	MOVE_TYPE_MOVERIGHT,
	MOVE_TYPE_SETMODEL,
	MOVE_TYPE_MAX
}MOVE_TYPE;


#endif
