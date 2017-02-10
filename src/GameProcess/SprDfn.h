#ifndef _SPRITEDEF_H
#define _SPRITEDEF_H



/******************************************************************************************************************

	Actor Sprite Frame Define

*******************************************************************************************************************/

//~~~ Hero�� ����, NPC�� ���� FrameDefinition. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct tagSPRFRMDEF
{
	WORD		wFstFrm;						// Action�� ���� Frame.
	WORD		wFrmCnt;						// Action�� FrameNumber.
	WORD		wDelay;							// Action�� �����ð�.
}SPRFRMDEF, *LPSPRFRMDEF;


/******************************************************************************************************************

	Effect Sprite Frame Define

*******************************************************************************************************************/

//~~~ Spell�� ���� FrameDefinition. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct tagEFFECTSPRINFO
{
	DWORD		dwFstFrm;
	DWORD		dwEndFrm;
	WORD		wDelay;
	WORD		wImgIdx;
	WORD		wEffectIdx;
	BYTE		bLightRadius[2];				// ���� �ʺ�.
	BYTE		bLightColor [2][3];				// ���� ��.
	BYTE		bMagicColor [3];				// Spell ��.
	BYTE		bBlendType;
	BYTE		bOpa;
	BYTE		bSwingCnt;
}EFFECTSPRINFO, *LPEFFECTSPRINFO;


class CSprite
{
public:
	EFFECTSPRINFO		m_stEffectSpr[_MAX_EFFECT];			// Spell�� ������ �˹�ȿ��.
	EFFECTSPRINFO		m_stMagicSpr[_MAX_MAGIC];			// Spellȿ��.
	EFFECTSPRINFO		m_stExplosionSpr[_MAX_EXPLOSION];	// Spell����ȿ��.

	EFFECTSPRINFO		m_stMonEffectSpr[_MAX_EFFECT];			// Spell�� ������ �˹�ȿ��.
	EFFECTSPRINFO		m_stMonMagicSpr[_MAX_MAGIC];			// Spellȿ��.
	EFFECTSPRINFO		m_stMonExplosionSpr[_MAX_EXPLOSION];	// Spell����ȿ��.


	SPRFRMDEF			m_stHeroSpr[_MAX_HERO_MTN];			// Hero�� ActionFrame Definition.
	SPRFRMDEF			m_stMonSpr [_MAX_MON_MTN];			// Monster�� ActionFrame Definition.
	SPRFRMDEF			m_stNPCSpr [_MAX_MON_MTN];			// Monster�� ActionFrame Definition.

	BYTE				m_bWOrder[_MAX_HERO_REALFRAME];	

public:
	CSprite();
	~CSprite();

	VOID InitSpriteInfo();
	VOID DeleteSpriteInfo();

	VOID SetInfo();

	VOID SetSprDfn(LPSPRFRMDEF pstSprDfn, WORD wFstFrm, WORD wFrmCnt, WORD wDelay);

	VOID SetEffectInfo(LPEFFECTSPRINFO pstEffect, DWORD dwFstFrm, DWORD dwEndFrm, WORD wDelay, WORD wImgIdx, WORD wEffectIdx,
					   BYTE bSLightRadius, BYTE bLLightRadius, 
					   BYTE bSLightRColor, BYTE bSLightGColor, BYTE bSLightBColor,
					   BYTE bLLightRColor, BYTE bLLightGColor, BYTE bLLightBColor, 
					   BYTE bMagicRColor = 255, BYTE bMagicGColor = 255, BYTE bMagicBColor = 255, 
					   BYTE bBlendType = _BLEND_LIGHTINV, BYTE bOpa = 0, BYTE bSwingCnt = 0);

	LPEFFECTSPRINFO GetEffectInfo(WORD wEffectNum);
	LPEFFECTSPRINFO GetExplosionInfo(WORD wEffectNum);
	LPEFFECTSPRINFO GetMagicInfo(WORD wEffectNum);

	VOID			SetMonFrameInfo(WORD wMonNum);

	BOOL			SetWeaponOrder(CHAR* szFileName);
};



#endif //_SPRITEDEF_H



















