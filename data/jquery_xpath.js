

(function($) {
    $.xpath = function(exp, ctxt) {
        var item, coll = [],
            result = document.evaluate(exp, ctxt || document, null, 5, null);

        while (item = result.iterateNext())
            coll.push(item);

        return $(coll);
    }
})(jQuery);


// onScreen jQuery plugin v0.2.1
// (c) 2011 Ben Pickles
//
// http://benpickles.github.com/onScreen
//
// Released under MIT license.
/* sample
$(function() {
  setInterval(function() {
    $("h2")                             // get all <h2>s
      .css("background-color", "")      // reset their background colours
      .filter(":onScreen")              // get only <h2>s on screen
        .css("background-color", "red") // give them a red background
  }, 1000)                              // repeat every second
})

*/
;(function($) {
  $.expr[":"].onScreen = function(elem) {
    var $window = $(window)
    var viewport_top = $window.scrollTop()
    var viewport_height = $window.height()
    var viewport_bottom = viewport_top + viewport_height
    var $elem = $(elem)
    var top = $elem.offset().top
    var height = $elem.height()
    var bottom = top + height

    return (top >= viewport_top && top < viewport_bottom) ||
           (bottom > viewport_top && bottom <= viewport_bottom) ||
           (height > viewport_height && top <= viewport_top && bottom >= viewport_bottom)
  }
})(jQuery);



;(function($) {
	$.expr[':'].contentIs = function(el, idx, meta) {
		
		var str = $(el).text();
		/*var n=str.indexOf(meta[3]);
		if(n !=-1)
		{
			fn_web_common_ns.log( "jQuery   contentIs :"+ $(el).text() + "\n meta[3] " +  meta[3]  );
		}*/
		
	    return str === meta[3];
	}
})(jQuery);





