// dllmain.h : 模块类的声明。

class CMyShortcutMenuModule : public ATL::CAtlDllModuleT< CMyShortcutMenuModule >
{
public :
	DECLARE_LIBID(LIBID_MyShortcutMenuLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYSHORTCUTMENU, "{8B9180B5-5FC0-4084-9468-A5DC70816DB1}")
};

extern class CMyShortcutMenuModule _AtlModule;
