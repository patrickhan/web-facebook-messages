

#pragma message("for Gecko version 2 later on")

#pragma warning(disable:4005)
#include "mozilla-config.h"
#pragma warning(default : 4005)
#include "mozilla/ModuleUtils.h"
#include "nsIClassInfoImpl.h"

#include "FNIMToggleEngine.h"



NS_DEFINE_NAMED_CID(FN_IM_TOGGLE_ENGINE_CID);

NS_GENERIC_FACTORY_CONSTRUCTOR(FNIMToggleEngine)

static const mozilla::Module::CIDEntry kFNIMToggleEngineCIDs[] = {
 // XPCONNECT_CIDENTRIES
  { &kFN_IM_TOGGLE_ENGINE_CID,      true,  NULL, FNIMToggleEngineConstructor }, 
  { NULL }
};

static const mozilla::Module::ContractIDEntry kFNIMToggleEngineContracts[] = {
 //XPCONNECT_CONTRACTS
  { FN_IM_TOGGLE_ENGINE_CONTRACTID,       &kFN_IM_TOGGLE_ENGINE_CID     },
  { NULL }
};
 
static const mozilla::Module::CategoryEntry kSFNIMToggleEngineCategories[] = {
    { "profile-after-change",  FN_IM_TOGGLE_ENGINE_CLASSNAME, FN_IM_TOGGLE_ENGINE_CONTRACTID },
    { NULL }
};
 

static const mozilla::Module kFNIMToggleEngineModule = {
  mozilla::Module::kVersion,
  kFNIMToggleEngineCIDs,
  kFNIMToggleEngineContracts,
  kSFNIMToggleEngineCategories,
  NULL,
  NULL,
  NULL
};
  
NSMODULE_DEFN(nsFNIMToggleEngineModule) = &kFNIMToggleEngineModule;