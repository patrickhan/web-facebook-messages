var ContactModule = {};
(function(NP){
    try
    {
        Components.utils.import("resource://webpagesvrmoudleLoader/webpgjs/dataOper.jsm");      
    }
    catch(err)
    {
        alert_log__("dataDBOper error: " + err);        
    }
    
    NP.getOwnerIdByEmail = function(Email, callback)
    {
        var sqltemplate = "SELECT ownerid FROM securekey, Email WHERE  \
                           Email.contactId = securekey.id AND Email.emailAddress=:email AND (NOT securekey.ownerid is null) \
                           AND length(trim(securekey.ownerid)) > 0"
        var params=[{email:Email}]; 
        dataDBOper_Asyn_V2(sqltemplate, params, callback);        
    };    

    NP.getPublicKeyByOwnerId = function(ownerid, callback)
    {
        ownerid = ownerid.toString();
        var sqltemplate = "SELECT publickey FROM securekey WHERE \
                           securekey.ownerid=:ownerid";
        var params=[{ownerid:ownerid}];
        dataDBOper_Asyn_V2(sqltemplate, params, callback);        
    };

    NP.getAllEmailsExceptMe = function(callback)
    {
        var sqltemplate = "SELECT Email.emailAddress as email FROM securekey, Email WHERE \
                           securekey.id = Email.contactId AND \
                           securekey.ownerid!=:ownerid AND (NOT securekey.ownerid is null) \
                           AND length(trim(securekey.ownerid)) > 0";
        var myidStr = ECHelperNS.getOwnerId().toString();        
        var params=[{ownerid:myidStr}];
        dataDBOper_Asyn_V2(sqltemplate, params, callback);        
    };    

    NP.getAllContactsBasicAndEmailXMe = function (callback)
    {
        var sqltemplate = "select a.[firstName], a.[lastName], b.[emailAddress] as email, c.[image] from BasicInfo a, Email b, securekey c where a.[basicInfoId]=c.[basicInfoId] and b.[contactId]=c.[id] and c.[isme]!=1;"
        var params=[];
        dataDBOper_Asyn_V2(sqltemplate, params, callback);
        
    };    

    NP.getAllEmails = function(callback)
    {
        var sqltemplate = "SELECT Email.emailAddress as email FROM securekey, Email WHERE \
                           securekey.id = Email.contactId AND (NOT securekey.ownerid is null)";
        var params=[];
        dataDBOper_Asyn_V2(sqltemplate, params, callback);        
    };

    NP.getfacebook_names = function(names , callback)
    {
        //Select imAccount as name from IMGroup where IMGroup.groupName in ("Closed Friends","Friends", "Patrick") union
        //select tb.name from (
        //select "Closed Friends" as name union
        //select "Friends" as name union
        //select "Patrick" as name) as tb WHERE not tb.name in (select groupName from IMGroup); 
        // names ["Closed Friends","Friends", "Patrick"] -- >("Closed Friends","Friends", "Patrick")
        var group_names_plaintext = " (\"" + names.join("\",\"")  +  " \")" ;
        var sql_groupName_collection = "Select imAccount as name from IMGroup where IMGroup.groupName in " + group_names_plaintext;
        var sql_facebookName_collection = ""; 
        if(names.length > 0)
        {
            var sub_select_union_pre = "select tb.name from ( ";
            var sub_select_union_after = ") as tb WHERE not tb.name in (select groupName from IMGroup); ";
            var sub_select_union = "";
            for (var index =  0; index < names.length; index++) {
                var aname  = names[index];
                if (aname.length > 0) {
                    if(sub_select_union.length == 0)
                    {
                        
                        sub_select_union +="select \"" + aname +  "\" as name";
                    
                    }
                    else{
                        sub_select_union +=" union " + "select \"" + aname +  "\" as name";
                    }
                }
            }
            
            if (sub_select_union.length > 0) {
                sql_facebookName_collection  = sub_select_union_pre +  sub_select_union +  sub_select_union_after
            }
        }
        var sql_all = sql_groupName_collection;
        if(sql_facebookName_collection.length > 0)
        {
            sql_all +=  " union " + sql_facebookName_collection;
        }
        //log(sql_all)
        var sqltemplate = sql_all;
        var params=[];
        dataDBOper_Asyn_V2(sqltemplate, params, callback, false);        
    };
}(ContactModule))
