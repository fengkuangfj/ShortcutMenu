// ShortcutMenu.h : CShortcutMenu ������

#pragma once
#include "resource.h"       // ������



#include "MyShortcutMenu_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CShortcutMenu


class ATL_NO_VTABLE CShortcutMenu :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShortcutMenu, &CLSID_ShortcutMenu>,
	public IDispatchImpl<IShortcutMenu, &IID_IShortcutMenu, &LIBID_MyShortcutMenuLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CShortcutMenu()
	{
	}

	HRESULT
		STDMETHODCALLTYPE
		Initialize(
		__in_opt PCIDLIST_ABSOLUTE	pidlFolder,
		__in_opt IDataObject *		pdtobj,
		__in_opt HKEY				hkeyProgID
		);

	HRESULT
		STDMETHODCALLTYPE
		QueryContextMenu(
		__in HMENU	hmenu,
		__in UINT	indexMenu,
		__in UINT	idCmdFirst,
		__in UINT	idCmdLast,
		__in UINT	uFlags
		);

	HRESULT
		STDMETHODCALLTYPE
		InvokeCommand(
		__in CMINVOKECOMMANDINFO *pici
		);

	HRESULT
		STDMETHODCALLTYPE
		GetCommandString(
		__in											UINT_PTR	idCmd,
		__in											UINT		uType,
		__reserved										UINT *		pReserved,
		__out_awcount(!(uType & GCS_UNICODE), cchMax)	LPSTR		pszName,
		__in											UINT		cchMax
		);

DECLARE_REGISTRY_RESOURCEID(IDR_SHORTCUTMENU)


BEGIN_COM_MAP(CShortcutMenu)
	COM_INTERFACE_ENTRY(IShortcutMenu)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT
		FinalConstruct();

	void
		FinalRelease();

public:
#define SHORTCUT_MENU_ITEM_U_1 L"ShortcutMenuItem1"
#define SHORTCUT_MENU_ITEM_U_2 L"ShortcutMenuItem2"
#define SHORTCUT_MENU_ITEM_U_3 L"ShortcutMenuItem3"
#define SHORTCUT_MENU_ITEM_A_1 "ShortcutMenuItem1"
#define SHORTCUT_MENU_ITEM_A_2 "ShortcutMenuItem2"
#define SHORTCUT_MENU_ITEM_A_3 "ShortcutMenuItem3"


	typedef enum _IDM_VERB
	{
		IDM_VERB_SHORTCUT_MENU_ITEM_SEPARATOR_1,
		IDM_VERB_SHORTCUT_MENU_ITEM_1,
		IDM_VERB_SHORTCUT_MENU_ITEM_2,
		IDM_VERB_SHORTCUT_MENU_ITEM_3,
		IDM_VERB_SHORTCUT_MENU_ITEM_SEPARATOR_2,
		IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT
	} IDM_VERB, *PIDM_VERB;


	static HBITMAP	ms_hShortcutMenuItemBmpChecked[IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT];
	static HBITMAP	ms_hShortcutMenuItemBmpUnchecked[IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT];
	static UINT		ms_uShortcutMenuItemOffset[IDM_VERB_SHORTCUT_MENU_ITEM_MAX_COUNT];
};

OBJECT_ENTRY_AUTO(__uuidof(ShortcutMenu), CShortcutMenu)
