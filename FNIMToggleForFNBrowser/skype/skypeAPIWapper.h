#ifndef SKYPEAPIWAPPER_HEADER__
#define SKYPEAPIWAPPER_HEADER__


#include <xstring>

 


#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>
using namespace ATL;

#include <xstring>
using namespace std;
 

#include "skype_dev/FNIM_skype_proxy/FNIM_skype_proxy.h"

class SkypeAPIWapper
{
public: 
    static bool dll_connect();
    static void dll_disconnect();

    static DWORD register_SkypeAPI_IFNIMChat(SkypeAPI_IFNIMChat* aSkypeAPI_IFNIMChat, LPCTSTR shakehandMsg);
    static void unregister_SkypeAPI_IFNIMChat(DWORD cookie);
};


/*
// Generated .IDL file (by the OLE/COM Object Viewer)
// 
// typelib filename: <could not determine filename>

[
  uuid(03282B5D-B38F-469D-849A-09B0A7F4881B),
  version(1.0),
  helpstring("Skype4COM 1.0 Type Library."),
  helpfile("Skype4COM.chm"),
  helpcontext(0x00000001),
  custom(DE77BA64-517C-11D1-A2DA-0000F8773CE9, 117441067),
  custom(DE77BA63-517C-11D1-A2DA-0000F8773CE9, 1320262014),
  custom(DE77BA65-517C-11D1-A2DA-0000F8773CE9, Created by MIDL version 7.00.0555 at Wed Nov 02 21:26:53 2011
)

]
library SKYPE4COMLib
{
    // TLib :     // TLib : OLE Automation : {00020430-0000-0000-C000-000000000046}
    importlib("stdole2.tlb");

    // Forward declare all types defined in this typelib
    interface IApplication;
    interface IApplicationStreamCollection;
    interface IApplicationStream;
    interface IUserCollection;
    interface IUser;
    interface ICall;
    interface IParticipantCollection;
    interface IParticipant;
    interface ICallChannel;
    interface ICallChannelManager;
    interface ISkype;
    interface IConversion;
    interface ICallCollection;
    interface IChatMessageCollection;
    interface IChatMessage;
    interface IChat;
    interface IChatMemberCollection;
    interface IChatMember;
    interface ICommand;
    interface IChatCollection;
    interface IConference;
    interface IConferenceCollection;
    interface IVoicemailCollection;
    interface IVoicemail;
    interface IProfile;
    interface IGroupCollection;
    interface IGroup;
    interface ISettings;
    interface IClient;
    interface IPluginEvent;
    interface IPluginMenuItem;
    interface ISmsMessage;
    interface ISmsTargetCollection;
    interface ISmsTarget;
    interface ISmsChunkCollection;
    interface ISmsChunk;
    interface ISmsMessageCollection;
    interface IFileTransferCollection;
    interface IFileTransfer;
    interface ICallChannelCollection;
    interface ICallChannelMessage;
    interface ISkypeApplication;
    interface ISkypeCall;
    interface ISkypeChat;
    interface ISkypeChatMessage;
    interface ISkypeChatMember;
    interface ISkypeConference;
    interface ISkypeFileTransfer;
    interface ISkypeSms;
    interface ISkypeUser;
    interface ISkypeVoicemail;
    dispinterface _ISkypeEvents;
    dispinterface _ICallChannelManagerEvents;
    interface ISkypePlugin;

    [
      odl,
      uuid(F9ADA565-2FAD-424D-878C-7AD12DF9E617),
      helpstring("IApplication interface."),
      helpcontext(0x0000000e),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IApplication : IDispatch {
        [id(0x00000001), propget, helpstring("Returns application name."), helpcontext(0x0000000e)]
        HRESULT Name([out, retval] BSTR* pVal);
        [id(0x00000002), helpstring("Creates application."), helpcontext(0x0000000e)]
        HRESULT Create();
        [id(0x00000003), helpstring("Deletes application."), helpcontext(0x0000000e)]
        HRESULT Delete();
        [id(0x00000004), propget, helpstring("Returns application streams."), helpcontext(0x0000000e)]
        HRESULT Streams([out, retval] IApplicationStreamCollection** pVal);
        [id(0x00000005), propget, helpstring("Returns application connectable users."), helpcontext(0x0000000e)]
        HRESULT ConnectableUsers([out, retval] IUserCollection** pVal);
        [id(0x00000006), propget, helpstring("Returns currently connecting users."), helpcontext(0x0000000e)]
        HRESULT ConnectingUsers([out, retval] IUserCollection** pVal);
        [id(0x00000007), helpstring("Connects application to user."), helpcontext(0x0000000e)]
        HRESULT Connect(
                        [in] BSTR Username, 
                        [in, optional, defaultvalue(0)] VARIANT_BOOL WaitConnected);
        [id(0x00000008), propget, helpstring("Returns application sending streams."), helpcontext(0x0000000e)]
        HRESULT SendingStreams([out, retval] IApplicationStreamCollection** pVal);
        [id(0x00000009), propget, helpstring("Returns application receiving streams."), helpcontext(0x0000000e)]
        HRESULT ReceivedStreams([out, retval] IApplicationStreamCollection** pVal);
        [id(0x0000000a), helpstring("Sends datagram to application streams."), helpcontext(0x0000000e)]
        HRESULT SendDatagram(
                        [in] BSTR Text, 
                        [in, optional, defaultvalue(0)] IApplicationStreamCollection* pStreams);
    };

    [
      odl,
      uuid(D8F1BCC4-2A73-47B9-83B3-D4D299CA5BC6),
      helpstring("IApplicationStreamCollection interface"),
      helpcontext(0x0000003a),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IApplicationStreamCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x0000003a)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x0000003a)]
        HRESULT Add([in] IApplicationStream* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x0000003a)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x0000003a)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x0000003a)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IApplicationStream** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x0000003a)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(E072F615-F833-4BCA-B473-CEE44D302030),
      helpstring("IApplicationStream interface"),
      helpcontext(0x00000038),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IApplicationStream : IDispatch {
        [id(0x00000001), propget, helpstring("Returns application name."), helpcontext(0x00000038)]
        HRESULT ApplicationName([out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns stream handle."), helpcontext(0x00000038)]
        HRESULT Handle([out, retval] BSTR* pVal);
        [id(0x00000003), helpstring("Reads stream."), helpcontext(0x00000038)]
        HRESULT Read([out, retval] BSTR* pText);
        [id(0x00000004), helpstring("Writes stream."), helpcontext(0x00000038)]
        HRESULT Write([in] BSTR Text);
        [id(0x00000005), helpstring("Send datagram on stream."), helpcontext(0x00000038)]
        HRESULT SendDatagram([in] BSTR Text);
        [id(0x00000006), propget, helpstring("Returns stream data length."), helpcontext(0x00000038)]
        HRESULT DataLength([out, retval] long* pVal);
        [id(0x00000007), helpstring("Disconnect stream."), helpcontext(0x00000038)]
        HRESULT Disconnect();
        [id(0x00000008), propget, helpstring("Returns stream partner handle."), helpcontext(0x00000038)]
        HRESULT PartnerHandle([out, retval] BSTR* pVal);
    };

    [
      odl,
      uuid(EC163200-44EB-483B-907F-A8C1CF56B8EE),
      helpstring("IUserCollection Interface"),
      helpcontext(0x00000010),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IUserCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000010)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000010)]
        HRESULT Add([in] IUser* pUser);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000010)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000010)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000010)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IUser** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000010)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(D0BC5168-A518-4192-9D20-0B907B23C4D1),
      helpstring("IUser Interface"),
      helpcontext(0x0000000f),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IUser : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets user handle."), helpcontext(0x0000000f)]
        HRESULT Handle([out, retval] BSTR* pVal);
        [id(0x00000001), propput, helpstring("Returns/sets user handle."), helpcontext(0x0000000f)]
        HRESULT Handle([in] BSTR pVal);
        [id(0x00000002), propget, helpstring("Returns user full name."), helpcontext(0x0000000f)]
        HRESULT FullName([out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns user birthday."), helpcontext(0x0000000f)]
        HRESULT Birthday([out, retval] DATE* pVal);
        [id(0x00000004), propget, helpstring("Returns user sex."), helpcontext(0x0000000f)]
        HRESULT Sex([out, retval] TUserSex* pVal);
        [id(0x00000005), propget, helpstring("Returns user country."), helpcontext(0x0000000f)]
        HRESULT Country([out, retval] BSTR* pVal);
        [id(0x00000006), propget, helpstring("Returns user province."), helpcontext(0x0000000f)]
        HRESULT Province([out, retval] BSTR* pVal);
        [id(0x00000007), propget, helpstring("Returns user city."), helpcontext(0x0000000f)]
        HRESULT City([out, retval] BSTR* pVal);
        [id(0x00000008), propget, helpstring("Returns user home phone number."), helpcontext(0x0000000f)]
        HRESULT PhoneHome([out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns user office phone number."), helpcontext(0x0000000f)]
        HRESULT PhoneOffice([out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns user mobile phone number."), helpcontext(0x0000000f)]
        HRESULT PhoneMobile([out, retval] BSTR* pVal);
        [id(0x0000000b), propget, helpstring("Returns user homepage."), helpcontext(0x0000000f)]
        HRESULT Homepage([out, retval] BSTR* pVal);
        [id(0x0000000c), propget, helpstring("Returns user about text."), helpcontext(0x0000000f)]
        HRESULT About([out, retval] BSTR* pVal);
        [id(0x0000000d), propget, helpstring("Returns true if user has call equipment."), helpcontext(0x0000000f)]
        HRESULT HasCallEquipment([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000e), propget, helpstring("Returns user buddy status."), helpcontext(0x0000000f)]
        HRESULT BuddyStatus([out, retval] TBuddyStatus* pVal);
        [id(0x0000000e), propput, helpstring("Returns user buddy status."), helpcontext(0x0000000f)]
        HRESULT BuddyStatus([in] TBuddyStatus pVal);
        [id(0x0000000f), propget, helpstring("Returns true if user is authorized by current user."), helpcontext(0x0000000f)]
        HRESULT IsAuthorized([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000f), propput, helpstring("Returns true if user is authorized by current user."), helpcontext(0x0000000f)]
        HRESULT IsAuthorized([in] VARIANT_BOOL pVal);
        [id(0x00000010), propget, helpstring("Returns true if user is blocked by current user."), helpcontext(0x0000000f)]
        HRESULT IsBlocked([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000010), propput, helpstring("Returns true if user is blocked by current user."), helpcontext(0x0000000f)]
        HRESULT IsBlocked([in] VARIANT_BOOL pVal);
        [id(0x00000011), propget, helpstring("Returns user display name."), helpcontext(0x0000000f)]
        HRESULT DisplayName([out, retval] BSTR* pVal);
        [id(0x00000012), propget, helpstring("Returns user online status."), helpcontext(0x0000000f)]
        HRESULT OnlineStatus([out, retval] TOnlineStatus* pVal);
        [id(0x00000013), propget, helpstring("Returns timestamp when user was last seen online."), helpcontext(0x0000000f)]
        HRESULT LastOnline([out, retval] DATE* pVal);
        [id(0x00000014), propget, helpstring("Returns user country code."), helpcontext(0x0000000f)]
        HRESULT CountryCode([out, retval] BSTR* pVal);
        [id(0x00000015), propget, helpstring("Returns received authorization request text."), helpcontext(0x0000000f)]
        HRESULT ReceivedAuthRequest([out, retval] BSTR* pVal);
        [id(0x00000016), propget, helpstring("Returns/sets users speed dial code."), helpcontext(0x0000000f)]
        HRESULT SpeedDial([out, retval] BSTR* pVal);
        [id(0x00000016), propput, helpstring("Returns/sets users speed dial code."), helpcontext(0x0000000f)]
        HRESULT SpeedDial([in] BSTR pVal);
        [id(0x00000017), propget, helpstring("Returns true if it is possible to send voicemail to user."), helpcontext(0x0000000f)]
        HRESULT CanLeaveVoicemail([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000018), propget, helpstring("Returns user mood text."), helpcontext(0x0000000f)]
        HRESULT MoodText([out, retval] BSTR* pVal);
        [id(0x00000019), propget, helpstring("Returns user aliases."), helpcontext(0x0000000f)]
        HRESULT Aliases([out, retval] BSTR* pVal);
        [id(0x0000001a), propget, helpstring("Returns user timezone."), helpcontext(0x0000000f)]
        HRESULT Timezone([out, retval] long* pVal);
        [id(0x0000001b), propget, helpstring("Returns user call forward active status."), helpcontext(0x0000000f)]
        HRESULT IsCallForwardActive([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000001c), propget, helpstring("Returns user language name."), helpcontext(0x0000000f)]
        HRESULT Language([out, retval] BSTR* pVal);
        [id(0x0000001d), propget, helpstring("Returns user language code."), helpcontext(0x0000000f)]
        HRESULT LanguageCode([out, retval] BSTR* pVal);
        [id(0x0000001e), propget, helpstring("Returns user video capabilty."), helpcontext(0x0000000f)]
        HRESULT IsVideoCapable([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000001f), propget, helpstring("Returns true if user is SkypeOut contact."), helpcontext(0x0000000f)]
        HRESULT IsSkypeOutContact([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000020), propget, helpstring("Returns user authenticated buddies count."), helpcontext(0x0000000f)]
        HRESULT NumberOfAuthBuddies([out, retval] long* pVal);
        [id(0x00000011), propput, helpstring("Returns user display name."), helpcontext(0x0000000f)]
        HRESULT DisplayName([in] BSTR pVal);
        [id(0x00000023), propget, helpstring("Returns user rich mood text."), helpcontext(0x0000000f)]
        HRESULT RichMoodText([out, retval] BSTR* pVal);
        [id(0x00000024), propget, helpstring("Returns true if user user can receive voicemails."), helpcontext(0x0000000f)]
        HRESULT IsVoicemailCapable([out, retval] VARIANT_BOOL* pVal);
    };

    typedef [uuid(F2E9781B-286D-42C7-8FA3-7DE5C52F286B), helpstring("User sex."), helpcontext(0x00000011)]
    enum {
        usexUnknown = 0xffffffff,
        usexMale = 0,
        usexFemale = 1
    } TUserSex;

    typedef [uuid(5E758C58-F940-476C-B737-8D823737FEBA), helpstring("Buddy status."), helpcontext(0x00000011)]
    enum {
        budUnknown = 0xffffffff,
        budNeverBeenFriend = 0,
        budDeletedFriend = 1,
        budPendingAuthorization = 2,
        budFriend = 3
    } TBuddyStatus;

    typedef [uuid(93F10C8A-D3E5-4E62-9315-1A5D21C9DBC3), helpstring("User online status."), helpcontext(0x00000011)]
    enum {
        olsUnknown = 0xffffffff,
        olsOffline = 0,
        olsOnline = 1,
        olsAway = 2,
        olsNotAvailable = 3,
        olsDoNotDisturb = 4,
        olsSkypeOut = 5,
        olsSkypeMe = 6
    } TOnlineStatus;

    [
      odl,
      uuid(76036886-436C-405F-A96E-7835CCFB82F3),
      helpstring("ICall Interface"),
      helpcontext(0x00000005),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICall : IDispatch {
        [id(0x00000001), propget, helpstring("Returns call id."), helpcontext(0x00000005)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000002), propget, helpstring("Returns call timestamp."), helpcontext(0x00000005)]
        HRESULT Timestamp([out, retval] DATE* pVal);
        [id(0x00000003), propget, helpstring("Returns call partner handle."), helpcontext(0x00000005)]
        HRESULT PartnerHandle([out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns call partner display name."), helpcontext(0x00000005)]
        HRESULT PartnerDisplayName([out, retval] BSTR* pVal);
        [id(0x00000005), propget, helpstring("Returns call conference id."), helpcontext(0x00000005)]
        HRESULT ConferenceId([out, retval] long* pVal);
        [id(0x00000006), propget, helpstring("Returns call type."), helpcontext(0x00000005)]
        HRESULT Type([out, retval] TCallType* pVal);
        [id(0x00000007), propget, helpstring("Returns call status."), helpcontext(0x00000005)]
        HRESULT Status([out, retval] TCallStatus* pVal);
        [id(0x00000007), propput, helpstring("Returns call status."), helpcontext(0x00000005)]
        HRESULT Status([in] TCallStatus pVal);
        [id(0x00000008), propget, helpstring("Returns call failure reason."), helpcontext(0x00000005)]
        HRESULT FailureReason([out, retval] TCallFailureReason* pVal);
        [id(0x00000009), propget, helpstring("Returns call subject."), helpcontext(0x00000005)]
        HRESULT Subject([out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns call PSTN number."), helpcontext(0x00000005)]
        HRESULT PstnNumber([out, retval] BSTR* pVal);
        [id(0x0000000b), propget, helpstring("Returns call duration in seconds."), helpcontext(0x00000005)]
        HRESULT Duration([out, retval] long* pVal);
        [id(0x0000000c), propget, helpstring("Returns call PSTN status."), helpcontext(0x00000005)]
        HRESULT PstnStatus([out, retval] BSTR* pVal);
        [id(0x0000000d), propput, helpstring("Marks call seen."), helpcontext(0x00000005)]
        HRESULT Seen([in] VARIANT_BOOL pVal);
        [id(0x0000000e), helpstring("Puts call on hold."), helpcontext(0x00000005)]
        HRESULT Hold();
        [id(0x0000000f), helpstring("Resumes the held call."), helpcontext(0x00000005)]
        HRESULT Resume();
        [id(0x00000010), helpstring("Ends the call."), helpcontext(0x00000005)]
        HRESULT Finish();
        [id(0x00000011), helpstring("Answers the call."), helpcontext(0x00000005)]
        HRESULT Answer();
        [id(0x00000012), propput, helpstring("Sends valus as DTMF."), helpcontext(0x00000005)]
        HRESULT DTMF([in] BSTR rhs);
        [id(0x00000013), propget, helpstring("Returns conference call participants."), helpcontext(0x00000005)]
        HRESULT Participants([out, retval] IParticipantCollection** pVal);
        [id(0x00000014), helpstring("Joins the call to conference."), helpcontext(0x00000005)]
        HRESULT Join([in] long Id);
        [id(0x00000015), propget, helpstring("Returns voicemail duration in seconds."), helpcontext(0x00000005)]
        HRESULT VmDuration([out, retval] long* pVal);
        [id(0x00000016), propget, helpstring("Returns voicemail allowed duration in seconds."), helpcontext(0x00000005)]
        HRESULT VmAllowedDuration([out, retval] long* pVal);
        [id(0x00000017), propget, helpstring("Returns call video status."), helpcontext(0x00000005)]
        HRESULT VideoStatus([out, retval] TCallVideoStatus* pVal);
        [id(0x00000018), propget, helpstring("Returns call video send status."), helpcontext(0x00000005)]
        HRESULT VideoSendStatus([out, retval] TCallVideoSendStatus* pVal);
        [id(0x00000019), propget, helpstring("Returns call video receive status."), helpcontext(0x00000005)]
        HRESULT VideoReceiveStatus([out, retval] TCallVideoSendStatus* pVal);
        [id(0x0000001a), helpstring("Starts video send."), helpcontext(0x00000005)]
        HRESULT StartVideoSend();
        [id(0x0000001b), helpstring("Stops video send."), helpcontext(0x00000005)]
        HRESULT StopVideoSend();
        [id(0x0000001c), helpstring("Starts video receive."), helpcontext(0x00000005)]
        HRESULT StartVideoReceive();
        [id(0x0000001d), helpstring("Stops video receive."), helpcontext(0x00000005)]
        HRESULT StopVideoReceive();
        [id(0x0000001e), helpstring("Redirects call to voicemail."), helpcontext(0x00000005)]
        HRESULT RedirectToVoicemail();
        [id(0x0000001f), helpstring("Forwards call."), helpcontext(0x00000005)]
        HRESULT Forward();
        [id(0x00000020), propget, helpstring("Returns call rate."), helpcontext(0x00000005)]
        HRESULT Rate([out, retval] long* pVal);
        [id(0x00000021), propget, helpstring("Returns call rate currency."), helpcontext(0x00000005)]
        HRESULT RateCurrency([out, retval] BSTR* pVal);
        [id(0x00000022), propget, helpstring("Returns call rate precision."), helpcontext(0x00000005)]
        HRESULT RatePrecision([out, retval] long* pVal);
        [id(0x00000023), propget, helpstring("Returns/sets call input sound device."), helpcontext(0x00000005)]
        HRESULT InputDevice(
                        [in] TCallIoDeviceType DeviceType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000023), propput, helpstring("Returns/sets call input sound device."), helpcontext(0x00000005)]
        HRESULT InputDevice(
                        [in] TCallIoDeviceType DeviceType, 
                        [in] BSTR pVal);
        [id(0x00000024), propget, helpstring("Returns/sets call output sound device."), helpcontext(0x00000005)]
        HRESULT OutputDevice(
                        [in] TCallIoDeviceType DeviceType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000024), propput, helpstring("Returns/sets call output sound device."), helpcontext(0x00000005)]
        HRESULT OutputDevice(
                        [in] TCallIoDeviceType DeviceType, 
                        [in] BSTR pVal);
        [id(0x00000025), propget, helpstring("Returns/sets call microphone sound device."), helpcontext(0x00000005)]
        HRESULT CaptureMicDevice(
                        [in] TCallIoDeviceType DeviceType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000025), propput, helpstring("Returns/sets call microphone sound device."), helpcontext(0x00000005)]
        HRESULT CaptureMicDevice(
                        [in] TCallIoDeviceType DeviceType, 
                        [in] BSTR pVal);
        [id(0x00000026), propget, helpstring("Returns call sound input status."), helpcontext(0x00000005)]
        HRESULT InputStatus([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000027), propget, helpstring("Returns call forwarder identity."), helpcontext(0x00000005)]
        HRESULT ForwardedBy([out, retval] BSTR* pVal);
        [id(0x0000000d), propget, helpstring("Marks call seen."), helpcontext(0x00000005)]
        HRESULT Seen([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000028), propget, helpstring("Returns true if call can be transferred."), helpcontext(0x00000005)]
        HRESULT CanTransfer(
                        [in] BSTR Target, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000029), propget, helpstring("Returns call transfer status."), helpcontext(0x00000005)]
        HRESULT TransferStatus([out, retval] TCallStatus* pVal);
        [id(0x0000002a), propget, helpstring("Returns true if call transfer is active."), helpcontext(0x00000005)]
        HRESULT TransferActive([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000002b), propget, helpstring("Returns call transferrer identity."), helpcontext(0x00000005)]
        HRESULT TransferredBy([out, retval] BSTR* pVal);
        [id(0x0000002c), propget, helpstring("Returns call transfer target identity."), helpcontext(0x00000005)]
        HRESULT TransferredTo([out, retval] BSTR* pVal);
        [id(0x0000002d), helpstring("Transfers the call to target user."), helpcontext(0x00000005)]
        HRESULT Transfer([in] BSTR Target);
        [id(0x0000002e), propget, helpstring("Returns the target number for incoming SkypeIN calls."), helpcontext(0x00000005)]
        HRESULT TargetIdentity([out, retval] BSTR* pVal);
    };

    typedef [uuid(38667A7C-DF57-4C1D-AC65-F7FC87B0E000), helpstring("Call types."), helpcontext(0x00000011)]
    enum {
        cltUnknown = 0xffffffff,
        cltIncomingPSTN = 0,
        cltOutgoingPSTN = 1,
        cltIncomingP2P = 2,
        cltOutgoingP2P = 3
    } TCallType;

    typedef [uuid(47E3ACA4-04BD-4A4B-AB17-7EBF9FD7F5DE), helpstring("Call status."), helpcontext(0x00000011)]
    enum {
        clsUnknown = 0xffffffff,
        clsUnplaced = 0,
        clsRouting = 1,
        clsEarlyMedia = 2,
        clsFailed = 3,
        clsRinging = 4,
        clsInProgress = 5,
        clsOnHold = 6,
        clsFinished = 7,
        clsMissed = 8,
        clsRefused = 9,
        clsBusy = 10,
        clsCancelled = 11,
        clsLocalHold = 12,
        clsRemoteHold = 13,
        clsVoicemailBufferingGreeting = 14,
        clsVoicemailPlayingGreeting = 15,
        clsVoicemailRecording = 16,
        clsVoicemailUploading = 17,
        clsVoicemailSent = 18,
        clsVoicemailCancelled = 19,
        clsVoicemailFailed = 20,
        clsTransferring = 21,
        clsTransferred = 22
    } TCallStatus;

    typedef [uuid(DCE03024-D231-45D4-AB69-D22C9E2954BA), helpstring("Failure reasons."), helpcontext(0x00000011)]
    enum {
        cfrUnknown = 0xffffffff,
        cfrMiscError = 0,
        cfrUserDoesNotExist = 1,
        cfrUserIsOffline = 2,
        cfrNoProxyFound = 3,
        cfrSessionTerminated = 4,
        cfrNoCommonCodec = 5,
        cfrSoundIOError = 6,
        cfrRemoteDeviceError = 7,
        cfrBlockedByRecipient = 8,
        cfrRecipientNotFriend = 9,
        cfrNotAuthorizedByRecipient = 10,
        cfrSoundRecordingError = 11
    } TCallFailureReason;

    [
      odl,
      uuid(F825FE12-9826-4BD2-BF7E-1ED95B8480FE),
      helpstring("IParticipantCollection Interface"),
      helpcontext(0x00000026),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IParticipantCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000026)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000026)]
        HRESULT Add([in] IParticipant* pParticipant);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000026)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000026)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000026)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IParticipant** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000026)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(F1B2AD09-1961-4336-A6BF-93010B73DE72),
      helpstring("IParticipant Interface"),
      helpcontext(0x00000025),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IParticipant : IDispatch {
        [id(0x00000001), propget, helpstring("Returns conference participant handle."), helpcontext(0x00000025)]
        HRESULT Handle([out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns conference participant display name."), helpcontext(0x00000025)]
        HRESULT DisplayName([out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns conference participant call type."), helpcontext(0x00000025)]
        HRESULT CallType([out, retval] TCallType* pVal);
        [id(0x00000004), propget, helpstring("Returns conference participant call status."), helpcontext(0x00000025)]
        HRESULT CallStatus([out, retval] TCallStatus* pVal);
    };

    typedef [uuid(169E6E65-20F4-47AD-8329-02425CD53769), helpstring("Call video status."), helpcontext(0x00000011)]
    enum {
        cvsUnknown = 0xffffffff,
        cvsNone = 0,
        cvsSendEnabled = 1,
        cvsReceiveEnabled = 2,
        cvsBothEnabled = 3
    } TCallVideoStatus;

    typedef [uuid(944F55CF-F7AC-4955-8368-B89027EBC75C), helpstring("Video send status."), helpcontext(0x00000011)]
    enum {
        vssUnknown = 0xffffffff,
        vssNotAvailable = 0,
        vssAvailable = 1,
        vssStarting = 2,
        vssRejected = 3,
        vssRunning = 4,
        vssStopping = 5,
        vssPaused = 6
    } TCallVideoSendStatus;

    typedef [uuid(8B0D63F5-57EC-4305-8F0D-517B6E85BAD2), helpstring("Audio device type"), helpcontext(0x00000011)]
    enum {
        callIoDeviceTypeUnknown = 0xffffffff,
        callIoDeviceTypeSoundcard = 0,
        callIoDeviceTypePort = 1,
        callIoDeviceTypeFile = 2
    } TCallIoDeviceType;

    [
      odl,
      uuid(B76C04C9-0EB1-4748-B0C0-D01DEB595906),
      helpstring("ICallChannel interface."),
      helpcontext(0x00000043),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICallChannel : IDispatch {
        [id(0x00000002), propget, helpstring("Call channel type."), helpcontext(0x00000043)]
        HRESULT Type([out, retval] TCallChannelType* pVal);
        [id(0x00000002), propput, helpstring("Call channel type."), helpcontext(0x00000043)]
        HRESULT Type([in] TCallChannelType pVal);
        [id(0x00000003), helpstring("Sends text message over channel."), helpcontext(0x00000043)]
        HRESULT SendTextMessage(BSTR Text);
        [id(0x00000004), propget, helpstring("Returns channel data stream."), helpcontext(0x00000043)]
        HRESULT Stream([out, retval] IApplicationStream** pVal);
        [id(0x00000005), propget, helpstring("Returns channel manager object."), helpcontext(0x00000043)]
        HRESULT Manager([out, retval] ICallChannelManager** pVal);
        [id(0x00000006), propget, helpstring("Returns channel call object."), helpcontext(0x00000043)]
        HRESULT Call([out, retval] ICall** pVal);
    };

    typedef [uuid(46FF6EA6-E4B4-4E0A-B079-2E616F633396), helpstring("Call channel types."), helpcontext(0x00000011)]
    enum {
        cctUnknown = 0xffffffff,
        cctDatagram = 0,
        cctReliable = 1
    } TCallChannelType;

    [
      odl,
      uuid(30C27C77-525F-4A3F-B9DD-C5A77C67250D),
      helpstring("ICallChannelManager interface."),
      helpcontext(0x00000045),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICallChannelManager : IDispatch {
        [id(0x00000001), helpstring("Connects to Skype."), helpcontext(0x00000045)]
        HRESULT Connect([in] ISkype* pSkype);
        [id(0x00000002), helpstring("Disconnects from Skype."), helpcontext(0x00000045)]
        HRESULT Disconnect();
        [id(0x00000003), propget, helpstring("Returns call data channels."), helpcontext(0x00000045)]
        HRESULT Channels([out, retval] ICallChannelCollection** pVal);
        [id(0x00000006), propget, helpstring("Returns/sets default data channel type."), helpcontext(0x00000045)]
        HRESULT ChannelType([out, retval] TCallChannelType* pVal);
        [id(0x00000006), propput, helpstring("Returns/sets default data channel type."), helpcontext(0x00000045)]
        HRESULT ChannelType([in] TCallChannelType pVal);
        [id(0x00000007), propget, helpstring("Returns/sets application name."), helpcontext(0x00000045)]
        HRESULT Name([out, retval] BSTR* pVal);
        [id(0x00000007), propput, helpstring("Returns/sets application name."), helpcontext(0x00000045)]
        HRESULT Name([in] BSTR pVal);
        [id(0x00000008), helpstring("Creates application context."), helpcontext(0x00000045)]
        HRESULT CreateApplication([in, optional, defaultvalue("")] BSTR ApplicationName);
        [id(0x00000009), propget, helpstring("Returns application context creation status."), helpcontext(0x00000045)]
        HRESULT Created([out, retval] VARIANT_BOOL* pVal);
    };

    [
      odl,
      uuid(B1878BFE-53D3-402E-8C86-190B19AF70D5),
      helpstring("ISkype Interface"),
      helpcontext(0x0000000d),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkype : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets Skype API wait timeout in milliseconds."), helpcontext(0x0000000d)]
        HRESULT Timeout([out, retval] long* pVal);
        [id(0x00000001), propput, helpstring("Returns/sets Skype API wait timeout in milliseconds."), helpcontext(0x0000000d)]
        HRESULT Timeout([in] long pVal);
        [id(0x00000002), propget, helpstring("Returns/sets USER, CALL, CHAT, CHATMESSAGE or VOICEMAIL object property value."), helpcontext(0x0000000d)]
        HRESULT Property(
                        [in] BSTR ObjectType, 
                        [in] BSTR ObjectId, 
                        [in] BSTR PropName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000002), propput, helpstring("Returns/sets USER, CALL, CHAT, CHATMESSAGE or VOICEMAIL object property value."), helpcontext(0x0000000d)]
        HRESULT Property(
                        [in] BSTR ObjectType, 
                        [in] BSTR ObjectId, 
                        [in] BSTR PropName, 
                        [in] BSTR pVal);
        [id(0x00000003), propget, helpstring("Returns/sets general variable value."), helpcontext(0x0000000d)]
        HRESULT Variable(
                        [in] BSTR Name, 
                        [out, retval] BSTR* pVal);
        [id(0x00000003), propput, helpstring("Returns/sets general variable value."), helpcontext(0x0000000d)]
        HRESULT Variable(
                        [in] BSTR Name, 
                        [in] BSTR pVal);
        [id(0x00000004), propget, helpstring("Returns current user handle."), helpcontext(0x0000000d)]
        HRESULT CurrentUserHandle([out, retval] BSTR* pVal);
        [id(0x00000005), propget, helpstring("Returns/sets current user online status."), helpcontext(0x0000000d)]
        HRESULT CurrentUserStatus([out, retval] TUserStatus* pVal);
        [id(0x00000005), propput, helpstring("Returns/sets current user online status."), helpcontext(0x0000000d)]
        HRESULT CurrentUserStatus([in] TUserStatus pVal);
        [id(0x00000006), propget, helpstring("Returns connection status."), helpcontext(0x0000000d)]
        HRESULT ConnectionStatus([out, retval] TConnectionStatus* pVal);
        [id(0x00000007), propget, helpstring("Returns/sets mute status."), helpcontext(0x0000000d)]
        HRESULT Mute([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000007), propput, helpstring("Returns/sets mute status."), helpcontext(0x0000000d)]
        HRESULT Mute([in] VARIANT_BOOL pVal);
        [id(0x00000008), propget, helpstring("Returns Skype application version."), helpcontext(0x0000000d)]
        HRESULT Version([out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns current user privilege."), helpcontext(0x0000000d)]
        HRESULT Privilege(
                        [in] BSTR Name, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000a), propget, helpstring("Returns current user object."), helpcontext(0x0000000d)]
        HRESULT CurrentUser([out, retval] IUser** pVal);
        [id(0x0000000b), propget, helpstring("Returns conversion object."), helpcontext(0x0000000d)]
        HRESULT Convert([out, retval] IConversion** pVal);
        [id(0x0000000c), propget, helpstring("Returns collection of users in the friends list."), helpcontext(0x0000000d)]
        HRESULT Friends([out, retval] IUserCollection** pVal);
        [id(0x0000000d), helpstring("Returns collection of users found as the result of search operation."), helpcontext(0x0000000d)]
        HRESULT SearchForUsers(
                        [in] BSTR Target, 
                        [out, retval] IUserCollection** pVal);
        [id(0x0000000e), propget, helpstring("Returns collection of calls in the call history."), helpcontext(0x0000000d)]
        HRESULT Calls(
                        [in, optional, defaultvalue("")] BSTR Target, 
                        [out, retval] ICallCollection** pVal);
        [id(0x0000000f), propget, helpstring("Returns collection of currently active calls."), helpcontext(0x0000000d)]
        HRESULT ActiveCalls([out, retval] ICallCollection** pVal);
        [id(0x00000010), propget, helpstring("Returns collection of missed calls."), helpcontext(0x0000000d)]
        HRESULT MissedCalls([out, retval] ICallCollection** pVal);
        [id(0x00000011), propget, helpstring("Returns chat messages."), helpcontext(0x0000000d)]
        HRESULT Messages(
                        [in, optional, defaultvalue("")] BSTR Target, 
                        [out, retval] IChatMessageCollection** pVal);
        [id(0x00000012), propget, helpstring("Returns collection of missed messages."), helpcontext(0x0000000d)]
        HRESULT MissedMessages([out, retval] IChatMessageCollection** pVal);
        [id(0x00000013), propget, helpstring("Returns Skype API attachment status."), helpcontext(0x0000000d)]
        HRESULT AttachmentStatus([out, retval] TAttachmentStatus* pVal);
        [id(0x00000014), propget, helpstring("Returns/sets Skype API protocol version."), helpcontext(0x0000000d)]
        HRESULT Protocol([out, retval] long* pVal);
        [id(0x00000014), propput, helpstring("Returns/sets Skype API protocol version."), helpcontext(0x0000000d)]
        HRESULT Protocol([in] long pVal);
        [id(0x00000015), helpstring("Connects to Skype API."), helpcontext(0x0000000d)]
        HRESULT Attach(
                        [in, optional, defaultvalue(5)] long Protocol, 
                        [in, optional, defaultvalue(-1)] VARIANT_BOOL Wait);
        [id(0x00000016), helpstring("Calls specified target and returns a new call object."), helpcontext(0x0000000d)]
        HRESULT PlaceCall(
                        [in] BSTR Target, 
                        [in, optional, defaultvalue("")] BSTR Target2, 
                        [in, optional, defaultvalue("")] BSTR Target3, 
                        [in, optional, defaultvalue("")] BSTR Target4, 
                        [out, retval] ICall** pCall);
        [id(0x00000017), helpstring("Sends IM message to specified user and returns a new message object."), helpcontext(0x0000000d)]
        HRESULT SendMessage(
                        [in] BSTR Username, 
                        [in] BSTR Text, 
                        [out, retval] IChatMessage** pMessage);
        [id(0x00000018), propget, helpstring("Returns a new user object."), helpcontext(0x0000000d)]
        HRESULT User(
                        [in, optional, defaultvalue("")] BSTR Username, 
                        [out, retval] IUser** pVal);
        [id(0x00000019), propget, helpstring("Returns a new message object."), helpcontext(0x0000000d)]
        HRESULT Message(
                        [in, optional, defaultvalue(0)] long Id, 
                        [out, retval] IChatMessage** pVal);
        [id(0x0000001a), propget, helpstring("Returns a new call object."), helpcontext(0x0000000d)]
        HRESULT Call(
                        [in, optional, defaultvalue(0)] long Id, 
                        [out, retval] ICall** pVal);
        [id(0x0000001b), helpstring("Sends Skype API command."), helpcontext(0x0000000d)]
        HRESULT SendCommand([in] ICommand* pCommand);
        [id(0x0000001c), propget, helpstring("Returns user IM conversations."), helpcontext(0x0000000d)]
        HRESULT Chats([out, retval] IChatCollection** pVal);
        [id(0x0000001d), propget, helpstring("Returns new chat object."), helpcontext(0x0000000d)]
        HRESULT Chat(
                        [in, optional, defaultvalue("")] BSTR Name, 
                        [out, retval] IChat** pVal);
        [id(0x0000001e), helpstring("Changes current user online status."), helpcontext(0x0000000d)]
        HRESULT ChangeUserStatus([in] TUserStatus newVal);
        [id(0x0000001f), propget, helpstring("Returns a new conference object."), helpcontext(0x0000000d)]
        HRESULT Conference(
                        [in, optional, defaultvalue(0)] long Id, 
                        [out, retval] IConference** pVal);
        [id(0x00000020), propget, helpstring("Returns collection of conferences."), helpcontext(0x0000000d)]
        HRESULT Conferences([out, retval] IConferenceCollection** pVal);
        [id(0x00000021), propget, helpstring("Returns user profile property value."), helpcontext(0x0000000d)]
        HRESULT Profile(
                        [in] BSTR Property, 
                        [out, retval] BSTR* pVal);
        [id(0x00000021), propput, helpstring("Returns user profile property value."), helpcontext(0x0000000d)]
        HRESULT Profile(
                        [in] BSTR Property, 
                        [in] BSTR pVal);
        [id(0x00000022), propget, helpstring("Returns active chats."), helpcontext(0x0000000d)]
        HRESULT ActiveChats([out, retval] IChatCollection** pVal);
        [id(0x00000023), propget, helpstring("Returns missed chats."), helpcontext(0x0000000d)]
        HRESULT MissedChats([out, retval] IChatCollection** pVal);
        [id(0x00000024), propget, helpstring("Returns most recent chats."), helpcontext(0x0000000d)]
        HRESULT RecentChats([out, retval] IChatCollection** pVal);
        [id(0x00000025), propget, helpstring("Returns bookmarked chats."), helpcontext(0x0000000d)]
        HRESULT BookmarkedChats([out, retval] IChatCollection** pVal);
        [id(0x00000026), helpstring("Creates a new chat with a single user."), helpcontext(0x0000000d)]
        HRESULT CreateChatWith(
                        [in] BSTR Username, 
                        [out, retval] IChat** pVal);
        [id(0x00000027), helpstring("Creates a new chat with multiple members."), helpcontext(0x0000000d)]
        HRESULT CreateChatMultiple(
                        [in] IUserCollection* pMembers, 
                        [out, retval] IChat** pChat);
        [id(0x00000028), propget, helpstring("Retuns voicemails."), helpcontext(0x0000000d)]
        HRESULT Voicemails([out, retval] IVoicemailCollection** pVal);
        [id(0x00000029), helpstring("Sends voicemail to specified user."), helpcontext(0x0000000d)]
        HRESULT SendVoicemail(
                        [in] BSTR Username, 
                        [out, retval] IVoicemail** pVoicemail);
        [id(0x0000002a), propget, helpstring("Returns users waiting authorization."), helpcontext(0x0000000d)]
        HRESULT UsersWaitingAuthorization([out, retval] IUserCollection** pVal);
        [id(0x0000002b), helpstring("Clears chat history."), helpcontext(0x0000000d)]
        HRESULT ClearChatHistory();
        [id(0x0000002c), helpstring("Clears voicemail history."), helpcontext(0x0000000d)]
        HRESULT ClearVoicemailHistory();
        [id(0x0000002d), helpstring("Clears call history."), helpcontext(0x0000000d)]
        HRESULT ClearCallHistory(
                        [in, optional, defaultvalue("ALL")] BSTR Username, 
                        [in, optional, defaultvalue(0)] TCallHistory Type);
        [id(0x0000002e), propget, helpstring("Returns/sets automatic command identifiers."), helpcontext(0x0000000d)]
        HRESULT CommandId([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000002e), propput, helpstring("Returns/sets automatic command identifiers."), helpcontext(0x0000000d)]
        HRESULT CommandId([in] VARIANT_BOOL pVal);
        [id(0x0000002f), propget, helpstring("Returns new application object."), helpcontext(0x0000000d)]
        HRESULT Application(
                        [in] BSTR Name, 
                        [out, retval] IApplication** pVal);
        [id(0x00000030), propget, helpstring("Returns user greeting."), helpcontext(0x0000000d)]
        HRESULT Greeting(
                        [in, optional, defaultvalue("")] BSTR Username, 
                        [out, retval] IVoicemail** pVal);
        [id(0x00000031), propget, helpstring("Enables/disables internal API cache."), helpcontext(0x0000000d)]
        HRESULT Cache([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000031), propput, helpstring("Enables/disables internal API cache."), helpcontext(0x0000000d)]
        HRESULT Cache([in] VARIANT_BOOL pVal);
        [id(0x00000032), helpstring("Empties command cache."), helpcontext(0x0000000d)]
        HRESULT ResetCache();
        [id(0x00000033), propget, helpstring("Returns logged-in user profile object."), helpcontext(0x0000000d)]
        HRESULT CurrentUserProfile([out, retval] IProfile** pVal);
        [id(0x00000034), propget, helpstring("Returns all contact groups."), helpcontext(0x0000000d)]
        HRESULT Groups([out, retval] IGroupCollection** pVal);
        [id(0x00000035), propget, helpstring("Returns user defined contact groups."), helpcontext(0x0000000d)]
        HRESULT CustomGroups([out, retval] IGroupCollection** pVal);
        [id(0x00000036), propget, helpstring("Returns predefined contact groups."), helpcontext(0x0000000d)]
        HRESULT HardwiredGroups([out, retval] IGroupCollection** pVal);
        [id(0x00000037), helpstring("Creates a new custom group."), helpcontext(0x0000000d)]
        HRESULT CreateGroup(
                        [in] BSTR GroupName, 
                        [out, retval] IGroup** pGroup);
        [id(0x00000038), helpstring("Deletes a custom group."), helpcontext(0x0000000d)]
        HRESULT DeleteGroup([in] long GroupId);
        [id(0x00000039), propget, helpstring("Returns settings object."), helpcontext(0x0000000d)]
        HRESULT Settings([out, retval] ISettings** pVal);
        [id(0x0000003a), propget, helpstring("Returns client object."), helpcontext(0x0000000d)]
        HRESULT Client([out, retval] IClient** pVal);
        [id(0x0000003b), propput, helpstring("Sets application display name."), helpcontext(0x0000000d)]
        HRESULT FriendlyName([in] BSTR rhs);
        [id(0x0000003c), propget, helpstring("Returns a new command object."), helpcontext(0x0000000d)]
        HRESULT Command(
                        [in] long Id, 
                        [in] BSTR Command, 
                        [in, optional, defaultvalue("")] BSTR Reply, 
                        [in, optional, defaultvalue(0)] VARIANT_BOOL Block, 
                        [in, optional, defaultvalue(30000)] long Timeout, 
                        [out, retval] ICommand** pVal);
        [id(0x0000003d), propget, helpstring("Returns voicemail object."), helpcontext(0x0000000d)]
        HRESULT Voicemail(
                        [in] long Id, 
                        [out, retval] IVoicemail** pVal);
        [id(0x0000003e), propget, helpstring("Returns missed voicemails."), helpcontext(0x0000000d)]
        HRESULT MissedVoicemails([out, retval] IVoicemailCollection** pVal);
        [id(0x0000003f), hidden, helpstring("Enables API security contexts."), helpcontext(0x0000000d)]
        HRESULT EnableApiSecurityContext([in] TApiSecurityContext Context);
        [id(0x00000040), propget, hidden, helpstring("Checks for enabled API security contexts."), helpcontext(0x0000000d)]
        HRESULT ApiSecurityContextEnabled(
                        [in] TApiSecurityContext Context, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000041), helpstring("Returns new SMS object."), helpcontext(0x0000000d)]
        HRESULT CreateSms(
                        [in] TSmsMessageType MessageType, 
                        [in] BSTR TargetNumbers, 
                        [out, retval] ISmsMessage** pMessage);
        [id(0x00000042), propget, helpstring("Returns SMS messages."), helpcontext(0x0000000d)]
        HRESULT Smss([out, retval] ISmsMessageCollection** pVal);
        [id(0x00000043), propget, helpstring("Returns missed SMS messages."), helpcontext(0x0000000d)]
        HRESULT MissedSmss([out, retval] ISmsMessageCollection** pVal);
        [id(0x00000044), helpstring("Sends a SMS messages."), helpcontext(0x0000000d)]
        HRESULT SendSms(
                        [in] BSTR TargetNumbers, 
                        [in] BSTR MessageText, 
                        [in, optional, defaultvalue("")] BSTR ReplyToNumber, 
                        [out, retval] ISmsMessage** pMessage);
        [id(0x00000045), helpstring("Search for Skype users."), helpcontext(0x0000000d)]
        HRESULT AsyncSearchUsers(
                        [in] BSTR Target, 
                        [out, retval] long* pCookie);
        [id(0x00000046), propget, helpstring("Returns API wrapper version."), helpcontext(0x0000000d)]
        HRESULT ApiWrapperVersion([out, retval] BSTR* pVal);
        [id(0x00000047), propget, helpstring("Returns/sets silent mode."), helpcontext(0x0000000d)]
        HRESULT SilentMode([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000047), propput, helpstring("Returns/sets silent mode."), helpcontext(0x0000000d)]
        HRESULT SilentMode([in] VARIANT_BOOL pVal);
        [id(0x00000048), propget, helpstring("Returns file transfers."), helpcontext(0x0000000d)]
        HRESULT FileTransfers([out, retval] IFileTransferCollection** pVal);
        [id(0x00000049), propget, helpstring("Returns active file transfers."), helpcontext(0x0000000d)]
        HRESULT ActiveFileTransfers([out, retval] IFileTransferCollection** pVal);
        [id(0x0000004a), propget, helpstring("Returns focused contacts."), helpcontext(0x0000000d)]
        HRESULT FocusedContacts([out, retval] IUserCollection** pVal);
        [id(0x0000004b), helpstring("Returns chat mathing the blob."), helpcontext(0x0000000d)]
        HRESULT FindChatUsingBlob(
                        [in] BSTR Blob, 
                        [out, retval] IChat** pChat);
        [id(0x0000004c), helpstring("Returns chat mathing the blob, optionally creating the chat."), helpcontext(0x0000000d)]
        HRESULT CreateChatUsingBlob(
                        [in] BSTR Blob, 
                        [out, retval] IChat** pChat);
        [id(0x0000004d), propget, helpcontext(0x0000000d)]
        HRESULT PredictiveDialerCountry([out, retval] BSTR* pVal);
    };

    typedef [uuid(FBAB58DC-9C60-4EE6-9826-26EE2335DD0A), helpstring("Current user status."), helpcontext(0x00000011)]
    enum {
        cusUnknown = 0xffffffff,
        cusOffline = 0,
        cusOnline = 1,
        cusAway = 2,
        cusNotAvailable = 3,
        cusDoNotDisturb = 4,
        cusInvisible = 5,
        cusLoggedOut = 6,
        cusSkypeMe = 7
    } TUserStatus;

    typedef [uuid(69658FFD-F587-4946-A4EC-7C0709EA9F44), helpstring("Connection status."), helpcontext(0x00000011)]
    enum {
        conUnknown = 0xffffffff,
        conOffline = 0,
        conConnecting = 1,
        conPausing = 2,
        conOnline = 3
    } TConnectionStatus;

    [
      odl,
      uuid(8D82F88A-B307-4074-8ED5-11C3BD213452),
      helpstring("IConversion Interface"),
      helpcontext(0x0000000a),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IConversion : IDispatch {
        [id(0x00000001), helpstring("Returns online status as text."), helpcontext(0x0000000a)]
        HRESULT OnlineStatusToText(
                        [in] TOnlineStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000002), helpstring("Returns online status code."), helpcontext(0x0000000a)]
        HRESULT TextToOnlineStatus(
                        [in] BSTR Text, 
                        [out, retval] TOnlineStatus* pVal);
        [id(0x00000003), helpstring("Returns buddy status as text."), helpcontext(0x0000000a)]
        HRESULT BuddyStatusToText(
                        [in] TBuddyStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000004), helpstring("Returns buddy status code."), helpcontext(0x0000000a)]
        HRESULT TextToBuddyStatus(
                        [in] BSTR Text, 
                        [out, retval] TBuddyStatus* pVal);
        [id(0x00000005), helpstring("Returns call status as text."), helpcontext(0x0000000a)]
        HRESULT CallStatusToText(
                        [in] TCallStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000006), helpstring("Returns call status code."), helpcontext(0x0000000a)]
        HRESULT TextToCallStatus(
                        [in] BSTR Text, 
                        [out, retval] TCallStatus* pVal);
        [id(0x00000007), helpstring("Returns call type as text."), helpcontext(0x0000000a)]
        HRESULT CallTypeToText(
                        [in] TCallType CallType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000008), helpstring("Returns call type code."), helpcontext(0x0000000a)]
        HRESULT TextToCallType(
                        [in] BSTR Text, 
                        [out, retval] TCallType* pVal);
        [id(0x00000009), helpstring("Returns user sex as text."), helpcontext(0x0000000a)]
        HRESULT UserSexToText(
                        [in] TUserSex Sex, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000a), helpstring("Returns user sex code."), helpcontext(0x0000000a)]
        HRESULT TextToUserSex(
                        [in] BSTR Text, 
                        [out, retval] TUserSex* pVal);
        [id(0x0000000b), helpstring("Returns connection status as text."), helpcontext(0x0000000a)]
        HRESULT ConnectionStatusToText(
                        [in] TConnectionStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000c), helpstring("Returns connection status code."), helpcontext(0x0000000a)]
        HRESULT TextToConnectionStatus(
                        [in] BSTR Text, 
                        [out, retval] TConnectionStatus* pVal);
        [id(0x0000000d), helpstring("Returns user status as text."), helpcontext(0x0000000a)]
        HRESULT UserStatusToText(
                        [in] TUserStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000e), helpstring("Returns user status code."), helpcontext(0x0000000a)]
        HRESULT TextToUserStatus(
                        [in] BSTR Text, 
                        [out, retval] TUserStatus* pVal);
        [id(0x0000000f), helpstring("Returns failure reason as text."), helpcontext(0x0000000a)]
        HRESULT CallFailureReasonToText(
                        [in] TCallFailureReason reason, 
                        [out, retval] BSTR* pVal);
        [id(0x00000010), helpstring("Returns attachment status as text."), helpcontext(0x0000000a)]
        HRESULT AttachmentStatusToText(
                        [in] TAttachmentStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000011), helpstring("Returns leave reason as text."), helpcontext(0x0000000a)]
        HRESULT ChatLeaveReasonToText(
                        [in] TChatLeaveReason reason, 
                        [out, retval] BSTR* pVal);
        [id(0x00000012), helpstring("Returns chatr status as text."), helpcontext(0x0000000a)]
        HRESULT ChatStatusToText(
                        [in] TChatStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000013), helpstring("Returns voicemail type as text."), helpcontext(0x0000000a)]
        HRESULT VoicemailTypeToText(
                        [in] TVoicemailType Type, 
                        [out, retval] BSTR* pVal);
        [id(0x00000014), helpstring("Returns voicemail status as text."), helpcontext(0x0000000a)]
        HRESULT VoicemailStatusToText(
                        [in] TVoicemailStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000015), helpstring("Returns voicemail status code."), helpcontext(0x0000000a)]
        HRESULT TextToVoicemailStatus(
                        [in] BSTR Text, 
                        [out, retval] TVoicemailStatus* pVal);
        [id(0x00000016), helpstring("Returns voicemail failure reason as text."), helpcontext(0x0000000a)]
        HRESULT VoicemailFailureReasonToText(
                        [in] TVoicemailFailureReason code, 
                        [out, retval] BSTR* pVal);
        [id(0x00000017), helpstring("Returns message status as text."), helpcontext(0x0000000a)]
        HRESULT ChatMessageStatusToText(
                        [in] TChatMessageStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000018), helpstring("Returns message status code."), helpcontext(0x0000000a)]
        HRESULT TextToChatMessageStatus(
                        [in] BSTR Text, 
                        [out, retval] TChatMessageStatus* pVal);
        [id(0x00000019), helpstring("Returns message type as text."), helpcontext(0x0000000a)]
        HRESULT ChatMessageTypeToText(
                        [in] TChatMessageType Type, 
                        [out, retval] BSTR* pVal);
        [id(0x0000001a), helpstring("Returns message type code."), helpcontext(0x0000000a)]
        HRESULT TextToChatMessageType(
                        [in] BSTR Text, 
                        [out, retval] TChatMessageType* pVal);
        [id(0x0000001b), helpstring("Returns attachment status code."), helpcontext(0x0000000a)]
        HRESULT TextToAttachmentStatus(
                        [in] BSTR Text, 
                        [out, retval] TAttachmentStatus* pVal);
        [id(0x0000001c), helpstring("Returns group type as text."), helpcontext(0x0000000a)]
        HRESULT GroupTypeToText(
                        [in] TGroupType Type, 
                        [out, retval] BSTR* pVal);
        [id(0x0000001d), helpstring("Returns group type code."), helpcontext(0x0000000a)]
        HRESULT TextToGroupType(
                        [in] BSTR Text, 
                        [out, retval] TGroupType* pVal);
        [id(0x0000001e), helpstring("Returns call video status as text."), helpcontext(0x0000000a)]
        HRESULT CallVideoStatusToText(
                        [in] TCallVideoStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x0000001f), helpstring("Returns call video send status as text."), helpcontext(0x0000000a)]
        HRESULT CallVideoSendStatusToText(
                        [in] TCallVideoSendStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000020), propget, helpstring("Returns/sets text conversion language."), helpcontext(0x0000000a)]
        HRESULT Language([out, retval] BSTR* pVal);
        [id(0x00000020), propput, helpstring("Returns/sets text conversion language."), helpcontext(0x0000000a)]
        HRESULT Language([in] BSTR pVal);
        [id(0x00000021), helpstring("Returns SMS message status as text."), helpcontext(0x0000000a)]
        HRESULT SmsMessageStatusToText(
                        [in] TSmsMessageStatus Status, 
                        [out, retval] BSTR* pVal);
        [id(0x00000022), helpstring("Returns SMS message type as text."), helpcontext(0x0000000a)]
        HRESULT SmsMessageTypeToText(
                        [in] TSmsMessageType Type, 
                        [out, retval] BSTR* pVal);
        [id(0x00000023), helpstring("Returns SMS target status as text."), helpcontext(0x0000000a)]
        HRESULT SmsTargetStatusToText(
                        [in] TSmsTargetStatus Status, 
                        [out, retval] BSTR* pVal);
    };

    typedef [uuid(74A50AB8-1E6F-4246-8933-08E4FBBCF4E5), helpstring("API attachment status."), helpcontext(0x00000011)]
    enum {
        apiAttachUnknown = 0xffffffff,
        apiAttachSuccess = 0,
        apiAttachPendingAuthorization = 1,
        apiAttachRefused = 2,
        apiAttachNotAvailable = 3,
        apiAttachAvailable = 4
    } TAttachmentStatus;

    typedef [uuid(FCDEF5B9-BAE9-4213-815F-0F68C7A8F03E), helpstring("Leave reasons."), helpcontext(0x00000011)]
    enum {
        leaUnknown = 0xffffffff,
        leaUserNotFound = 0,
        leaUserIncapable = 1,
        leaAdderNotFriend = 2,
        leaAddedNotAuthorized = 3,
        leaAddDeclined = 4,
        leaUnsubscribe = 5
    } TChatLeaveReason;

    typedef [uuid(D90B58CC-53AA-4A8C-8774-4B48BF307D9B), helpstring("Chat status."), helpcontext(0x00000011)]
    enum {
        chsUnknown = 0xffffffff,
        chsLegacyDialog = 0,
        chsDialog = 1,
        chsMultiNeedAccept = 2,
        chsMultiSubscribed = 3,
        chsUnsubscribed = 4
    } TChatStatus;

    typedef [uuid(7771BE16-D5F0-4368-8A88-643B5B519A43), helpstring("Voicemail type."), helpcontext(0x00000011)]
    enum {
        vmtUnknown = 0xffffffff,
        vmtIncoming = 0,
        vmtDefaultGreeting = 1,
        vmtCustomGreeting = 2,
        vmtOutgoing = 3
    } TVoicemailType;

    typedef [uuid(F9810AFA-DBC3-4327-9876-E94A47E7CED5), helpstring("Voicemail status."), helpcontext(0x00000011)]
    enum {
        vmsUnknown = 0xffffffff,
        vmsNotDownloaded = 0,
        vmsDownloading = 1,
        vmsUnplayed = 2,
        vmsBuffering = 3,
        vmsPlaying = 4,
        vmsPlayed = 5,
        vmsBlank = 6,
        vmsRecording = 7,
        vmsRecorded = 8,
        vmsUploading = 9,
        vmsUploaded = 10,
        vmsDeleting = 11,
        vmsFailed = 12
    } TVoicemailStatus;

    typedef [uuid(977E2F50-2361-4E81-B9F3-2303B8C8BB49), helpstring("Voicemail failure reason."), helpcontext(0x00000011)]
    enum {
        vmrUnknown = 0xffffffff,
        vmrNoError = 0,
        vmrMiscError = 1,
        vmrConnectError = 2,
        vmrNoPrivilege = 3,
        vmrNoVoicemail = 4,
        vmrFileReadError = 5,
        vmrFileWriteError = 6,
        vmrRecordingError = 7,
        vmrPlaybackError = 8
    } TVoicemailFailureReason;

    typedef [uuid(6CF9ED72-45D0-479E-936A-EB34B748661E), helpstring("Chatmessage status."), helpcontext(0x00000011)]
    enum {
        cmsUnknown = 0xffffffff,
        cmsSending = 0,
        cmsSent = 1,
        cmsReceived = 2,
        cmsRead = 3
    } TChatMessageStatus;

    typedef [uuid(28B277BA-2D86-467D-BB47-A805A15585C1), helpstring("Chatmessage types."), helpcontext(0x00000011)]
    enum {
        cmeUnknown = 0xffffffff,
        cmeCreatedChatWith = 0,
        cmeSawMembers = 1,
        cmeAddedMembers = 2,
        cmeSetTopic = 3,
        cmeSaid = 4,
        cmeLeft = 5,
        cmeEmoted = 6,
        cmePostedContacts = 7,
        cmeGapInChat = 8,
        cmeSetRole = 9,
        cmeKicked = 10,
        cmeSetOptions = 11,
        cmeKickBanned = 12,
        cmeJoinedAsApplicant = 13,
        cmeSetPicture = 14,
        cmeSetGuidelines = 15
    } TChatMessageType;

    typedef [uuid(4015AAE2-C9AD-40E6-A06C-A1609840CCDD), helpstring("Contact group types."), helpcontext(0x00000011)]
    enum {
        grpUnknown = 0xffffffff,
        grpCustomGroup = 0,
        grpAllUsers = 1,
        grpAllFriends = 2,
        grpSkypeFriends = 3,
        grpSkypeOutFriends = 4,
        grpOnlineFriends = 5,
        grpPendingAuthorizationFriends = 6,
        grpRecentlyContactedUsers = 7,
        grpUsersWaitingMyAuthorization = 8,
        grpUsersAuthorizedByMe = 9,
        grpUsersBlockedByMe = 10,
        grpUngroupedFriends = 11,
        grpSharedGroup = 12,
        grpProposedSharedGroup = 13
    } TGroupType;

    typedef [uuid(531F8BE0-6AB6-4521-A998-6C87BB9E5D5C), helpstring("SMS message status"), helpcontext(0x00000011)]
    enum {
        smsMessageStatusUnknown = 0xffffffff,
        smsMessageStatusReceived = 0,
        smsMessageStatusRead = 1,
        smsMessageStatusComposing = 2,
        smsMessageStatusSendingToServer = 3,
        smsMessageStatusSentToServer = 4,
        smsMessageStatusDelivered = 5,
        smsMessageStatusSomeTargetsFailed = 6,
        smsMessageStatusFailed = 7
    } TSmsMessageStatus;

    typedef [uuid(48A2B076-BA6A-433B-8065-314987C89CC1), helpstring("SMS message types"), helpcontext(0x00000011)]
    enum {
        smsMessageTypeUnknown = 0xffffffff,
        smsMessageTypeIncoming = 0,
        smsMessageTypeOutgoing = 1,
        smsMessageTypeCCRequest = 2,
        smsMessageTypeCCSubmit = 3
    } TSmsMessageType;

    typedef [uuid(34F2A71C-D453-4199-AB29-5B6E17B3FB5E), helpstring("SMS target statuses"), helpcontext(0x00000011)]
    enum {
        smsTargetStatusUnknown = 0xffffffff,
        smsTargetStatusUndefined = 0,
        smsTargetStatusAnalyzing = 1,
        smsTargetStatusAcceptable = 2,
        smsTargetStatusNotRoutable = 3,
        smsTargetStatusDeliveryPending = 4,
        smsTargetStatusDeliverySuccessful = 5,
        smsTargetStatusDeliveryFailed = 6
    } TSmsTargetStatus;

    [
      odl,
      uuid(72E1EC13-0DF9-48AE-8A31-E2900D85BA55),
      helpstring("ICallCollection Interface"),
      helpcontext(0x00000006),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICallCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000006)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000006)]
        HRESULT Add([in] ICall* pCall);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000006)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000006)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000006)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] ICall** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000006)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(9511117A-7BCA-4669-BE96-6EA6866975C1),
      helpstring("IChatMessageCollection Interface"),
      helpcontext(0x0000000c),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IChatMessageCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x0000000c)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x0000000c)]
        HRESULT Add([in] IChatMessage* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x0000000c)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x0000000c)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x0000000c)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IChatMessage** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x0000000c)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(4CFF5C70-3C95-4566-824A-FA164586D535),
      helpstring("IChatMessage interface"),
      helpcontext(0x0000000b),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IChatMessage : IDispatch {
        [id(0x00000001), propget, helpstring("Returns message id."), helpcontext(0x0000000b)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000002), propget, helpstring("Returns message timestamp."), helpcontext(0x0000000b)]
        HRESULT Timestamp([out, retval] DATE* pVal);
        [id(0x00000003), propget, helpstring("Returns message from handle."), helpcontext(0x0000000b)]
        HRESULT FromHandle([out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns message from display name."), helpcontext(0x0000000b)]
        HRESULT FromDisplayName([out, retval] BSTR* pVal);
        [id(0x00000005), propget, helpstring("Returns message type."), helpcontext(0x0000000b)]
        HRESULT Type([out, retval] TChatMessageType* pVal);
        [id(0x00000006), propget, helpstring("Returns message status."), helpcontext(0x0000000b)]
        HRESULT Status([out, retval] TChatMessageStatus* pVal);
        [id(0x00000007), propget, helpstring("Returns chat leave reason."), helpcontext(0x0000000b)]
        HRESULT LeaveReason([out, retval] TChatLeaveReason* pVal);
        [id(0x00000008), propget, helpstring("Returns/sets message body."), helpcontext(0x0000000b)]
        HRESULT Body([out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns chat name."), helpcontext(0x0000000b)]
        HRESULT ChatName([out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns people added to chat."), helpcontext(0x0000000b)]
        HRESULT Users([out, retval] IUserCollection** pVal);
        [id(0x0000000b), propput, helpstring("Sets message seen status."), helpcontext(0x0000000b)]
        HRESULT Seen([in] VARIANT_BOOL rhs);
        [id(0x0000000c), propget, helpstring("Returns message chat object."), helpcontext(0x0000000b)]
        HRESULT Chat([out, retval] IChat** pVal);
        [id(0x0000000d), propget, helpstring("Returns message sender."), helpcontext(0x0000000b)]
        HRESULT Sender([out, retval] IUser** pVal);
        [id(0x0000000e), propget, helpstring("Returns last message editor Skypename."), helpcontext(0x0000000b)]
        HRESULT EditedBy([out, retval] BSTR* pVal);
        [id(0x0000000f), propget, helpstring("Returns last message edit timestamp."), helpcontext(0x0000000b)]
        HRESULT EditedTimestamp([out, retval] DATE* pVal);
        [id(0x00000008), propput, helpstring("Returns/sets message body."), helpcontext(0x0000000b)]
        HRESULT Body([in] BSTR pVal);
        [id(0x00000010), propget, helpstring("Returns changed member role."), helpcontext(0x0000000b)]
        HRESULT Role([out, retval] TChatMemberRole* pVal);
        [id(0x00000011), propget, helpstring("Returns changed chat options."), helpcontext(0x0000000b)]
        HRESULT Options([out, retval] long* pVal);
        [id(0x00000012), propget, helpstring("Returns true if the message can be edited."), helpcontext(0x0000000b)]
        HRESULT IsEditable([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000013), propget, helpstring("Returns chat message unique identifier."), helpcontext(0x0000000b)]
        HRESULT Guid([out, retval] BSTR* pVal);
    };

    [
      odl,
      uuid(8C24106C-3368-4580-93E5-5ED4ACCDE306),
      helpstring("IChat Interface"),
      helpcontext(0x0000001f),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IChat : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets chat name."), helpcontext(0x0000001f)]
        HRESULT Name([out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns chat messages."), helpcontext(0x0000001f)]
        HRESULT Messages([out, retval] IChatMessageCollection** pVal);
        [id(0x00000003), propget, helpstring("Returns chat timestamp."), helpcontext(0x0000001f)]
        HRESULT Timestamp([out, retval] DATE* pVal);
        [id(0x00000004), propget, helpstring("Returns chat adder."), helpcontext(0x0000001f)]
        HRESULT Adder([out, retval] IUser** pVal);
        [id(0x00000005), propget, helpstring("Returns chat status."), helpcontext(0x0000001f)]
        HRESULT Status([out, retval] TChatStatus* pVal);
        [id(0x00000006), propget, helpstring("Returns chat posters."), helpcontext(0x0000001f)]
        HRESULT Posters([out, retval] IUserCollection** pVal);
        [id(0x00000007), propget, helpstring("Returns chat members."), helpcontext(0x0000001f)]
        HRESULT Members([out, retval] IUserCollection** pVal);
        [id(0x00000008), propget, helpstring("Returns chat topic."), helpcontext(0x0000001f)]
        HRESULT Topic([out, retval] BSTR* pVal);
        [id(0x00000008), propput, helpstring("Returns chat topic."), helpcontext(0x0000001f)]
        HRESULT Topic([in] BSTR pVal);
        [id(0x00000009), propget, helpstring("Returns chat active members."), helpcontext(0x0000001f)]
        HRESULT ActiveMembers([out, retval] IUserCollection** pVal);
        [id(0x0000000a), propget, helpstring("Returns chat friendly name."), helpcontext(0x0000001f)]
        HRESULT FriendlyName([out, retval] BSTR* pVal);
        [id(0x0000000b), helpstring("Opens chat window."), helpcontext(0x0000001f)]
        HRESULT OpenWindow();
        [id(0x0000000c), helpstring("Sends chat message."), helpcontext(0x0000001f)]
        HRESULT SendMessage(
                        [in] BSTR MessageText, 
                        [out, retval] IChatMessage** pVal);
        [id(0x0000000d), helpstring("Leaves the chat."), helpcontext(0x0000001f)]
        HRESULT Leave();
        [id(0x0000000e), helpstring("Adds new members to the chat."), helpcontext(0x0000001f)]
        HRESULT AddMembers([in] IUserCollection* pMembers);
        [id(0x0000000f), propget, helpstring("Returns most recent chat messages."), helpcontext(0x0000001f)]
        HRESULT RecentMessages([out, retval] IChatMessageCollection** pVal);
        [id(0x00000010), propget, helpstring("Returns chat bookmarked status.")]
        HRESULT Bookmarked([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000011), helpstring("Bookmarks the chat.")]
        HRESULT Bookmark();
        [id(0x00000012), helpstring("Bookmarks the chat.")]
        HRESULT Unbookmark();
        [id(0x00000013), propget, helpstring("Returns/sets chat topic in XML."), helpcontext(0x0000001f)]
        HRESULT TopicXML([out, retval] BSTR* pVal);
        [id(0x00000013), propput, helpstring("Returns/sets chat topic in XML."), helpcontext(0x0000001f)]
        HRESULT TopicXML([in] BSTR pVal);
        [id(0x00000014), propget, helpstring("Returns chat members collection."), helpcontext(0x0000001f)]
        HRESULT MemberObjects([out, retval] IChatMemberCollection** pVal);
        [id(0x00000015), propget, helpstring("Returns chat global unique identifier."), helpcontext(0x0000001f)]
        HRESULT Blob([out, retval] BSTR* pVal);
        [id(0x00000016), propget, helpstring("Returns/sets chat options."), helpcontext(0x0000001f)]
        HRESULT Options([out, retval] long* pVal);
        [id(0x00000016), propput, helpstring("Returns/sets chat options."), helpcontext(0x0000001f)]
        HRESULT Options([in] long pVal);
        [id(0x00000017), propget, helpstring("Returns chat password hint."), helpcontext(0x0000001f)]
        HRESULT PasswordHint([out, retval] BSTR* pVal);
        [id(0x00000018), helpstring("Sets chat password and hint."), helpcontext(0x0000001f)]
        HRESULT SetPassword(
                        [in] BSTR Password, 
                        [in, optional, defaultvalue("")] BSTR Hint);
        [id(0x00000019), propget, helpstring("Returns/sets chat guidelines."), helpcontext(0x0000001f)]
        HRESULT GuideLines([out, retval] BSTR* pVal);
        [id(0x00000019), propput, helpstring("Returns/sets chat guidelines."), helpcontext(0x0000001f)]
        HRESULT GuideLines([in] BSTR pVal);
        [id(0x0000001a), propget, helpstring("Returns/sets chat description."), helpcontext(0x0000001f)]
        HRESULT Description([out, retval] BSTR* pVal);
        [id(0x0000001a), propput, helpstring("Returns/sets chat description."), helpcontext(0x0000001f)]
        HRESULT Description([in] BSTR pVal);
        [id(0x0000001b), propget, helpstring("Returns dialog chat partner Skypename."), helpcontext(0x0000001f)]
        HRESULT DialogPartner([out, retval] BSTR* pVal);
        [id(0x0000001c), propget, helpstring("Returns last chat activity timestamp."), helpcontext(0x0000001f)]
        HRESULT ActivityTimestamp([out, retval] DATE* pVal);
        [id(0x0000001d), propget, helpstring("Returns my role in chat."), helpcontext(0x0000001f)]
        HRESULT MyRole([out, retval] TChatMemberRole* pVal);
        [id(0x0000001e), propget, helpstring("Returns chat applicants collection."), helpcontext(0x0000001f)]
        HRESULT Applicants([out, retval] IUserCollection** pVal);
        [id(0x0000001f), helpstring("Joins chat."), helpcontext(0x0000001f)]
        HRESULT Join();
        [id(0x00000020), helpstring("Kicks member from chat."), helpcontext(0x0000001f)]
        HRESULT Kick([in] BSTR Handle);
        [id(0x00000021), helpstring("Kicks and bans member from chat."), helpcontext(0x0000001f)]
        HRESULT KickBan([in] BSTR Handle);
        [id(0x00000022), helpstring("Closes chat."), helpcontext(0x0000001f)]
        HRESULT Disband();
        [id(0x00000023), helpstring("Enters password for chat."), helpcontext(0x0000001f)]
        HRESULT EnterPassword([in] BSTR Password);
        [id(0x00000024), helpstring("Clears recent chat messages."), helpcontext(0x0000001f)]
        HRESULT ClearRecentMessages();
        [id(0x00000025), helpstring("Accepts add to shared group."), helpcontext(0x0000001f)]
        HRESULT AcceptAdd();
        [id(0x00000026), propput, helpstring("Sets chat alert string."), helpcontext(0x0000001f)]
        HRESULT AlertString([in] BSTR rhs);
        [id(0x00000027), propget, helpstring("Returns chat type."), helpcontext(0x0000001f)]
        HRESULT Type([out, retval] TChatType* pVal);
        [id(0x00000028), propget, helpstring("Returns chat status."), helpcontext(0x0000001f)]
        HRESULT MyStatus([out, retval] TChatMyStatus* pVal);
    };

    [
      odl,
      uuid(8FFC686B-2E5E-4763-8B03-FF4FD3A0C4DA),
      helpstring("IChatMemberCollection interface"),
      helpcontext(0x00000056),
      dual,
      oleautomation
    ]
    interface IChatMemberCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000056)]
        HRESULT Count([out, retval] long* pVal);
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000056)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IChatMember** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000056)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(9E9F0473-94C2-4FDD-85D2-43E3478765F9),
      helpstring("IChatMember interface"),
      helpcontext(0x00000055),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IChatMember : IDispatch {
        [id(0x00000001), propget, helpstring("Returns chat member object id."), helpcontext(0x00000055)]
        HRESULT Id([out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns chat member Skypename."), helpcontext(0x00000055)]
        HRESULT Handle([out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns/sets chat member role."), helpcontext(0x00000055)]
        HRESULT Role([out, retval] TChatMemberRole* pVal);
        [id(0x00000003), propput, helpstring("Returns/sets chat member role."), helpcontext(0x00000055)]
        HRESULT Role([in] TChatMemberRole pVal);
        [id(0x00000004), propget, helpstring("Returns true if chat member role can be changed."), helpcontext(0x00000055)]
        HRESULT CanSetRoleTo(
                        [in] TChatMemberRole Role, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000005), propget, helpstring("Returns true if chat member is active."), helpcontext(0x00000055)]
        HRESULT IsActive([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000006), propget, helpstring("Returns related Chat object."), helpcontext(0x00000055)]
        HRESULT Chat([out, retval] IChat** pVal);
    };

    typedef [uuid(AE9D03DE-7E88-466A-A3E8-1E840ACD9310), helpstring("Chate member roles."), helpcontext(0x00000011)]
    enum {
        chatMemberRoleUnknown = 0xffffffff,
        chatMemberRoleCreator = 0,
        chatMemberRoleMaster = 1,
        chatMemberRoleHelper = 2,
        chatMemberRoleUser = 3,
        chatMemberRoleListener = 4,
        chatMemberRoleApplicant = 5
    } TChatMemberRole;

    typedef [uuid(204D84E3-D7D1-450D-A038-6A3A5210E4FB), helpstring("Chate types."), helpcontext(0x00000011)]
    enum {
        chatTypeUnknown = 0xffffffff,
        chatTypeDialog = 0,
        chatTypeLegacyDialog = 1,
        chatTypeLegacyUnsubscribed = 2,
        chatTypeMultiChat = 3,
        chatTypeSharedGroup = 4
    } TChatType;

    typedef [uuid(1685094C-829A-431B-880C-FE61D82A085E), helpstring("Call status."), helpcontext(0x00000011)]
    enum {
        chatStatusUnknown = 0xffffffff,
        chatStatusConnecting = 0,
        chatStatusWaitingRemoteAccept = 1,
        chatStatusAcceptRequired = 2,
        chatStatusPasswordRequired = 3,
        chatStatusSubscribed = 4,
        chatStatusUnsubscribed = 5,
        chatStatusDisbanded = 6,
        chatStatusQueuedBecauseChatIsFull = 7,
        chatStatusApplicationDenied = 8,
        chatStatusKicked = 9,
        chatStatusBanned = 10,
        chatStatusRetryConnecting = 11
    } TChatMyStatus;

    [
      odl,
      uuid(48E046A8-31D7-4E5F-A611-47BF32B86405),
      helpstring("ICommand Interface"),
      helpcontext(0x00000007),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICommand : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets command id."), helpcontext(0x00000007)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000001), propput, helpstring("Returns/sets command id."), helpcontext(0x00000007)]
        HRESULT Id([in] long pVal);
        [id(0x00000002), propget, helpstring("Returns/sets wait timeout in milliseconds."), helpcontext(0x00000007)]
        HRESULT Timeout([out, retval] long* pVal);
        [id(0x00000002), propput, helpstring("Returns/sets wait timeout in milliseconds."), helpcontext(0x00000007)]
        HRESULT Timeout([in] long pVal);
        [id(0x00000003), propget, helpstring("Returns/sets blocking command flag."), helpcontext(0x00000007)]
        HRESULT Blocking([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000003), propput, helpstring("Returns/sets blocking command flag."), helpcontext(0x00000007)]
        HRESULT Blocking([in] VARIANT_BOOL pVal);
        [id(0x00000004), propget, helpstring("Returns/sets command text."), helpcontext(0x00000007)]
        HRESULT Command([out, retval] BSTR* pVal);
        [id(0x00000004), propput, helpstring("Returns/sets command text."), helpcontext(0x00000007)]
        HRESULT Command([in] BSTR pVal);
        [id(0x00000005), propget, helpstring("Returns/sets reply text."), helpcontext(0x00000007)]
        HRESULT Reply([out, retval] BSTR* pVal);
        [id(0x00000005), propput, helpstring("Returns/sets reply text."), helpcontext(0x00000007)]
        HRESULT Reply([in] BSTR pVal);
        [id(0x00000006), propget, helpstring("Returns/sets expected reply text."), helpcontext(0x00000007)]
        HRESULT Expected([out, retval] BSTR* pVal);
        [id(0x00000006), propput, helpstring("Returns/sets expected reply text."), helpcontext(0x00000007)]
        HRESULT Expected([in] BSTR pVal);
    };

    [
      odl,
      uuid(052A4165-010A-457D-A874-E661B6322846),
      helpstring("IChatCollection Interface"),
      helpcontext(0x00000020),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IChatCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000020)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000020)]
        HRESULT Add([in] IChat* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000020)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000020)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000020)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IChat** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000020)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(AEB48497-5090-479C-8BE0-BD51597156A1),
      helpstring("IConference Interface"),
      helpcontext(0x00000027),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IConference : IDispatch {
        [id(0x00000001), propget, helpstring("Returns conference id"), helpcontext(0x00000027)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000002), propget, helpstring("Returns calls that are part of this conference."), helpcontext(0x00000027)]
        HRESULT Calls([out, retval] ICallCollection** pVal);
        [id(0x00000003), propget, helpstring("Returns active calls that are part of this conference."), helpcontext(0x00000027)]
        HRESULT ActiveCalls([out, retval] ICallCollection** pVal);
        [id(0x00000004), helpstring("Hold conference."), helpcontext(0x00000027)]
        HRESULT Hold();
        [id(0x00000005), helpstring("Resume conference."), helpcontext(0x00000027)]
        HRESULT Resume();
        [id(0x00000006), helpstring("End conference."), helpcontext(0x00000027)]
        HRESULT Finish();
    };

    [
      odl,
      uuid(F3E0C529-7D4F-4AF5-B501-27D25D4D2825),
      helpstring("IConferenceCollection Interface"),
      helpcontext(0x00000028),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IConferenceCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000028)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000028)]
        HRESULT Add([in] IConference* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000028)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000028)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000028)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IConference** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000028)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(21494848-BBD5-4192-BE32-57D1A19D8E94),
      helpstring("IVoicemailCollection Interface"),
      helpcontext(0x00000034),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IVoicemailCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000034)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000034)]
        HRESULT Add([in] IVoicemail* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000034)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000034)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000034)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IVoicemail** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000034)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(120B425E-6313-4924-B5A9-3E9F2E444A00),
      helpstring("IVoicemail interface"),
      helpcontext(0x00000033),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IVoicemail : IDispatch {
        [id(0x00000001), propget, helpstring("Returns voicemail type."), helpcontext(0x00000033)]
        HRESULT Type([out, retval] TVoicemailType* pVal);
        [id(0x00000002), propget, helpstring("Returns voicemail partner handle."), helpcontext(0x00000033)]
        HRESULT PartnerHandle([out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns voicemail partner display name."), helpcontext(0x00000033)]
        HRESULT PartnerDisplayName([out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns voicemail status."), helpcontext(0x00000033)]
        HRESULT Status([out, retval] TVoicemailStatus* pVal);
        [id(0x00000005), propget, helpstring("Returns voicemail failure reason."), helpcontext(0x00000033)]
        HRESULT FailureReason([out, retval] TVoicemailFailureReason* pVal);
        [id(0x00000006), propget, helpstring("Returns voicemail timestamp."), helpcontext(0x00000033)]
        HRESULT Timestamp([out, retval] DATE* pVal);
        [id(0x00000007), propget, helpstring("Returns voicemail duration in seconds."), helpcontext(0x00000033)]
        HRESULT Duration([out, retval] long* pVal);
        [id(0x00000008), propget, helpstring("Returns voicemail allowed duration in seconds."), helpcontext(0x00000033)]
        HRESULT AllowedDuration([out, retval] long* pVal);
        [id(0x00000009), propget, helpstring("Returns voicemail id."), helpcontext(0x00000033)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x0000000a), helpstring("Opens voicemail."), helpcontext(0x00000033)]
        HRESULT Open();
        [id(0x0000000b), helpstring("Starts voicemail playback."), helpcontext(0x00000033)]
        HRESULT StartPlayback();
        [id(0x0000000c), helpstring("Stops voicemail playback."), helpcontext(0x00000033)]
        HRESULT StopPlayback();
        [id(0x0000000d), helpstring("Uploads voicemail."), helpcontext(0x00000033)]
        HRESULT Upload();
        [id(0x0000000e), helpstring("Downloads voicemail."), helpcontext(0x00000033)]
        HRESULT Download();
        [id(0x0000000f), helpstring("Starts voicemail recording."), helpcontext(0x00000033)]
        HRESULT StartRecording();
        [id(0x00000010), helpstring("Stops voicemail recording."), helpcontext(0x00000033)]
        HRESULT StopRecording();
        [id(0x00000011), helpstring("Deletes voicemail."), helpcontext(0x00000033)]
        HRESULT Delete();
        [id(0x00000012), helpstring("Starts playback in call."), helpcontext(0x00000033)]
        HRESULT StartPlaybackInCall();
        [id(0x00000013), helpstring("Changes played voicemail status back to unplayed."), helpcontext(0x00000033)]
        HRESULT SetUnplayed();
    };

    typedef [uuid(AA127663-5272-473D-B14C-1A8BC3FB66C6), helpstring("Call history."), helpcontext(0x00000011)]
    enum {
        chsAllCalls = 0,
        chsMissedCalls = 1,
        chsIncomingCalls = 2,
        chsOutgoingCalls = 3
    } TCallHistory;

    [
      odl,
      uuid(B9A3D72F-04C1-4878-993C-D89F83E20569),
      helpstring("IProfile interface"),
      helpcontext(0x0000003c),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IProfile : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets user fullname."), helpcontext(0x0000003c)]
        HRESULT FullName([out, retval] BSTR* pVal);
        [id(0x00000001), propput, helpstring("Returns/sets user fullname."), helpcontext(0x0000003c)]
        HRESULT FullName([in] BSTR pVal);
        [id(0x00000002), propget, helpstring("Returns/sets user birthday."), helpcontext(0x0000003c)]
        HRESULT Birthday([out, retval] BSTR* pVal);
        [id(0x00000002), propput, helpstring("Returns/sets user birthday."), helpcontext(0x0000003c)]
        HRESULT Birthday([in] BSTR pVal);
        [id(0x00000003), propget, helpstring("Returns/sets user sex."), helpcontext(0x0000003c)]
        HRESULT Sex([out, retval] TUserSex* pVal);
        [id(0x00000003), propput, helpstring("Returns/sets user sex."), helpcontext(0x0000003c)]
        HRESULT Sex([in] TUserSex pVal);
        [id(0x00000004), propget, helpstring("Returns/sets user language code."), helpcontext(0x0000003c)]
        HRESULT Languages([out, retval] BSTR* pVal);
        [id(0x00000004), propput, helpstring("Returns/sets user language code."), helpcontext(0x0000003c)]
        HRESULT Languages([in] BSTR pVal);
        [id(0x00000005), propget, helpstring("Returns/sets user country code."), helpcontext(0x0000003c)]
        HRESULT Country([out, retval] BSTR* pVal);
        [id(0x00000005), propput, helpstring("Returns/sets user country code."), helpcontext(0x0000003c)]
        HRESULT Country([in] BSTR pVal);
        [id(0x00000006), propget, helpstring("Returns/sets user province."), helpcontext(0x0000003c)]
        HRESULT Province([out, retval] BSTR* pVal);
        [id(0x00000006), propput, helpstring("Returns/sets user province."), helpcontext(0x0000003c)]
        HRESULT Province([in] BSTR pVal);
        [id(0x00000007), propget, helpstring("Returns/sets user city."), helpcontext(0x0000003c)]
        HRESULT City([out, retval] BSTR* pVal);
        [id(0x00000007), propput, helpstring("Returns/sets user city."), helpcontext(0x0000003c)]
        HRESULT City([in] BSTR pVal);
        [id(0x00000008), propget, helpstring("Returns/sets user home phone."), helpcontext(0x0000003c)]
        HRESULT PhoneHome([out, retval] BSTR* pVal);
        [id(0x00000008), propput, helpstring("Returns/sets user home phone."), helpcontext(0x0000003c)]
        HRESULT PhoneHome([in] BSTR pVal);
        [id(0x00000009), propget, helpstring("Returns/sets user business phone."), helpcontext(0x0000003c)]
        HRESULT PhoneOffice([out, retval] BSTR* pVal);
        [id(0x00000009), propput, helpstring("Returns/sets user business phone."), helpcontext(0x0000003c)]
        HRESULT PhoneOffice([in] BSTR pVal);
        [id(0x0000000a), propget, helpstring("Returns/sets user mobile phone."), helpcontext(0x0000003c)]
        HRESULT PhoneMobile([out, retval] BSTR* pVal);
        [id(0x0000000a), propput, helpstring("Returns/sets user mobile phone."), helpcontext(0x0000003c)]
        HRESULT PhoneMobile([in] BSTR pVal);
        [id(0x0000000b), propget, helpstring("Returns/sets user homepage."), helpcontext(0x0000003c)]
        HRESULT Homepage([out, retval] BSTR* pVal);
        [id(0x0000000b), propput, helpstring("Returns/sets user homepage."), helpcontext(0x0000003c)]
        HRESULT Homepage([in] BSTR pVal);
        [id(0x0000000c), propget, helpstring("Returns/sets user about text."), helpcontext(0x0000003c)]
        HRESULT About([out, retval] BSTR* pVal);
        [id(0x0000000c), propput, helpstring("Returns/sets user about text."), helpcontext(0x0000003c)]
        HRESULT About([in] BSTR pVal);
        [id(0x0000000d), propget, helpstring("Returns/sets user mood text."), helpcontext(0x0000003c)]
        HRESULT MoodText([out, retval] BSTR* pVal);
        [id(0x0000000d), propput, helpstring("Returns/sets user mood text."), helpcontext(0x0000003c)]
        HRESULT MoodText([in] BSTR pVal);
        [id(0x0000000e), propget, helpstring("Returns/sets user timezone."), helpcontext(0x0000003c)]
        HRESULT Timezone([out, retval] long* pVal);
        [id(0x0000000e), propput, helpstring("Returns/sets user timezone."), helpcontext(0x0000003c)]
        HRESULT Timezone([in] long pVal);
        [id(0x0000000f), propget, helpstring("Returns/sets user call no answer timeout."), helpcontext(0x0000003c)]
        HRESULT CallNoAnswerTimeout([out, retval] short* pVal);
        [id(0x0000000f), propput, helpstring("Returns/sets user call no answer timeout."), helpcontext(0x0000003c)]
        HRESULT CallNoAnswerTimeout([in] short pVal);
        [id(0x00000010), propget, helpstring("Returns/sets user call apply call forward flag."), helpcontext(0x0000003c)]
        HRESULT CallApplyCF([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000010), propput, helpstring("Returns/sets user call apply call forward flag."), helpcontext(0x0000003c)]
        HRESULT CallApplyCF([in] VARIANT_BOOL pVal);
        [id(0x00000011), propget, helpstring("Returns/sets user call send to voicemail flag."), helpcontext(0x0000003c)]
        HRESULT CallSendToVM([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000011), propput, helpstring("Returns/sets user call send to voicemail flag."), helpcontext(0x0000003c)]
        HRESULT CallSendToVM([in] VARIANT_BOOL pVal);
        [id(0x00000012), propget, helpstring("Returns/sets user call forwarding rules."), helpcontext(0x0000003c)]
        HRESULT CallForwardRules([out, retval] BSTR* pVal);
        [id(0x00000012), propput, helpstring("Returns/sets user call forwarding rules."), helpcontext(0x0000003c)]
        HRESULT CallForwardRules([in] BSTR pVal);
        [id(0x00000013), propget, helpstring("Returns balance in currency cents."), helpcontext(0x0000003c)]
        HRESULT Balance([out, retval] long* pVal);
        [id(0x00000014), propget, helpstring("Returns balance currency code."), helpcontext(0x0000003c)]
        HRESULT BalanceCurrency([out, retval] BSTR* pVal);
        [id(0x00000015), propget, helpstring("Returns balance as text."), helpcontext(0x0000003c)]
        HRESULT BalanceToText([out, retval] BSTR* pVal);
        [id(0x00000016), propget, helpstring("Returns ISO country code from current IP address."), helpcontext(0x0000003c)]
        HRESULT IPCountry([out, retval] BSTR* pVal);
        [id(0x00000017), propget, helpstring("Returns validated SMS reply-to numbers."), helpcontext(0x0000003c)]
        HRESULT ValidatedSmsNumbers([out, retval] BSTR* pVal);
        [id(0x00000018), propget, helpstring("Returns/sets mood text in XML."), helpcontext(0x0000003c)]
        HRESULT RichMoodText([out, retval] BSTR* pVal);
        [id(0x00000018), propput, helpstring("Returns/sets mood text in XML."), helpcontext(0x0000003c)]
        HRESULT RichMoodText([in] BSTR pVal);
    };

    [
      odl,
      uuid(4C5C99DC-09CF-4A9C-BD94-8D655454A1F4),
      helpstring("IGroupCollection interface"),
      helpcontext(0x00000008),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IGroupCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000008)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000008)]
        HRESULT Add([in] IGroup* pGroup);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000008)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000008)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000008)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IGroup** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000008)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(84513274-9C49-4AAA-B8FC-316EB32CFE95),
      helpstring("IGroup interface."),
      helpcontext(0x00000009),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IGroup : IDispatch {
        [id(0x00000001), propget, helpstring("Returns group id."), helpcontext(0x00000009)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000002), propget, helpstring("Returns group type."), helpcontext(0x00000009)]
        HRESULT Type([out, retval] TGroupType* pVal);
        [id(0x00000003), propget, helpstring("Returns custom group persistent id."), helpcontext(0x00000009)]
        HRESULT CustomGroupId([out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns/sets group display name."), helpcontext(0x00000009)]
        HRESULT DisplayName([out, retval] BSTR* pVal);
        [id(0x00000004), propput, helpstring("Returns/sets group display name."), helpcontext(0x00000009)]
        HRESULT DisplayName([in] BSTR pVal);
        [id(0x00000005), propget, helpstring("Returns group users."), helpcontext(0x00000009)]
        HRESULT Users([out, retval] IUserCollection** pVal);
        [id(0x00000006), propget, helpstring("Returns group online users."), helpcontext(0x00000009)]
        HRESULT OnlineUsers([out, retval] IUserCollection** pVal);
        [id(0x00000007), propget, helpstring("Returns group visible status."), helpcontext(0x00000009)]
        HRESULT IsVisible([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000008), propget, helpstring("Returns group expanded status."), helpcontext(0x00000009)]
        HRESULT IsExpanded([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000009), helpstring("Adds new a user or PSTN number to group."), helpcontext(0x00000009)]
        HRESULT AddUser([in] BSTR Username);
        [id(0x0000000a), helpstring("Removes a user or PSTN number from group."), helpcontext(0x00000009)]
        HRESULT RemoveUser([in] BSTR Username);
        [id(0x0000000b), helpstring("Shares a group."), helpcontext(0x00000009)]
        HRESULT Share([in, optional, defaultvalue("")] BSTR MessageText);
        [id(0x0000000c), helpstring("Accepts a shared group."), helpcontext(0x00000009)]
        HRESULT Accept();
        [id(0x0000000d), helpstring("Decline a shared group.")]
        HRESULT Decline();
    };

    [
      odl,
      uuid(2BC8C53B-3312-4A77-AC87-31DF18A1EC51),
      helpstring("ISettings interface."),
      helpcontext(0x00000002),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISettings : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets audio in device."), helpcontext(0x00000002)]
        HRESULT AudioIn([out, retval] BSTR* pVal);
        [id(0x00000001), propput, helpstring("Returns/sets audio in device."), helpcontext(0x00000002)]
        HRESULT AudioIn([in] BSTR pVal);
        [id(0x00000002), propget, helpstring("Returns/sets audio out device."), helpcontext(0x00000002)]
        HRESULT AudioOut([out, retval] BSTR* pVal);
        [id(0x00000002), propput, helpstring("Returns/sets audio out device."), helpcontext(0x00000002)]
        HRESULT AudioOut([in] BSTR pVal);
        [id(0x00000003), propget, helpstring("Returns/sets auto-away status."), helpcontext(0x00000002)]
        HRESULT AutoAway([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000003), propput, helpstring("Returns/sets auto-away status."), helpcontext(0x00000002)]
        HRESULT AutoAway([in] VARIANT_BOOL pVal);
        [id(0x00000004), propget, helpstring("Returns/sets ringer device."), helpcontext(0x00000002)]
        HRESULT Ringer([out, retval] BSTR* pVal);
        [id(0x00000004), propput, helpstring("Returns/sets ringer device."), helpcontext(0x00000002)]
        HRESULT Ringer([in] BSTR pVal);
        [id(0x00000005), propput, helpstring("Returns/sets user avatar picture."), helpcontext(0x00000002)]
        HRESULT Avatar(
                        [in, optional, defaultvalue("1")] BSTR Id, 
                        [in] BSTR rhs);
        [id(0x00000006), propget, helpstring("Returns/sets ringtone status."), helpcontext(0x00000002)]
        HRESULT RingToneStatus(
                        [in, optional, defaultvalue("1")] BSTR Id, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000007), propput, helpstring("Sets ringtone."), helpcontext(0x00000002)]
        HRESULT RingTone(
                        [in, optional, defaultvalue("1")] BSTR Id, 
                        [in] BSTR rhs);
        [id(0x00000008), propget, helpstring("Returns/sets video in device."), helpcontext(0x00000002)]
        HRESULT VideoIn([out, retval] BSTR* pVal);
        [id(0x00000008), propput, helpstring("Returns/sets video in device."), helpcontext(0x00000002)]
        HRESULT VideoIn([in] BSTR pVal);
        [id(0x00000009), propget, helpstring("Returns/sets pc speaker on/off."), helpcontext(0x00000002)]
        HRESULT PCSpeaker([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000009), propput, helpstring("Returns/sets pc speaker on/off."), helpcontext(0x00000002)]
        HRESULT PCSpeaker([in] VARIANT_BOOL pVal);
        [id(0x0000000a), propget, helpstring("Returns/sets automatic gain control status."), helpcontext(0x00000002)]
        HRESULT AGC([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000a), propput, helpstring("Returns/sets automatic gain control status."), helpcontext(0x00000002)]
        HRESULT AGC([in] VARIANT_BOOL pVal);
        [id(0x0000000b), propget, helpstring("Returns/sets automatic echo cancellation status."), helpcontext(0x00000002)]
        HRESULT AEC([out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000b), propput, helpstring("Returns/sets automatic echo cancellation status."), helpcontext(0x00000002)]
        HRESULT AEC([in] VARIANT_BOOL pVal);
        [id(0x0000000c), propget, helpstring("Returns/sets user interface language."), helpcontext(0x00000002)]
        HRESULT Language([out, retval] BSTR* pVal);
        [id(0x0000000c), propput, helpstring("Returns/sets user interface language."), helpcontext(0x00000002)]
        HRESULT Language([in] BSTR pVal);
        [id(0x00000006), propput, helpstring("Returns/sets ringtone status."), helpcontext(0x00000002)]
        HRESULT RingToneStatus(
                        [in, optional, defaultvalue("1")] BSTR Id, 
                        [in] VARIANT_BOOL pVal);
        [id(0x0000000d), helpstring("Saves avatar to file."), helpcontext(0x00000002)]
        HRESULT SaveAvatarToFile(
                        [in] BSTR Filename, 
                        [in, optional, defaultvalue("1")] BSTR AvatarId);
        [id(0x0000000e), helpstring("Loads avatar from file."), helpcontext(0x00000002)]
        HRESULT LoadAvatarFromFile(
                        [in] BSTR Filename, 
                        [in, optional, defaultvalue("1")] BSTR AvatarId);
        [id(0x0000000f), helpstring("Resets idle timer."), helpcontext(0x00000002)]
        HRESULT ResetIdleTimer();
    };

    [
      odl,
      uuid(838731B0-88E7-4BED-81DC-B35CA8433341),
      helpstring("IClient interface."),
      helpcontext(0x00000024),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IClient : IDispatch {
        [id(0x00000001), helpstring("Starts Skype application."), helpcontext(0x00000024)]
        HRESULT Start(
                        [in, optional, defaultvalue(0)] VARIANT_BOOL Minimized, 
                        [in, optional, defaultvalue(0)] VARIANT_BOOL Nosplash);
        [id(0x00000002), helpstring("Hides Skype application window."), helpcontext(0x00000024)]
        HRESULT Minimize();
        [id(0x00000003), helpstring("Closes Skype application."), helpcontext(0x00000024)]
        HRESULT Shutdown();
        [id(0x00000004), propget, helpstring("Returns Skype application running status."), helpcontext(0x00000024)]
        HRESULT IsRunning([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000005), helpstring("Opens current user profile dialog."), helpcontext(0x00000024)]
        HRESULT OpenProfileDialog();
        [id(0x00000006), helpstring("Opens user information dialog."), helpcontext(0x00000024)]
        HRESULT OpenUserInfoDialog([in] BSTR Username);
        [id(0x00000007), helpstring("Opens create conference dialog."), helpcontext(0x00000024)]
        HRESULT OpenConferenceDialog();
        [id(0x00000008), helpstring("Opens search dialog."), helpcontext(0x00000024)]
        HRESULT OpenSearchDialog();
        [id(0x00000009), helpstring("Opens options dialog."), helpcontext(0x00000024)]
        HRESULT OpenOptionsDialog([in] BSTR Page);
        [id(0x0000000a), helpstring("Opens call history tab."), helpcontext(0x00000024)]
        HRESULT OpenCallHistoryTab();
        [id(0x0000000b), helpstring("Opens contacts tab."), helpcontext(0x00000024)]
        HRESULT OpenContactsTab();
        [id(0x0000000c), helpstring("Opens dial pad tab."), helpcontext(0x00000024)]
        HRESULT OpenDialpadTab();
        [id(0x0000000d), helpstring("Opens send contacts dialog."), helpcontext(0x00000024)]
        HRESULT OpenSendContactsDialog([in, optional, defaultvalue("")] BSTR Username);
        [id(0x0000000e), helpstring("Opens blocked users dialog."), helpcontext(0x00000024)]
        HRESULT OpenBlockedUsersDialog();
        [id(0x0000000f), helpstring("Opens import contacts wizard."), helpcontext(0x00000024)]
        HRESULT OpenImportContactsWizard();
        [id(0x00000010), helpstring("Opens getting started wizard."), helpcontext(0x00000024)]
        HRESULT OpenGettingStartedWizard();
        [id(0x00000011), helpstring("Opens authorization dialog."), helpcontext(0x00000024)]
        HRESULT OpenAuthorizationDialog([in] BSTR Username);
        [id(0x00000012), helpstring("Open dialog."), helpcontext(0x00000024)]
        HRESULT OpenDialog(
                        [in] BSTR Name, 
                        [in, optional, defaultvalue("")] BSTR Param1, 
                        [in, optional, defaultvalue("")] BSTR Param2);
        [id(0x00000013), helpstring("Opens video test dialog."), helpcontext(0x00000024)]
        HRESULT OpenVideoTestDialog();
        [id(0x00000014), helpstring("Opens "Add a Contact" dialog."), helpcontext(0x00000024)]
        HRESULT OpenAddContactDialog([in, optional, defaultvalue("")] BSTR Username);
        [id(0x00000015), helpstring("Opens "Send an IM Message" dialog."), helpcontext(0x00000024)]
        HRESULT OpenMessageDialog(
                        [in] BSTR Username, 
                        [in, optional, defaultvalue("")] BSTR Text);
        [id(0x00000016), helpstring("Opens file transfer dialog."), helpcontext(0x00000024)]
        HRESULT OpenFileTransferDialog(
                        [in] BSTR User, 
                        [in] BSTR Folder);
        [id(0x00000017), helpstring("Sets focus to Skype application window."), helpcontext(0x00000024)]
        HRESULT Focus();
        [id(0x00000018), helpstring("Sends button button pressed to client."), helpcontext(0x00000024)]
        HRESULT ButtonPressed([in] BSTR Key);
        [id(0x00000019), helpstring("Sends button released event to client."), helpcontext(0x00000024)]
        HRESULT ButtonReleased([in] BSTR Key);
        [id(0x0000001a), helpstring("Opens SMS window")]
        HRESULT OpenSmsDialog([in] BSTR SmsId);
        [id(0x0000001b), helpstring("Creates new plugin event."), helpcontext(0x00000024)]
        HRESULT CreateEvent(
                        [in] BSTR EventId, 
                        [in] BSTR Caption, 
                        [in] BSTR Hint, 
                        [out, retval] IPluginEvent** pEvent);
        [id(0x0000001c), helpstring("Creates new tools menu item"), helpcontext(0x00000024)]
        HRESULT CreateMenuItem(
                        [in] BSTR MenuItemId, 
                        [in] TPluginContext PluginContext, 
                        [in] BSTR CaptionText, 
                        [in, optional, defaultvalue("")] BSTR HintText, 
                        [in, optional, defaultvalue("")] BSTR IconPath, 
                        [in, optional, defaultvalue(-1)] VARIANT_BOOL Enabled, 
                        [in, optional, defaultvalue(0)] TPluginContactType ContactType, 
                        [in, optional, defaultvalue(0)] VARIANT_BOOL MultipleContacts, 
                        [out, retval] IPluginMenuItem** pMenuItem);
        [id(0x0000001d), propget, helpstring("Returns/sets wallpaper."), helpcontext(0x00000024)]
        HRESULT Wallpaper([out, retval] BSTR* pVal);
        [id(0x0000001d), propput, helpstring("Returns/sets wallpaper."), helpcontext(0x00000024)]
        HRESULT Wallpaper([in] BSTR pVal);
        [id(0x0000001e), helpstring("Opens Live tab."), helpcontext(0x00000024)]
        HRESULT OpenLiveTab();
    };

    [
      odl,
      uuid(4DF5F83A-0ABA-417D-A6FC-62A68AE06EF7),
      helpstring("IPluginEvent Interface"),
      helpcontext(0x00000058),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IPluginEvent : IDispatch {
        [id(0x00000001), propget, helpstring("Event identity."), helpcontext(0x00000058)]
        HRESULT Id([out, retval] BSTR* pVal);
        [id(0x00000002), helpstring("Deletes the event."), helpcontext(0x00000058)]
        HRESULT Delete();
    };

    typedef [uuid(ED06559A-B942-49F5-AE48-DBD6BEF807B9), helpstring("Plugin context"), helpcontext(0x00000011)]
    enum {
        pluginContextUnknown = 0xffffffff,
        pluginContextChat = 0,
        pluginContextCall = 1,
        pluginContextContact = 2,
        pluginContextMyself = 3,
        pluginContextTools = 4
    } TPluginContext;

    typedef [uuid(000D0FD6-DC80-4CB1-A5AF-1A748DF8159E), helpstring("Plugin contact types"), helpcontext(0x00000011)]
    enum {
        pluginContactTypeUnknown = 0xffffffff,
        pluginContactTypeAll = 0,
        pluginContactTypeSkype = 1,
        pluginContactTypeSkypeOut = 2
    } TPluginContactType;

    [
      odl,
      uuid(C4BDF667-3FF7-4B44-A9F4-F3937E3E6D86),
      helpstring("IPluginMenuItem Interface"),
      helpcontext(0x00000057),
      dual,
      nonextensible,
      oleautomation
    ]
    interface IPluginMenuItem : IDispatch {
        [id(0x00000001), propget, helpstring("Menu item identity."), helpcontext(0x00000057)]
        HRESULT Id([out, retval] BSTR* pVal);
        [id(0x00000002), propput, helpstring("Menu item caption."), helpcontext(0x00000057)]
        HRESULT Caption([in] BSTR rhs);
        [id(0x00000003), propput, helpstring("Menu item hint."), helpcontext(0x00000057)]
        HRESULT Hint([in] BSTR rhs);
        [id(0x00000004), propput, helpstring("Menu item enabled status."), helpcontext(0x00000057)]
        HRESULT Enabled([in] VARIANT_BOOL rhs);
        [id(0x00000005), helpstring("Deletes menu item."), helpcontext(0x00000057)]
        HRESULT Delete();
    };

    typedef [uuid(775C273F-6B14-4AA5-B33C-83127F41BA2E), helpstring("API security contexts"), helpcontext(0x00000011)]
    enum {
        apiContextUnknown = 0,
        apiContextVoice = 1,
        apiContextMessaging = 2,
        apiContextAccount = 4,
        apiContextContacts = 8
    } TApiSecurityContext;

    [
      odl,
      uuid(82D97F2A-0E17-40F3-8E01-24937F936FF4),
      helpstring("ISmsMessage interface"),
      helpcontext(0x0000004c),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISmsMessage : IDispatch {
        [id(0x00000001), propget, helpstring("Returns message id."), helpcontext(0x0000004c)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000002), propget, helpstring("Returns message type."), helpcontext(0x0000004c)]
        HRESULT Type([out, retval] TSmsMessageType* pVal);
        [id(0x00000003), propget, helpstring("Returns message status."), helpcontext(0x0000004c)]
        HRESULT Status([out, retval] TSmsMessageStatus* pVal);
        [id(0x00000004), propget, helpstring("Returns message failure reason."), helpcontext(0x0000004c)]
        HRESULT FailureReason([out, retval] TSmsFailureReason* pVal);
        [id(0x00000005), propget, helpstring("Returns true if message failed unseen."), helpcontext(0x0000004c)]
        HRESULT IsFailedUnseen([out, retval] VARIANT_BOOL* pVal);
        [id(0x00000006), propput, helpstring("Sets message status read."), helpcontext(0x0000004c)]
        HRESULT Seen([in] VARIANT_BOOL rhs);
        [id(0x00000007), propget, helpstring("Returns price value."), helpcontext(0x0000004c)]
        HRESULT Price([out, retval] long* pVal);
        [id(0x00000008), propget, helpstring("Returns price precision."), helpcontext(0x0000004c)]
        HRESULT PricePrecision([out, retval] long* pVal);
        [id(0x00000009), propget, helpstring("Returns price currency code."), helpcontext(0x0000004c)]
        HRESULT PriceCurrency([out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns/sets reply-to number."), helpcontext(0x0000004c)]
        HRESULT ReplyToNumber([out, retval] BSTR* pVal);
        [id(0x0000000a), propput, helpstring("Returns/sets reply-to number."), helpcontext(0x0000004c)]
        HRESULT ReplyToNumber([in] BSTR pVal);
        [id(0x0000000b), propget, helpstring("Returns/sets message targets."), helpcontext(0x0000004c)]
        HRESULT Targets([out, retval] ISmsTargetCollection** pVal);
        [id(0x0000000c), propget, helpstring("Returns/sets message text."), helpcontext(0x0000004c)]
        HRESULT Body([out, retval] BSTR* pVal);
        [id(0x0000000c), propput, helpstring("Returns/sets message text."), helpcontext(0x0000004c)]
        HRESULT Body([in] BSTR pVal);
        [id(0x0000000d), propget, helpstring("Returns message chunks."), helpcontext(0x0000004c)]
        HRESULT Chunks([out, retval] ISmsChunkCollection** pVal);
        [id(0x0000000e), propget, helpstring("Returns message timestamp."), helpcontext(0x0000004c)]
        HRESULT Timestamp([out, retval] DATE* pVal);
        [id(0x0000000f), helpstring("Sends the message."), helpcontext(0x0000004c)]
        HRESULT Send();
        [id(0x00000010), helpstring("Deletes the message."), helpcontext(0x0000004c)]
        HRESULT Delete();
        [id(0x00000011), propget, helpstring("Returns/sets message target numbers."), helpcontext(0x0000004c)]
        HRESULT TargetNumbers([out, retval] BSTR* pVal);
        [id(0x00000011), propput, helpstring("Returns/sets message target numbers."), helpcontext(0x0000004c)]
        HRESULT TargetNumbers([in] BSTR pVal);
    };

    typedef [uuid(FE7E480A-5B32-432E-9711-E8E9C10C6BF9), helpstring("SMS message failure reasons"), helpcontext(0x00000011)]
    enum {
        smsFailureReasonUnknown = 0xffffffff,
        smsFailureReasonMiscError = 0,
        smsFailureReasonServerConnectFailed = 1,
        smsFailureReasonNoSmsCapability = 2,
        smsFailureReasonInsufficientFunds = 3,
        smsFailureReasonInvalidConfirmationCode = 4,
        smsFailureReasonUserBlocked = 5,
        smsFailureReasonIPBlocked = 6,
        smsFailureReasonNodeBlocked = 7
    } TSmsFailureReason;

    [
      odl,
      uuid(A2365EF3-4805-4DD3-A9D4-1A8AE3E17D84),
      helpstring("ISmsTargetCollection interface"),
      helpcontext(0x0000004b),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISmsTargetCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x0000004b)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x0000004b)]
        HRESULT Add([in] ISmsTarget* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x0000004b)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x0000004b)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x0000004b)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] ISmsTarget** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x0000004b)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(A9B9C33A-49A6-41D5-B13F-2AA4F284F406),
      helpstring("ISmsTarget interface"),
      helpcontext(0x0000004a),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISmsTarget : IDispatch {
        [id(0x00000001), propget, helpstring("Returns message target status"), helpcontext(0x0000004a)]
        HRESULT Status([out, retval] TSmsTargetStatus* pVal);
        [id(0x00000002), propget, helpstring("Returns message target number"), helpcontext(0x0000004a)]
        HRESULT Number([out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns related SMS message"), helpcontext(0x0000004a)]
        HRESULT Message([out, retval] ISmsMessage** pVal);
    };

    [
      odl,
      uuid(BBDA7D2D-B1C2-4AF9-AB5B-D762341D8903),
      helpstring("ISmsChunkCollection interface"),
      helpcontext(0x00000049),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISmsChunkCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000049)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000049)]
        HRESULT Add([in] ISmsChunk* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000049)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000049)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000049)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] ISmsChunk** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000049)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(A9062508-C926-4415-ABB7-A5A46DB34456),
      helpstring("ISmsChunk interface"),
      helpcontext(0x00000048),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISmsChunk : IDispatch {
        [id(0x00000001), propget, helpstring("Returns message id."), helpcontext(0x00000048)]
        HRESULT Id([out, retval] long* pVal);
        [id(0x00000002), propget, helpstring("Returns number of characters left in chunk."), helpcontext(0x00000048)]
        HRESULT CharactersLeft([out, retval] long* pVal);
        [id(0x00000003), propget, helpstring("Returns chunk text."), helpcontext(0x00000048)]
        HRESULT Text([out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns related SMS message."), helpcontext(0x00000048)]
        HRESULT Message([out, retval] ISmsMessage** pVal);
    };

    [
      odl,
      uuid(1D5BAB2E-69CC-4136-8E02-FC20767DC9E2),
      helpstring("ISmsMessageCollection interface"),
      helpcontext(0x0000004d),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISmsMessageCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x0000004d)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x0000004d)]
        HRESULT Add([in] ISmsMessage* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x0000004d)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x0000004d)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x0000004d)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] ISmsMessage** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x0000004d)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(70A59A25-E823-4C3F-8F33-775008895EE3),
      helpstring("IFileTransferCollection Interface"),
      helpcontext(0x0000005a),
      dual,
      oleautomation
    ]
    interface IFileTransferCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x0000005a)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x0000005a)]
        HRESULT Add([in] IFileTransfer* pItem);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x0000005a)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x0000005a)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x0000005a)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] IFileTransfer** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x0000005a)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(4D36B368-B88C-45FA-B136-3EF77B2EAD39),
      helpstring("IFileTransfer Interface"),
      helpcontext(0x00000059),
      dual,
      oleautomation
    ]
    interface IFileTransfer : IDispatch {
        [id(0x00000001), propget, helpstring("Returns file transfer identity."), helpcontext(0x00000059)]
        HRESULT Id([out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns file transfer type."), helpcontext(0x00000059)]
        HRESULT Type([out, retval] TFileTransferType* pVal);
        [id(0x00000003), propget, helpstring("Returns file transfer status."), helpcontext(0x00000059)]
        HRESULT Status([out, retval] TFileTransferStatus* pVal);
        [id(0x00000004), propget, helpstring("Returns file transfer failure reason code."), helpcontext(0x00000059)]
        HRESULT FailureReason([out, retval] TFileTransferFailureReason* pVal);
        [id(0x00000005), propget, helpstring("Returns file transfer partner Skypename."), helpcontext(0x00000059)]
        HRESULT PartnerHandle([out, retval] BSTR* pVal);
        [id(0x00000006), propget, helpstring("Returns file transfer partner display name."), helpcontext(0x00000059)]
        HRESULT PartnerDisplayName([out, retval] BSTR* pVal);
        [id(0x00000007), propget, helpstring("Returns file transfer start timestamp."), helpcontext(0x00000059)]
        HRESULT StartTime([out, retval] DATE* pVal);
        [id(0x00000008), propget, helpstring("Returns file transfer end timestamp."), helpcontext(0x00000059)]
        HRESULT FinishTime([out, retval] DATE* pVal);
        [id(0x00000009), propget, helpstring("Returns file transfer file path."), helpcontext(0x00000059)]
        HRESULT FilePath([out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns file transfer file name."), helpcontext(0x00000059)]
        HRESULT Filename([out, retval] BSTR* pVal);
        [id(0x0000000b), propget, helpstring("Returns file transfer speed in bytes per second."), helpcontext(0x00000059)]
        HRESULT BytesPerSecond([out, retval] BSTR* pVal);
        [id(0x0000000c), propget, helpstring("Returns file transfer total bytes transferred."), helpcontext(0x00000059)]
        HRESULT BytesTransferred([out, retval] BSTR* pVal);
    };

    typedef [uuid(BD808125-6CB8-46AD-88E1-13961434781F), helpstring("File transfer types"), helpcontext(0x00000011)]
    enum {
        fileTransferTypeIncoming = 0,
        fileTransferTypeOutgoing = 1
    } TFileTransferType;

    typedef [uuid(C4CE4074-11E0-4026-A809-5C6D259F1B7C), helpstring("File transfer status"), helpcontext(0x00000011)]
    enum {
        fileTransferStatusNew = 0,
        fileTransferStatusConnecting = 1,
        fileTransferStatusWaitingForAccept = 2,
        fileTransferStatusTransferring = 3,
        fileTransferStatusTransferringOverRelay = 4,
        fileTransferStatusPaused = 5,
        fileTransferStatusRemotelyPaused = 6,
        fileTransferStatusCancelled = 7,
        fileTransferStatusCompleted = 8,
        fileTransferStatusFailed = 9
    } TFileTransferStatus;

    typedef [uuid(A59E0AAE-86BA-4D10-959B-4E75C2C8DAD4), helpstring("File transfer failure reasons"), helpcontext(0x00000011)]
    enum {
        fileTransferFailureReasonSenderNotAuthorized = 1,
        fileTransferFailureReasonRemotelyCancelled = 2,
        fileTransferFailureReasonFailedRead = 3,
        fileTransferFailureReasonFailedRemoteRead = 4,
        fileTransferFailureReasonFailedWrite = 5,
        fileTransferFailureReasonFailedRemoteWrite = 6,
        fileTransferFailureReasonRemoteDoesNotSupportFT = 7,
        fileTransferFailureReasonRemoteOfflineTooLong = 8
    } TFileTransferFailureReason;

    [
      odl,
      uuid(8CB09087-E389-4C6D-A6A2-7D4BCA8545D9),
      helpstring("ICallChannelCollection Interface"),
      helpcontext(0x00000044),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICallChannelCollection : IDispatch {
        [id(0x00000001), propget, helpstring("Returns collection size."), helpcontext(0x00000044)]
        HRESULT Count([out, retval] long* pVal);
        [id(0x00000002), helpstring("Adds new item to the collection."), helpcontext(0x00000044)]
        HRESULT Add([in] ICallChannel* pChannel);
        [id(0x00000003), helpstring("Removes item from the collection."), helpcontext(0x00000044)]
        HRESULT Remove([in] long Index);
        [id(0x00000004), helpstring("Removes all items from the collection."), helpcontext(0x00000044)]
        HRESULT RemoveAll();
        [id(00000000), propget, helpstring("Returns collection item with specified index."), helpcontext(0x00000044)]
        HRESULT Item(
                        [in] long Index, 
                        [out, retval] ICallChannel** pVal);
        [id(0xfffffffc), propget, helpstring("Returns collection enumerator object."), helpcontext(0x00000044)]
        HRESULT _NewEnum([out, retval] IUnknown** pVal);
    };

    [
      odl,
      uuid(0EF6FD5D-607D-4EA3-9C90-683D73449E9D),
      helpstring("ICallChannelMessage interface."),
      helpcontext(0x00000046),
      dual,
      nonextensible,
      oleautomation
    ]
    interface ICallChannelMessage : IDispatch {
        [id(0x00000001), propget, helpstring("Returns/sets message text."), helpcontext(0x00000046)]
        HRESULT Text([out, retval] BSTR* pVal);
        [id(0x00000001), propput, helpstring("Returns/sets message text."), helpcontext(0x00000046)]
        HRESULT Text([in] BSTR pVal);
    };

    [
      odl,
      uuid(55A5200C-B2E8-4795-A6FA-858CA3FE2F26),
      helpstring("ISkypeApplication interface."),
      helpcontext(0x00000003),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeApplication : IDispatch {
        [id(0x00000001), helpstring("Creates application."), helpcontext(0x00000003)]
        HRESULT CreateApplication([in] BSTR Name);
        [id(0x00000002), helpstring("Deletes application."), helpcontext(0x00000003)]
        HRESULT DeleteApplication([in] BSTR Name);
        [id(0x00000003), propget, helpstring("Returns application streams."), helpcontext(0x00000003)]
        HRESULT ApplicationStreams(
                        [in] BSTR AppName, 
                        [out, retval] IApplicationStreamCollection** pVal);
        [id(0x00000004), helpstring("Connects application to user."), helpcontext(0x00000003)]
        HRESULT ConnectApplicationUser(
                        [in] BSTR AppName, 
                        [in] BSTR Username, 
                        [in, optional, defaultvalue(0)] VARIANT_BOOL WaitConnected);
        [id(0x00000005), helpstring("Reads stream."), helpcontext(0x00000003)]
        HRESULT ReadApplicationStream(
                        [in] BSTR AppName, 
                        [in] BSTR StreamHandle, 
                        [out, retval] BSTR* pVal);
        [id(0x00000006), helpstring("Writes stream."), helpcontext(0x00000003)]
        HRESULT WriteApplicationStream(
                        [in] BSTR AppName, 
                        [in] BSTR StreamHandle, 
                        [in] BSTR Text);
        [id(0x00000007), propget, helpstring("Returns application connectable users."), helpcontext(0x00000003)]
        HRESULT ApplicationConnectableUsers(
                        [in] BSTR AppName, 
                        [out, retval] IUserCollection** pVal);
        [id(0x00000008), propget, helpstring("Returns currently connecting users."), helpcontext(0x00000003)]
        HRESULT ApplicationConnectingUsers(
                        [in] BSTR AppName, 
                        [out, retval] IUserCollection** pVal);
        [id(0x00000009), helpstring("Disconnects application from user."), helpcontext(0x00000003)]
        HRESULT DisconnectApplicationUser(
                        [in] BSTR AppName, 
                        [in] BSTR Username);
        [id(0x0000000a), helpstring("Send datagram on stream."), helpcontext(0x00000003)]
        HRESULT SendApplicationDatagram(
                        [in] BSTR AppName, 
                        [in] BSTR StreamHandle, 
                        [in] BSTR Text);
        [id(0x0000000b), propget, helpstring("Returns application sending streams."), helpcontext(0x00000003)]
        HRESULT ApplicationSendingStreams(
                        [in] BSTR AppName, 
                        [out, retval] IApplicationStreamCollection** pVal);
        [id(0x0000000c), propget, helpstring("Returns application receiving streams."), helpcontext(0x00000003)]
        HRESULT ApplicationReceivedStreams(
                        [in] BSTR AppName, 
                        [out, retval] IApplicationStreamCollection** pVal);
    };

    [
      odl,
      uuid(54590FC3-0405-4A2D-B4A5-BEAC026577F2),
      helpstring("ISkypeCall Interface"),
      helpcontext(0x0000002d),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeCall : IDispatch {
        [id(0x00000001), propget, helpstring("Returns call timestamp."), helpcontext(0x0000002d)]
        HRESULT CallTimestamp(
                        [in] BSTR CallId, 
                        [out, retval] DATE* pVal);
        [id(0x00000002), propget, helpstring("Returns call partner handle."), helpcontext(0x0000002d)]
        HRESULT CallPartnerHandle(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns call partner display name."), helpcontext(0x0000002d)]
        HRESULT CallPartnerDisplayName(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns call conference id."), helpcontext(0x0000002d)]
        HRESULT CallConferenceId(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000005), propget, helpstring("Returns call type."), helpcontext(0x0000002d)]
        HRESULT CallType(
                        [in] BSTR CallId, 
                        [out, retval] TCallType* pVal);
        [id(0x00000006), propget, helpstring("Returns call status."), helpcontext(0x0000002d)]
        HRESULT CallStatus(
                        [in] BSTR CallId, 
                        [out, retval] TCallStatus* pVal);
        [id(0x00000006), propput, helpstring("Returns call status."), helpcontext(0x0000002d)]
        HRESULT CallStatus(
                        [in] BSTR CallId, 
                        [in] TCallStatus pVal);
        [id(0x00000007), propget, helpstring("Returns call failure reason."), helpcontext(0x0000002d)]
        HRESULT CallFailureReason(
                        [in] BSTR CallId, 
                        [out, retval] TCallFailureReason* pVal);
        [id(0x00000008), propget, helpstring("Returns call subject."), helpcontext(0x0000002d)]
        HRESULT CallSubject(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns call PSTN number."), helpcontext(0x0000002d)]
        HRESULT CallPstnNumber(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns call duration in seconds."), helpcontext(0x0000002d)]
        HRESULT CallDuration(
                        [in] BSTR CallId, 
                        [out, retval] long* pVal);
        [id(0x0000000b), propget, helpstring("Returns call PSTN status."), helpcontext(0x0000002d)]
        HRESULT CallPstnStatus(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000c), propput, helpstring("Marks call seen."), helpcontext(0x0000002d)]
        HRESULT CallSeenStatus(
                        [in] BSTR CallId, 
                        [in] VARIANT_BOOL pVal);
        [id(0x0000000d), helpstring("Puts call on hold."), helpcontext(0x0000002d)]
        HRESULT CallHold([in] BSTR CallId);
        [id(0x0000000e), helpstring("Resumes the held call."), helpcontext(0x0000002d)]
        HRESULT CallResume([in] BSTR CallId);
        [id(0x0000000f), helpstring("Ends the call."), helpcontext(0x0000002d)]
        HRESULT CallFinish([in] BSTR CallId);
        [id(0x00000010), helpstring("Answers the call."), helpcontext(0x0000002d)]
        HRESULT CallAnswer([in] BSTR CallId);
        [id(0x00000011), propput, helpstring("Sends valus as DTMF."), helpcontext(0x0000002d)]
        HRESULT CallDTMF(
                        [in] BSTR CallId, 
                        [in] BSTR rhs);
        [id(0x00000012), propget, helpstring("Returns conference call participants."), helpcontext(0x0000002d)]
        HRESULT CallParticipants(
                        [in] BSTR CallId, 
                        [out, retval] IParticipantCollection** pVal);
        [id(0x00000013), helpstring("Joins the call to conference."), helpcontext(0x0000002d)]
        HRESULT CallJoin(
                        [in] BSTR CallId1, 
                        [in] BSTR CallId2);
        [id(0x00000014), propget, helpstring("Returns voicemail duration in seconds."), helpcontext(0x0000002d)]
        HRESULT CallVmDuration(
                        [in] BSTR CallId, 
                        [out, retval] long* pVal);
        [id(0x00000015), propget, helpstring("Returns voicemail allowed duration in seconds."), helpcontext(0x0000002d)]
        HRESULT CallVmAllowedDuration(
                        [in] BSTR CallId, 
                        [out, retval] long* pVal);
        [id(0x00000016), propget, helpstring("Returns call video status."), helpcontext(0x0000002d)]
        HRESULT CallVideoStatus(
                        [in] BSTR CallId, 
                        [out, retval] TCallVideoStatus* pVal);
        [id(0x00000017), propget, helpstring("Returns call video send status."), helpcontext(0x0000002d)]
        HRESULT CallVideoSendStatus(
                        [in] BSTR CallId, 
                        [out, retval] TCallVideoSendStatus* pVal);
        [id(0x00000018), propget, helpstring("Returns call video receive status."), helpcontext(0x0000002d)]
        HRESULT CallVideoReceiveStatus(
                        [in] BSTR CallId, 
                        [out, retval] TCallVideoSendStatus* pVal);
        [id(0x00000019), helpstring("Starts video send."), helpcontext(0x0000002d)]
        HRESULT StartCallVideoSend([in] BSTR CallId);
        [id(0x0000001a), helpstring("Stops video send."), helpcontext(0x0000002d)]
        HRESULT StopCallVideoSend([in] BSTR CallId);
        [id(0x0000001b), helpstring("Starts video receive."), helpcontext(0x0000002d)]
        HRESULT StartCallVideoReceive([in] BSTR CallId);
        [id(0x0000001c), helpstring("Stops video receive."), helpcontext(0x0000002d)]
        HRESULT StopCallVideoReceive([in] BSTR CallId);
        [id(0x0000001d), helpstring("Redirects call to voicemail."), helpcontext(0x0000002d)]
        HRESULT RedirectCallToVoicemail([in] BSTR CallId);
        [id(0x0000001e), helpstring("Forwards call."), helpcontext(0x0000002d)]
        HRESULT ForwardCall([in] BSTR CallId);
        [id(0x0000001f), propget, helpstring("Returns call rate."), helpcontext(0x0000002d)]
        HRESULT CallRate(
                        [in] BSTR CallId, 
                        [out, retval] long* pVal);
        [id(0x00000020), propget, helpstring("Returns call rate currency."), helpcontext(0x0000002d)]
        HRESULT CallRateCurrency(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000021), propget, helpstring("Returns call rate precision."), helpcontext(0x0000002d)]
        HRESULT CallRatePrecision(
                        [in] BSTR CallId, 
                        [out, retval] long* pVal);
        [id(0x00000022), propget, helpstring("Returns/sets call input sound device."), helpcontext(0x0000002d)]
        HRESULT CallInputDevice(
                        [in] BSTR CallId, 
                        [in] TCallIoDeviceType DeviceType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000022), propput, helpstring("Returns/sets call input sound device."), helpcontext(0x0000002d)]
        HRESULT CallInputDevice(
                        [in] BSTR CallId, 
                        [in] TCallIoDeviceType DeviceType, 
                        [in] BSTR pVal);
        [id(0x00000023), propget, helpstring("Returns/sets call output sound device."), helpcontext(0x0000002d)]
        HRESULT CallOutputDevice(
                        [in] BSTR CallId, 
                        [in] TCallIoDeviceType DeviceType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000023), propput, helpstring("Returns/sets call output sound device."), helpcontext(0x0000002d)]
        HRESULT CallOutputDevice(
                        [in] BSTR CallId, 
                        [in] TCallIoDeviceType DeviceType, 
                        [in] BSTR pVal);
        [id(0x00000024), propget, helpstring("Returns/sets call microphone sound device."), helpcontext(0x0000002d)]
        HRESULT CallCaptureMicDevice(
                        [in] BSTR CallId, 
                        [in] TCallIoDeviceType DeviceType, 
                        [out, retval] BSTR* pVal);
        [id(0x00000024), propput, helpstring("Returns/sets call microphone sound device."), helpcontext(0x0000002d)]
        HRESULT CallCaptureMicDevice(
                        [in] BSTR CallId, 
                        [in] TCallIoDeviceType DeviceType, 
                        [in] BSTR pVal);
        [id(0x00000025), propget, helpstring("Returns call sound input status."), helpcontext(0x0000002d)]
        HRESULT CallInputStatus(
                        [in] BSTR CallId, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000026), propget, helpstring("Returns call forwarder identity."), helpcontext(0x0000002d)]
        HRESULT CallForwardedBy(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000c), propget, helpstring("Marks call seen."), helpcontext(0x0000002d)]
        HRESULT CallSeenStatus(
                        [in] BSTR CallId, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000027), propget, helpstring("Returns true if call can be transferred."), helpcontext(0x0000002d)]
        HRESULT CallCanTransfer(
                        [in] BSTR CallId, 
                        [in] BSTR Target, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000028), propget, helpstring("Returns call transfer status."), helpcontext(0x0000002d)]
        HRESULT CallTransferStatus(
                        [in] BSTR CallId, 
                        [out, retval] TCallStatus* pVal);
        [id(0x00000029), propget, helpstring("Returns true if call transfer is active."), helpcontext(0x0000002d)]
        HRESULT CallTransferActive(
                        [in] BSTR CallId, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000002a), propget, helpstring("Returns call transferrer identity."), helpcontext(0x0000002d)]
        HRESULT CallTransferredBy(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000002b), propget, helpstring("Returns call transfer target identity."), helpcontext(0x0000002d)]
        HRESULT CallTransferredTo(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000002c), helpstring("Transfers the call to target user."), helpcontext(0x0000002d)]
        HRESULT TransferCall(
                        [in] BSTR CallId, 
                        [in] BSTR Target);
        [id(0x0000002e), propget, helpstring("Returns the target number for incoming SkypeIN calls."), helpcontext(0x0000002d)]
        HRESULT CallTargetIdentity(
                        [in] BSTR CallId, 
                        [out, retval] BSTR* pVal);
    };

    [
      odl,
      uuid(3F6758D2-1D3C-4A8F-BD99-6FC6B0E2DC8F),
      helpstring("ISkypeChat Interface"),
      helpcontext(0x00000030),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeChat : IDispatch {
        [id(0x00000001), propget, helpstring("Returns chat timestamp."), helpcontext(0x00000030)]
        HRESULT ChatTimestamp(
                        [in] BSTR ChatName, 
                        [out, retval] DATE* pVal);
        [id(0x00000002), propget, helpstring("Returns chat adder."), helpcontext(0x00000030)]
        HRESULT ChatAdder(
                        [in] BSTR ChatName, 
                        [out, retval] IUser** pVal);
        [id(0x00000003), propget, helpstring("Returns chat status."), helpcontext(0x00000030)]
        HRESULT ChatStatus(
                        [in] BSTR ChatName, 
                        [out, retval] TChatStatus* pVal);
        [id(0x00000004), propget, helpstring("Returns chat posters."), helpcontext(0x00000030)]
        HRESULT ChatPosters(
                        [in] BSTR ChatName, 
                        [out, retval] IUserCollection** pVal);
        [id(0x00000005), propget, helpstring("Returns chat members."), helpcontext(0x00000030)]
        HRESULT ChatMembers(
                        [in] BSTR ChatName, 
                        [out, retval] IUserCollection** pVal);
        [id(0x00000006), propget, helpstring("Returns chat topic."), helpcontext(0x00000030)]
        HRESULT ChatTopic(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000006), propput, helpstring("Returns chat topic."), helpcontext(0x00000030)]
        HRESULT ChatTopic(
                        [in] BSTR ChatName, 
                        [in] BSTR pVal);
        [id(0x00000007), propget, helpstring("Returns chat active members."), helpcontext(0x00000030)]
        HRESULT ChatActiveMembers(
                        [in] BSTR ChatName, 
                        [out, retval] IUserCollection** pVal);
        [id(0x00000008), propget, helpstring("Returns chat friendly name."), helpcontext(0x00000030)]
        HRESULT ChatFriendlyName(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns chat messages."), helpcontext(0x00000030)]
        HRESULT ChatMessages(
                        [in] BSTR ChatName, 
                        [out, retval] IChatMessageCollection** pVal);
        [id(0x0000000a), helpstring("Opens chat window."), helpcontext(0x00000030)]
        HRESULT OpenChatWindow([in] BSTR ChatName);
        [id(0x0000000b), helpstring("Sends chat message."), helpcontext(0x00000030)]
        HRESULT SendChatMessage(
                        [in] BSTR ChatName, 
                        [in] BSTR MessageText, 
                        [out, retval] IChatMessage** pVal);
        [id(0x0000000c), helpstring("Leaves the chat."), helpcontext(0x00000030)]
        HRESULT LeaveChat([in] BSTR ChatName);
        [id(0x0000000d), helpstring("Adds new members to the chat."), helpcontext(0x00000030)]
        HRESULT AddChatMembers(
                        [in] BSTR ChatName, 
                        [in] IUserCollection* pMembers);
        [id(0x0000000e), propget, helpstring("Returns most recent chat messages."), helpcontext(0x00000030)]
        HRESULT ChatRecentMessages(
                        [in] BSTR ChatName, 
                        [out, retval] IChatMessageCollection** pVal);
        [id(0x0000000f), propget, helpstring("Returns chat bookmarked status."), helpcontext(0x00000030)]
        HRESULT ChatBookmarked(
                        [in] BSTR ChatName, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000010), helpstring("Bookmarks the chat."), helpcontext(0x00000030)]
        HRESULT BookmarkChat([in] BSTR ChatName);
        [id(0x00000011), helpstring("Unbookmarks the chat."), helpcontext(0x00000030)]
        HRESULT UnbookmarkChat([in] BSTR ChatName);
        [id(0x00000012), propget, helpstring("Returns/sets chat topic in XML."), helpcontext(0x00000030)]
        HRESULT ChatTopicXML(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000012), propput, helpstring("Returns/sets chat topic in XML."), helpcontext(0x00000030)]
        HRESULT ChatTopicXML(
                        [in] BSTR ChatName, 
                        [in] BSTR pVal);
        [id(0x00000013), propget, helpstring("Returns chat members collection."), helpcontext(0x00000030)]
        HRESULT ChatMemberObjects(
                        [in] BSTR ChatName, 
                        [out, retval] IChatMemberCollection** pVal);
        [id(0x00000014), propget, helpstring("Returns chat global unique identifier."), helpcontext(0x00000030)]
        HRESULT ChatBlob(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000015), propget, helpstring("Returns/sets chat options."), helpcontext(0x00000030)]
        HRESULT ChatOptions(
                        [in] BSTR ChatName, 
                        [out, retval] long* pVal);
        [id(0x00000015), propput, helpstring("Returns/sets chat options."), helpcontext(0x00000030)]
        HRESULT ChatOptions(
                        [in] BSTR ChatName, 
                        [in] long pVal);
        [id(0x00000016), propget, helpstring("Returns chat password hint."), helpcontext(0x00000030)]
        HRESULT ChatPasswordHint(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000017), helpstring("Sets chat password and hint."), helpcontext(0x00000030)]
        HRESULT SetChatPassword(
                        [in] BSTR ChatName, 
                        [in] BSTR Password, 
                        [in, optional, defaultvalue("")] BSTR Hint);
        [id(0x00000018), propget, helpstring("Returns/sets chat guidelines."), helpcontext(0x00000030)]
        HRESULT ChatGuideLines(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000018), propput, helpstring("Returns/sets chat guidelines."), helpcontext(0x00000030)]
        HRESULT ChatGuideLines(
                        [in] BSTR ChatName, 
                        [in] BSTR pVal);
        [id(0x00000019), propget, helpstring("Returns/sets chat description."), helpcontext(0x00000030)]
        HRESULT ChatDescription(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x00000019), propput, helpstring("Returns/sets chat description."), helpcontext(0x00000030)]
        HRESULT ChatDescription(
                        [in] BSTR ChatName, 
                        [in] BSTR pVal);
        [id(0x0000001a), propget, helpstring("Returns dialog chat partner Skypename."), helpcontext(0x00000030)]
        HRESULT ChatDialogPartner(
                        [in] BSTR ChatName, 
                        [out, retval] BSTR* pVal);
        [id(0x0000001b), propget, helpstring("Returns last chat activity timestamp."), helpcontext(0x00000030)]
        HRESULT ChatActivityTimestamp(
                        [in] BSTR ChatName, 
                        [out, retval] DATE* pVal);
        [id(0x0000001c), propget, helpstring("Returns my role in chat."), helpcontext(0x00000030)]
        HRESULT ChatMyRole(
                        [in] BSTR ChatName, 
                        [out, retval] TChatMemberRole* pVal);
        [id(0x0000001d), propget, helpstring("Returns chat applicants collection."), helpcontext(0x00000030)]
        HRESULT ChatApplicants(
                        [in] BSTR ChatName, 
                        [out, retval] IUserCollection** pVal);
        [id(0x0000001e), helpstring("Joins chat."), helpcontext(0x00000030)]
        HRESULT JoinChat([in] BSTR ChatName);
        [id(0x0000001f), helpstring("Kicks member from chat."), helpcontext(0x00000030)]
        HRESULT KickChatMember(
                        [in] BSTR ChatName, 
                        [in] BSTR Handle);
        [id(0x00000020), helpstring("Kicks and bans member from chat."), helpcontext(0x00000030)]
        HRESULT KickBanChatMember(
                        [in] BSTR ChatName, 
                        [in] BSTR Handle);
        [id(0x00000021), helpstring("Closes chat."), helpcontext(0x00000030)]
        HRESULT DisbandChat([in] BSTR ChatName);
        [id(0x00000022), helpstring("Enters password for chat."), helpcontext(0x00000030)]
        HRESULT EnterChatPassword(
                        [in] BSTR ChatName, 
                        [in] BSTR Password);
        [id(0x00000023), helpstring("Clears recent chat messages."), helpcontext(0x00000030)]
        HRESULT ClearChatRecentMessages([in] BSTR ChatName);
        [id(0x00000024), helpstring("Accepts add to shared group."), helpcontext(0x00000030)]
        HRESULT AcceptSharedGroupAdd([in] BSTR ChatName);
        [id(0x00000025), propput, helpstring("Sets chat alert string."), helpcontext(0x00000030)]
        HRESULT ChatAlertString(
                        [in] BSTR ChatName, 
                        [in] BSTR rhs);
        [id(0x00000026), propget, helpstring("Returns chat type."), helpcontext(0x00000030)]
        HRESULT ChatType(
                        [in] BSTR ChatName, 
                        [out, retval] TChatType* pVal);
        [id(0x00000027), propget, helpstring("Returns chat status."), helpcontext(0x00000030)]
        HRESULT ChatMyStatus(
                        [in] BSTR ChatName, 
                        [out, retval] TChatMyStatus* pVal);
    };

    [
      odl,
      uuid(A569B841-CC8A-4C12-B937-CBC17D9E64F0),
      helpstring("ISkypeChatMessage interface"),
      helpcontext(0x0000002f),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeChatMessage : IDispatch {
        [id(0x00000001), propget, helpstring("Returns message timestamp."), helpcontext(0x0000002f)]
        HRESULT ChatMessageTimestamp(
                        [in] BSTR MessageId, 
                        [out, retval] DATE* pVal);
        [id(0x00000002), propget, helpstring("Returns message from handle."), helpcontext(0x0000002f)]
        HRESULT ChatMessageFromHandle(
                        [in] BSTR MessageId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns message from display name."), helpcontext(0x0000002f)]
        HRESULT ChatMessageFromDisplayName(
                        [in] BSTR MessageId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns message type."), helpcontext(0x0000002f)]
        HRESULT ChatMessageType(
                        [in] BSTR MessageId, 
                        [out, retval] TChatMessageType* pVal);
        [id(0x00000005), propget, helpstring("Returns message status."), helpcontext(0x0000002f)]
        HRESULT ChatMessageStatus(
                        [in] BSTR MessageId, 
                        [out, retval] TChatMessageStatus* pVal);
        [id(0x00000006), propget, helpstring("Returns chat leave reason."), helpcontext(0x0000002f)]
        HRESULT ChatMessageLeaveReason(
                        [in] BSTR MessageId, 
                        [out, retval] TChatLeaveReason* pVal);
        [id(0x00000007), propget, helpstring("Returns/sets message body."), helpcontext(0x0000002f)]
        HRESULT ChatMessageBody(
                        [in] BSTR MessageId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000008), propget, helpstring("Returns chat name."), helpcontext(0x0000002f)]
        HRESULT ChatMessageChatname(
                        [in] BSTR MessageId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns people added to chat."), helpcontext(0x0000002f)]
        HRESULT ChatMessageUsers(
                        [in] BSTR MessageId, 
                        [out, retval] IUserCollection** pVal);
        [id(0x0000000a), propput, helpstring("Sets message seen status."), helpcontext(0x0000002f)]
        HRESULT ChatMessageSeen([in] BSTR rhs);
        [id(0x0000000b), propget, helpstring("Returns message sender."), helpcontext(0x0000002f)]
        HRESULT ChatMessageSender(
                        [in] BSTR MessageId, 
                        [out, retval] IUser** pVal);
        [id(0x0000000c), propget, helpstring("Returns true if the message can be edited."), helpcontext(0x0000002f)]
        HRESULT ChatMessageIsEditable(
                        [in] BSTR MessageId, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000d), propget, helpstring("Returns last message editor Skypename."), helpcontext(0x0000002f)]
        HRESULT ChatMessageEditedBy(
                        [in] BSTR MessageId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000e), propget, helpstring("Returns last message edit timestamp."), helpcontext(0x0000002f)]
        HRESULT ChatMessageEditedTimestamp(
                        BSTR MessageId, 
                        [out, retval] DATE* pVal);
        [id(0x00000007), propput, helpstring("Returns/sets message body."), helpcontext(0x0000002f)]
        HRESULT ChatMessageBody(
                        [in] BSTR MessageId, 
                        [in] BSTR pVal);
        [id(0x0000000f), propget, helpstring("Returns changed member role."), helpcontext(0x0000002f)]
        HRESULT ChatMessageRole(
                        [in] BSTR MessageId, 
                        [out, retval] TChatMemberRole* pVal);
        [id(0x00000010), propget, helpstring("Returns changed chat options."), helpcontext(0x0000002f)]
        HRESULT ChatMessageOptons(
                        [in] BSTR MessageId, 
                        [out, retval] long* pVal);
        [id(0x00000011), propget, helpstring("Returns chat message unique identifier."), helpcontext(0x0000002f)]
        HRESULT ChatMessageGuid(
                        [in] BSTR MessageId, 
                        [out, retval] BSTR* pVal);
    };

    [
      odl,
      uuid(6CF6DBDE-AB7C-4635-96ED-2FF525AB4457),
      helpstring("IChatMember interface"),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeChatMember : IDispatch {
        [id(0x00000001), propget, helpstring("Returns chat member object id.")]
        HRESULT ChatMemberHandle(
                        [in] BSTR MemberId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns/sets chat member role.")]
        HRESULT ChatMemberRole(
                        [in] BSTR MemberId, 
                        [out, retval] TChatMemberRole* pVal);
        [id(0x00000002), propput, helpstring("Returns/sets chat member role.")]
        HRESULT ChatMemberRole(
                        [in] BSTR MemberId, 
                        [in] TChatMemberRole pVal);
        [id(0x00000003), propget, helpstring("Returns true if chat member role can be changed.")]
        HRESULT CanSetChatMemberRoleTo(
                        [in] BSTR MemberId, 
                        [in] TChatMemberRole Role, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000004), propget, helpstring("Returns true if chat member is active.")]
        HRESULT IsChatMemberActive(
                        [in] BSTR MemberId, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000005), propget, helpstring("Returns related Chat object.")]
        HRESULT ChatMemberChat(
                        [in] BSTR MemberId, 
                        [out, retval] IChat** pVal);
    };

    [
      odl,
      uuid(30678F8A-C104-40C0-A6AE-7C150E83300E),
      helpstring("ISkypeConference Interface"),
      helpcontext(0x00000031),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeConference : IDispatch {
        [id(0x00000001), propget, helpstring("Returns calls that are part of this conference."), helpcontext(0x00000031)]
        HRESULT ConferenceCalls(
                        [in] BSTR ConfId, 
                        [out, retval] ICallCollection** pVal);
        [id(0x00000002), propget, helpstring("Returns active calls that are part of this conference."), helpcontext(0x00000031)]
        HRESULT ConferenceActiveCalls(
                        [in] BSTR ConfId, 
                        [out, retval] ICallCollection** pVal);
    };

    [
      odl,
      uuid(2B929860-6AF4-40DF-9D77-308CA7C23E66),
      hidden,
      dual,
      oleautomation
    ]
    interface ISkypeFileTransfer : IDispatch {
        [id(0x00000001), propget, helpstring("Returns file transfer type.")]
        HRESULT FileTransferType(
                        [in] BSTR TransferId, 
                        [out, retval] TFileTransferType* pVal);
        [id(0x00000002), propget, helpstring("Returns file transfer status.")]
        HRESULT FileTransferStatus(
                        [in] BSTR TransferId, 
                        [out, retval] TFileTransferStatus* pVal);
        [id(0x00000003), propget, helpstring("Returns file transfer failure reason code.")]
        HRESULT FileTransferFailureReason(
                        [in] BSTR TransferId, 
                        [out, retval] TFileTransferFailureReason* pVal);
        [id(0x00000004), propget, helpstring("Returns file transfer partner Skypename.")]
        HRESULT FileTransferPartnerHandle(
                        [in] BSTR TransferId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000005), propget, helpstring("Returns file transfer partner display name.")]
        HRESULT FileTransferPartnerDisplayName(
                        [in] BSTR TransferId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000006), propget, helpstring("Returns file transfer start timestamp.")]
        HRESULT FileTransferStartTime(
                        [in] BSTR TransferId, 
                        [out, retval] DATE* pVal);
        [id(0x00000007), propget, helpstring("Returns file transfer end timestamp.")]
        HRESULT FileTransferFinishTime(
                        [in] BSTR TransferId, 
                        [out, retval] DATE* pVal);
        [id(0x00000008), propget, helpstring("Returns file transfer file path.")]
        HRESULT FileTransferFilePath(
                        [in] BSTR TransferId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns file transfer file name.")]
        HRESULT FileTransferFileName(
                        [in] BSTR TransferId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns file transfer speed in bytes per second.")]
        HRESULT FileTransferBytesPerSecond(
                        [in] BSTR TransferId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000b), propget, helpstring("Returns file transfer total bytes transferred.")]
        HRESULT FileTransferBytesTransferred(
                        [in] BSTR TransferId, 
                        [out, retval] BSTR* pVal);
    };

    [
      odl,
      uuid(6D0B4547-771D-4C4F-B3E8-98A33FD24D2B),
      helpstring("ISkypeSms Interface"),
      helpcontext(0x0000004e),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeSms : IDispatch {
        [id(0x00000001), propget, helpstring("Returns message type."), helpcontext(0x0000004e)]
        HRESULT SmsMessageType(
                        [in] BSTR SmsId, 
                        [out, retval] TSmsMessageType* pVal);
        [id(0x00000002), propget, helpstring("Returns message status."), helpcontext(0x0000004e)]
        HRESULT SmsMessageStatus(
                        [in] BSTR SmsId, 
                        [out, retval] TSmsMessageStatus* pVal);
        [id(0x00000003), propget, helpstring("Returns message failure reason."), helpcontext(0x0000004e)]
        HRESULT SmsFailureReason(
                        [in] BSTR SmsId, 
                        [out, retval] TSmsFailureReason* pVal);
        [id(0x00000004), propget, helpstring("Returns true if message failed unseen."), helpcontext(0x0000004e)]
        HRESULT SmsIsFailedUnseen(
                        [in] BSTR SmsId, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000005), propput, helpstring("Sets message status read."), helpcontext(0x0000004e)]
        HRESULT SmsSeen([in] BSTR rhs);
        [id(0x00000006), propget, helpstring("Returns price value."), helpcontext(0x0000004e)]
        HRESULT SmsPrice(
                        [in] BSTR SmsId, 
                        [out, retval] long* pVal);
        [id(0x00000007), propget, helpstring("Returns price currency code."), helpcontext(0x0000004e)]
        HRESULT SmsPriceCurrency(
                        [in] BSTR SmsId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000008), propget, helpstring("Returns price precision."), helpcontext(0x0000004e)]
        HRESULT SmsPricePrecision(
                        [in] BSTR SmsId, 
                        [out, retval] long* pVal);
        [id(0x00000009), propget, helpstring("Returns/sets reply-to number."), helpcontext(0x0000004e)]
        HRESULT SmsReplyToNumber(
                        [in] BSTR SmsId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000009), propput, helpstring("Returns/sets reply-to number."), helpcontext(0x0000004e)]
        HRESULT SmsReplyToNumber(
                        [in] BSTR SmsId, 
                        [in] BSTR pVal);
        [id(0x0000000a), propget, helpstring("Returns/sets message targets."), helpcontext(0x0000004e)]
        HRESULT SmsTargets(
                        [in] BSTR SmsId, 
                        [out, retval] ISmsTargetCollection** pVal);
        [id(0x0000000b), propget, helpstring("Returns/sets message text."), helpcontext(0x0000004e)]
        HRESULT SmsBody(
                        [in] BSTR SmsId, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000b), propput, helpstring("Returns/sets message text."), helpcontext(0x0000004e)]
        HRESULT SmsBody(
                        [in] BSTR SmsId, 
                        [in] BSTR pVal);
        [id(0x0000000c), propget, helpstring("Returns message chunks."), helpcontext(0x0000004e)]
        HRESULT SmsChunks(
                        [in] BSTR SmsId, 
                        [out, retval] ISmsChunkCollection** pVal);
        [id(0x0000000d), helpstring("Sends the message."), helpcontext(0x0000004e)]
        HRESULT SendSmsMessage([in] BSTR SmsId);
        [id(0x0000000e), helpstring("Deletes the message."), helpcontext(0x0000004e)]
        HRESULT DeleteSmsMessage([in] BSTR SmsId);
        [id(0x0000000f), propget, helpstring("Returns message target status"), helpcontext(0x0000004e)]
        HRESULT SmsTargetStatus(
                        [in] BSTR SmsId, 
                        [in] BSTR Number, 
                        [out, retval] TSmsTargetStatus* pVal);
        [id(0x00000010), propget, helpstring("Returns chunk text."), helpcontext(0x0000004e)]
        HRESULT SmsChunkText(
                        [in] BSTR SmsId, 
                        [in] BSTR ChunkId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000011), propget, helpstring("Returns number of characters left in chunk."), helpcontext(0x0000004e)]
        HRESULT SmsChunkCharactersLeft(
                        [in] BSTR SmsId, 
                        [in] BSTR ChunkId, 
                        [out, retval] long* pVal);
        [id(0x00000012), propget, helpstring("Returns message timestamp."), helpcontext(0x0000004e)]
        HRESULT SmsTimestamp(
                        [in] BSTR SmsId, 
                        [out, retval] DATE* pVal);
        [id(0x00000013), propget, helpstring("Returns/sets message target numbers."), helpcontext(0x0000004e)]
        HRESULT SmsTargetNumbers(
                        [in] BSTR SmsId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000013), propput, helpstring("Returns/sets message target numbers."), helpcontext(0x0000004e)]
        HRESULT SmsTargetNumbers(
                        [in] BSTR SmsId, 
                        [in] BSTR pVal);
    };

    [
      odl,
      uuid(C219279C-F557-4BAD-B3BE-750E91CA9944),
      helpstring("ISkypeUser Interface"),
      helpcontext(0x0000002e),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeUser : IDispatch {
        [id(0x00000001), propget, helpstring("Returns user full name."), helpcontext(0x0000002e)]
        HRESULT UserFullName(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("Returns user birthday."), helpcontext(0x0000002e)]
        HRESULT UserBirthday(
                        [in] BSTR Username, 
                        [out, retval] DATE* pVal);
        [id(0x00000003), propget, helpstring("Returns user sex."), helpcontext(0x0000002e)]
        HRESULT UserSex(
                        [in] BSTR Username, 
                        [out, retval] TUserSex* pVal);
        [id(0x00000004), propget, helpstring("Returns user country."), helpcontext(0x0000002e)]
        HRESULT UserCountry(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000005), propget, helpstring("Returns user province."), helpcontext(0x0000002e)]
        HRESULT UserProvince(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000006), propget, helpstring("Returns user city."), helpcontext(0x0000002e)]
        HRESULT UserCity(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000007), propget, helpstring("Returns user home phone number."), helpcontext(0x0000002e)]
        HRESULT UserPhoneHome(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000008), propget, helpstring("Returns user office phone number."), helpcontext(0x0000002e)]
        HRESULT UserPhoneOffice(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000009), propget, helpstring("Returns user mobile phone number."), helpcontext(0x0000002e)]
        HRESULT UserPhoneMobile(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000a), propget, helpstring("Returns user homepage."), helpcontext(0x0000002e)]
        HRESULT UserHomepage(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000b), propget, helpstring("Returns user about text."), helpcontext(0x0000002e)]
        HRESULT UserAbout(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x0000000c), propget, helpstring("Returns true if user has call equipment."), helpcontext(0x0000002e)]
        HRESULT UserHasCallEquipment(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000d), propget, helpstring("Returns user buddy status."), helpcontext(0x0000002e)]
        HRESULT UserBuddyStatus(
                        [in] BSTR Username, 
                        [out, retval] TBuddyStatus* pVal);
        [id(0x0000000d), propput, helpstring("Returns user buddy status."), helpcontext(0x0000002e)]
        HRESULT UserBuddyStatus(
                        [in] BSTR Username, 
                        [in] TBuddyStatus pVal);
        [id(0x0000000e), propget, helpstring("Returns true if user is authorized by current user."), helpcontext(0x0000002e)]
        HRESULT UserIsAuthorized(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000e), propput, helpstring("Returns true if user is authorized by current user."), helpcontext(0x0000002e)]
        HRESULT UserIsAuthorized(
                        [in] BSTR Username, 
                        [in] VARIANT_BOOL pVal);
        [id(0x0000000f), propget, helpstring("Returns true if user is blocked by current user."), helpcontext(0x0000002e)]
        HRESULT UserIsBlocked(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000000f), propput, helpstring("Returns true if user is blocked by current user."), helpcontext(0x0000002e)]
        HRESULT UserIsBlocked(
                        [in] BSTR Username, 
                        [in] VARIANT_BOOL pVal);
        [id(0x00000010), propget, helpstring("Returns user display name."), helpcontext(0x0000002e)]
        HRESULT UserDisplayName(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000011), propget, helpstring("Returns user online status."), helpcontext(0x0000002e)]
        HRESULT UserOnlineStatus(
                        [in] BSTR Username, 
                        [out, retval] TOnlineStatus* pVal);
        [id(0x00000012), propget, helpstring("Returns timestamp when user was last seen online."), helpcontext(0x0000002e)]
        HRESULT UserLastOnline(
                        [in] BSTR Username, 
                        [out, retval] DATE* pVal);
        [id(0x00000013), propget, helpstring("Returns user country code."), helpcontext(0x0000002e)]
        HRESULT UserCountryCode(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000014), propget, helpstring("Returns received authorization request text."), helpcontext(0x0000002e)]
        HRESULT UserReceivedAuthRequest(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000015), propget, helpstring("Returns/sets users speed dial code."), helpcontext(0x0000002e)]
        HRESULT UserSpeedDial(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000015), propput, helpstring("Returns/sets users speed dial code."), helpcontext(0x0000002e)]
        HRESULT UserSpeedDial(
                        [in] BSTR Username, 
                        [in] BSTR pVal);
        [id(0x00000016), propget, helpstring("Returns true if it is possible to send voicemail to user."), helpcontext(0x0000002e)]
        HRESULT UserCanLeaveVoicemail(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x00000017), propget, helpstring("Returns user mood text."), helpcontext(0x0000002e)]
        HRESULT UserMoodText(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000018), propget, helpstring("Returns user aliases."), helpcontext(0x0000002e)]
        HRESULT UserAliases(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000019), propget, helpstring("Returns user timezone."), helpcontext(0x0000002e)]
        HRESULT UserTimezone(
                        [in] BSTR Username, 
                        [out, retval] long* pVal);
        [id(0x0000001a), propget, helpstring("Returns user call forward active status."), helpcontext(0x0000002e)]
        HRESULT IsCallForwardActive(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000001b), propget, helpstring("Returns user language name."), helpcontext(0x0000002e)]
        HRESULT UserLanguage(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x0000001c), propget, helpstring("Returns user language code."), helpcontext(0x0000002e)]
        HRESULT UserLanguageCode(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x0000001d), propget, helpstring("Returns user video capabilty."), helpcontext(0x0000002e)]
        HRESULT UserIsVideoCapable(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
        [id(0x0000001e), propget, helpstring("Returns user authenticated buddies count."), helpcontext(0x0000002e)]
        HRESULT UserNumberOfAuthBuddies(
                        [in] BSTR Username, 
                        [out, retval] long* pVal);
        [id(0x00000010), propput, helpstring("Returns user display name."), helpcontext(0x0000002e)]
        HRESULT UserDisplayName(
                        [in] BSTR Username, 
                        [in] BSTR pVal);
        [id(0x0000001f), propget, helpstring("Returns user rich mood text."), helpcontext(0x0000002e)]
        HRESULT UserRichMoodText(
                        [in] BSTR Username, 
                        [out, retval] BSTR* pVal);
        [id(0x00000020), propget, helpstring("Returns true if user user can receive voicemails."), helpcontext(0x0000002e)]
        HRESULT UserIsVoicemailCapable(
                        [in] BSTR Username, 
                        [out, retval] VARIANT_BOOL* pVal);
    };

    [
      odl,
      uuid(4D33E14E-9921-4860-92F4-5DC1586F403C),
      helpstring("ISkypeVoicemail interface"),
      helpcontext(0x00000032),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypeVoicemail : IDispatch {
        [id(0x00000001), propget, helpstring("Returns voicemail type."), helpcontext(0x00000032)]
        HRESULT VoicemailType(
                        [in] BSTR VoicemailId, 
                        [out, retval] TVoicemailType* pVal);
        [id(0x00000002), propget, helpstring("Returns voicemail partner handle."), helpcontext(0x00000032)]
        HRESULT VoicemailPartnerHandle(
                        [in] BSTR VoicemailId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000003), propget, helpstring("Returns voicemail partner display name."), helpcontext(0x00000032)]
        HRESULT VoicemailPartnerDisplayName(
                        [in] BSTR VoicemailId, 
                        [out, retval] BSTR* pVal);
        [id(0x00000004), propget, helpstring("Returns voicemail status."), helpcontext(0x00000032)]
        HRESULT VoicemailStatus(
                        [in] BSTR VoicemailId, 
                        [out, retval] TVoicemailStatus* pVal);
        [id(0x00000005), propget, helpstring("Returns voicemail failure reason."), helpcontext(0x00000032)]
        HRESULT VoicemailFailureReason(
                        [in] BSTR VoicemailId, 
                        [out, retval] TVoicemailFailureReason* pVal);
        [id(0x00000006), propget, helpstring("Returns voicemail timestamp."), helpcontext(0x00000032)]
        HRESULT VoicemailTimestamp(
                        [in] BSTR VoicemailId, 
                        [out, retval] DATE* pVal);
        [id(0x00000007), propget, helpstring("Returns voicemail duration in seconds."), helpcontext(0x00000032)]
        HRESULT VoicemailDuration(
                        [in] BSTR VoicemailId, 
                        [out, retval] long* pVal);
        [id(0x00000008), propget, helpstring("Returns voicemail allowed duration in seconds."), helpcontext(0x00000032)]
        HRESULT VoicemailAllowedDuration(
                        [in] BSTR VoicemailId, 
                        [out, retval] long* pVal);
        [id(0x00000009), helpstring("Opens voicemail."), helpcontext(0x00000032)]
        HRESULT OpenVoicemail([in] BSTR VoicemailId);
        [id(0x0000000a), helpstring("Starts voicemail playback."), helpcontext(0x00000032)]
        HRESULT StartVoicemailPlayback([in] BSTR VoicemailId);
        [id(0x0000000b), helpstring("Stops voicemail playback."), helpcontext(0x00000032)]
        HRESULT StopVoicemailPlayback([in] BSTR VoicemailId);
        [id(0x0000000c), helpstring("Uploads voicemail."), helpcontext(0x00000032)]
        HRESULT UploadVoicemail([in] BSTR VoicemailId);
        [id(0x0000000d), helpstring("Downloads voicemail."), helpcontext(0x00000032)]
        HRESULT DownloadVoicemail([in] BSTR VoicemailId);
        [id(0x0000000e), helpstring("Starts voicemail recording."), helpcontext(0x00000032)]
        HRESULT StartVoicemailRecording([in] BSTR VoicemailId);
        [id(0x0000000f), helpstring("Stops voicemail recording."), helpcontext(0x00000032)]
        HRESULT StopVoicemailRecording([in] BSTR VoicemailId);
        [id(0x00000010), helpstring("Deletes voicemail."), helpcontext(0x00000032)]
        HRESULT DeleteVoicemail([in] BSTR VoicemailId);
        [id(0x00000011), helpstring("Starts playback in call."), helpcontext(0x00000032)]
        HRESULT StartVoicemailPlaybackInCall([in] BSTR VoicemailId);
        [id(0x00000012), helpstring("Changes played voicemail status back to unplayed."), helpcontext(0x00000032)]
        HRESULT SetVoicemailUnplayed([in] BSTR VoicemailId);
    };

    [
      uuid(F4F90CDD-C620-4118-945E-CAA1BBEBA435),
      helpstring("_ISkypeEvents Interface"),
      helpcontext(0x00000004)
    ]
    dispinterface _ISkypeEvents {
        properties:
        methods:
            [id(0x00000001), helpstring("Fired on Skype API command message."), helpcontext(0x00000004)]
            HRESULT Command([in] ICommand* pCommand);
            [id(0x00000002), helpstring("Fired on Skype API reply message."), helpcontext(0x00000004)]
            HRESULT Reply([in] ICommand* pCommand);
            [id(0x00000003), helpstring("Fired on Skype API error message."), helpcontext(0x00000004)]
            HRESULT Error(
                            [in] ICommand* pCommand, 
                            [in] long Number, 
                            [in] BSTR Description);
            [id(0x00000004), helpstring("Fired on attachment status change."), helpcontext(0x00000004)]
            HRESULT AttachmentStatus([in] TAttachmentStatus Status);
            [id(0x00000005), helpstring("Fired on connection status change."), helpcontext(0x00000004)]
            HRESULT ConnectionStatus([in] TConnectionStatus Status);
            [id(0x00000006), helpstring("Fired on user status change."), helpcontext(0x00000004)]
            HRESULT UserStatus([in] TUserStatus Status);
            [id(0x00000007), helpstring("Fired on user online status change."), helpcontext(0x00000004)]
            HRESULT OnlineStatus(
                            [in] IUser* pUser, 
                            [in] TOnlineStatus Status);
            [id(0x00000008), helpstring("Fired on call status change."), helpcontext(0x00000004)]
            HRESULT CallStatus(
                            [in] ICall* pCall, 
                            [in] TCallStatus Status);
            [id(0x00000009), helpstring("Fired on call history change."), helpcontext(0x00000004)]
            HRESULT CallHistory();
            [id(0x0000000a), helpstring("Fired on mute status change."), helpcontext(0x00000004)]
            HRESULT Mute([in] VARIANT_BOOL Mute);
            [id(0x0000000b), helpstring("Fired on message status change."), helpcontext(0x00000004)]
            HRESULT MessageStatus(
                            [in] IChatMessage* pMessage, 
                            [in] TChatMessageStatus Status);
            [id(0x0000000c), helpstring("Fired on message history change."), helpcontext(0x00000004)]
            HRESULT MessageHistory([in] BSTR Username);
            [id(0x0000000d), helpstring("Fired on auto away status change."), helpcontext(0x00000004)]
            HRESULT AutoAway([in] VARIANT_BOOL Automatic);
            [id(0x0000000e), helpstring("Fired on call dtmf pressed."), helpcontext(0x00000004)]
            HRESULT CallDtmfReceived(
                            [in] ICall* pCall, 
                            [in] BSTR code);
            [id(0x0000000f), helpstring("Fired on voicemail status change."), helpcontext(0x00000004)]
            HRESULT VoicemailStatus(
                            [in] IVoicemail* pMail, 
                            [in] TVoicemailStatus Status);
            [id(0x00000010), helpstring("Fired on application connecting users change."), helpcontext(0x00000004)]
            HRESULT ApplicationConnecting(
                            [in] IApplication* pApp, 
                            [in] IUserCollection* pUsers);
            [id(0x00000011), helpstring("Fired on application streams change."), helpcontext(0x00000004)]
            HRESULT ApplicationStreams(
                            [in] IApplication* pApp, 
                            [in] IApplicationStreamCollection* pStreams);
            [id(0x00000012), helpstring("Fired on application datagram."), helpcontext(0x00000004)]
            HRESULT ApplicationDatagram(
                            [in] IApplication* pApp, 
                            [in] IApplicationStream* pStream, 
                            [in] BSTR Text);
            [id(0x00000013), helpstring("Fired on application sending data."), helpcontext(0x00000004)]
            HRESULT ApplicationSending(
                            [in] IApplication* pApp, 
                            [in] IApplicationStreamCollection* pStreams);
            [id(0x00000014), helpstring("Fired on application receiving data."), helpcontext(0x00000004)]
            HRESULT ApplicationReceiving(
                            [in] IApplication* pApp, 
                            [in] IApplicationStreamCollection* pStreams);
            [id(0x00000015), helpstring("Fired on contacts focus received or lost."), helpcontext(0x00000004)]
            HRESULT ContactsFocused([in] BSTR Username);
            [id(0x00000016), helpstring("Fired on group visibility status change."), helpcontext(0x00000004)]
            HRESULT GroupVisible(
                            [in] IGroup* pGroup, 
                            [in] VARIANT_BOOL Visible);
            [id(0x00000017), helpstring("Fired on group selection status change."), helpcontext(0x00000004)]
            HRESULT GroupExpanded(
                            [in] IGroup* pGroup, 
                            [in] VARIANT_BOOL Expanded);
            [id(0x00000018), helpstring("Fired on group user list change."), helpcontext(0x00000004)]
            HRESULT GroupUsers(
                            [in] IGroup* pGroup, 
                            [in] IUserCollection* pUsers);
            [id(0x00000019), helpstring("Fired when group is deleted."), helpcontext(0x00000004)]
            HRESULT GroupDeleted([in] long GroupId);
            [id(0x0000001a), helpstring("Fired when user mood text changes."), helpcontext(0x00000004)]
            HRESULT UserMood(
                            [in] IUser* pUser, 
                            [in] BSTR MoodText);
            [id(0x0000001b), helpstring("Fired when SMS message status changes."), helpcontext(0x00000004)]
            HRESULT SmsMessageStatusChanged(
                            [in] ISmsMessage* pMessage, 
                            [in] TSmsMessageStatus Status);
            [id(0x0000001c), helpstring("Fired when SMS target status changes."), helpcontext(0x00000004)]
            HRESULT SmsTargetStatusChanged(
                            [in] ISmsTarget* pTarget, 
                            [in] TSmsTargetStatus Status);
            [id(0x0000001d), helpstring("Fired when voice input status changes during an active call."), helpcontext(0x00000004)]
            HRESULT CallInputStatusChanged(
                            [in] ICall* pCall, 
                            [in] VARIANT_BOOL Status);
            [id(0x0000001e), helpstring("Fired when search finishes."), helpcontext(0x00000004)]
            HRESULT AsyncSearchUsersFinished(
                            [in] long Cookie, 
                            [in] IUserCollection* pUsers);
            [id(0x0000001f), helpstring("Fired when call seen status changes."), helpcontext(0x00000004)]
            HRESULT CallSeenStatusChanged(
                            [in] ICall* pCall, 
                            VARIANT_BOOL Status);
            [id(0x00000020), helpstring("Fired when plugin event is clicked."), helpcontext(0x00000004)]
            HRESULT PluginEventClicked([in] IPluginEvent* pEvent);
            [id(0x00000021), helpstring("Fired when plugin menu item is selected."), helpcontext(0x00000004)]
            HRESULT PluginMenuItemClicked(
                            [in] IPluginMenuItem* pMenuItem, 
                            [in] IUserCollection* pUsers, 
                            [in] TPluginContext PluginContext, 
                            [in] BSTR ContextId);
            [id(0x00000022), helpstring("Fired when wallpaper changes."), helpcontext(0x00000004)]
            HRESULT WallpaperChanged([in] BSTR Path);
            [id(0x00000023), helpstring("Fired when file transfer status changes."), helpcontext(0x00000004)]
            HRESULT FileTransferStatusChanged(
                            [in] IFileTransfer* pTransfer, 
                            [in] TFileTransferStatus Status);
            [id(0x00000024), helpstring("Fired when call transfer status changes."), helpcontext(0x00000004)]
            HRESULT CallTransferStatusChanged(
                            [in] ICall* pCall, 
                            [in] TCallStatus Status);
            [id(0x00000025), helpstring("Fired when list of chat members changes."), helpcontext(0x00000004)]
            HRESULT ChatMembersChanged(
                            [in] IChat* pChat, 
                            [in] IUserCollection* pMembers);
            [id(0x00000026), helpstring("Fired when chat member role changes."), helpcontext(0x00000004)]
            HRESULT ChatMemberRoleChanged(
                            [in] IChatMember* pMember, 
                            [in] TChatMemberRole Role);
            [id(0x00000027), helpcontext(0x00000004)]
            HRESULT CallVideoStatusChanged(
                            [in] ICall* pCall, 
                            [in] TCallVideoStatus Status);
            [id(0x00000028), helpcontext(0x00000004)]
            HRESULT CallVideoSendStatusChanged(
                            [in] ICall* pCall, 
                            [in] TCallVideoSendStatus Status);
            [id(0x00000029), helpcontext(0x00000004)]
            HRESULT CallVideoReceiveStatusChanged(
                            [in] ICall* pCall, 
                            [in] TCallVideoSendStatus Status);
            [id(0x0000002a), helpcontext(0x00000004)]
            HRESULT SilentModeStatusChanged([in] VARIANT_BOOL Silent);
            [id(0x0000002b), helpcontext(0x00000004)]
            HRESULT UILanguageChanged([in] BSTR code);
            [id(0x0000002c), helpcontext(0x00000004)]
            HRESULT UserAuthorizationRequestReceived([in] IUser* pUser);
    };

    [
      uuid(497ABB45-20AE-49D1-A39D-CBE84A31B20C),
      helpstring("_ICallChannelManagerEvents interface"),
      helpcontext(0x00000047)
    ]
    dispinterface _ICallChannelManagerEvents {
        properties:
        methods:
            [id(0x00000001), helpstring("Fired when channel is created or deleted."), helpcontext(0x00000047)]
            HRESULT Channels(
                            [in] ICallChannelManager* pManager, 
                            [in] ICallChannelCollection* pChannels);
            [id(0x00000002), helpstring("Fired when a message is received."), helpcontext(0x00000047)]
            HRESULT Message(
                            [in] ICallChannelManager* pManager, 
                            [in] ICallChannel* pChannel, 
                            [in] ICallChannelMessage* pMessage);
            [id(0x00000003), helpstring("Fired when application context is created."), helpcontext(0x00000047)]
            HRESULT Created();
    };

    [
      uuid(830690FC-BF2F-47A6-AC2D-330BCB402664),
      helpstring("Skype class."),
      helpcontext(0x00000012)
    ]
    coclass Skype {
        [default] interface ISkype;
        [default, source] dispinterface _ISkypeEvents;
        interface ISkypeApplication;
        interface ISkypeCall;
        interface ISkypeChat;
        interface ISkypeChatMessage;
        interface ISkypeConference;
        interface ISkypeFileTransfer;
        interface ISkypePlugin;
        interface ISkypeSms;
        interface ISkypeUser;
        interface ISkypeVoicemail;
    };

    [
      odl,
      uuid(B77A3D1F-6847-402F-BB82-A0564379088E),
      hidden,
      dual,
      nonextensible,
      oleautomation
    ]
    interface ISkypePlugin : IDispatch {
        [id(0x00000001)]
        HRESULT CreatePluginEvent(
                        [in] BSTR EventId, 
                        [in] BSTR Caption, 
                        [in] BSTR Hint, 
                        [out, retval] IPluginEvent** pEvent);
        [id(0x00000002)]
        HRESULT DeletePluginEvent([in] BSTR EventId);
        [id(0x00000003)]
        HRESULT CreatePluginMenuItem(
                        [in] BSTR MenuItemId, 
                        [in] TPluginContext PluginContext, 
                        [in] BSTR CaptionText, 
                        [in, optional, defaultvalue("")] BSTR HintText, 
                        [in, optional, defaultvalue("")] BSTR IconPath, 
                        [in, optional, defaultvalue(-1)] VARIANT_BOOL Enabled, 
                        [in, optional, defaultvalue(0)] TPluginContactType ContactType, 
                        [in, optional, defaultvalue(0)] VARIANT_BOOL MultipleContacts, 
                        [out, retval] IPluginMenuItem** pMenuItem);
        [id(0x00000004)]
        HRESULT DeletePluginMenuItem([in] BSTR MenuItemId);
        [id(0x00000005), propput]
        HRESULT PluginMenuItemCaption(
                        [in] BSTR MenuItemId, 
                        [in] BSTR rhs);
        [id(0x00000006), propput]
        HRESULT PluginMenuItemHint(
                        [in] BSTR MenuItemId, 
                        [in] BSTR rhs);
        [id(0x00000007)]
        HRESULT EnablePluginMenuItem(
                        [in] BSTR MenuItemId, 
                        [in] VARIANT_BOOL Enabled);
    };

    [
      uuid(3E01D8E0-A72B-4C9F-99BD-8A6E7B97A48D),
      helpstring("User class."),
      helpcontext(0x00000013)
    ]
    coclass User {
        [default] interface IUser;
    };

    [
      uuid(7B030003-037D-490D-9169-A4F391B3D831),
      helpstring("User collection class."),
      helpcontext(0x00000014)
    ]
    coclass UserCollection {
        [default] interface IUserCollection;
    };

    [
      uuid(2EEAB6D0-491E-4962-BBA1-FF1CCA6D4DD0),
      helpstring("Conversion class."),
      helpcontext(0x00000015)
    ]
    coclass Conversion {
        [default] interface IConversion;
    };

    [
      uuid(D26B1D42-9C42-4E7B-BB73-86384C4B4345),
      helpstring("Call class."),
      helpcontext(0x00000016)
    ]
    coclass Call {
        [default] interface ICall;
    };

    [
      uuid(F3188CF3-EF22-4C5B-92CB-605964761C3B),
      helpstring("Call collection class."),
      helpcontext(0x00000017)
    ]
    coclass CallCollection {
        [default] interface ICallCollection;
    };

    [
      uuid(7ACDC5B4-76A1-4BDF-918D-6962FCABBAD3),
      helpstring("Chat class."),
      helpcontext(0x00000022)
    ]
    coclass Chat {
        [default] interface IChat;
    };

    [
      uuid(15B6FEE5-5FB3-4071-AC1F-7AEDC0E2A6BB),
      helpstring("Chat collection class."),
      helpcontext(0x00000023)
    ]
    coclass ChatCollection {
        [default] interface IChatCollection;
    };

    [
      uuid(52071016-E648-4D3B-B57E-2B46CC993CE0),
      helpstring("Conference call participant class."),
      helpcontext(0x00000029)
    ]
    coclass Participant {
        [default] interface IParticipant;
    };

    [
      uuid(E1BC9147-C3E3-4E8A-8304-5E6B5C1C0774),
      helpstring("Participants collection class."),
      helpcontext(0x0000002a)
    ]
    coclass ParticipantCollection {
        [default] interface IParticipantCollection;
    };

    [
      uuid(A983C9EC-D73E-4364-B89B-ACD1E405674F),
      helpstring("Conference class"),
      helpcontext(0x0000002b)
    ]
    coclass Conference {
        [default] interface IConference;
    };

    [
      uuid(3506CDB7-8BC6-40C0-B108-CEA0B9480130),
      helpstring("Conference collection class."),
      helpcontext(0x0000002c)
    ]
    coclass ConferenceCollection {
        [default] interface IConferenceCollection;
    };

    [
      uuid(DD0E8ED5-1494-4B87-A35C-39F6ED4B1153),
      helpstring("Voicemail class"),
      helpcontext(0x00000035)
    ]
    coclass Voicemail {
        [default] interface IVoicemail;
    };

    [
      uuid(A7DF2611-D752-4C9F-A90A-B56F18485EE9),
      helpstring("Voicemail collection class"),
      helpcontext(0x00000036)
    ]
    coclass VoicemailCollection {
        [default] interface IVoicemailCollection;
    };

    [
      uuid(29DCD339-D184-469B-8BFB-199A2CCF014E),
      helpstring("Application class."),
      helpcontext(0x0000001d)
    ]
    coclass Application {
        [default] interface IApplication;
    };

    [
      uuid(6FA10A39-4760-4C94-A210-2398848618EC),
      helpstring("Application stream class."),
      helpcontext(0x00000037)
    ]
    coclass ApplicationStream {
        [default] interface IApplicationStream;
    };

    [
      uuid(4B42750B-57A1-47E7-B340-8EAE0E3126A4),
      helpstring("Application stream collection class."),
      helpcontext(0x00000039)
    ]
    coclass ApplicationStreamCollection {
        [default] interface IApplicationStreamCollection;
    };

    [
      uuid(9017071A-2E34-4C3A-9BBB-688CBB5A9FF2),
      helpstring("Chat message class."),
      helpcontext(0x00000018)
    ]
    coclass ChatMessage {
        [default] interface IChatMessage;
    };

    [
      uuid(10DD084E-A5AE-456F-A3BE-DA67EBE6B090),
      helpstring("Chat message collection class."),
      helpcontext(0x00000019)
    ]
    coclass ChatMessageCollection {
        [default] interface IChatMessageCollection;
    };

    [
      uuid(452CCB69-6A95-4370-9E5A-B3EFB06A7651),
      helpstring("Current user profile class."),
      helpcontext(0x0000003d)
    ]
    coclass Profile {
        [default] interface IProfile;
    };

    [
      uuid(222C0F35-3D78-4570-9F6D-BAEE289D0304),
      helpstring("Contact group class."),
      helpcontext(0x0000001b)
    ]
    coclass Group {
        [default] interface IGroup;
    };

    [
      uuid(A8109DB9-88E0-42FE-98EA-8A12BE5394C6),
      helpstring("Contact groups collection class."),
      helpcontext(0x0000001c)
    ]
    coclass GroupCollection {
        [default] interface IGroupCollection;
    };

    [
      uuid(B0FE88F0-C92F-46D6-878F-31599BEA944C),
      helpstring("User settings class."),
      helpcontext(0x0000003b)
    ]
    coclass Settings {
        [default] interface ISettings;
    };

    [
      uuid(B09AC3FF-0D5D-41C6-A34E-7C3F58A3127C),
      helpstring("Skype user interface class."),
      helpcontext(0x0000003e)
    ]
    coclass Client {
        [default] interface IClient;
    };

    [
      uuid(2DBCDA9F-1248-400B-A382-A56D71BF7B15),
      helpstring("Command class."),
      helpcontext(0x0000001a)
    ]
    coclass Command {
        [default] interface ICommand;
    };

    [
      uuid(89DD2F9D-C325-48BF-A615-96BD039BBC83),
      helpstring("Call data channel."),
      helpcontext(0x0000003f)
    ]
    coclass CallChannel {
        [default] interface ICallChannel;
    };

    [
      uuid(42FE718B-A148-41D6-885B-01A0AFAE8723),
      helpstring("Call channel collection class."),
      helpcontext(0x00000040)
    ]
    coclass CallChannelCollection {
        [default] interface ICallChannelCollection;
    };

    [
      uuid(5E541E71-A474-4EAD-8FCB-24D400D023B7),
      helpstring("Call data channel manager."),
      helpcontext(0x0000003f)
    ]
    coclass CallChannelManager {
        [default] interface ICallChannelManager;
        [default, source] dispinterface _ICallChannelManagerEvents;
    };

    [
      uuid(3D3E7C1B-79A7-4CC7-8925-41FA813E9913),
      helpstring("Call data channel message."),
      helpcontext(0x00000042)
    ]
    coclass CallChannelMessage {
        [default] interface ICallChannelMessage;
    };

    [
      uuid(FFC8B962-9B40-4DFF-9458-1830C7DD7F5D),
      helpstring("IEProtocolHandler Class"),
      hidden
    ]
    coclass IEProtocolHandler {
        [default] interface IUnknown;
    };

    [
      uuid(F278D870-7AF7-4957-96EE-E6AC72D0B109),
      helpstring("SMS message."),
      helpcontext(0x0000004f)
    ]
    coclass SmsMessage {
        [default] interface ISmsMessage;
    };

    [
      uuid(1BCA4635-F1FC-44C8-B829-48229AEB32E3),
      helpstring("SMS message collection."),
      helpcontext(0x00000050)
    ]
    coclass SmsMessageCollection {
        [default] interface ISmsMessageCollection;
    };

    [
      uuid(5792FC7D-5E1D-4F1A-BD4F-A7A50F92BC6E),
      helpstring("SMS chunk."),
      helpcontext(0x00000053)
    ]
    coclass SmsChunk {
        [default] interface ISmsChunk;
    };

    [
      uuid(CC461FC3-C9BE-41FB-8E47-E0115CBC01CC),
      helpstring("SMS chunk collection."),
      helpcontext(0x00000054)
    ]
    coclass SmsChunkCollection {
        [default] interface ISmsChunkCollection;
    };

    [
      uuid(61F8FAF0-82D0-407C-AE97-31441483AE40),
      helpstring("SMS target."),
      helpcontext(0x00000051)
    ]
    coclass SmsTarget {
        [default] interface ISmsTarget;
    };

    [
      uuid(6AC51E9C-7947-4B46-A978-0AD601C4EFC9),
      helpstring("SMS target collection."),
      helpcontext(0x00000052)
    ]
    coclass SmsTargetCollection {
        [default] interface ISmsTargetCollection;
    };

    [
      uuid(3F06DCD2-3A04-463D-A08B-1FFED02C4D4C),
      helpstring("Plugin menu item class."),
      helpcontext(0x0000005b)
    ]
    coclass PluginMenuItem {
        [default] interface IPluginMenuItem;
    };

    [
      uuid(9D073235-D787-497D-8D1F-929559F1C621),
      helpstring("Plugin event class."),
      helpcontext(0x0000005c)
    ]
    coclass PluginEvent {
        [default] interface IPluginEvent;
    };
};

*/
#endif //SKYPEAPIWAPPER_HEADER__


