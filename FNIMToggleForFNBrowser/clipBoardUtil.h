
//ref 
//#include "clipBoardUtil.h"
//


#ifndef CLIPBOARDUTIL_HEADER_ 
#define CLIPBOARDUTIL_HEADER_ 

#include <xstring>
#include <windows.h>
#include <list>

using namespace std;
namespace FN_Browser_Help
{

	class FN_ClipboardBackup 
  {
		public:
     FN_ClipboardBackup();
			FN_ClipboardBackup(HWND hwnd);
      
			virtual ~FN_ClipboardBackup();
			BOOL Backup(HWND hwnd);
			BOOL Restore(HWND hwnd);

			struct ClipboardData {
				UINT m_nFormat;
				TCHAR m_szFormatName[100];
				UINT m_nLength;
				LPVOID m_pData;
			};
		private:
			VOID ClearBackupDatas();
			list<ClipboardData> userClipboardList;
      HWND hwnd_ref;


	};
	
    std::wstring GetClipboardText(HWND hwnd) ;
	BOOL GetClipboardTextEx(HWND hwnd, std::wstring &content);
    void  ClearClipboardText(HWND hwnd) ;
    BOOL WriteClipData(HWND hwnd, LPCTSTR buff);



};

//using namespace FN_Browser_Help;

#endif //CLIPBOARDUTIL_HEADER_ 

