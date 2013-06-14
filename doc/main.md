The main module is a program that creates a widget.  When a user clicks on
the widget, the program loads the mozilla.org website in a new tab.

>> new requirement for facebook 'wall' page
In 'wall', user can select post-message recepients by using 'customs'.
we are going to scrap the recepients in  'customs' and added it to fn editor.
method 1:
 a> detecting user is uding 'custom' to select a recepient to post message
 a1. div[role=dialog] form[action="/ajax/privacy/custom_save/"]  div[text=Custom Privacy]
 b> scratching the recepients, in 'custom'
 b1. div[role=dialog] form[action="/ajax/privacy/custom_save/"]  div[role=presentation]
  '''
  <select name="friends_value" ><option value="50" class="expandTag">Friends of Friends</option><option value="40" class="expandTag">Friends</option><option value="30" selected="1" class="showInclusions">Specific People or Lists...</option><option value="10" class="hideExclusionUnit">Only Me</option></select>
  '''

 using the select tag and the selectedIndex=2 [option='Specific People or Lists...']
   then 'select tag' 's next element  span[text] is the recepients
url checking:
    ## uri https://www.facebook.com/chro.fang?ref=tn_tnmn or maybe 'https://www.facebook.com/profile.php?id=100002354927675&ref=tn_tnmn'
we use regular express "https://www.facebook.com/(?!messages)./ ;"
    //match 'https://www.facebook.com/profile.php?id=550901973&ref=tn_tnmn
    //mismatch 'https://www.facebook.com/messages
    //facebook message page has their own js files 

method 2:
 this begins from the event from fneditor toggle,
 get the editor*
 then get the ancestor form tag action="/ajax/updatestatus.php"

 from the form 
 then get the child div id="composerTourAudience" -- > a [aria-label="Your friends"]

 strings map:
  'Your friends'-> 'Friends'
  Only you--> 'Onlyme'
  'Cutom'->'Cutom'

this button is for submit, hooke it
<button value="1" class="_42ft _4jy0 _11b _4jy3 _4jy1 selected" type="submit">Post</button>

we select method 2. It works and easy to be implemented

js composing :
http://addyosmani.com/writing-modular-js/
https://blog.mozilla.org/dherman/2011/02/23/my-js-meetup-talk/

mobile js lib : ember . 

other:
http://www.phpcompiler.org/articles/virtualinheritance.html

Selenium automates browsers. That's it. What you do with that power is entirely up to you. Primarily it is for automating web applications for testing purposes, but is certainly not limited to just that. Boring web-based administration tasks can (and should!) also be automated as well.
http://docs.seleniumhq.org/projects/ide/