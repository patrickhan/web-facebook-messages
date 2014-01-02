Purpose:
Openning this addons preference ui to click the checkbox to on/off the preference needed to debug the firefox addons

refer:
https://developer.mozilla.org/en-US/Add-ons/Setting_up_extension_development_environment
http://stealthpuppy.com/prepare-mozilla-firefox-for-enterprise-deployment-and-virtualization/


Development preferences

There is a set of development preferences that, when enabled, allows you to view more information about application activity, thus making debugging easier. However,  these preferences can degrade performance, so you may want to use a separate development profile when you enable these preferences.

Accessing Firefox development preferences

To change preference settings in Firefox or SeaMonkey, type about:config in the Location Bar. You can also use the Extension Developer's Extension, which provides a menu interface for Firefox settings. Alternatively, install the Developer Profile to set the preferences listed below and skip the rest of this section.

Accessing Thunderbird development preferences

To change preference settings in Thunderbird, open the "Preferences" (Unix) or "Options" (Windows) interface. On the "Advanced" page, select the "General" tab then click the "Config Editor" button.

Recommended development preferences

Not all preferences are defined by default, and are therefore not listed by default. You will have to create new (boolean) entries for them. For more information about Mozilla preferences, refer to the mozillaZine article on "about:config".

javascript.options.showInConsole = true. Logs errors in chrome files to the Error Console.
nglayout.debug.disable_xul_cache = true. Disables the XUL cache so that changes to windows and dialogs do not require a restart. This assumes you're using directories rather than JARs. Changes to XUL overlays will still require reloading of the document overlaid.
browser.dom.window.dump.enabled = true. Enables the use of the dump() statement to print to the standard console. See window.dump for more info. You can use nsIConsoleService instead of dump() from a privileged script.
javascript.options.strict		= true. Enables strict JavaScript warnings in the Error Console. Note that since many people have this setting turned off when developing, you will see lots of warnings for problems with their code in addition to warnings for your own extension. You can filter those with Console2.
devtools.chrome.enabled			= true. This enables to run JavaScript code snippets in the chrome context of the Scratchpad from the Tools menu. Don't forget to switch from content to browser as context.
devtools.debugger.remote-enabled = true. This adds a "Browser Debugger" entry to the "Web Developer" submenu of the "Tools" menu.  The Browser Debugger can be used to debug the JavaScript code of extensions.
extensions.logging.enabled			= true. This will send more detailed information about installation and update problems to the Error Console. (Note that the extension manager automatically restarts the application at startup sometimes, which may mean you won't have time to see the messages logged before the automatic restart happens. To see them, prevent the automatic restart by setting the environment NO_EM_RESTART to 1 before starting the application.)
nglayout.debug.disable_xul_fastload = true. For Gecko 2.0+ (Firefox 4.0+). See this bug for more information. Although the bug has been closed, it is believed that this pref is still relevant.
You might also want to set 
dom.report_all_js_exceptions = true. See Exception logging in JavaScript for details.
devtools.errorconsole.deprecation_warnings. Detect deprecated code use.


Preventing the first launch extension selector
Starting in Firefox 8, on the first launch of a new version of Firefox, it presents user interface letting users select which third party add-ons to keep. This lets them weed out add-ons that were installed without their knowledge, or that are no longer needed.

However, this interface can be disruptive when debugging add-ons. You can avoid this by setting the preference 
extensions.autoDisableScopes=14

how about these:

lockPref("toolkit.telemetry.prompted", true);
lockPref("browser.rights.override", true);
lockPref("browser.startup.homepage_override.mstone", "ignore");

The profile migrator can also be disabled, by adding the following lines to the override.ini file in the firefox root directory:
[XRE]
EnableProfileMigrator=false