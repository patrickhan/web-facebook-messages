/*
 * there are some test code for development
 *
 */
 
"use strict";


var fn_web_mocktest_ns  = undefined === fn_web_mocktest_ns ? {}: fn_web_mocktest_ns;

(function(ns)
{
    function insert_data_ToBox(tobox)
    {
        return  $('<span>fntest003@gmail.com</sapen>').hide().appendTo($(tobox) );
    }
    
    //export
    ns.insert_data_ToBox = insert_data_ToBox;
    
})(fn_web_mocktest_ns)