/*
 *
 * I want use it to show test
 *
 */
"use strict";

var facebook_test_ns = (undefined === facebook_test_ns)? {}: facebook_test_ns;

(function (ns) {
   
   var float_panel = null;
   function create_float_div() {
     var div = $('<div></div>').appendTo(document.body).addClass("fb-test-float fb-test-bottom-right fb-test-size")
     return div;
   }
   function add_css(css_href )
   {
        var cssNode = $("<link/>", {
            rel: "stylesheet",
            type: "text/css",
            href: css_href  //"/styles/yourcss.css"
        }).appendTo("head");
        return cssNode;
   }
   
   function change_css(css_href_str , cssNode$)
   {
        cssNode$.attr( {href : "\""+css_href_str+"\"" });
        return cssNode$;
   }
   
   function create_test_panel()
   {
        //alert(999)
        if (float_panel) {
            return float_panel;
        }
        
        float_panel = create_float_div();
        //add_css("test-panel.css");
        return float_panel;
   }
   
   facebook_test_ns.create_test_panel =  create_test_panel;
   
})(facebook_test_ns);



