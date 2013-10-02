// This is an active module of the fn web page features
/*
 * Adds web page logic for fn integration
 * Copyright (c) 2013
 */


var foroutlook 	= require("./foroutlookmail.js");
var foryahoo 	= require("./foryahoomail.js");
var forgmail 	= require("./forgmail.js");
var forfacebook = require("./forfacebook.js");
var testcode 	= require("./testcode.js");
var fortwitter 	= require("./fortwitter.js");

function log(msg)
{
	console.error(msg);
}

exports.main = function() {
   
    //onstart logic
    testcode.attach();
    forfacebook.attach();
    forgmail.attach();
    foroutlook.attach();
    foryahoo.attach();
    fortwitter.attach();
	
	log("exports.main ======");
};

exports.onUnload = function (reason) 
{
   
    testcode.detach();
    forfacebook.detach();
    forgmail.detach();
    foroutlook.detach();
    foryahoo.detach();
    fortwitter.detach();
    log("exports.onUnload");
};


