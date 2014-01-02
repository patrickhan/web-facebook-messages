var {Cc, Ci, Cm, Cr, Cu} = require("chrome");
var addon_pref = require("sdk/simple-prefs");
Cu.import("resource://gre/modules/Services.jsm");
const gPref = Services.prefs;
const pref_AllDevPrefs_On = "AllDevPrefs_On";
const this_addon_prefName_perfix = "extensions.openDevPrefs@woodyITService."

function log(msg)
{
 console.log(msg)
}
exports.main = function() {  
	for (var prefName in addon_pref.prefs)
	{
		if( pref_AllDevPrefs_On === perfName)
		{
			continue;
		}	
		gPref.setBoolPref(prefName , addon_pref.prefs[prefName] );
		
		log(prefName + " = " + addon_pref.prefs[prefName])
	}
};

exports.onUnload = function (reason) {
};

function turn_all_dev_prefs(on)
{
	for (var prefName in addon_pref.prefs)
	{
		if( pref_AllDevPrefs_On === prefName)
		{
			continue;
		}
		addon_pref.prefs[prefName]  = on;

		
		log(prefName + " = " + addon_pref.prefs[prefName])
	}
}
///addon preference callback
function onAddon_PrefChange(prefName) {
	log(prefName + " 0=0 " + addon_pref.prefs[prefName])
	if(pref_AllDevPrefs_On === prefName )
	{
		turn_all_dev_prefs(addon_pref.prefs[prefName]);
		return;
	}
	gPref.setBoolPref(prefName , addon_pref.prefs[prefName] );
	
	log(prefName + " = " + addon_pref.prefs[prefName])
}
// `""` listens to all changes in the extension's branch
addon_pref.on("", onAddon_PrefChange);
/*
addon_pref.on("AllDevPrefs_On", onAddon_PrefChange);
addon_pref.on("javascript.options.showInConsole", onAddon_PrefChange);
addon_pref.on("nglayout.debug.disable_xul_cache", onAddon_PrefChange);
addon_pref.on("browser.dom.window.dump.enabled" , onAddon_PrefChange);
addon_pref.on("javascript.options.strict"		, onAddon_PrefChange);
addon_pref.on("devtools.chrome.enabled"			, onAddon_PrefChange);
addon_pref.on("devtools.debugger.remote-enabled", onAddon_PrefChange);
addon_pref.on("extensions.logging.enabled"		, onAddon_PrefChange);
addon_pref.on("nglayout.debug.disable_xul_fastload", onAddon_PrefChange);
addon_pref.on("dom.report_all_js_exceptions"	, onAddon_PrefChange);
addon_pref.on("devtools.errorconsole.deprecation_warnings", onAddon_PrefChange);
*/