/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IFNIMToggle.idl
 */

#ifndef __gen_IFNIMToggle_h__
#define __gen_IFNIMToggle_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsISimpleEnumerator_h__
#include "nsISimpleEnumerator.h"
#endif

#ifndef __gen_nsIArray_h__
#include "nsIArray.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIWebBrowser; /* forward declaration */

class nsIDOMElement; /* forward declaration */

class nsIDOMEventListener; /* forward declaration */

class nsIObserver; /* forward declaration */

//IFNIMToggleEngine
#define FN_IM_TOGGLE_ENGINE_CONTRACTID "@fntechnologies.com/imtoggle/engine;1"
#define FN_IM_TOGGLE_ENGINE_CLASSNAME  "FN IM toggle Engine"
//{55AD9AD9-28C2-4ef4-92CC-AC4FBE3D7476}
#define FN_IM_TOGGLE_ENGINE_CID { 0x55ad9ad9, 0x28c2, 0x4ef4, { 0x92, 0xcc, 0xac, 0x4f, 0xbe, 0x3d, 0x74, 0x76 } }
//IFNIMToggleApplication
#define FN_IM_TOGGLE_APPLICATION_CONTRACTID "@fntechnologies.com/imtoggle/application;1"
#define FN_IM_TOGGLE_APPLICATION_CLASSNAME  "FN IM Toggle Application"
//{AF8BA177-A959-4128-A861-DA38FF55E66B}
#define FN_IM_TOGGLE_APPLICTAION_CID { 0xaf8ba177, 0xa959, 0x4128, { 0xa8, 0x61, 0xda, 0x38, 0xff, 0x55, 0xe6, 0x6b } }
//IFNIMToggleApplication2
#define FN_IM_TOGGLE_APPLICATION2_CONTRACTID "@fntechnologies.com/imtoggle/application;2"
#define FN_IM_TOGGLE_APPLICATION2_CLASSNAME  "FN IM Toggle Application2"
// {232A4ADA-74D4-431f-ADE3-32D68CE89323}
#define FN_IM_TOGGLE_APPLICTAION2_CID { 0x232a4ada, 0x74d4, 0x431f, { 0xad, 0xe3, 0x32, 0xd6, 0x8c, 0xe8, 0x93, 0x23 } }
//IFNIMToggleApplicationTrait
#define FN_IM_TOGGLE_APPLICATIONTRAIT_CONTRACTID "@fntechnologies.com/imtoggle/applicationtrait;1"
#define FN_IM_TOGGLE_APPLICATIONTRAIT_CLASSNAME  "FN IM Toggle Application Trait"
// {B6092702-AEE3-471c-A692-40CF1AF250CD}
#define FN_IM_TOGGLE_APPLICTAIONTRAIT_CID { 0xb6092702, 0xaee3, 0x471c, { 0xa6, 0x92, 0x40, 0xcf, 0x1a, 0xf2, 0x50, 0xcd } }
//IFNIMToggleApplicationUserAccount
#define FN_IM_TOGGLE_APPLICATIONUSERACCOUNT_CONTRACTID "@fntechnologies.com/imtoggle/useraccount;1"
#define FN_IM_TOGGLE_APPLICATIONUSERACCOUNT_CLASSNAME  "FN IM Toggle User Account"
// {E2AE5CD5-895B-4628-A874-AFC58D66C579}
#define FN_IM_TOGGLE_APPLICATIONUSERACCOUNT_CID { 0xe2ae5cd5, 0x895b, 0x4628, { 0xa8, 0x74, 0xaf, 0xc5, 0x8d, 0x66, 0xc5, 0x79 } }
//IFNIMToggleChatSession
#define FN_IM_TOGGLE_CHAT_SESSION_CONTRACTID "@fntechnologies.com/imtoggle/chatsession;1"
#define FN_IM_TOGGLE_CHAT_SESSION_CLASSNAME  "FN IM Toggle Chat Session"
//{1C103DD5-67B1-4089-87BD-584472910AEC}
#define FN_IM_TOGGLE_CHAT_SESSION_CID { 0x1c103dd5, 0x67b1, 0x4089, { 0x87, 0xbd, 0x58, 0x44, 0x72, 0x91, 0xa, 0xec } }
//IFNIMToggleChatSessionContactor
#define FN_IM_TOGGLE_CHAT_SESSIONCONTACTOR_CONTRACTID "@fntechnologies.com/imtoggle/chatsession/contactor;1"
#define FN_IM_TOGGLE_CHAT_SESSIONCONTACTOR_CLASSNAME  "FN IM Toggle Chat Session Contactor"
// {D48CE837-CB9E-4e51-8CE1-C5684B9676E6}
#define FN_IM_TOGGLE_CHAT_SESSIONCONTACTOR_CID { 0xd48ce837, 0xcb9e, 0x4e51, { 0x8c, 0xe1, 0xc5, 0x68, 0x4b, 0x96, 0x76, 0xe6 } }
//IFNIMToggleChatSessionMainWindow
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOW_CONTRACTID "@fntechnologies.com/imtoggle/chatsessionMainWindow;1"
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOW_CLASSNAME  "FN IM Toggle Chat Session MainWindow"
//{22F09D6C-0DCB-4a57-B2DA-BE19C8A652CA}
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOW_CID { 0x22f09d6c, 0xdcb, 0x4a57, { 0xb2, 0xda, 0xbe, 0x19, 0xc8, 0xa6, 0x52, 0xca } }
//IFNIMToggleChatInputWindow
#define FN_IM_TOGGLE_CHAT_INPUTWINDOW_CONTRACTID "@fntechnologies.com/imtoggle/chatinputwindow;1"
#define FN_IM_TOGGLE_CHAT_INPUTWINDOW_CLASSNAME  "FN IM Toggle chat inputwindow"
//{75082F28-9DF5-4fd9-8188-4079020B9C1D}
#define FN_IM_TOGGLE_CHAT_INPUTWINDOW_CID { 0x75082f28, 0x9df5, 0x4fd9, { 0x81, 0x88, 0x40, 0x79, 0x2, 0xb, 0x9c, 0x1d } }
//IFNIMToggleChatReadWindow
#define FN_IM_TOGGLE_CHAT_READWINDOW_CONTRACTID "@fntechnologies.com/imtoggle/chatreadwindow;1"
#define FN_IM_TOGGLE_CHAT_READWINDOW_CLASSNAME  "FN IM Toggle chat readwindow"
//{26E940E4-FF36-451c-818D-100182B78F02}
#define FN_IM_TOGGLE_CHAT_READWINDOW_CID { 0x26e940e4, 0xff36, 0x451c, { 0x81, 0x8d, 0x10, 0x1, 0x82, 0xb7, 0x8f, 0x2 } }
//
//IFNIMToggleIMApplicationHandler
#define FN_IM_TOGGLE_IMAPPLICATION_HANDLER_CONTRACTID "@fntechnologies.com/imtoggle/imapplicationhandler;1"
#define FN_IM_TOGGLE_IMAPPLICATION_HANDLER_CLASSNAME  "FN IM Toggle IMApplication handler"
//{75B12F70-E748-4a82-8426-2A2806B448A9}
#define FN_IM_TOGGLE_IMAPPLICATION_HANDLER_CID { 0x75b12f70, 0xe748, 0x4a82, { 0x84, 0x26, 0x2a, 0x28, 0x6, 0xb4, 0x48, 0xa9 } }
//IFNIMToggleChatSessionHandler
#define FN_IM_TOGGLE_CHAT_SESSION_HANDLER_CONTRACTID "@fntechnologies.com/imtoggle/chatsessionhandler;1"
#define FN_IM_TOGGLE_CHAT_SESSION_HANDLER_CLASSNAME  "FN IM Toggle Chat Session handler"
//{0A812783-F3CE-4c25-AABF-4BB94F47F3F3}
#define FN_IM_TOGGLE_CHAT_SESSION_HANDLER_CID { 0xa812783, 0xf3ce, 0x4c25, { 0xaa, 0xbf, 0x4b, 0xb9, 0x4f, 0x47, 0xf3, 0xf3 } }
//IFNIMToggleButton
#define FN_IM_TOGGLE_BUTTON_CONTRACTID "@fntechnologies.com/imtoggle/button;1"
#define FN_IM_TOGGLE_BUTTON_CLASSNAME  "FN IM Toggle button"
//{A87AE301-9F65-4a22-B7A9-770CD8009931}
#define FN_IM_TOGGLE_BUTTON_CID { 0xa87ae301, 0x9f65, 0x4a22, { 0xb7, 0xa9, 0x77, 0xc, 0xd8, 0x0, 0x99, 0x31 } }
//IFNIMToggleChatFNInputWindow
#define FN_IM_TOGGLE_CHAT_FNINPUTWINDOW_CONTRACTID "@fntechnologies.com/imtoggle/chatfninputwindow;1"
#define FN_IM_TOGGLE_CHAT_FNINPUTWINDOW_CLASSNAME  "FN IM Toggle chat fninputwindow"
//{3ACD8379-D245-4ce6-9EE9-A58137ED146A}
#define FN_IM_TOGGLE_CHAT_FNINPUTWINDOW_CID { 0x3acd8379, 0xd245, 0x4ce6, { 0x9e, 0xe9, 0xa5, 0x81, 0x37, 0xed, 0x14, 0x6a } }
//IFNIMToggleChatFNReadWindow
#define FN_IM_TOGGLE_CHAT_FNREADWINDOW_CONTRACTID "@fntechnologies.com/imtoggle/chatfnreadwindow;1"
#define FN_IM_TOGGLE_CHAT_FNREADWINDOW_CLASSNAME  "FN IM Toggle chat fnreadwindow"
//{9C617DEB-C9D8-4306-ACA1-40F353B51D6D}
#define FN_IM_TOGGLE_CHAT_FNREADWINDOW_CID { 0x9c617deb, 0xc9d8, 0x4306, { 0xac, 0xa1, 0x40, 0xf3, 0x53, 0xb5, 0x1d, 0x6d } }
//IFNIMToggleChatFNMainWindow
#define FN_IM_TOGGLE_CHAT_FNMAINWINDOW_CONTRACTID "@fntechnologies.com/imtoggle/chatfnmainwindow;1"
#define FN_IM_TOGGLE_CHAT_FNMAINWINDOW_CLASSNAME  "FN IM Toggle chat fnmainwindow"
// {B313F5CE-3DC2-497e-8439-348190AE0648}
#define FN_IM_TOGGLE_CHAT_FNMAINWINDOW_CID { 0xb313f5ce, 0x3dc2, 0x497e, { 0x84, 0x39, 0x34, 0x81, 0x90, 0xae, 0x6, 0x48 } }
//IFNIMToggleChatFNInput
#define FN_IM_TOGGLE_CHAT_FNINPUT_CONTRACTID "@fntechnologies.com/imtoggle/chatfninput;1"
#define FN_IM_TOGGLE_CHAT_FNINPUT_CLASSNAME  "FN IM Toggle chat fninput"
//{0319D312-445E-4635-8034-1A6CAB546955}
#define FN_IM_TOGGLE_CHAT_FNINPUT_CID {  0x319d312, 0x445e, 0x4635, { 0x80, 0x34, 0x1a, 0x6c, 0xab, 0x54, 0x69, 0x55 }  }
//IFNIMToggleChatFNReader
#define FN_IM_TOGGLE_CHAT_FNREAD_CONTRACTID "@fntechnologies.com/imtoggle/chatfnreader;1"
#define FN_IM_TOGGLE_CHAT_FNREAD_CLASSNAME  "FN IM Toggle chat fnreader"
// {8B0899BA-ECAF-4036-9811-18DB3FE6EF1B}
#define FN_IM_TOGGLE_CHAT_FNREAD_CID { 0x8b0899ba, 0xecaf, 0x4036, { 0x98, 0x11, 0x18, 0xdb, 0x3f, 0xe6, 0xef, 0x1b } }
//IFNIMToggleChatSessionCreator
#define FN_IM_TOGGLE_CHAT_SESSIONCREATOR_CONTRACTID "@fntechnologies.com/imtoggle/chatsessionCreator;1"
#define FN_IM_TOGGLE_CHAT_SESSIONCREATOR_CLASSNAME  "FN IM Toggle Chat Session MainWindow Locator"
// {8CF757A1-456E-4fa1-A605-4806B7F253AE}
#define FN_IM_TOGGLE_CHAT_SESSIONCREATOR_CID { 0x8cf757a1, 0x456e, 0x4fa1, { 0xa6, 0x5, 0x48, 0x6, 0xb7, 0xf2, 0x53, 0xae } }
//IFNIMToggleChatSessionMainWindowLocator
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOWLOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/chatsessionMainWindowLocator;1"
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOWLOCATOR_CLASSNAME  "FN IM Toggle Chat Session MainWindow Locator"
// {49DCFF77-443F-4a92-AC45-7C98038C0422}
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOWLOCATOR_CID { 0x49dcff77, 0x443f, 0x4a92, { 0xac, 0x45, 0x7c, 0x98, 0x3, 0x8c, 0x4, 0x22 } }
//IFNIMToggleChatSessionMainWindowLocator_InProcess
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOWLOCATOR_INPROCESS_CONTRACTID "@fntechnologies.com/imtoggle/chatsessionMainWindowLocator/inprocess;1"
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOWLOCATOR_INPROCESS_CLASSNAME  "FN IM Toggle Chat Session MainWindow Locator in Process"
// {93FE0515-122C-4f2b-BEA4-660B6D97BDBC}
#define FN_IM_TOGGLE_CHAT_SESSION_MAINWINDOWLOCATOR_INPROCESS_CID { 0x93fe0515, 0x122c, 0x4f2b, { 0xbe, 0xa4, 0x66, 0xb, 0x6d, 0x97, 0xbd, 0xbc} }
//IFNIMToggleChatInputWindowLocator
#define FN_IM_TOGGLE_CHAT_INPUTWINDOWLocator_CONTRACTID "@fntechnologies.com/imtoggle/chatinputwindowLocator;1"
#define FN_IM_TOGGLE_CHAT_INPUTWINDOWLocator_CLASSNAME  "FN IM Toggle chat inputwindow Locator"
// {15F4BB7C-743F-421d-BAC6-71E2A384C268}
#define FN_IM_TOGGLE_CHAT_INPUTWINDOWLocator_CID { 0x15f4bb7c, 0x743f, 0x421d, { 0xba, 0xc6, 0x71, 0xe2, 0xa3, 0x84, 0xc2, 0x68 } }
//IFNIMToggleChatReadWindowLocator
#define FN_IM_TOGGLE_CHAT_READWINDOWLOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/chatreadwindowLocator;1"
#define FN_IM_TOGGLE_CHAT_READWINDOWLOCATOR_CLASSNAME  "FN IM Toggle chat readwindow Locator"
// {9A8DB503-FD48-4b8c-ACAF-5AECA21FCAFF}
#define FN_IM_TOGGLE_CHAT_READWINDOWLOCATOR_CID { 0x9a8db503, 0xfd48, 0x4b8c, { 0xac, 0xaf, 0x5a, 0xec, 0xa2, 0x1f, 0xca, 0xff } }
//IFNIMToggleChatFNMainWindowLocator
#define FN_IM_TOGGLE_CHAT_FNREADWINDOWLOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/chatfnmainwindowLocator;1"
#define FN_IM_TOGGLE_CHAT_FNREADWINDOWLOCATOR_CLASSNAME  "FN IM Toggle chat fnmainwindow Locator"
//{A49ACAE7-A8D8-44bd-89AD-957A3048DE08}
#define FN_IM_TOGGLE_CHAT_FNMAINWINDOWLOCATOR_CID { 0xa49acae7, 0xa8d8, 0x44bd, { 0x89, 0xad, 0x95, 0x7a, 0x30, 0x48, 0xde, 0x8 } }
//IFNIMToggleButtonLocator
#define FN_IM_TOGGLE_BUTTONLOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/buttonLocator;1"
#define FN_IM_TOGGLE_BUTTONLOCATOR_CLASSNAME  "FN IM Toggle button Locator"
//{E5857E0C-01A3-48ae-91D4-B5BDDF868AF7}
#define FN_IM_TOGGLE_BUTTONLOCATOR_CID { 0xe5857e0c, 0x1a3, 0x48ae, { 0x91, 0xd4, 0xb5, 0xbd, 0xdf, 0x86, 0x8a, 0xf7 } }
//interface IFNIMToggleChatFNReadWindowLocator;
#define FN_IM_TOGGLE_CHATFNREADWINDOWLOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/chatfnreadwindowlocator;1"
#define FN_IM_TOGGLE_CHATFNREADWINDOWLOCATOR_CLASSNAME  "FN IM Toggle chat fnreadwindow locator"
// {3A107F8E-1D8E-46c3-9378-0324E329F3FD}
#define FN_IM_TOGGLE_CHATFNREADWINDOWLOCATOR_CID {0x3a107f8e, 0x1d8e, 0x46c3, { 0x93, 0x78, 0x3, 0x24, 0xe3, 0x29, 0xf3, 0xfd } }
//IFNIMToggleChatFNInputWindowLocator
#define FN_IM_TOGGLE_CHATFNINPUTWINDOWLOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/chatfninputwindowlocator;1"
#define FN_IM_TOGGLE_CHATFNINPUTWINDOWLOCATOR_CLASSNAME  "FN IM Toggle chat fninputwindow locator"
// {FE626D08-5082-4d69-BB97-9E66E1CE76E6}
#define FN_IM_TOGGLE_CHATFNINPUTWINDOWLOCATOR_CID {0xfe626d08, 0x5082, 0x4d69, { 0xbb, 0x97, 0x9e, 0x66, 0xe1, 0xce, 0x76, 0xe6 } }
//IFNIMToggleButtonEvnetListener
#define FN_IM_TOGGLE_BUUTONEVENTLISTENER_CONTRACTID "@fntechnologies.com/imtoggle/buttonevnetlistener;1"
#define FN_IM_TOGGLE_BUUTONEVENTLISTENER_CLASSNAME  "FN IM Toggle button evnet listener"
// {8E69D738-3955-4b8f-A4E4-3D73FE580F17}
#define FN_IM_TOGGLE_BUUTONEVENTLISTENER_CID { 0x8e69d738, 0x3955, 0x4b8f, { 0xa4, 0xe4, 0x3d, 0x73, 0xfe, 0x58, 0xf, 0x17 } }
//IFNIMWindowDestroyEvnetListener
#define FN_IM_TOGGLE_DESTROYEVNETLISTENER_CONTRACTID "@fntechnologies.com/imtoggle/destroyeventlistener;1"
#define FN_IM_TOGGLE_DESTROYEVNETLISTENER_CLASSNAME  "FN IM Toggle destroy event listener"
// {546EA08D-E4D6-4e45-9372-A1D0EF838962}IFNIMWindowDestroyEvnetListener
#define FN_IM_TOGGLE_DESTROYEVNETLISTENER_CID { 0x546ea08d, 0xe4d6, 0x4e45, { 0x93, 0x72, 0xa1, 0xd0, 0xef, 0x83, 0x89, 0x62 } }
//IFNIMSendInvitation
#define FN_IM_TOGGLE_SENDINVITATION_CONTRACTID "@fntechnologies.com/imtoggle/sendinvitation;1"
#define FN_IM_TOGGLE_SENDINVITATION_CLASSNAME  "FN IM Toggle sendinvitation"
// {7EA0F550-4FA7-4d47-894F-76D5B7495AB1} IFNIMSendInvitation
#define FN_IM_TOGGLE_SENDINVITATION_CID {  0x7ea0f550, 0x4fa7, 0x4d47, { 0x89, 0x4f, 0x76, 0xd5, 0xb7, 0x49, 0x5a, 0xb1 } }
//IFNIMWindowCreator
#define FN_IM_TOGGLE_WINDOWCREATOR_CONTRACTID "@fntechnologies.com/imtoggle/WindowCreator;1"
#define FN_IM_TOGGLE_WINDOWCREATOR_CLASSNAME  "FN IM Toggle Window Creator"
// {B8638490-09BD-45f2-A4BA-AAF29AC7E9E9} IFNIMWindowCreator
#define FN_IM_TOGGLE_WINDOWCREATOR_CID {  0xb8638490, 0x9bd, 0x45f2, { 0xa4, 0xba, 0xaa, 0xf2, 0x9a, 0xc7, 0xe9, 0xe9 } }
#define FN_IM_TOGGLE_WINDOW_LOCATOR_CONTRACTID "@fntechnologies.com/imtoggle/WindowLocator;1"
#define FN_IM_TOGGLE_WINDOW_LOCATOR_CLASSNAME  "FN IM Toggle Window Locator"
// {850EF326-0C87-4a9d-8CD0-F02816CD1340} IFNIMWindowLocator
#define FN_IM_TOGGLE_WINDOW_LOCATOR_CID {  0x850ef326, 0xc87, 0x4a9d, { 0x8c, 0xd0, 0xf0, 0x28, 0x16, 0xcd, 0x13, 0x40 } }
class IFNIMWindowLocator; /* forward declaration */

class IFNIMToggleChatSession; /* forward declaration */

class IFNIMToggleChatSessionCreator; /* forward declaration */

class IFNIMToggleChatSessionContactor; /* forward declaration */

class IFNIMToggleApplication; /* forward declaration */

class IFNIMToggleApplicationTrait; /* forward declaration */

class IFNIMToggleApplicationUserAccount; /* forward declaration */

class IFNIMToggleChatFNMainWindowLocator; /* forward declaration */

class IFNIMToggleChatFNMainWindow; /* forward declaration */

class IFNIMToggleChatFNReader; /* forward declaration */

class IFNIMToggleChatFNInput; /* forward declaration */

class IFNIMToggleChatFNReadWindowLocator; /* forward declaration */

class IFNIMToggleChatFNInputWindowLocator; /* forward declaration */

class IFNIMToggleChatReadWindowLocator; /* forward declaration */

class IFNIMToggleChatInputWindowLocator; /* forward declaration */

class IFNIMToggleChatSessionMainWindowLocator; /* forward declaration */

class IFNIMToggleButtonEvnetListener; /* forward declaration */

class IFNIMWindowDestroyEvnetListener; /* forward declaration */


/* starting interface:    IFNIMWindowLocator */
#define IFNIMWINDOWLOCATOR_IID_STR "850ef326-0c87-4a9d-8cd0-f02816cd1340"

#define IFNIMWINDOWLOCATOR_IID \
  {0x850ef326, 0x0c87, 0x4a9d, \
    { 0x8c, 0xd0, 0xf0, 0x28, 0x16, 0xcd, 0x13, 0x40 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMWindowLocator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMWINDOWLOCATOR_IID)

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* void locate (); */
  NS_SCRIPTABLE NS_IMETHOD Locate(void) = 0;

  /* void syncPosition (); */
  NS_SCRIPTABLE NS_IMETHOD SyncPosition(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMWindowLocator, IFNIMWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMWINDOWLOCATOR \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD Locate(void); \
  NS_SCRIPTABLE NS_IMETHOD SyncPosition(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Locate(void) { return _to Locate(); } \
  NS_SCRIPTABLE NS_IMETHOD SyncPosition(void) { return _to SyncPosition(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Locate(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Locate(); } \
  NS_SCRIPTABLE NS_IMETHOD SyncPosition(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->SyncPosition(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void locate (); */
NS_IMETHODIMP _MYCLASS_::Locate()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void syncPosition (); */
NS_IMETHODIMP _MYCLASS_::SyncPosition()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatInputWindow */
#define IFNIMTOGGLECHATINPUTWINDOW_IID_STR "75082f28-9df5-4fd9-8188-4079020b9c1d"

#define IFNIMTOGGLECHATINPUTWINDOW_IID \
  {0x75082f28, 0x9df5, 0x4fd9, \
    { 0x81, 0x88, 0x40, 0x79, 0x02, 0x0b, 0x9c, 0x1d }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatInputWindow : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATINPUTWINDOW_IID)

  /* attribute PRUint32 m_hWnd; */
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) = 0;

  /* attribute PRUint32 parentWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) = 0;

  /* attribute AString classname; */
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) = 0;

  /* attribute AString caption; */
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) = 0;

  /* attribute AString content; */
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent) = 0;

  /* void submit (); */
  NS_SCRIPTABLE NS_IMETHOD Submit(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatInputWindow, IFNIMTOGGLECHATINPUTWINDOW_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATINPUTWINDOW \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname); \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname); \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption); \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption); \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent); \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent); \
  NS_SCRIPTABLE NS_IMETHOD Submit(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATINPUTWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return _to GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return _to SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return _to GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return _to SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) { return _to GetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) { return _to SetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) { return _to GetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) { return _to SetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) { return _to GetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent) { return _to SetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD Submit(void) { return _to Submit(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATINPUTWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD Submit(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Submit(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatInputWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATINPUTWINDOW

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatInputWindow)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute PRUint32 m_hWnd; */
NS_IMETHODIMP _MYCLASS_::GetM_hWnd(PRUint32 *aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetM_hWnd(PRUint32 aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRUint32 parentWindow; */
NS_IMETHODIMP _MYCLASS_::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString classname; */
NS_IMETHODIMP _MYCLASS_::GetClassname(nsAString & aClassname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetClassname(const nsAString & aClassname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString caption; */
NS_IMETHODIMP _MYCLASS_::GetCaption(nsAString & aCaption)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCaption(const nsAString & aCaption)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString content; */
NS_IMETHODIMP _MYCLASS_::GetContent(nsAString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetContent(const nsAString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void submit (); */
NS_IMETHODIMP _MYCLASS_::Submit()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatReadWindow */
#define IFNIMTOGGLECHATREADWINDOW_IID_STR "26e940e4-ff36-451c-818d-100182b78f02"

#define IFNIMTOGGLECHATREADWINDOW_IID \
  {0x26e940e4, 0xff36, 0x451c, \
    { 0x81, 0x8d, 0x10, 0x01, 0x82, 0xb7, 0x8f, 0x02 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatReadWindow : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATREADWINDOW_IID)

  /* attribute PRUint32 m_hWnd; */
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) = 0;

  /* attribute PRUint32 parentWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) = 0;

  /* attribute AString classname; */
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) = 0;

  /* attribute AString caption; */
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) = 0;

  /* readonly attribute AString content; */
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatReadWindow, IFNIMTOGGLECHATREADWINDOW_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATREADWINDOW \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname); \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname); \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption); \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption); \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATREADWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return _to GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return _to SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return _to GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return _to SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) { return _to GetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) { return _to SetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) { return _to GetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) { return _to SetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) { return _to GetContent(aContent); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATREADWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContent(aContent); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatReadWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATREADWINDOW

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatReadWindow)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute PRUint32 m_hWnd; */
NS_IMETHODIMP _MYCLASS_::GetM_hWnd(PRUint32 *aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetM_hWnd(PRUint32 aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRUint32 parentWindow; */
NS_IMETHODIMP _MYCLASS_::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString classname; */
NS_IMETHODIMP _MYCLASS_::GetClassname(nsAString & aClassname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetClassname(const nsAString & aClassname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString caption; */
NS_IMETHODIMP _MYCLASS_::GetCaption(nsAString & aCaption)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCaption(const nsAString & aCaption)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString content; */
NS_IMETHODIMP _MYCLASS_::GetContent(nsAString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNInputWindow */
#define IFNIMTOGGLECHATFNINPUTWINDOW_IID_STR "3acd8379-d245-4ce6-9ee9-a58137ed146a"

#define IFNIMTOGGLECHATFNINPUTWINDOW_IID \
  {0x3acd8379, 0xd245, 0x4ce6, \
    { 0x9e, 0xe9, 0xa5, 0x81, 0x37, 0xed, 0x14, 0x6a }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNInputWindow : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNINPUTWINDOW_IID)

  /* attribute PRUint32 m_hWnd; */
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) = 0;

  /* attribute PRUint32 parentWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) = 0;

  /* attribute IFNIMToggleChatInputWindow origianlInputWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlInputWindow(IFNIMToggleChatInputWindow * *aOrigianlInputWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlInputWindow(IFNIMToggleChatInputWindow * aOrigianlInputWindow) = 0;

  /* void submit (); */
  NS_SCRIPTABLE NS_IMETHOD Submit(void) = 0;

  /* void show (in boolean show); */
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) = 0;

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* void focus (); */
  NS_SCRIPTABLE NS_IMETHOD Focus(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNInputWindow, IFNIMTOGGLECHATFNINPUTWINDOW_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNINPUTWINDOW \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlInputWindow(IFNIMToggleChatInputWindow * *aOrigianlInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlInputWindow(IFNIMToggleChatInputWindow * aOrigianlInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD Submit(void); \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show); \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD Focus(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNINPUTWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return _to GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return _to SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return _to GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return _to SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlInputWindow(IFNIMToggleChatInputWindow * *aOrigianlInputWindow) { return _to GetOrigianlInputWindow(aOrigianlInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlInputWindow(IFNIMToggleChatInputWindow * aOrigianlInputWindow) { return _to SetOrigianlInputWindow(aOrigianlInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD Submit(void) { return _to Submit(); } \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) { return _to Show(show); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Focus(void) { return _to Focus(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNINPUTWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlInputWindow(IFNIMToggleChatInputWindow * *aOrigianlInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOrigianlInputWindow(aOrigianlInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlInputWindow(IFNIMToggleChatInputWindow * aOrigianlInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOrigianlInputWindow(aOrigianlInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD Submit(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Submit(); } \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) { return !_to ? NS_ERROR_NULL_POINTER : _to->Show(show); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Focus(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Focus(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNInputWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNINPUTWINDOW

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNInputWindow)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute PRUint32 m_hWnd; */
NS_IMETHODIMP _MYCLASS_::GetM_hWnd(PRUint32 *aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetM_hWnd(PRUint32 aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRUint32 parentWindow; */
NS_IMETHODIMP _MYCLASS_::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatInputWindow origianlInputWindow; */
NS_IMETHODIMP _MYCLASS_::GetOrigianlInputWindow(IFNIMToggleChatInputWindow * *aOrigianlInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetOrigianlInputWindow(IFNIMToggleChatInputWindow * aOrigianlInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void submit (); */
NS_IMETHODIMP _MYCLASS_::Submit()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void show (in boolean show); */
NS_IMETHODIMP _MYCLASS_::Show(PRBool show)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void focus (); */
NS_IMETHODIMP _MYCLASS_::Focus()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNReadWindow */
#define IFNIMTOGGLECHATFNREADWINDOW_IID_STR "9c617deb-c9d8-4306-aca1-40f353b51d6d"

#define IFNIMTOGGLECHATFNREADWINDOW_IID \
  {0x9c617deb, 0xc9d8, 0x4306, \
    { 0xac, 0xa1, 0x40, 0xf3, 0x53, 0xb5, 0x1d, 0x6d }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNReadWindow : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNREADWINDOW_IID)

  /* attribute PRUint32 m_hWnd; */
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) = 0;

  /* attribute PRUint32 parentWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) = 0;

  /* attribute IFNIMToggleChatReadWindow origianlReadWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlReadWindow(IFNIMToggleChatReadWindow * *aOrigianlReadWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlReadWindow(IFNIMToggleChatReadWindow * aOrigianlReadWindow) = 0;

  /* attribute AString content; */
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent) = 0;

  /* void show (in boolean show); */
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) = 0;

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* void appendContent (in AString content); */
  NS_SCRIPTABLE NS_IMETHOD AppendContent(const nsAString & content) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNReadWindow, IFNIMTOGGLECHATFNREADWINDOW_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNREADWINDOW \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlReadWindow(IFNIMToggleChatReadWindow * *aOrigianlReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlReadWindow(IFNIMToggleChatReadWindow * aOrigianlReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent); \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent); \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show); \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD AppendContent(const nsAString & content); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNREADWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return _to GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return _to SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return _to GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return _to SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlReadWindow(IFNIMToggleChatReadWindow * *aOrigianlReadWindow) { return _to GetOrigianlReadWindow(aOrigianlReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlReadWindow(IFNIMToggleChatReadWindow * aOrigianlReadWindow) { return _to SetOrigianlReadWindow(aOrigianlReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) { return _to GetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent) { return _to SetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) { return _to Show(show); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD AppendContent(const nsAString & content) { return _to AppendContent(content); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNREADWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetParentWindow(PRUint32 *aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetParentWindow(PRUint32 aParentWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetParentWindow(aParentWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetOrigianlReadWindow(IFNIMToggleChatReadWindow * *aOrigianlReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOrigianlReadWindow(aOrigianlReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetOrigianlReadWindow(IFNIMToggleChatReadWindow * aOrigianlReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOrigianlReadWindow(aOrigianlReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & aContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContent(aContent); } \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) { return !_to ? NS_ERROR_NULL_POINTER : _to->Show(show); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD AppendContent(const nsAString & content) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendContent(content); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNReadWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNREADWINDOW

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNReadWindow)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute PRUint32 m_hWnd; */
NS_IMETHODIMP _MYCLASS_::GetM_hWnd(PRUint32 *aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetM_hWnd(PRUint32 aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRUint32 parentWindow; */
NS_IMETHODIMP _MYCLASS_::GetParentWindow(PRUint32 *aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetParentWindow(PRUint32 aParentWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatReadWindow origianlReadWindow; */
NS_IMETHODIMP _MYCLASS_::GetOrigianlReadWindow(IFNIMToggleChatReadWindow * *aOrigianlReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetOrigianlReadWindow(IFNIMToggleChatReadWindow * aOrigianlReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString content; */
NS_IMETHODIMP _MYCLASS_::GetContent(nsAString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetContent(const nsAString & aContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void show (in boolean show); */
NS_IMETHODIMP _MYCLASS_::Show(PRBool show)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void appendContent (in AString content); */
NS_IMETHODIMP _MYCLASS_::AppendContent(const nsAString & content)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSessionMainWindow */
#define IFNIMTOGGLECHATSESSIONMAINWINDOW_IID_STR "22f09d6c-0dcb-4a57-b2da-be19c8a652ca"

#define IFNIMTOGGLECHATSESSIONMAINWINDOW_IID \
  {0x22f09d6c, 0x0dcb, 0x4a57, \
    { 0xb2, 0xda, 0xbe, 0x19, 0xc8, 0xa6, 0x52, 0xca }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSessionMainWindow : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSIONMAINWINDOW_IID)

  /* attribute PRUint32 m_hWnd; */
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) = 0;

  /* attribute AString classname; */
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) = 0;

  /* attribute AString caption; */
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) = 0;

  /* nsIArray findoutWindow (); */
  NS_SCRIPTABLE NS_IMETHOD FindoutWindow(nsIArray **_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSessionMainWindow, IFNIMTOGGLECHATSESSIONMAINWINDOW_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOW \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname); \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname); \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption); \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption); \
  NS_SCRIPTABLE NS_IMETHOD FindoutWindow(nsIArray **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSIONMAINWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return _to GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return _to SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) { return _to GetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) { return _to SetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) { return _to GetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) { return _to SetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD FindoutWindow(nsIArray **_retval) { return _to FindoutWindow(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSIONMAINWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD SetM_hWnd(PRUint32 aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassname(nsAString & aClassname) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassname(const nsAString & aClassname) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClassname(aClassname); } \
  NS_SCRIPTABLE NS_IMETHOD GetCaption(nsAString & aCaption) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD SetCaption(const nsAString & aCaption) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCaption(aCaption); } \
  NS_SCRIPTABLE NS_IMETHOD FindoutWindow(nsIArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->FindoutWindow(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSessionMainWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOW

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSessionMainWindow)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute PRUint32 m_hWnd; */
NS_IMETHODIMP _MYCLASS_::GetM_hWnd(PRUint32 *aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetM_hWnd(PRUint32 aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString classname; */
NS_IMETHODIMP _MYCLASS_::GetClassname(nsAString & aClassname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetClassname(const nsAString & aClassname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString caption; */
NS_IMETHODIMP _MYCLASS_::GetCaption(nsAString & aCaption)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCaption(const nsAString & aCaption)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIArray findoutWindow (); */
NS_IMETHODIMP _MYCLASS_::FindoutWindow(nsIArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleButton */
#define IFNIMTOGGLEBUTTON_IID_STR "a87ae301-9f65-4a22-b7a9-770cd8009931"

#define IFNIMTOGGLEBUTTON_IID \
  {0xa87ae301, 0x9f65, 0x4a22, \
    { 0xb7, 0xa9, 0x77, 0x0c, 0xd8, 0x00, 0x99, 0x31 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleButton : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEBUTTON_IID)

  /* readonly attribute PRUint32 m_hWnd; */
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) = 0;

  /* attribute boolean state; */
  NS_SCRIPTABLE NS_IMETHOD GetState(PRBool *aState) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetState(PRBool aState) = 0;

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* boolean createNew (in PRUint32 parent, in PRInt32 left, in PRInt32 top, in PRUint32 w, in PRUint32 h, in PRUint32 style, in PRUint32 exStyle); */
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) = 0;

  /* void addToggleEventListener (in IFNIMToggleButtonEvnetListener listener); */
  NS_SCRIPTABLE NS_IMETHOD AddToggleEventListener(IFNIMToggleButtonEvnetListener *listener) = 0;

  /* void addDestroyEvnetListener (in IFNIMWindowDestroyEvnetListener listener); */
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleButton, IFNIMTOGGLEBUTTON_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEBUTTON \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd); \
  NS_SCRIPTABLE NS_IMETHOD GetState(PRBool *aState); \
  NS_SCRIPTABLE NS_IMETHOD SetState(PRBool aState); \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval); \
  NS_SCRIPTABLE NS_IMETHOD AddToggleEventListener(IFNIMToggleButtonEvnetListener *listener); \
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEBUTTON(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return _to GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetState(PRBool *aState) { return _to GetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD SetState(PRBool aState) { return _to SetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) { return _to CreateNew(parent, left, top, w, h, style, exStyle, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddToggleEventListener(IFNIMToggleButtonEvnetListener *listener) { return _to AddToggleEventListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener) { return _to AddDestroyEvnetListener(listener); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEBUTTON(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetM_hWnd(PRUint32 *aM_hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetM_hWnd(aM_hWnd); } \
  NS_SCRIPTABLE NS_IMETHOD GetState(PRBool *aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD SetState(PRBool aState) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetState(aState); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateNew(parent, left, top, w, h, style, exStyle, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddToggleEventListener(IFNIMToggleButtonEvnetListener *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddToggleEventListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDestroyEvnetListener(listener); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleButton
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEBUTTON

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleButton)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* readonly attribute PRUint32 m_hWnd; */
NS_IMETHODIMP _MYCLASS_::GetM_hWnd(PRUint32 *aM_hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean state; */
NS_IMETHODIMP _MYCLASS_::GetState(PRBool *aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetState(PRBool aState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean createNew (in PRUint32 parent, in PRInt32 left, in PRInt32 top, in PRUint32 w, in PRUint32 h, in PRUint32 style, in PRUint32 exStyle); */
NS_IMETHODIMP _MYCLASS_::CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addToggleEventListener (in IFNIMToggleButtonEvnetListener listener); */
NS_IMETHODIMP _MYCLASS_::AddToggleEventListener(IFNIMToggleButtonEvnetListener *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addDestroyEvnetListener (in IFNIMWindowDestroyEvnetListener listener); */
NS_IMETHODIMP _MYCLASS_::AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSessionCreator */
#define IFNIMTOGGLECHATSESSIONCREATOR_IID_STR "8cf757a1-456e-4fa1-a605-4806b7f253ae"

#define IFNIMTOGGLECHATSESSIONCREATOR_IID \
  {0x8cf757a1, 0x456e, 0x4fa1, \
    { 0xa6, 0x05, 0x48, 0x06, 0xb7, 0xf2, 0x53, 0xae }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSessionCreator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSIONCREATOR_IID)

  /* IFNIMToggleChatSession createSession (); */
  NS_SCRIPTABLE NS_IMETHOD CreateSession(IFNIMToggleChatSession **_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSessionCreator, IFNIMTOGGLECHATSESSIONCREATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSIONCREATOR \
  NS_SCRIPTABLE NS_IMETHOD CreateSession(IFNIMToggleChatSession **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSIONCREATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD CreateSession(IFNIMToggleChatSession **_retval) { return _to CreateSession(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSIONCREATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD CreateSession(IFNIMToggleChatSession **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateSession(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSessionCreator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONCREATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSessionCreator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* IFNIMToggleChatSession createSession (); */
NS_IMETHODIMP _MYCLASS_::CreateSession(IFNIMToggleChatSession **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSession */
#define IFNIMTOGGLECHATSESSION_IID_STR "1c103dd5-67b1-4089-87bd-584472910aec"

#define IFNIMTOGGLECHATSESSION_IID \
  {0x1c103dd5, 0x67b1, 0x4089, \
    { 0x87, 0xbd, 0x58, 0x44, 0x72, 0x91, 0x0a, 0xec }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSession : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSION_IID)

  /* attribute IFNIMToggleApplication applictaion; */
  NS_SCRIPTABLE NS_IMETHOD GetApplictaion(IFNIMToggleApplication * *aApplictaion) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetApplictaion(IFNIMToggleApplication * aApplictaion) = 0;

  /* attribute IFNIMToggleButton toggleButton; */
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton) = 0;

  /* attribute IFNIMToggleChatReadWindow readWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetReadWindow(IFNIMToggleChatReadWindow * *aReadWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetReadWindow(IFNIMToggleChatReadWindow * aReadWindow) = 0;

  /* attribute IFNIMToggleChatInputWindow inputWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetInputWindow(IFNIMToggleChatInputWindow * *aInputWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInputWindow(IFNIMToggleChatInputWindow * aInputWindow) = 0;

  /* attribute IFNIMToggleChatFNInputWindow fnInputWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNInputWindow * *aFnInputWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNInputWindow * aFnInputWindow) = 0;

  /* attribute IFNIMToggleChatFNReadWindow fnReadWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNReadWindow * *aFnReadWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNReadWindow * aFnReadWindow) = 0;

  /* IFNIMToggleChatSessionMainWindow getMainWindow (); */
  NS_SCRIPTABLE NS_IMETHOD GetMainWindow(IFNIMToggleChatSessionMainWindow **_retval) = 0;

  /* void setMainwindowHandle (in PRUint32 hwnd); */
  NS_SCRIPTABLE NS_IMETHOD SetMainwindowHandle(PRUint32 hwnd) = 0;

  /* boolean exist (); */
  NS_SCRIPTABLE NS_IMETHOD Exist(PRBool *_retval) = 0;

  /* void addToggleButton (); */
  NS_SCRIPTABLE NS_IMETHOD AddToggleButton(void) = 0;

  /* void showFNWidnows (in boolean show); */
  NS_SCRIPTABLE NS_IMETHOD ShowFNWidnows(PRBool show) = 0;

  /* void submit (); */
  NS_SCRIPTABLE NS_IMETHOD Submit(void) = 0;

  /* void quit (); */
  NS_SCRIPTABLE NS_IMETHOD Quit(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSession, IFNIMTOGGLECHATSESSION_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSION \
  NS_SCRIPTABLE NS_IMETHOD GetApplictaion(IFNIMToggleApplication * *aApplictaion); \
  NS_SCRIPTABLE NS_IMETHOD SetApplictaion(IFNIMToggleApplication * aApplictaion); \
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton); \
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton); \
  NS_SCRIPTABLE NS_IMETHOD GetReadWindow(IFNIMToggleChatReadWindow * *aReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetReadWindow(IFNIMToggleChatReadWindow * aReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetInputWindow(IFNIMToggleChatInputWindow * *aInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetInputWindow(IFNIMToggleChatInputWindow * aInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNInputWindow * *aFnInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNInputWindow * aFnInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNReadWindow * *aFnReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNReadWindow * aFnReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetMainWindow(IFNIMToggleChatSessionMainWindow **_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetMainwindowHandle(PRUint32 hwnd); \
  NS_SCRIPTABLE NS_IMETHOD Exist(PRBool *_retval); \
  NS_SCRIPTABLE NS_IMETHOD AddToggleButton(void); \
  NS_SCRIPTABLE NS_IMETHOD ShowFNWidnows(PRBool show); \
  NS_SCRIPTABLE NS_IMETHOD Submit(void); \
  NS_SCRIPTABLE NS_IMETHOD Quit(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplictaion(IFNIMToggleApplication * *aApplictaion) { return _to GetApplictaion(aApplictaion); } \
  NS_SCRIPTABLE NS_IMETHOD SetApplictaion(IFNIMToggleApplication * aApplictaion) { return _to SetApplictaion(aApplictaion); } \
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton) { return _to GetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton) { return _to SetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD GetReadWindow(IFNIMToggleChatReadWindow * *aReadWindow) { return _to GetReadWindow(aReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetReadWindow(IFNIMToggleChatReadWindow * aReadWindow) { return _to SetReadWindow(aReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetInputWindow(IFNIMToggleChatInputWindow * *aInputWindow) { return _to GetInputWindow(aInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetInputWindow(IFNIMToggleChatInputWindow * aInputWindow) { return _to SetInputWindow(aInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNInputWindow * *aFnInputWindow) { return _to GetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNInputWindow * aFnInputWindow) { return _to SetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNReadWindow * *aFnReadWindow) { return _to GetFnReadWindow(aFnReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNReadWindow * aFnReadWindow) { return _to SetFnReadWindow(aFnReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetMainWindow(IFNIMToggleChatSessionMainWindow **_retval) { return _to GetMainWindow(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetMainwindowHandle(PRUint32 hwnd) { return _to SetMainwindowHandle(hwnd); } \
  NS_SCRIPTABLE NS_IMETHOD Exist(PRBool *_retval) { return _to Exist(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddToggleButton(void) { return _to AddToggleButton(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowFNWidnows(PRBool show) { return _to ShowFNWidnows(show); } \
  NS_SCRIPTABLE NS_IMETHOD Submit(void) { return _to Submit(); } \
  NS_SCRIPTABLE NS_IMETHOD Quit(void) { return _to Quit(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplictaion(IFNIMToggleApplication * *aApplictaion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetApplictaion(aApplictaion); } \
  NS_SCRIPTABLE NS_IMETHOD SetApplictaion(IFNIMToggleApplication * aApplictaion) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetApplictaion(aApplictaion); } \
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD GetReadWindow(IFNIMToggleChatReadWindow * *aReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetReadWindow(aReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetReadWindow(IFNIMToggleChatReadWindow * aReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetReadWindow(aReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetInputWindow(IFNIMToggleChatInputWindow * *aInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInputWindow(aInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetInputWindow(IFNIMToggleChatInputWindow * aInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInputWindow(aInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNInputWindow * *aFnInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNInputWindow * aFnInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNReadWindow * *aFnReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFnReadWindow(aFnReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNReadWindow * aFnReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFnReadWindow(aFnReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetMainWindow(IFNIMToggleChatSessionMainWindow **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMainWindow(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetMainwindowHandle(PRUint32 hwnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMainwindowHandle(hwnd); } \
  NS_SCRIPTABLE NS_IMETHOD Exist(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Exist(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddToggleButton(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddToggleButton(); } \
  NS_SCRIPTABLE NS_IMETHOD ShowFNWidnows(PRBool show) { return !_to ? NS_ERROR_NULL_POINTER : _to->ShowFNWidnows(show); } \
  NS_SCRIPTABLE NS_IMETHOD Submit(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Submit(); } \
  NS_SCRIPTABLE NS_IMETHOD Quit(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Quit(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSession
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSION

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSession)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute IFNIMToggleApplication applictaion; */
NS_IMETHODIMP _MYCLASS_::GetApplictaion(IFNIMToggleApplication * *aApplictaion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetApplictaion(IFNIMToggleApplication * aApplictaion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleButton toggleButton; */
NS_IMETHODIMP _MYCLASS_::GetToggleButton(IFNIMToggleButton * *aToggleButton)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetToggleButton(IFNIMToggleButton * aToggleButton)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatReadWindow readWindow; */
NS_IMETHODIMP _MYCLASS_::GetReadWindow(IFNIMToggleChatReadWindow * *aReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetReadWindow(IFNIMToggleChatReadWindow * aReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatInputWindow inputWindow; */
NS_IMETHODIMP _MYCLASS_::GetInputWindow(IFNIMToggleChatInputWindow * *aInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetInputWindow(IFNIMToggleChatInputWindow * aInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatFNInputWindow fnInputWindow; */
NS_IMETHODIMP _MYCLASS_::GetFnInputWindow(IFNIMToggleChatFNInputWindow * *aFnInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetFnInputWindow(IFNIMToggleChatFNInputWindow * aFnInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatFNReadWindow fnReadWindow; */
NS_IMETHODIMP _MYCLASS_::GetFnReadWindow(IFNIMToggleChatFNReadWindow * *aFnReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetFnReadWindow(IFNIMToggleChatFNReadWindow * aFnReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* IFNIMToggleChatSessionMainWindow getMainWindow (); */
NS_IMETHODIMP _MYCLASS_::GetMainWindow(IFNIMToggleChatSessionMainWindow **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setMainwindowHandle (in PRUint32 hwnd); */
NS_IMETHODIMP _MYCLASS_::SetMainwindowHandle(PRUint32 hwnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean exist (); */
NS_IMETHODIMP _MYCLASS_::Exist(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addToggleButton (); */
NS_IMETHODIMP _MYCLASS_::AddToggleButton()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void showFNWidnows (in boolean show); */
NS_IMETHODIMP _MYCLASS_::ShowFNWidnows(PRBool show)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void submit (); */
NS_IMETHODIMP _MYCLASS_::Submit()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void quit (); */
NS_IMETHODIMP _MYCLASS_::Quit()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSessionHandler */
#define IFNIMTOGGLECHATSESSIONHANDLER_IID_STR "0a812783-f3ce-4c25-aabf-4bb94f47f3f3"

#define IFNIMTOGGLECHATSESSIONHANDLER_IID \
  {0x0a812783, 0xf3ce, 0x4c25, \
    { 0xaa, 0xbf, 0x4b, 0xb9, 0x4f, 0x47, 0xf3, 0xf3 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSessionHandler : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSIONHANDLER_IID)

  /* attribute IFNIMToggleButton toggleButton; */
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton) = 0;

  /* attribute IFNIMToggleChatSession chatSession; */
  NS_SCRIPTABLE NS_IMETHOD GetChatSession(IFNIMToggleChatSession * *aChatSession) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetChatSession(IFNIMToggleChatSession * aChatSession) = 0;

  /* attribute IFNIMToggleChatFNReadWindow fnInputWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNReadWindow * *aFnInputWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNReadWindow * aFnInputWindow) = 0;

  /* attribute IFNIMToggleChatFNInputWindow fnReadWindow; */
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNInputWindow * *aFnReadWindow) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNInputWindow * aFnReadWindow) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSessionHandler, IFNIMTOGGLECHATSESSIONHANDLER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSIONHANDLER \
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton); \
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton); \
  NS_SCRIPTABLE NS_IMETHOD GetChatSession(IFNIMToggleChatSession * *aChatSession); \
  NS_SCRIPTABLE NS_IMETHOD SetChatSession(IFNIMToggleChatSession * aChatSession); \
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNReadWindow * *aFnInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNReadWindow * aFnInputWindow); \
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNInputWindow * *aFnReadWindow); \
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNInputWindow * aFnReadWindow); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSIONHANDLER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton) { return _to GetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton) { return _to SetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD GetChatSession(IFNIMToggleChatSession * *aChatSession) { return _to GetChatSession(aChatSession); } \
  NS_SCRIPTABLE NS_IMETHOD SetChatSession(IFNIMToggleChatSession * aChatSession) { return _to SetChatSession(aChatSession); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNReadWindow * *aFnInputWindow) { return _to GetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNReadWindow * aFnInputWindow) { return _to SetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNInputWindow * *aFnReadWindow) { return _to GetFnReadWindow(aFnReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNInputWindow * aFnReadWindow) { return _to SetFnReadWindow(aFnReadWindow); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSIONHANDLER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetToggleButton(IFNIMToggleButton * *aToggleButton) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD SetToggleButton(IFNIMToggleButton * aToggleButton) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetToggleButton(aToggleButton); } \
  NS_SCRIPTABLE NS_IMETHOD GetChatSession(IFNIMToggleChatSession * *aChatSession) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChatSession(aChatSession); } \
  NS_SCRIPTABLE NS_IMETHOD SetChatSession(IFNIMToggleChatSession * aChatSession) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetChatSession(aChatSession); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnInputWindow(IFNIMToggleChatFNReadWindow * *aFnInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnInputWindow(IFNIMToggleChatFNReadWindow * aFnInputWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFnInputWindow(aFnInputWindow); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnReadWindow(IFNIMToggleChatFNInputWindow * *aFnReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFnReadWindow(aFnReadWindow); } \
  NS_SCRIPTABLE NS_IMETHOD SetFnReadWindow(IFNIMToggleChatFNInputWindow * aFnReadWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFnReadWindow(aFnReadWindow); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSessionHandler
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONHANDLER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSessionHandler)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute IFNIMToggleButton toggleButton; */
NS_IMETHODIMP _MYCLASS_::GetToggleButton(IFNIMToggleButton * *aToggleButton)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetToggleButton(IFNIMToggleButton * aToggleButton)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatSession chatSession; */
NS_IMETHODIMP _MYCLASS_::GetChatSession(IFNIMToggleChatSession * *aChatSession)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetChatSession(IFNIMToggleChatSession * aChatSession)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatFNReadWindow fnInputWindow; */
NS_IMETHODIMP _MYCLASS_::GetFnInputWindow(IFNIMToggleChatFNReadWindow * *aFnInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetFnInputWindow(IFNIMToggleChatFNReadWindow * aFnInputWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatFNInputWindow fnReadWindow; */
NS_IMETHODIMP _MYCLASS_::GetFnReadWindow(IFNIMToggleChatFNInputWindow * *aFnReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetFnReadWindow(IFNIMToggleChatFNInputWindow * aFnReadWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleEngine */
#define IFNIMTOGGLEENGINE_IID_STR "55ad9ad9-28c2-4ef4-92cc-ac4fbe3d7476"

#define IFNIMTOGGLEENGINE_IID \
  {0x55ad9ad9, 0x28c2, 0x4ef4, \
    { 0x92, 0xcc, 0xac, 0x4f, 0xbe, 0x3d, 0x74, 0x76 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleEngine : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEENGINE_IID)

  /* void registerIMApp (in IFNIMToggleApplication anIMapp); */
  NS_SCRIPTABLE NS_IMETHOD RegisterIMApp(IFNIMToggleApplication *anIMapp) = 0;

  /* void unRegisterIMApp (in IFNIMToggleApplication anIMapp); */
  NS_SCRIPTABLE NS_IMETHOD UnRegisterIMApp(IFNIMToggleApplication *anIMapp) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleEngine, IFNIMTOGGLEENGINE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEENGINE \
  NS_SCRIPTABLE NS_IMETHOD RegisterIMApp(IFNIMToggleApplication *anIMapp); \
  NS_SCRIPTABLE NS_IMETHOD UnRegisterIMApp(IFNIMToggleApplication *anIMapp); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEENGINE(_to) \
  NS_SCRIPTABLE NS_IMETHOD RegisterIMApp(IFNIMToggleApplication *anIMapp) { return _to RegisterIMApp(anIMapp); } \
  NS_SCRIPTABLE NS_IMETHOD UnRegisterIMApp(IFNIMToggleApplication *anIMapp) { return _to UnRegisterIMApp(anIMapp); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEENGINE(_to) \
  NS_SCRIPTABLE NS_IMETHOD RegisterIMApp(IFNIMToggleApplication *anIMapp) { return !_to ? NS_ERROR_NULL_POINTER : _to->RegisterIMApp(anIMapp); } \
  NS_SCRIPTABLE NS_IMETHOD UnRegisterIMApp(IFNIMToggleApplication *anIMapp) { return !_to ? NS_ERROR_NULL_POINTER : _to->UnRegisterIMApp(anIMapp); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleEngine
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEENGINE

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleEngine)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void registerIMApp (in IFNIMToggleApplication anIMapp); */
NS_IMETHODIMP _MYCLASS_::RegisterIMApp(IFNIMToggleApplication *anIMapp)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void unRegisterIMApp (in IFNIMToggleApplication anIMapp); */
NS_IMETHODIMP _MYCLASS_::UnRegisterIMApp(IFNIMToggleApplication *anIMapp)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleApplication */
#define IFNIMTOGGLEAPPLICATION_IID_STR "af8ba177-a959-4128-a861-da38ff55e66b"

#define IFNIMTOGGLEAPPLICATION_IID \
  {0xaf8ba177, 0xa959, 0x4128, \
    { 0xa8, 0x61, 0xda, 0x38, 0xff, 0x55, 0xe6, 0x6b }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleApplication : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEAPPLICATION_IID)

  /* readonly attribute AString applicationName; */
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName) = 0;

  /* void start (in PRUint32 processID); */
  NS_SCRIPTABLE NS_IMETHOD Start(PRUint32 processID) = 0;

  /* void quit (); */
  NS_SCRIPTABLE NS_IMETHOD Quit(void) = 0;

  /* void removeSession (in IFNIMToggleChatSession aSession); */
  NS_SCRIPTABLE NS_IMETHOD RemoveSession(IFNIMToggleChatSession *aSession) = 0;

  /* PRUint32 getFNInputHWND (in PRUint32 topLevel); */
  NS_SCRIPTABLE NS_IMETHOD GetFNInputHWND(PRUint32 topLevel, PRUint32 *_retval) = 0;

  /* void setFNInputHWND (in PRUint32 top, in PRUint32 fninputHWND); */
  NS_SCRIPTABLE NS_IMETHOD SetFNInputHWND(PRUint32 top, PRUint32 fninputHWND) = 0;

  /* boolean isMyApp (in AString appToken); */
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleApplication, IFNIMTOGGLEAPPLICATION_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEAPPLICATION \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName); \
  NS_SCRIPTABLE NS_IMETHOD Start(PRUint32 processID); \
  NS_SCRIPTABLE NS_IMETHOD Quit(void); \
  NS_SCRIPTABLE NS_IMETHOD RemoveSession(IFNIMToggleChatSession *aSession); \
  NS_SCRIPTABLE NS_IMETHOD GetFNInputHWND(PRUint32 topLevel, PRUint32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetFNInputHWND(PRUint32 top, PRUint32 fninputHWND); \
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEAPPLICATION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName) { return _to GetApplicationName(aApplicationName); } \
  NS_SCRIPTABLE NS_IMETHOD Start(PRUint32 processID) { return _to Start(processID); } \
  NS_SCRIPTABLE NS_IMETHOD Quit(void) { return _to Quit(); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveSession(IFNIMToggleChatSession *aSession) { return _to RemoveSession(aSession); } \
  NS_SCRIPTABLE NS_IMETHOD GetFNInputHWND(PRUint32 topLevel, PRUint32 *_retval) { return _to GetFNInputHWND(topLevel, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetFNInputHWND(PRUint32 top, PRUint32 fninputHWND) { return _to SetFNInputHWND(top, fninputHWND); } \
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval) { return _to IsMyApp(appToken, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEAPPLICATION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetApplicationName(aApplicationName); } \
  NS_SCRIPTABLE NS_IMETHOD Start(PRUint32 processID) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(processID); } \
  NS_SCRIPTABLE NS_IMETHOD Quit(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Quit(); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveSession(IFNIMToggleChatSession *aSession) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveSession(aSession); } \
  NS_SCRIPTABLE NS_IMETHOD GetFNInputHWND(PRUint32 topLevel, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFNInputHWND(topLevel, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetFNInputHWND(PRUint32 top, PRUint32 fninputHWND) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFNInputHWND(top, fninputHWND); } \
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsMyApp(appToken, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleApplication
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEAPPLICATION

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleApplication)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* readonly attribute AString applicationName; */
NS_IMETHODIMP _MYCLASS_::GetApplicationName(nsAString & aApplicationName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void start (in PRUint32 processID); */
NS_IMETHODIMP _MYCLASS_::Start(PRUint32 processID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void quit (); */
NS_IMETHODIMP _MYCLASS_::Quit()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeSession (in IFNIMToggleChatSession aSession); */
NS_IMETHODIMP _MYCLASS_::RemoveSession(IFNIMToggleChatSession *aSession)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRUint32 getFNInputHWND (in PRUint32 topLevel); */
NS_IMETHODIMP _MYCLASS_::GetFNInputHWND(PRUint32 topLevel, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFNInputHWND (in PRUint32 top, in PRUint32 fninputHWND); */
NS_IMETHODIMP _MYCLASS_::SetFNInputHWND(PRUint32 top, PRUint32 fninputHWND)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isMyApp (in AString appToken); */
NS_IMETHODIMP _MYCLASS_::IsMyApp(const nsAString & appToken, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleApplication2 */
#define IFNIMTOGGLEAPPLICATION2_IID_STR "232a4ada-74d4-431f-ade3-32d68ce89323"

#define IFNIMTOGGLEAPPLICATION2_IID \
  {0x232a4ada, 0x74d4, 0x431f, \
    { 0xad, 0xe3, 0x32, 0xd6, 0x8c, 0xe8, 0x93, 0x23 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleApplication2 : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEAPPLICATION2_IID)

  /* attribute IFNIMToggleApplicationTrait applicationTrait; */
  NS_SCRIPTABLE NS_IMETHOD GetApplicationTrait(IFNIMToggleApplicationTrait * *aApplicationTrait) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetApplicationTrait(IFNIMToggleApplicationTrait * aApplicationTrait) = 0;

  /* attribute IFNIMToggleChatSessionMainWindowLocator sessionMainWindowLocator; */
  NS_SCRIPTABLE NS_IMETHOD GetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * *aSessionMainWindowLocator) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * aSessionMainWindowLocator) = 0;

  /* attribute IFNIMToggleChatSessionCreator sessionCreator; */
  NS_SCRIPTABLE NS_IMETHOD GetSessionCreator(IFNIMToggleChatSessionCreator * *aSessionCreator) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSessionCreator(IFNIMToggleChatSessionCreator * aSessionCreator) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleApplication2, IFNIMTOGGLEAPPLICATION2_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEAPPLICATION2 \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationTrait(IFNIMToggleApplicationTrait * *aApplicationTrait); \
  NS_SCRIPTABLE NS_IMETHOD SetApplicationTrait(IFNIMToggleApplicationTrait * aApplicationTrait); \
  NS_SCRIPTABLE NS_IMETHOD GetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * *aSessionMainWindowLocator); \
  NS_SCRIPTABLE NS_IMETHOD SetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * aSessionMainWindowLocator); \
  NS_SCRIPTABLE NS_IMETHOD GetSessionCreator(IFNIMToggleChatSessionCreator * *aSessionCreator); \
  NS_SCRIPTABLE NS_IMETHOD SetSessionCreator(IFNIMToggleChatSessionCreator * aSessionCreator); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEAPPLICATION2(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationTrait(IFNIMToggleApplicationTrait * *aApplicationTrait) { return _to GetApplicationTrait(aApplicationTrait); } \
  NS_SCRIPTABLE NS_IMETHOD SetApplicationTrait(IFNIMToggleApplicationTrait * aApplicationTrait) { return _to SetApplicationTrait(aApplicationTrait); } \
  NS_SCRIPTABLE NS_IMETHOD GetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * *aSessionMainWindowLocator) { return _to GetSessionMainWindowLocator(aSessionMainWindowLocator); } \
  NS_SCRIPTABLE NS_IMETHOD SetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * aSessionMainWindowLocator) { return _to SetSessionMainWindowLocator(aSessionMainWindowLocator); } \
  NS_SCRIPTABLE NS_IMETHOD GetSessionCreator(IFNIMToggleChatSessionCreator * *aSessionCreator) { return _to GetSessionCreator(aSessionCreator); } \
  NS_SCRIPTABLE NS_IMETHOD SetSessionCreator(IFNIMToggleChatSessionCreator * aSessionCreator) { return _to SetSessionCreator(aSessionCreator); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEAPPLICATION2(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationTrait(IFNIMToggleApplicationTrait * *aApplicationTrait) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetApplicationTrait(aApplicationTrait); } \
  NS_SCRIPTABLE NS_IMETHOD SetApplicationTrait(IFNIMToggleApplicationTrait * aApplicationTrait) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetApplicationTrait(aApplicationTrait); } \
  NS_SCRIPTABLE NS_IMETHOD GetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * *aSessionMainWindowLocator) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSessionMainWindowLocator(aSessionMainWindowLocator); } \
  NS_SCRIPTABLE NS_IMETHOD SetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * aSessionMainWindowLocator) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSessionMainWindowLocator(aSessionMainWindowLocator); } \
  NS_SCRIPTABLE NS_IMETHOD GetSessionCreator(IFNIMToggleChatSessionCreator * *aSessionCreator) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSessionCreator(aSessionCreator); } \
  NS_SCRIPTABLE NS_IMETHOD SetSessionCreator(IFNIMToggleChatSessionCreator * aSessionCreator) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSessionCreator(aSessionCreator); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleApplication2
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEAPPLICATION2

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleApplication2)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute IFNIMToggleApplicationTrait applicationTrait; */
NS_IMETHODIMP _MYCLASS_::GetApplicationTrait(IFNIMToggleApplicationTrait * *aApplicationTrait)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetApplicationTrait(IFNIMToggleApplicationTrait * aApplicationTrait)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatSessionMainWindowLocator sessionMainWindowLocator; */
NS_IMETHODIMP _MYCLASS_::GetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * *aSessionMainWindowLocator)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetSessionMainWindowLocator(IFNIMToggleChatSessionMainWindowLocator * aSessionMainWindowLocator)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute IFNIMToggleChatSessionCreator sessionCreator; */
NS_IMETHODIMP _MYCLASS_::GetSessionCreator(IFNIMToggleChatSessionCreator * *aSessionCreator)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetSessionCreator(IFNIMToggleChatSessionCreator * aSessionCreator)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleApplicationTrait */
#define IFNIMTOGGLEAPPLICATIONTRAIT_IID_STR "b6092702-aee3-471c-a692-40cf1af250cd"

#define IFNIMTOGGLEAPPLICATIONTRAIT_IID \
  {0xb6092702, 0xaee3, 0x471c, \
    { 0xa6, 0x92, 0x40, 0xcf, 0x1a, 0xf2, 0x50, 0xcd }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleApplicationTrait : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEAPPLICATIONTRAIT_IID)

  /* readonly attribute AString applicationName; */
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName) = 0;

  /* boolean isMyApp (in AString appToken); */
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleApplicationTrait, IFNIMTOGGLEAPPLICATIONTRAIT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEAPPLICATIONTRAIT \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName); \
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEAPPLICATIONTRAIT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName) { return _to GetApplicationName(aApplicationName); } \
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval) { return _to IsMyApp(appToken, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEAPPLICATIONTRAIT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetApplicationName(nsAString & aApplicationName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetApplicationName(aApplicationName); } \
  NS_SCRIPTABLE NS_IMETHOD IsMyApp(const nsAString & appToken, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsMyApp(appToken, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleApplicationTrait
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEAPPLICATIONTRAIT

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleApplicationTrait)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* readonly attribute AString applicationName; */
NS_IMETHODIMP _MYCLASS_::GetApplicationName(nsAString & aApplicationName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isMyApp (in AString appToken); */
NS_IMETHODIMP _MYCLASS_::IsMyApp(const nsAString & appToken, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleIMApplicationHandler */
#define IFNIMTOGGLEIMAPPLICATIONHANDLER_IID_STR "75b12f70-e748-4a82-8426-2a2806b448a9"

#define IFNIMTOGGLEIMAPPLICATIONHANDLER_IID \
  {0x75b12f70, 0xe748, 0x4a82, \
    { 0x84, 0x26, 0x2a, 0x28, 0x06, 0xb4, 0x48, 0xa9 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleIMApplicationHandler : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEIMAPPLICATIONHANDLER_IID)

  /* void init (in PRUint32 processID, in IFNIMToggleApplication app); */
  NS_SCRIPTABLE NS_IMETHOD Init(PRUint32 processID, IFNIMToggleApplication *app) = 0;

  /* void quit (); */
  NS_SCRIPTABLE NS_IMETHOD Quit(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleIMApplicationHandler, IFNIMTOGGLEIMAPPLICATIONHANDLER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEIMAPPLICATIONHANDLER \
  NS_SCRIPTABLE NS_IMETHOD Init(PRUint32 processID, IFNIMToggleApplication *app); \
  NS_SCRIPTABLE NS_IMETHOD Quit(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEIMAPPLICATIONHANDLER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(PRUint32 processID, IFNIMToggleApplication *app) { return _to Init(processID, app); } \
  NS_SCRIPTABLE NS_IMETHOD Quit(void) { return _to Quit(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEIMAPPLICATIONHANDLER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(PRUint32 processID, IFNIMToggleApplication *app) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(processID, app); } \
  NS_SCRIPTABLE NS_IMETHOD Quit(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Quit(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleIMApplicationHandler
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEIMAPPLICATIONHANDLER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleIMApplicationHandler)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void init (in PRUint32 processID, in IFNIMToggleApplication app); */
NS_IMETHODIMP _MYCLASS_::Init(PRUint32 processID, IFNIMToggleApplication *app)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void quit (); */
NS_IMETHODIMP _MYCLASS_::Quit()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNMainWindow */
#define IFNIMTOGGLECHATFNMAINWINDOW_IID_STR "b313f5ce-3dc2-497e-8439-348190ae0648"

#define IFNIMTOGGLECHATFNMAINWINDOW_IID \
  {0xb313f5ce, 0x3dc2, 0x497e, \
    { 0x84, 0x39, 0x34, 0x81, 0x90, 0xae, 0x06, 0x48 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNMainWindow : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNMAINWINDOW_IID)

  /* attribute AString title; */
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsAString & aTitle) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsAString & aTitle) = 0;

  /* readonly attribute PRUint32 windowHandle; */
  NS_SCRIPTABLE NS_IMETHOD GetWindowHandle(PRUint32 *aWindowHandle) = 0;

  /* readonly attribute nsISupports fnInput; */
  NS_SCRIPTABLE NS_IMETHOD GetFnInput(nsISupports * *aFnInput) = 0;

  /* readonly attribute nsISupports fnReader; */
  NS_SCRIPTABLE NS_IMETHOD GetFnReader(nsISupports * *aFnReader) = 0;

  /* void addUIListener_Close (in nsIDOMEventListener aListener); */
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Close(nsIDOMEventListener *aListener) = 0;

  /* void addUIListener_Submit (in nsIDOMEventListener aListener); */
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Submit(nsIDOMEventListener *aListener) = 0;

  /* void addUIListener_Invitation (in nsIDOMEventListener aListener); */
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Invitation(nsIDOMEventListener *aListener) = 0;

  /* void addDestroyEvnetListener (in IFNIMWindowDestroyEvnetListener listener); */
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener) = 0;

  /* void addDocumentReadyObserver (in nsIObserver aObserver); */
  NS_SCRIPTABLE NS_IMETHOD AddDocumentReadyObserver(nsIObserver *aObserver) = 0;

  /* void show (in boolean show); */
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) = 0;

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* boolean windowVisible (); */
  NS_SCRIPTABLE NS_IMETHOD WindowVisible(PRBool *_retval) = 0;

  /* boolean createNew (in PRUint32 parent, in PRInt32 left, in PRInt32 top, in PRUint32 w, in PRUint32 h, in PRUint32 style, in PRUint32 exStyle); */
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNMainWindow, IFNIMTOGGLECHATFNMAINWINDOW_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNMAINWINDOW \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsAString & aTitle); \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsAString & aTitle); \
  NS_SCRIPTABLE NS_IMETHOD GetWindowHandle(PRUint32 *aWindowHandle); \
  NS_SCRIPTABLE NS_IMETHOD GetFnInput(nsISupports * *aFnInput); \
  NS_SCRIPTABLE NS_IMETHOD GetFnReader(nsISupports * *aFnReader); \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Close(nsIDOMEventListener *aListener); \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Submit(nsIDOMEventListener *aListener); \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Invitation(nsIDOMEventListener *aListener); \
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener); \
  NS_SCRIPTABLE NS_IMETHOD AddDocumentReadyObserver(nsIObserver *aObserver); \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show); \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD WindowVisible(PRBool *_retval); \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNMAINWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsAString & aTitle) { return _to GetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsAString & aTitle) { return _to SetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD GetWindowHandle(PRUint32 *aWindowHandle) { return _to GetWindowHandle(aWindowHandle); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnInput(nsISupports * *aFnInput) { return _to GetFnInput(aFnInput); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnReader(nsISupports * *aFnReader) { return _to GetFnReader(aFnReader); } \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Close(nsIDOMEventListener *aListener) { return _to AddUIListener_Close(aListener); } \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Submit(nsIDOMEventListener *aListener) { return _to AddUIListener_Submit(aListener); } \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Invitation(nsIDOMEventListener *aListener) { return _to AddUIListener_Invitation(aListener); } \
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener) { return _to AddDestroyEvnetListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD AddDocumentReadyObserver(nsIObserver *aObserver) { return _to AddDocumentReadyObserver(aObserver); } \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) { return _to Show(show); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD WindowVisible(PRBool *_retval) { return _to WindowVisible(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) { return _to CreateNew(parent, left, top, w, h, style, exStyle, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNMAINWINDOW(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsAString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsAString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD GetWindowHandle(PRUint32 *aWindowHandle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWindowHandle(aWindowHandle); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnInput(nsISupports * *aFnInput) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFnInput(aFnInput); } \
  NS_SCRIPTABLE NS_IMETHOD GetFnReader(nsISupports * *aFnReader) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFnReader(aFnReader); } \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Close(nsIDOMEventListener *aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddUIListener_Close(aListener); } \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Submit(nsIDOMEventListener *aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddUIListener_Submit(aListener); } \
  NS_SCRIPTABLE NS_IMETHOD AddUIListener_Invitation(nsIDOMEventListener *aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddUIListener_Invitation(aListener); } \
  NS_SCRIPTABLE NS_IMETHOD AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDestroyEvnetListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD AddDocumentReadyObserver(nsIObserver *aObserver) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDocumentReadyObserver(aObserver); } \
  NS_SCRIPTABLE NS_IMETHOD Show(PRBool show) { return !_to ? NS_ERROR_NULL_POINTER : _to->Show(show); } \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD WindowVisible(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->WindowVisible(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateNew(parent, left, top, w, h, style, exStyle, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNMainWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNMAINWINDOW

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNMainWindow)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute AString title; */
NS_IMETHODIMP _MYCLASS_::GetTitle(nsAString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetTitle(const nsAString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRUint32 windowHandle; */
NS_IMETHODIMP _MYCLASS_::GetWindowHandle(PRUint32 *aWindowHandle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsISupports fnInput; */
NS_IMETHODIMP _MYCLASS_::GetFnInput(nsISupports * *aFnInput)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsISupports fnReader; */
NS_IMETHODIMP _MYCLASS_::GetFnReader(nsISupports * *aFnReader)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addUIListener_Close (in nsIDOMEventListener aListener); */
NS_IMETHODIMP _MYCLASS_::AddUIListener_Close(nsIDOMEventListener *aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addUIListener_Submit (in nsIDOMEventListener aListener); */
NS_IMETHODIMP _MYCLASS_::AddUIListener_Submit(nsIDOMEventListener *aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addUIListener_Invitation (in nsIDOMEventListener aListener); */
NS_IMETHODIMP _MYCLASS_::AddUIListener_Invitation(nsIDOMEventListener *aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addDestroyEvnetListener (in IFNIMWindowDestroyEvnetListener listener); */
NS_IMETHODIMP _MYCLASS_::AddDestroyEvnetListener(IFNIMWindowDestroyEvnetListener *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addDocumentReadyObserver (in nsIObserver aObserver); */
NS_IMETHODIMP _MYCLASS_::AddDocumentReadyObserver(nsIObserver *aObserver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void show (in boolean show); */
NS_IMETHODIMP _MYCLASS_::Show(PRBool show)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean windowVisible (); */
NS_IMETHODIMP _MYCLASS_::WindowVisible(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean createNew (in PRUint32 parent, in PRInt32 left, in PRInt32 top, in PRUint32 w, in PRUint32 h, in PRUint32 style, in PRUint32 exStyle); */
NS_IMETHODIMP _MYCLASS_::CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNReader */
#define IFNIMTOGGLECHATFNREADER_IID_STR "8b0899ba-ecaf-4036-9811-18db3fe6ef1b"

#define IFNIMTOGGLECHATFNREADER_IID \
  {0x8b0899ba, 0xecaf, 0x4036, \
    { 0x98, 0x11, 0x18, 0xdb, 0x3f, 0xe6, 0xef, 0x1b }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNReader : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNREADER_IID)

  /* void appendContent1 (in AString content); */
  NS_SCRIPTABLE NS_IMETHOD AppendContent1(const nsAString & content) = 0;

  /* void setContent1 (in AString content); */
  NS_SCRIPTABLE NS_IMETHOD SetContent1(const nsAString & content) = 0;

  /* attribute nsIWebBrowser webBrowser; */
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNReader, IFNIMTOGGLECHATFNREADER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNREADER \
  NS_SCRIPTABLE NS_IMETHOD AppendContent1(const nsAString & content); \
  NS_SCRIPTABLE NS_IMETHOD SetContent1(const nsAString & content); \
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser); \
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNREADER(_to) \
  NS_SCRIPTABLE NS_IMETHOD AppendContent1(const nsAString & content) { return _to AppendContent1(content); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent1(const nsAString & content) { return _to SetContent1(content); } \
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser) { return _to GetWebBrowser(aWebBrowser); } \
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser) { return _to SetWebBrowser(aWebBrowser); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNREADER(_to) \
  NS_SCRIPTABLE NS_IMETHOD AppendContent1(const nsAString & content) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendContent1(content); } \
  NS_SCRIPTABLE NS_IMETHOD SetContent1(const nsAString & content) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContent1(content); } \
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWebBrowser(aWebBrowser); } \
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWebBrowser(aWebBrowser); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNReader
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNREADER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNReader)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void appendContent1 (in AString content); */
NS_IMETHODIMP _MYCLASS_::AppendContent1(const nsAString & content)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setContent1 (in AString content); */
NS_IMETHODIMP _MYCLASS_::SetContent1(const nsAString & content)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIWebBrowser webBrowser; */
NS_IMETHODIMP _MYCLASS_::GetWebBrowser(nsIWebBrowser * *aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetWebBrowser(nsIWebBrowser * aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNInput */
#define IFNIMTOGGLECHATFNINPUT_IID_STR "0319d312-445e-4635-8034-1a6cab546955"

#define IFNIMTOGGLECHATFNINPUT_IID \
  {0x0319d312, 0x445e, 0x4635, \
    { 0x80, 0x34, 0x1a, 0x6c, 0xab, 0x54, 0x69, 0x55 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNInput : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNINPUT_IID)

  /* void setContent (in AString content); */
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & content) = 0;

  /* void getContent (out AString content); */
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & content) = 0;

  /* attribute nsIWebBrowser webBrowser; */
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser) = 0;

  /* boolean isFocused (); */
  NS_SCRIPTABLE NS_IMETHOD IsFocused(PRBool *_retval) = 0;

  /* void setFocus (); */
  NS_SCRIPTABLE NS_IMETHOD SetFocus(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNInput, IFNIMTOGGLECHATFNINPUT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNINPUT \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & content); \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & content); \
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser); \
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser); \
  NS_SCRIPTABLE NS_IMETHOD IsFocused(PRBool *_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetFocus(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNINPUT(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & content) { return _to SetContent(content); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & content) { return _to GetContent(content); } \
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser) { return _to GetWebBrowser(aWebBrowser); } \
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser) { return _to SetWebBrowser(aWebBrowser); } \
  NS_SCRIPTABLE NS_IMETHOD IsFocused(PRBool *_retval) { return _to IsFocused(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetFocus(void) { return _to SetFocus(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNINPUT(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetContent(const nsAString & content) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContent(content); } \
  NS_SCRIPTABLE NS_IMETHOD GetContent(nsAString & content) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContent(content); } \
  NS_SCRIPTABLE NS_IMETHOD GetWebBrowser(nsIWebBrowser * *aWebBrowser) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWebBrowser(aWebBrowser); } \
  NS_SCRIPTABLE NS_IMETHOD SetWebBrowser(nsIWebBrowser * aWebBrowser) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWebBrowser(aWebBrowser); } \
  NS_SCRIPTABLE NS_IMETHOD IsFocused(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsFocused(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetFocus(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFocus(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNInput
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNINPUT

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNInput)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void setContent (in AString content); */
NS_IMETHODIMP _MYCLASS_::SetContent(const nsAString & content)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getContent (out AString content); */
NS_IMETHODIMP _MYCLASS_::GetContent(nsAString & content)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIWebBrowser webBrowser; */
NS_IMETHODIMP _MYCLASS_::GetWebBrowser(nsIWebBrowser * *aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetWebBrowser(nsIWebBrowser * aWebBrowser)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isFocused (); */
NS_IMETHODIMP _MYCLASS_::IsFocused(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFocus (); */
NS_IMETHODIMP _MYCLASS_::SetFocus()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNMainWindowLocator */
#define IFNIMTOGGLECHATFNMAINWINDOWLOCATOR_IID_STR "49dcff77-443f-4a92-ac45-7c98038c0422"

#define IFNIMTOGGLECHATFNMAINWINDOWLOCATOR_IID \
  {0x49dcff77, 0x443f, 0x4a92, \
    { 0xac, 0x45, 0x7c, 0x98, 0x03, 0x8c, 0x04, 0x22 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNMainWindowLocator : public IFNIMWindowLocator {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNMAINWINDOWLOCATOR_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNMainWindowLocator, IFNIMTOGGLECHATFNMAINWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNMAINWINDOWLOCATOR \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNMAINWINDOWLOCATOR(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNMAINWINDOWLOCATOR(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNMainWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNMAINWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNMainWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatReadWindowLocator */
#define IFNIMTOGGLECHATREADWINDOWLOCATOR_IID_STR "9a8db503-fd48-4b8c-acaf-5aeca21fcaff"

#define IFNIMTOGGLECHATREADWINDOWLOCATOR_IID \
  {0x9a8db503, 0xfd48, 0x4b8c, \
    { 0xac, 0xaf, 0x5a, 0xec, 0xa2, 0x1f, 0xca, 0xff }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatReadWindowLocator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATREADWINDOWLOCATOR_IID)

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* void find (out PRUint32 hWnd); */
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatReadWindowLocator, IFNIMTOGGLECHATREADWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATREADWINDOWLOCATOR \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATREADWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd) { return _to Find(hWnd); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATREADWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->Find(hWnd); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatReadWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATREADWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatReadWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void find (out PRUint32 hWnd); */
NS_IMETHODIMP _MYCLASS_::Find(PRUint32 *hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatInputWindowLocator */
#define IFNIMTOGGLECHATINPUTWINDOWLOCATOR_IID_STR "15f4bb7c-743f-421d-bac6-71e2a384c268"

#define IFNIMTOGGLECHATINPUTWINDOWLOCATOR_IID \
  {0x15f4bb7c, 0x743f, 0x421d, \
    { 0xba, 0xc6, 0x71, 0xe2, 0xa3, 0x84, 0xc2, 0x68 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatInputWindowLocator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATINPUTWINDOWLOCATOR_IID)

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* void find (out PRUint32 hWnd); */
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatInputWindowLocator, IFNIMTOGGLECHATINPUTWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATINPUTWINDOWLOCATOR \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATINPUTWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd) { return _to Find(hWnd); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATINPUTWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Find(PRUint32 *hWnd) { return !_to ? NS_ERROR_NULL_POINTER : _to->Find(hWnd); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatInputWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATINPUTWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatInputWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void find (out PRUint32 hWnd); */
NS_IMETHODIMP _MYCLASS_::Find(PRUint32 *hWnd)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSessionMainWindowLocator */
#define IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_IID_STR "a49acae7-a8d8-44bd-89ad-957a3048de08"

#define IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_IID \
  {0xa49acae7, 0xa8d8, 0x44bd, \
    { 0x89, 0xad, 0x95, 0x7a, 0x30, 0x48, 0xde, 0x08 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSessionMainWindowLocator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_IID)

  /* void close (); */
  NS_SCRIPTABLE NS_IMETHOD Close(void) = 0;

  /* nsIArray find (); */
  NS_SCRIPTABLE NS_IMETHOD Find(nsIArray **_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSessionMainWindowLocator, IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR \
  NS_SCRIPTABLE NS_IMETHOD Close(void); \
  NS_SCRIPTABLE NS_IMETHOD Find(nsIArray **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return _to Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Find(nsIArray **_retval) { return _to Find(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD Close(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Close(); } \
  NS_SCRIPTABLE NS_IMETHOD Find(nsIArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Find(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSessionMainWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSessionMainWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void close (); */
NS_IMETHODIMP _MYCLASS_::Close()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIArray find (); */
NS_IMETHODIMP _MYCLASS_::Find(nsIArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSessionMainWindowLocator_InProcess */
#define IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS_IID_STR "93fe0515-122c-4f2b-bea4-660b6d97bdbc"

#define IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS_IID \
  {0x93fe0515, 0x122c, 0x4f2b, \
    { 0xbe, 0xa4, 0x66, 0x0b, 0x6d, 0x97, 0xbd, 0xbc }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSessionMainWindowLocator_InProcess : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS_IID)

  /* nsIArray find_InProcess (in PRUint32 pid); */
  NS_SCRIPTABLE NS_IMETHOD Find_InProcess(PRUint32 pid, nsIArray **_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSessionMainWindowLocator_InProcess, IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS \
  NS_SCRIPTABLE NS_IMETHOD Find_InProcess(PRUint32 pid, nsIArray **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS(_to) \
  NS_SCRIPTABLE NS_IMETHOD Find_InProcess(PRUint32 pid, nsIArray **_retval) { return _to Find_InProcess(pid, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS(_to) \
  NS_SCRIPTABLE NS_IMETHOD Find_InProcess(PRUint32 pid, nsIArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Find_InProcess(pid, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSessionMainWindowLocator_InProcess
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONMAINWINDOWLOCATOR_INPROCESS

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSessionMainWindowLocator_InProcess)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* nsIArray find_InProcess (in PRUint32 pid); */
NS_IMETHODIMP _MYCLASS_::Find_InProcess(PRUint32 pid, nsIArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleButtonEvnetListener */
#define IFNIMTOGGLEBUTTONEVNETLISTENER_IID_STR "8e69d738-3955-4b8f-a4e4-3d73fe580f17"

#define IFNIMTOGGLEBUTTONEVNETLISTENER_IID \
  {0x8e69d738, 0x3955, 0x4b8f, \
    { 0xa4, 0xe4, 0x3d, 0x73, 0xfe, 0x58, 0x0f, 0x17 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleButtonEvnetListener : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEBUTTONEVNETLISTENER_IID)

  /* void onToggle (in boolean state, out boolean stop); */
  NS_SCRIPTABLE NS_IMETHOD OnToggle(PRBool state, PRBool *stop) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleButtonEvnetListener, IFNIMTOGGLEBUTTONEVNETLISTENER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEBUTTONEVNETLISTENER \
  NS_SCRIPTABLE NS_IMETHOD OnToggle(PRBool state, PRBool *stop); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEBUTTONEVNETLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnToggle(PRBool state, PRBool *stop) { return _to OnToggle(state, stop); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEBUTTONEVNETLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnToggle(PRBool state, PRBool *stop) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnToggle(state, stop); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleButtonEvnetListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEBUTTONEVNETLISTENER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleButtonEvnetListener)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void onToggle (in boolean state, out boolean stop); */
NS_IMETHODIMP _MYCLASS_::OnToggle(PRBool state, PRBool *stop)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleButtonLocator */
#define IFNIMTOGGLEBUTTONLOCATOR_IID_STR "e5857e0c-01a3-48ae-91d4-b5bddf868af7"

#define IFNIMTOGGLEBUTTONLOCATOR_IID \
  {0xe5857e0c, 0x01a3, 0x48ae, \
    { 0x91, 0xd4, 0xb5, 0xbd, 0xdf, 0x86, 0x8a, 0xf7 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleButtonLocator : public IFNIMWindowLocator {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEBUTTONLOCATOR_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleButtonLocator, IFNIMTOGGLEBUTTONLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEBUTTONLOCATOR \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEBUTTONLOCATOR(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEBUTTONLOCATOR(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleButtonLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEBUTTONLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleButtonLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNReadWindowLocator */
#define IFNIMTOGGLECHATFNREADWINDOWLOCATOR_IID_STR "3a107f8e-1d8e-46c3-9378-0324e329f3fd"

#define IFNIMTOGGLECHATFNREADWINDOWLOCATOR_IID \
  {0x3a107f8e, 0x1d8e, 0x46c3, \
    { 0x93, 0x78, 0x03, 0x24, 0xe3, 0x29, 0xf3, 0xfd }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNReadWindowLocator : public IFNIMWindowLocator {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNREADWINDOWLOCATOR_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNReadWindowLocator, IFNIMTOGGLECHATFNREADWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNREADWINDOWLOCATOR \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNREADWINDOWLOCATOR(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNREADWINDOWLOCATOR(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNReadWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNREADWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNReadWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatFNInputWindowLocator */
#define IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR_IID_STR "fe626d08-5082-4d69-bb97-9e66e1ce76e6"

#define IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR_IID \
  {0xfe626d08, 0x5082, 0x4d69, \
    { 0xbb, 0x97, 0x9e, 0x66, 0xe1, 0xce, 0x76, 0xe6 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatFNInputWindowLocator : public IFNIMWindowLocator {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR_IID)

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatFNInputWindowLocator, IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatFNInputWindowLocator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATFNINPUTWINDOWLOCATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatFNInputWindowLocator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMWindowDestroyEvnetListener */
#define IFNIMWINDOWDESTROYEVNETLISTENER_IID_STR "546ea08d-e4d6-4e45-9372-a1d0ef838962"

#define IFNIMWINDOWDESTROYEVNETLISTENER_IID \
  {0x546ea08d, 0xe4d6, 0x4e45, \
    { 0x93, 0x72, 0xa1, 0xd0, 0xef, 0x83, 0x89, 0x62 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMWindowDestroyEvnetListener : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMWINDOWDESTROYEVNETLISTENER_IID)

  /* void onDestroy (in nsISupports obj); */
  NS_SCRIPTABLE NS_IMETHOD OnDestroy(nsISupports *obj) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMWindowDestroyEvnetListener, IFNIMWINDOWDESTROYEVNETLISTENER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMWINDOWDESTROYEVNETLISTENER \
  NS_SCRIPTABLE NS_IMETHOD OnDestroy(nsISupports *obj); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMWINDOWDESTROYEVNETLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnDestroy(nsISupports *obj) { return _to OnDestroy(obj); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMWINDOWDESTROYEVNETLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnDestroy(nsISupports *obj) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnDestroy(obj); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMWindowDestroyEvnetListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMWINDOWDESTROYEVNETLISTENER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMWindowDestroyEvnetListener)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void onDestroy (in nsISupports obj); */
NS_IMETHODIMP _MYCLASS_::OnDestroy(nsISupports *obj)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleApplicationUserAccount */
#define IFNIMTOGGLEAPPLICATIONUSERACCOUNT_IID_STR "546ea08d-e4d6-4e45-9372-a1d0ef838962"

#define IFNIMTOGGLEAPPLICATIONUSERACCOUNT_IID \
  {0x546ea08d, 0xe4d6, 0x4e45, \
    { 0x93, 0x72, 0xa1, 0xd0, 0xef, 0x83, 0x89, 0x62 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleApplicationUserAccount : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLEAPPLICATIONUSERACCOUNT_IID)

  /* attribute AString nickname; */
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleApplicationUserAccount, IFNIMTOGGLEAPPLICATIONUSERACCOUNT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLEAPPLICATIONUSERACCOUNT \
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname); \
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLEAPPLICATIONUSERACCOUNT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname) { return _to GetNickname(aNickname); } \
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname) { return _to SetNickname(aNickname); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLEAPPLICATIONUSERACCOUNT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNickname(aNickname); } \
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetNickname(aNickname); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleApplicationUserAccount
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLEAPPLICATIONUSERACCOUNT

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleApplicationUserAccount)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute AString nickname; */
NS_IMETHODIMP _MYCLASS_::GetNickname(nsAString & aNickname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetNickname(const nsAString & aNickname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMToggleChatSessionContactor */
#define IFNIMTOGGLECHATSESSIONCONTACTOR_IID_STR "546ea08d-e4d6-4e45-9372-a1d0ef838962"

#define IFNIMTOGGLECHATSESSIONCONTACTOR_IID \
  {0x546ea08d, 0xe4d6, 0x4e45, \
    { 0x93, 0x72, 0xa1, 0xd0, 0xef, 0x83, 0x89, 0x62 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMToggleChatSessionContactor : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMTOGGLECHATSESSIONCONTACTOR_IID)

  /* attribute AString nickname; */
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMToggleChatSessionContactor, IFNIMTOGGLECHATSESSIONCONTACTOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMTOGGLECHATSESSIONCONTACTOR \
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname); \
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMTOGGLECHATSESSIONCONTACTOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname) { return _to GetNickname(aNickname); } \
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname) { return _to SetNickname(aNickname); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMTOGGLECHATSESSIONCONTACTOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetNickname(nsAString & aNickname) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNickname(aNickname); } \
  NS_SCRIPTABLE NS_IMETHOD SetNickname(const nsAString & aNickname) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetNickname(aNickname); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMToggleChatSessionContactor
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMTOGGLECHATSESSIONCONTACTOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMToggleChatSessionContactor)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute AString nickname; */
NS_IMETHODIMP _MYCLASS_::GetNickname(nsAString & aNickname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetNickname(const nsAString & aNickname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMSendInvitation */
#define IFNIMSENDINVITATION_IID_STR "7ea0f550-4fa7-4d47-894f-76d5b7495ab1"

#define IFNIMSENDINVITATION_IID \
  {0x7ea0f550, 0x4fa7, 0x4d47, \
    { 0x89, 0x4f, 0x76, 0xd5, 0xb7, 0x49, 0x5a, 0xb1 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMSendInvitation : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMSENDINVITATION_IID)

  /* attribute AString invitationContent; */
  NS_SCRIPTABLE NS_IMETHOD GetInvitationContent(nsAString & aInvitationContent) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInvitationContent(const nsAString & aInvitationContent) = 0;

  /* void sendInvitation (); */
  NS_SCRIPTABLE NS_IMETHOD SendInvitation(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMSendInvitation, IFNIMSENDINVITATION_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMSENDINVITATION \
  NS_SCRIPTABLE NS_IMETHOD GetInvitationContent(nsAString & aInvitationContent); \
  NS_SCRIPTABLE NS_IMETHOD SetInvitationContent(const nsAString & aInvitationContent); \
  NS_SCRIPTABLE NS_IMETHOD SendInvitation(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMSENDINVITATION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetInvitationContent(nsAString & aInvitationContent) { return _to GetInvitationContent(aInvitationContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetInvitationContent(const nsAString & aInvitationContent) { return _to SetInvitationContent(aInvitationContent); } \
  NS_SCRIPTABLE NS_IMETHOD SendInvitation(void) { return _to SendInvitation(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMSENDINVITATION(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetInvitationContent(nsAString & aInvitationContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInvitationContent(aInvitationContent); } \
  NS_SCRIPTABLE NS_IMETHOD SetInvitationContent(const nsAString & aInvitationContent) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInvitationContent(aInvitationContent); } \
  NS_SCRIPTABLE NS_IMETHOD SendInvitation(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->SendInvitation(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMSendInvitation
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMSENDINVITATION

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMSendInvitation)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute AString invitationContent; */
NS_IMETHODIMP _MYCLASS_::GetInvitationContent(nsAString & aInvitationContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetInvitationContent(const nsAString & aInvitationContent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void sendInvitation (); */
NS_IMETHODIMP _MYCLASS_::SendInvitation()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    IFNIMWindowCreator */
#define IFNIMWINDOWCREATOR_IID_STR "b8638490-09bd-45f2-a4ba-aaf29ac7e9e9"

#define IFNIMWINDOWCREATOR_IID \
  {0xb8638490, 0x09bd, 0x45f2, \
    { 0xa4, 0xba, 0xaa, 0xf2, 0x9a, 0xc7, 0xe9, 0xe9 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFNIMWindowCreator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFNIMWINDOWCREATOR_IID)

  /* boolean createNew (in PRUint32 parent, in PRInt32 left, in PRInt32 top, in PRUint32 w, in PRUint32 h, in PRUint32 style, in PRUint32 exStyle); */
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFNIMWindowCreator, IFNIMWINDOWCREATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFNIMWINDOWCREATOR \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFNIMWINDOWCREATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) { return _to CreateNew(parent, left, top, w, h, style, exStyle, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFNIMWINDOWCREATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateNew(parent, left, top, w, h, style, exStyle, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFNIMWindowCreator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFNIMWINDOWCREATOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFNIMWindowCreator)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* boolean createNew (in PRUint32 parent, in PRInt32 left, in PRInt32 top, in PRUint32 w, in PRUint32 h, in PRUint32 style, in PRUint32 exStyle); */
NS_IMETHODIMP _MYCLASS_::CreateNew(PRUint32 parent, PRInt32 left, PRInt32 top, PRUint32 w, PRUint32 h, PRUint32 style, PRUint32 exStyle, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IFNIMToggle_h__ */
