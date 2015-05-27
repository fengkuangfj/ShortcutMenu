// ShortcutMenu.cpp : CShortcutMenu 的实现

#include "stdafx.h"
#include "ShortcutMenu.h"


// CShortcutMenu


HBITMAP	CShortcutMenu::ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT]	= {0};
HBITMAP	CShortcutMenu::ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT]	= {0};
UINT	CShortcutMenu::ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT]		= {0};


HRESULT
	STDMETHODCALLTYPE
	CShortcutMenu::Initialize( 
	__in_opt PCIDLIST_ABSOLUTE	pidlFolder,
	__in_opt IDataObject *		pdtobj,
	__in_opt HKEY				hkeyProgID
	)
{
	return S_OK;
}

HRESULT
	STDMETHODCALLTYPE
	CShortcutMenu::QueryContextMenu(
	__in HMENU	hmenu,
	__in UINT	indexMenu,
	__in UINT	idCmdFirst,
	__in UINT	idCmdLast,
	__in UINT	uFlags
	)
{
	HRESULT			hRet			= E_FAIL;


	MENUITEMINFO	MenuItemInfo	= {0};
	UINT			idCmdCurrent	= 0;


	__try
	{
		idCmdCurrent = idCmdFirst;

		idCmdCurrent++;
		idCmdCurrent++;
		idCmdCurrent++;

		if (!hmenu)
			__leave;

		if ((CMF_DEFAULTONLY & uFlags))
			__leave;

		// 插入第一个分隔符
		if (idCmdCurrent > idCmdLast)
			__leave;

		MenuItemInfo.cbSize			= sizeof(MENUITEMINFO);
		MenuItemInfo.fMask			= MIIM_STATE | MIIM_TYPE | MIIM_ID;
		MenuItemInfo.fState			= MFS_ENABLED;
		MenuItemInfo.fType			= MFT_SEPARATOR;
		MenuItemInfo.wID			= idCmdCurrent++;

		if (!InsertMenuItem(
			hmenu,
			indexMenu++,
			TRUE,
			&MenuItemInfo
			))
			__leave;

		ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_SEPARATOR_1] = MenuItemInfo.wID - idCmdFirst;

		// 插入第一项
		if (idCmdCurrent > idCmdLast)
			__leave;

		memset(&MenuItemInfo, 0, sizeof(MenuItemInfo));
		MenuItemInfo.cbSize			= sizeof(MENUITEMINFO);
		MenuItemInfo.fMask			= MIIM_STATE | MIIM_STRING | MIIM_CHECKMARKS | MIIM_ID;
		MenuItemInfo.fState			= MFS_ENABLED;
		MenuItemInfo.dwTypeData		= SHORTCUT_MENU_ITEM_U_1;
		MenuItemInfo.hbmpChecked	= ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_1];
		MenuItemInfo.hbmpUnchecked	= ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_1];
		MenuItemInfo.wID			= idCmdCurrent++;

		if (!InsertMenuItem(
			hmenu,
			indexMenu++,
			TRUE,
			&MenuItemInfo
			))
			__leave;

		ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_1] = MenuItemInfo.wID - idCmdFirst;

		// 插入第二项
		if (idCmdCurrent > idCmdLast)
			__leave;

		memset(&MenuItemInfo, 0, sizeof(MenuItemInfo));
		MenuItemInfo.cbSize			= sizeof(MENUITEMINFO);
		MenuItemInfo.fMask			= MIIM_STATE | MIIM_STRING | MIIM_ID;
		MenuItemInfo.fState			= MFS_ENABLED;
		MenuItemInfo.dwTypeData		= SHORTCUT_MENU_ITEM_U_2;
		MenuItemInfo.wID			= idCmdCurrent++;

		if (!InsertMenuItem(
			hmenu,
			indexMenu++,
			TRUE,
			&MenuItemInfo
			))
			__leave;

		ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_2] = MenuItemInfo.wID - idCmdFirst;

		// 插入第三项
		if (idCmdCurrent > idCmdLast)
			__leave;

		memset(&MenuItemInfo, 0, sizeof(MenuItemInfo));
		MenuItemInfo.cbSize			= sizeof(MENUITEMINFO);
		MenuItemInfo.fMask			= MIIM_STATE | MIIM_STRING | MIIM_CHECKMARKS | MIIM_FTYPE | MIIM_ID;
		MenuItemInfo.fState			= MFS_CHECKED | MFS_ENABLED;
		MenuItemInfo.dwTypeData		= SHORTCUT_MENU_ITEM_U_3;
		MenuItemInfo.hbmpChecked	= NULL;
		MenuItemInfo.hbmpUnchecked	= ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_3];
		MenuItemInfo.fType			= MFT_RADIOCHECK;
		MenuItemInfo.wID			= idCmdCurrent++;

		if (!InsertMenuItem(
			hmenu,
			indexMenu++,
			TRUE,
			&MenuItemInfo
			))
			__leave;

		ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_3] = MenuItemInfo.wID - idCmdFirst;

		// 插入第二个分隔符
		if (idCmdCurrent > idCmdLast)
			__leave;

		memset(&MenuItemInfo, 0, sizeof(MenuItemInfo));
		MenuItemInfo.cbSize			= sizeof(MENUITEMINFO);
		MenuItemInfo.fMask			= MIIM_STATE | MIIM_TYPE | MIIM_ID;
		MenuItemInfo.fState			= MFS_ENABLED;
		MenuItemInfo.fType			= MFT_SEPARATOR;
		MenuItemInfo.wID			= idCmdCurrent++;

		if (!InsertMenuItem(
			hmenu,
			indexMenu++,
			TRUE,
			&MenuItemInfo
			))
			__leave;

		ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_SEPARATOR_2] = MenuItemInfo.wID - idCmdFirst;

		// 设置返回值
		hRet = MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(idCmdCurrent - idCmdFirst));
	}
	__finally
	{
		;
	}

	return hRet;
}

HRESULT
	STDMETHODCALLTYPE
	CShortcutMenu::InvokeCommand(
	__in CMINVOKECOMMANDINFO *pici
	)
{
	HRESULT					hRet					= E_FAIL;

	CMINVOKECOMMANDINFOEX * pCmInvokeCommandInfoEx	= NULL;


	__try
	{
		if (!pici)
			__leave;

		if (CMIC_MASK_UNICODE & pici->fMask)
		{
			if (pici->cbSize != sizeof(CMINVOKECOMMANDINFOEX))
				__leave;

			pCmInvokeCommandInfoEx = (CMINVOKECOMMANDINFOEX *)pici;

			if (HIWORD(pCmInvokeCommandInfoEx->lpVerbW))
			{
				if (0 != StrCmpIW(pCmInvokeCommandInfoEx->lpVerbW, SHORTCUT_MENU_ITEM_U_1))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_1, SHORTCUT_MENU_ITEM_U_1, MB_OK);
				else if (0 != StrCmpIW(pCmInvokeCommandInfoEx->lpVerbW, SHORTCUT_MENU_ITEM_U_2))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_2, SHORTCUT_MENU_ITEM_U_2, MB_OK);
				else if (0 != StrCmpIW(pCmInvokeCommandInfoEx->lpVerbW, SHORTCUT_MENU_ITEM_U_3))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_3, SHORTCUT_MENU_ITEM_U_3, MB_OK);
			}
			else
			{
				if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_1] == LOWORD(pCmInvokeCommandInfoEx->lpVerb))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_1, SHORTCUT_MENU_ITEM_U_1, MB_OK);
				else if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_2] == LOWORD(pCmInvokeCommandInfoEx->lpVerb))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_2, SHORTCUT_MENU_ITEM_U_2, MB_OK);
				else if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_3] == LOWORD(pCmInvokeCommandInfoEx->lpVerb))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_3, SHORTCUT_MENU_ITEM_U_3, MB_OK);
			}
		}
		else
		{
			if (HIWORD(pici->lpVerb))
			{
				if (0 != StrCmpIA(pici->lpVerb, SHORTCUT_MENU_ITEM_A_1))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_1, SHORTCUT_MENU_ITEM_U_1, MB_OK);
				else if (0 != StrCmpIA(pici->lpVerb, SHORTCUT_MENU_ITEM_A_2))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_2, SHORTCUT_MENU_ITEM_U_2, MB_OK);
				else if (0 != StrCmpIA(pici->lpVerb, SHORTCUT_MENU_ITEM_A_3))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_3, SHORTCUT_MENU_ITEM_U_3, MB_OK);
			}
			else
			{
				if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_1] == LOWORD(pici->lpVerb))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_1, SHORTCUT_MENU_ITEM_U_1, MB_OK);
				else if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_2] == LOWORD(pici->lpVerb))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_2, SHORTCUT_MENU_ITEM_U_2, MB_OK);
				else if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_3] == LOWORD(pici->lpVerb))
					MessageBox(NULL, SHORTCUT_MENU_ITEM_U_3, SHORTCUT_MENU_ITEM_U_3, MB_OK);
			}
		}

		hRet = S_OK;
	}
	__finally
	{
		;
	}

	return hRet;
}

HRESULT
	STDMETHODCALLTYPE
	CShortcutMenu::GetCommandString(
	__in											UINT_PTR	idCmd,
	__in											UINT		uType,
	__reserved										UINT *		pReserved,
	__out_awcount(!(uType & GCS_UNICODE), cchMax)	LPSTR		pszName,
	__in											UINT		cchMax
	)
{
	HRESULT hRet = E_FAIL;


	__try
	{
		if (pReserved || !pszName)
			__leave;

		if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_1] == idCmd ||
			ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_2] == idCmd ||
			ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_3] == idCmd)
		{
			switch (uType)
			{
			case GCS_HELPTEXTA:
				break;
			case GCS_HELPTEXTW:
				{
					if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_1] == idCmd)
						StringCchCopyW(reinterpret_cast<PWSTR>(pszName), cchMax, L"ShortcutMenuItem1_HelpText");
					else if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_2] == idCmd)
						StringCchCopyW(reinterpret_cast<PWSTR>(pszName), cchMax, L"ShortcutMenuItem2_HelpText");
					else
						StringCchCopyW(reinterpret_cast<PWSTR>(pszName), cchMax, L"ShortcutMenuItem3_HelpText");

					break; 	
				}
			case GCS_VERBA:
				break; 		
			case GCS_VERBW:
				{
					if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_1] == idCmd)
						StringCchCopyW(reinterpret_cast<PWSTR>(pszName), cchMax, L"ShortcutMenuItem1_Verb");
					else if (ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_2] == idCmd)
						StringCchCopyW(reinterpret_cast<PWSTR>(pszName), cchMax, L"ShortcutMenuItem2_Verb");
					else
						StringCchCopyW(reinterpret_cast<PWSTR>(pszName), cchMax, L"ShortcutMenuItem3_Verb");

					break; 
				}
			case GCS_VALIDATEA:
			case GCS_VALIDATEW:
				__leave;
			default:
				__leave;
			}
		}

		hRet = S_OK;
	}
	__finally
	{
		;
	}

	return hRet;
}

HRESULT
	CShortcutMenu::FinalConstruct()
{
	HRESULT		hRet		= E_FAIL;

	HINSTANCE	hInstance	= NULL;


	__try
	{
		hInstance = _AtlBaseModule.GetModuleInstance();
		if (!hInstance)
			__leave;

		ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_1] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDI_ICON_SHORTCUT_MENU_ITEM_1));
		if (!ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_1])
			__leave;

		ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_1] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDI_ICON_SHORTCUT_MENU_ITEM_1));
		if (!ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_1])
			__leave;

		ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_2] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDI_ICON_SHORTCUT_MENU_ITEM_2));
		if (!ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_2])
			__leave;

		ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_2] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDI_ICON_SHORTCUT_MENU_ITEM_2));
		if (!ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_2])
			__leave;

		ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_3] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDI_ICON_SHORTCUT_MENU_ITEM_3));
		if (!ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_3])
			__leave;

		ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_3] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDI_ICON_SHORTCUT_MENU_ITEM_3));
		if (!ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_3])
			__leave;

		hRet = S_OK;
	}
	__finally
	{
		if (S_OK != hRet)
			FinalRelease();
	}

	return hRet;
}

void
	CShortcutMenu::FinalRelease()
{
	int i = 0;


	while (i++ < IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT)
	{
		if (ms_hShortcutMenuItemBmpChecked[i])
		{
			DeleteObject(ms_hShortcutMenuItemBmpChecked[i]);
			ms_hShortcutMenuItemBmpChecked[i] = NULL;
		}

		if (ms_hShortcutMenuItemBmpUnchecked[i])
		{
			DeleteObject(ms_hShortcutMenuItemBmpUnchecked[i]);
			ms_hShortcutMenuItemBmpUnchecked[i] = NULL;
		}

		ms_uShortcutMenuItemOffset[i] = 0;
	}

	return;
}