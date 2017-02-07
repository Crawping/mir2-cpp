/******************************************************************************************************************
                                                                                                                   
	Module Name:
																													
	Author:																											
	Date:
																													
	[Date][Modifier] : Modified contents
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	CInventoryWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	Function Name : CInventoryWnd::CInventoryWnd()

	Author : 
	Date :

	Purpose   :
	Return   :

	[Date][Modifier] : ��������

*******************************************************************************************************************/
CInventoryWnd::CInventoryWnd()
{
	Init();
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::~CInventoryWnd()

	Author : 
	Date :

	Purpose   :
	Return   :

	[Date][Modifier] : ��������

*******************************************************************************************************************/
CInventoryWnd::~CInventoryWnd()
{
	Destroy();
}


VOID CInventoryWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();
	m_nStartLineNum	= 0;
	ZeroMemory(m_rcInvenCell, sizeof(RECT) *_INVEN_MAX_CELL);
	ZeroMemory(m_rcBeltCell,  sizeof(RECT) *_BELT_MAX_CELL );
	ZeroMemory(m_stInventoryItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(m_stBeltItem,	  sizeof(ITEMSET)*_MAX_BELT_ITEM );

	m_xInvenScrlBar.Init();

	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].Init();
	}
}


VOID CInventoryWnd::Destroy()
{
	INT nCnt;
	CGameWnd::Destroy();
	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].Destroy();
	}
	Init();
}


/******************************************************************************************************************

	Function Name : CInventoryWnd::CreateInventoryWnd()

	Author : 
	Date :

	Purpose   :
	Params   : INT nID
	         CWHWilImageData* pxWndImage
	         INT nFrameImgIdx
	         INT nStartX
	         INT nStartY
	         INT nWidth
	         INT nHeight
	         BOOL bCanMove
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::CreateInventoryWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	// ������ ����.
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	// ��ư����.
	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].CreateGameBtn(pxWndImage, 280, 281, nStartX+255, nStartY+291);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLUP	 ].CreateGameBtn(pxWndImage, 74, 75, nStartX+247, nStartY+ 20);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLDOWN].CreateGameBtn(pxWndImage, 74, 75, nStartX+247, nStartY+167);
	
	m_xInvenScrlBar.CreateScrlBar(pxWndImage, 270, _INVEN_MAX_CELL_YCNT, 10, 218, 10);

	// �κ��丮 �������� Set.
	for ( INT nYCnt = 0; nYCnt < _INVEN_CELL_YCNT; nYCnt++ )
	{
		for ( INT nXCnt = 0; nXCnt < _INVEN_CELL_XCNT; nXCnt++ )
		{
			SetRect(&m_rcInvenCell[nXCnt+nYCnt*_INVEN_CELL_XCNT], 
					_INVEN_CELL_XSTART+(nXCnt*_INVENTORY_CELL_WIDTH), 
					_INVEN_CELL_YSTART+(nYCnt*_INVENTORY_CELL_HEIGHT),
					_INVEN_CELL_XSTART+(nXCnt*_INVENTORY_CELL_WIDTH) +_INVENTORY_CELL_WIDTH, 
					_INVEN_CELL_YSTART+(nYCnt*_INVENTORY_CELL_HEIGHT)+_INVENTORY_CELL_HEIGHT);
		}
	}

	// ��Ʈ �������� Set.
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		SetRect(&m_rcBeltCell[nCnt], 
				_BELT_CELL_XSTART+(nCnt*_BELT_CELL_XGAP), 
				_BELT_CELL_YSTART,
				_BELT_CELL_XSTART+(nCnt*_BELT_CELL_XGAP)+_INVENTORY_CELL_WIDTH, 
				_BELT_CELL_YSTART+_INVENTORY_CELL_HEIGHT);
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::SetInvenBtnInit()

	Author : 
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetInvenBtnInit()
{
	for( INT nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


/******************************************************************************************************************

	Function Name : CInventoryWnd::ShowInventoryWnd()

	Author : 
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ShowInventoryWnd()
{
	INT nCnt;

	// ������ �����׸���.
	ShowGameWnd();


	RECT rcTitle = {m_rcWnd.left+31, m_rcWnd.top+27, m_rcWnd.left+133, m_rcWnd.top+43};

	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(200, 200, 255), RGB(0, 0, 0), "[����â]", g_xMainWnd.CreateGameFont("�ü�ü", 10, 0, FW_BOLD));

	// ��ũ�ѹ�.
	m_xInvenScrlBar.ShowScrlBar(m_rcWnd.left+254, m_rcWnd.top-165, m_nStartLineNum, 12);
	
	// �κ��丮 ������ �׸���.
	for ( nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			INT nStartX, nStartY;

			if ( nCnt >= m_nStartLineNum*_INVEN_CELL_XCNT && nCnt < (m_nStartLineNum+_INVEN_CELL_YCNT)*_INVEN_CELL_XCNT ) 
			{
				nStartX = m_rcWnd.left+m_rcInvenCell[nCnt-(m_nStartLineNum*_INVEN_CELL_XCNT)].left;
				nStartY = m_rcWnd.top +m_rcInvenCell[nCnt-(m_nStartLineNum*_INVEN_CELL_XCNT)].top;

//				m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks = 4;
				m_stInventoryItem[nCnt].xItem.DrawItem(nStartX, nStartY);

//				RECT rc = {nStartX, nStartY, nStartX+_INVENTORY_CELL_WIDTH, nStartY+_INVENTORY_CELL_HEIGHT};
//				g_xMainWnd.DrawWithGDI(rc, NULL, RGB(255, 0, 255), 1);
			}
		}
	}

	// ��Ʈ ������ �׸���.
	for ( nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		if ( m_stBeltItem[nCnt].bSetted )
		{
			INT nStartX, nStartY;

			nStartX = m_rcWnd.left+m_rcBeltCell[nCnt].left;
			nStartY = m_rcWnd.top+m_rcBeltCell[nCnt].top;

			m_stBeltItem[nCnt].xItem.DrawItem(nStartX, nStartY);
		}
	}

	// �κ��丮 ������ ��ư �׸���.
	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].ShowGameBtn();
	}

	// �������� ����ġ �����ֱ�.
	ShowInvenItemState();	
}




/******************************************************************************************************************

	Function Name : CInventoryWnd::ShowInvenItemState()

	Author : 
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ShowInvenItemState()
{
/*	INT nInventoryNum = GetInvenNum(g_xGameProc.m_ptMousePos);
	if ( nInventoryNum != -1 )
	{
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			m_stInventoryItem[nInventoryNum].xItem.ShowItemStatus(m_rcWnd.left+95, m_rcWnd.top+250);
		}
	}
*/
	INT nInventoryNum = GetInvenNum(g_xGameProc.m_ptMousePos);
	if ( nInventoryNum != -1 )
	{
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			INT nStartX, nStartY;

			if ( nInventoryNum >= m_nStartLineNum*_INVEN_CELL_XCNT && nInventoryNum < (m_nStartLineNum+_INVEN_CELL_YCNT)*_INVEN_CELL_XCNT ) 
			{
				nStartX = m_rcWnd.left+m_rcInvenCell[nInventoryNum-(m_nStartLineNum*_INVEN_CELL_XCNT)].left;
				nStartY = m_rcWnd.top +m_rcInvenCell[nInventoryNum-(m_nStartLineNum*_INVEN_CELL_XCNT)].top;

				m_stInventoryItem[nInventoryNum].xItem.ShowItemStatus(nStartX+15, nStartY+15);
			}
		}
	}

	INT nBeltInventoryNum = GetBeltNum(g_xGameProc.m_ptMousePos);
	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			m_stBeltItem[nBeltInventoryNum].xItem.ShowItemStatus(m_rcWnd.left+95, m_rcWnd.top+250);
		}		
	}
}














/******************************************************************************************************************

	������ �ְ��� ����, �κ��丮��ġ �������� ���̺�� �ε�.(�κ��丮 �� ��Ʈ)

*******************************************************************************************************************/
/******************************************************************************************************************

	Function Name : CInventoryWnd::CheckItemPos()

	Author : 
	Date :

	Purpose   :
	Params   : CHAR* szName
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::CheckItemPos(CHAR* szName)
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];
	INT		nCnt1, nCnt2;
	ITEMSET	stInvenItem[_MAX_INVEN_ITEM];						// �ӽõ���Ÿ �ε�뺯��.
	ITEMSET	stBeltItem[_MAX_BELT_ITEM];							
	ITEMSET	stCheckedInvenItem[_MAX_INVEN_ITEM];				// �˻�� ����Ÿ �����뺯��.
	ITEMSET	stCehckedBeltItem[_MAX_BELT_ITEM];

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itm", "");

	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(stInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(stCheckedInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(stBeltItem , sizeof(ITEMSET)*_MAX_BELT_ITEM );
	ZeroMemory(stCehckedBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, &stInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM, &dwReadLen, NULL);
		ReadFile(hFile, &stBeltItem , sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwReadLen, NULL);

		// �������� ���� �κ��丮����Ÿ�� Ŭ���̾�Ʈ���� �������� �����Ų ��Ʈâ����Ÿ�� ���ϸ鼭 �´� ��ġ�� ������Ų��.
		for ( nCnt1 = 0; nCnt1 < _MAX_BELT_ITEM; nCnt1++ )
		{
			if ( stBeltItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_stInventoryItem[nCnt2].bSetted )
					{
						// ���������������� �̾Ƴ���.
						if ( stBeltItem[nCnt1].xItem.m_stItemInfo.nMakeIndex  != m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 !strcmp(stBeltItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 (stBeltItem[nCnt1].xItem.m_stItemInfo.nDura    == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura   ) &&
							 (stBeltItem[nCnt1].xItem.m_stItemInfo.nDuraMax == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax) )
						{
							stCehckedBeltItem[nCnt1] = m_stInventoryItem[nCnt2];
							ZeroMemory(&stBeltItem[nCnt1], sizeof(ITEMSET));
							DeleteInvenItem(nCnt2);
							break;
						}						   
					}
				}
			}
		} 

		memcpy(m_stBeltItem, stCehckedBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM);

		// �κ��丮.
		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( stInvenItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_stInventoryItem[nCnt2].bSetted )
					{
						// ���������������� �̾Ƴ���.
						if ( stInvenItem[nCnt1].xItem.m_stItemInfo.nMakeIndex != m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 !strcmp(stInvenItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 (stInvenItem[nCnt1].xItem.m_stItemInfo.nDura	 == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura    ) &&
							 (stInvenItem[nCnt1].xItem.m_stItemInfo.nDuraMax == m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax ) )
						{
							stCheckedInvenItem[nCnt1] = m_stInventoryItem[nCnt2];
							ZeroMemory(&stInvenItem[nCnt1], sizeof(ITEMSET));
							DeleteInvenItem(nCnt2);
							break;
						}						
					}
				}
			}
		}

		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( m_stInventoryItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( !stCheckedInvenItem[nCnt2].bSetted )
					{
						stCheckedInvenItem[nCnt2] = m_stInventoryItem[nCnt1];
						break;
					}
				}
			}
		}
		memcpy(m_stInventoryItem, stCheckedInvenItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM);

		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::SaveItemPos()

	Author : 
	Date :

	Purpose   :
	Params   : CHAR* szName
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::SaveItemPos(CHAR* szName)
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itm", "");
	hFile = CreateFile(szItemFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		WriteFile(hFile, m_stInventoryItem, sizeof(ITEMSET)*_MAX_INVEN_ITEM, &dwWriteLen, NULL);
		WriteFile(hFile, m_stBeltItem,		sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwWriteLen, NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************************************************

	Function Name : CInventoryWnd::GetInvenNum()

	Author : 
	Date :

	Purpose   : ���콺 ��ġ���� ���� �κ��丮�� ����ȣ�� ���´�.
	Params   : POINT ptMouse
	Return   : INT

	[Date][Modifier] : ��������

*******************************************************************************************************************/
INT CInventoryWnd::GetInvenNum(POINT ptMouse)
{
	RECT	rc;
	for ( INT nCnt = 0; nCnt < _INVEN_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcInvenCell[nCnt].left, m_rcWnd.top+m_rcInvenCell[nCnt].top, 
			    m_rcWnd.left+m_rcInvenCell[nCnt].left+_INVENTORY_CELL_WIDTH, m_rcWnd.top+m_rcInvenCell[nCnt].top+_INVENTORY_CELL_HEIGHT);
		if ( PtInRect(&rc, ptMouse) )
		{
			return (nCnt+m_nStartLineNum*_INVEN_CELL_XCNT);
		}
	}

	return -1;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::GetBeltNum()

	Author : 
	Date :

	Purpose   : ���콺 ��ġ���� ���� ��Ʈ�� ����ȣ�� ���´�.
	Params   : POINT ptMouse
	Return   : INT

	[Date][Modifier] : ��������

*******************************************************************************************************************/
INT CInventoryWnd::GetBeltNum(POINT ptMouse)
{
	RECT	rc;
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcBeltCell[nCnt].left, m_rcWnd.top+m_rcBeltCell[nCnt].top, 
			    m_rcWnd.left+m_rcBeltCell[nCnt].left+_INVENTORY_CELL_WIDTH, m_rcWnd.top+m_rcBeltCell[nCnt].top+_INVENTORY_CELL_HEIGHT);
		if ( PtInRect(&rc, ptMouse) )
		{
			return (nCnt);
		}
	}

	return -1;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::DeleteInventoryCurrItem()

	Author : 
	Date :

	Purpose   : �κ��丮�� �ش缿 �������� �����.
	Params   : INT nInventoryNum
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteInvenItem(INT nInventoryNum)
{
	ZeroMemory(&m_stInventoryItem[nInventoryNum], sizeof(ITEMSET));
}



VOID CInventoryWnd::DeleteInvenItem(INT nMakeIndex, CHAR* szName)
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if ( m_stInventoryItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteInvenItem(nCnt);
					break;
				}
			}
		}		
	}
}


/******************************************************************************************************************

	Function Name : CInventoryWnd::DeleteInventoryAllItem()

	Author : 
	Date :

	Purpose   : �κ��丮�� ��� �������� �����.
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteAllInvenItem()
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		ZeroMemory(&m_stInventoryItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::DeleteCurrBeltItemList()

	Author : 
	Date :

	Purpose   : ��Ʈ�� �ش缿 �������� �����.
	Params   : INT nBeltInventoryNum
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteBeltItem(INT nBeltInventoryNum)
{
	ZeroMemory(&m_stBeltItem[nBeltInventoryNum], sizeof(ITEMSET));
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::DeleteAllBeltItemList()

	Author : 
	Date :

	Purpose   : ��Ʈ�� ��� �������� �����.
	Params   : INT nBeltInventoryNum
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteAllBeltItem()
{
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		ZeroMemory(&m_stBeltItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::AddInvenItem()

	Author : 
	Date :

	Purpose   : �κ��丮�� �������� �ִ´�.
	Params   : CItem xItem
	         INT nInvenNum
	         BOOL bUseInvenNum
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::AddInvenItem(CItem xItem, INT nInvenNum, BOOL bUseInvenNum)
{
	if ( bUseInvenNum )
	{
		if ( !m_stInventoryItem[nInvenNum].bSetted )
		{
			m_stInventoryItem[nInvenNum].bSetted = TRUE;
			m_stInventoryItem[nInvenNum].xItem = xItem;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( !m_stInventoryItem[nCnt].bSetted )
		{
			m_stInventoryItem[nCnt].bSetted = TRUE;
			m_stInventoryItem[nCnt].xItem = xItem;

			return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::AddBeltItem()

	Author : 
	Date :

	Purpose   : ��Ʈ�� �������� �ִ´�.
	Params   : CItem xItem
	         INT nBeltNum
	         BOOL bUseBeltNum
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum)
{
	if ( bUseBeltNum )
	{
		if ( !m_stBeltItem[nBeltNum].bSetted )
		{
			m_stBeltItem[nBeltNum].bSetted = TRUE;
			m_stBeltItem[nBeltNum].xItem = xItem;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		if ( !m_stBeltItem[nCnt].bSetted )
		{
			m_stBeltItem[nCnt].bSetted = TRUE;
			m_stBeltItem[nCnt].xItem = xItem;

			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::ExtractInvenItem()

	Author : 
	Date :

	Purpose   : �κ��丮���� ���� ��ȣ�� �������� �̾ƿ´�.
	Params   : CItem* pxItem
	         INT nInventoryNum
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::ExtractInvenItem(CItem* pxItem, INT nInventoryNum)
{
	if ( m_stInventoryItem[nInventoryNum].bSetted )
	{
		memcpy(pxItem, &m_stInventoryItem[nInventoryNum].xItem, sizeof(CItem));
		DeleteInvenItem(nInventoryNum);
				
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::ExtractBeltItem()

	Author : 
	Date :

	Purpose   : ����â���� ���� ��ȣ�� �������� �̾ƿ´�.
	Params   : CItem* pxItem
	         INT nBeltInventoryNum
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum)
{
	if ( m_stBeltItem[nBeltInventoryNum].bSetted )
	{
		memcpy(pxItem, &m_stBeltItem[nBeltInventoryNum].xItem, sizeof(CItem));
		DeleteBeltItem(nBeltInventoryNum);
				
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::ChangeInvenWithCommon()

	Author : 
	Date :

	Purpose   : �κ��丮�� �����۰� ����(���콺)�������� �ٲ۴�.
	Params   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ChangeInvenWithCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xInvenItem;
		if ( ExtractInvenItem(&xInvenItem, nInventoryNum) )
		{
			AddInvenItem(pstCommonItemSet->xItem, nInventoryNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xInvenItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = nInventoryNum; 
		}
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::ChangeBeltWithCommon()

	Author : 
	Date :

	Purpose   : ��Ʈ�� �����۰� ����(���콺)�������� �ٲ۴�.
	Params   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xBeltItem;
		if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xBeltItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= TRUE;
			pstCommonItemSet->xItem.m_shCellNum = nBeltInventoryNum; 
		}
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::SetCommonFromInven()

	Author : 
	Date :

	Purpose   : �κ��丮�� �ش��ȣ �������� ����(���콺)���������� �����Ѵ�.
	Params   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetCommonFromInven(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xInvenItem;
	if ( ExtractInvenItem(&xInvenItem, nInventoryNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xInvenItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = nInventoryNum; 
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::SetCommonFromBelt()

	Author : 
	Date :

	Purpose   : ��Ʈâ�� �ش��ȣ �������� ����(���콺)���������� �����Ѵ�.
	Params   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xBeltItem;
	if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xBeltItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= TRUE;
		pstCommonItemSet->xItem.m_shCellNum = nBeltInventoryNum; 
	}
}	



/******************************************************************************************************************

	Function Name : CInventoryWnd::SetInvenFromCommon()

	Author : 
	Date :

	Purpose   : ����(���콺)�������� �κ��丮�� �ش��ȣ�� �����Ѵ�.
	Params   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetInvenFromCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		pstCommonItemSet->xItem.m_shCellNum = nInventoryNum;
		AddInvenItem(pstCommonItemSet->xItem, nInventoryNum, TRUE);

		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::SetBeltFromCommon()

	Author : 
	Date :

	Purpose   : ����(���콺)�������� ��Ʈâ�� �ش��ȣ�� �����Ѵ�.
	Params   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		pstCommonItemSet->xItem.m_shCellNum = nBeltInventoryNum;
		AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);

		ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
	}
}


VOID CInventoryWnd::AddNewBeltItem(LPCOMMONITEMSET pstCommonItemSet)
{
	INT nCnt;
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsBeltItem )
	{
		if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */ 
			 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
		{
			for ( nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
			{
				if ( m_stInventoryItem[nCnt].bSetted && 
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode == pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode &&
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.bShape == pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bShape && 
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.nDura == pstCommonItemSet->xItem.m_stItemInfo.nDura && 
					 m_stInventoryItem[nCnt].xItem.m_stItemInfo.nDuraMax == pstCommonItemSet->xItem.m_stItemInfo.nDuraMax )
					 
				{
					if ( !m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].bSetted )
					{
						m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].xItem = m_stInventoryItem[nCnt].xItem;
						m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].bSetted = TRUE;
						DeleteInvenItem(nCnt);
					}
					break;
				}
			}
		}			 
	}
}












/******************************************************************************************************************

	Message Function.(���콺�Է�)

*******************************************************************************************************************/
BOOL CInventoryWnd::OnKeyUp(LPCOMMONITEMSET pstCommonItemSet, WPARAM wParam, LPARAM lParam)
{
	INT nBeltInventoryNum;

	nBeltInventoryNum = -1;
	
	switch ( wParam )
	{
	case '1': 	nBeltInventoryNum = 0;		break;
	case '2': 	nBeltInventoryNum = 1;		break;
	case '3': 	nBeltInventoryNum = 2;		break;
	case '4': 	nBeltInventoryNum = 3;		break;
	case '5': 	nBeltInventoryNum = 4;		break;
	case '6': 	nBeltInventoryNum = 5;		break;
	}

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !pstCommonItemSet->bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, pstCommonItemSet);
			}
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{		
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					ChangeBeltWithCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}
		else
		{
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					 SetBeltFromCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}

		if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
		{			
			pstCommonItemSet->bWaitResponse = TRUE;
			pstCommonItemSet->bIsHideItem	= TRUE;
			g_xClientSocket.SendItemIndex(CM_EAT, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
			return TRUE;
		}
	}

	return FALSE;
}


/******************************************************************************************************************

	Function Name : CInventoryWnd::OnLButtonDown()

	Author : 
	Date :

	Purpose   :
	Params   : POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nCnt, nInventoryNum, nBeltInventoryNum;

	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].ChangeRect(m_rcWnd.left+255, m_rcWnd.top+291);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLUP	 ].ChangeRect(m_rcWnd.left+247, m_rcWnd.top+ 20);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLDOWN].ChangeRect(m_rcWnd.left+247, m_rcWnd.top+167);


	if ( m_xInvenScrlBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xInvenScrlBar.GetScrlRate();
		m_nStartLineNum = 11*fScrlRate;

		return FALSE;
	}


	for( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		if ( m_xInventoryBtn[nCnt].OnLButtonDown(ptMouse) )		
			return TRUE;
	}

	nInventoryNum	  = GetInvenNum(ptMouse);
	nBeltInventoryNum = GetBeltNum(ptMouse);

	if ( (nInventoryNum == -1 && nBeltInventoryNum == -1) )		m_bCanMove = TRUE;
	else													
	{
		if ( nInventoryNum != -1 )
		{
			if ( m_stInventoryItem[nInventoryNum].bSetted )		m_bCanMove = FALSE;
			else												m_bCanMove = TRUE;				
		}
		else if ( nBeltInventoryNum != -1 )
		{
			if ( m_stBeltItem[nInventoryNum].bSetted )			m_bCanMove = FALSE;
			else												m_bCanMove = TRUE;				
		}
	}
	
	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::OnLButtonUp()

	Author : 
	Date :

	Purpose   :
	Params   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nInventoryNum, nBeltInventoryNum;

	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].ChangeRect(m_rcWnd.left+255, m_rcWnd.top+291);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLUP	 ].ChangeRect(m_rcWnd.left+247, m_rcWnd.top+ 20);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLDOWN].ChangeRect(m_rcWnd.left+247, m_rcWnd.top+167);

	if ( m_xInvenScrlBar.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	// �κ��丮 �����츦 �ٴ´�.
	if ( m_xInventoryBtn[_BTN_ID_INVENCLOSE].OnLButtonUp(ptMouse) )
		return TRUE;

	// ��ũ�� Up, Downó��.
//	m_xInventoryBtn[_BTN_ID_INVENSCRLUP	 ].OnLButtonUp(ptMouse);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLDOWN].OnLButtonUp(ptMouse);

	nInventoryNum	  = GetInvenNum(ptMouse);
	nBeltInventoryNum = GetBeltNum(ptMouse);

	// ����(���콺)�����ۿ� ����â���� �� �������� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴ϶��, ������ ������ Off��Ų��.
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bWaitResponse )
	{
		nInventoryNum = GetInvenNum(ptMouse);
		if ( nInventoryNum != -1 )
		{
			g_xClientSocket.SendTakeOnOffItem(CM_TAKEOFFITEM, pstCommonItemSet->xItem.m_shCellNum, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex);
			pstCommonItemSet->bWaitResponse	= TRUE;
			return FALSE;
		}
	}

	// �κ��丮 ���������� Ŭ���Ѱ��.
	if ( nInventoryNum != -1 )
	{
		// Ŭ�����κ��丮�� �������� �������.
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			// ����(���콺)�����ۼ��� ���������,
			if ( !pstCommonItemSet->bSetted )
			{				  
				// ���콺�� �������� ���δ�.
				SetCommonFromInven(nInventoryNum, pstCommonItemSet);
			}
			// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�, ������������ �ƴҶ���.
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				ChangeInvenWithCommon(nInventoryNum, pstCommonItemSet);
			}
		}
		// Ŭ���� �κ��丮�� �������� �������.
		else
		{
			// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�,
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				SetInvenFromCommon(nInventoryNum, pstCommonItemSet);
			}
		}
	}

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !pstCommonItemSet->bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, pstCommonItemSet);
			}
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{		
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					ChangeBeltWithCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}
		else
		{
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				if ( /*pstCommonItemSet->xItem.m_stItemInfo.szMakeIndex[0] == 'G' && */
					 (pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					 SetBeltFromCommon(nBeltInventoryNum, pstCommonItemSet);
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::OnLButtonDoubleClick()

	Author : 
	Date :

	Purpose   :
	Params   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	Return   : BOOL

	[Date][Modifier] : ��������

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{	
	INT nInventoryNum	  = GetInvenNum(ptMouse);
	INT nBeltInventoryNum = GetBeltNum(ptMouse);

	if ( nInventoryNum != -1 )
	{
		// Ŭ�����κ��丮�� �������� �������.
		if ( m_stInventoryItem[nInventoryNum].bSetted )
		{
			// ����(���콺)�����ۼ��� ���������,
			if ( !pstCommonItemSet->bSetted )
			{				  
				// ���콺�� �������� ���δ�.
				SetCommonFromInven(nInventoryNum, pstCommonItemSet);
			}
			// ����(���콺)�����ۼ��� �ְ�, �����κ��� �����ȣ�� ��ٸ��� ���� �ƴϸ�,
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				ChangeInvenWithCommon(nInventoryNum, pstCommonItemSet);
			}
		}
	}

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !pstCommonItemSet->bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, pstCommonItemSet);
			}
			else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
			{				  
				ChangeBeltWithCommon(nBeltInventoryNum, pstCommonItemSet);
			} 
		}
	}

	if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
	{			
		pstCommonItemSet->bWaitResponse = TRUE;
		g_xClientSocket.SendItemIndex(CM_EAT, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
	}

	return TRUE;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::OnMouseMove()

	Author : 
	Date :

	Purpose   :
	Params   : POINT ptMouse
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::OnMouseMove(POINT ptMouse)
{
	m_xInventoryBtn[_BTN_ID_INVENCLOSE	 ].ChangeRect(m_rcWnd.left+255, m_rcWnd.top+291);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLUP	 ].ChangeRect(m_rcWnd.left+247, m_rcWnd.top+ 20);
//	m_xInventoryBtn[_BTN_ID_INVENSCRLDOWN].ChangeRect(m_rcWnd.left+247, m_rcWnd.top+167);

	for( INT nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
		m_xInventoryBtn[nCnt].OnMouseMove(ptMouse);
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::OnScrollDown()

	Author : 
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::OnScrollDown()
{
	if ( m_nStartLineNum > 0 )												m_nStartLineNum--;
}



/******************************************************************************************************************

	Function Name : CInventoryWnd::OnScrollUp()

	Author : 
	Date :

	Purpose   :
	Return   : VOID

	[Date][Modifier] : ��������

*******************************************************************************************************************/
VOID CInventoryWnd::OnScrollUp()
{
//	if ( m_nStartLineNum < _INVEN_MAX_CELL_YCNT - _INVEN_CELL_YCNT )		m_nStartLineNum++;
	if ( m_nStartLineNum < (_INVEN_MAX_CELL_YCNT-1) )
	{
		m_nStartLineNum++;
	}
}
