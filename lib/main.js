// This is an active module of the fn web page features
/*
 * Adds web page logic for fn integration
 * Copyright (c) 2013
 */		 

var foroutlook 	= require("./foroutlookmail.js");
var foryahoo 	= require("./foryahoomail.js");
var forgmail 	= require("./forgmail.js");
var forgoogleplus= require("./forgoogle+.js");
var forfacebook = require("./forfacebook.js");
var fortwitter 	= require("./fortwitter.js");
var forfnboxhelper 	= require("./fnbox_guard.js");
//persistToggleOption logic
var persistToggleOption = require("./forpersistToggleOption.js");
//test code
var testcode 	= require("./testcode.js");

function log(msg)
{
	console.error(msg);
}

exports.main = function() {
   
    //onstart logic
    testcode.attach();
    forfacebook.attach();
    forgmail.attach();
    forgoogleplus.attach();
    foroutlook.attach();
    foryahoo.attach();
    fortwitter.attach();
    
    persistToggleOption.attach();
    forfnboxhelper.attach();
        
	log("exports.main ======");
};

exports.onUnload = function (reason) 
{
   
    testcode.detach();
    forfacebook.detach();
    forgmail.detach();
    forgoogleplus.detach();
    foroutlook.detach();
    foryahoo.detach();
    fortwitter.detach();
    
    persistToggleOption.detach();
    forfnboxhelper.detach(); 
    log("exports.onUnload");
};


