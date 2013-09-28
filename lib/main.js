// This is an active module of the fn web page features
/*
 * Adds web page logic for fn integration
 * Copyright (c) 2013
 */




var forgmail = require("./forgmail.js");
var forfacebook = require("./forfacebook.js");
var testcode = require("./testcode.js");

exports.main = function() {
   
    //onstart logic
    testcode.attach();
    forfacebook.attach();
    forgmail.attach();
	
	console.error("exports.main ======");
};

exports.onUnload = function (reason) 
{
   
    testcode.detach();
    forfacebook.detach();
    forgmail.detach();
    console.error("exports.onUnload");
};


