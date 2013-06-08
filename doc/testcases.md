testcase 1 :  Do invitation in facebook:
    1.1 user1 : Start and login fnclient in a computers , the fnclient is installed and 1 user is logged in.
    1.2 Do 'contact import' action for 'facebook'
    1.3 check the 'facebook contacts' is added into fn contacts
    1.4 select a 'facebook contact', let us say it is 'John Smith'
    1.5 Open facebook in fnbrowser and login facebook (uer:fntest001@gmail.com/pwd:123Yp456)
    1.6 Open the message page in facebook "https://www.facebook.com/messages/new"
        1.6.1 In the 'to box' of the 'facebook new message' page, input 'John Smith'
        1.6.2 In the 'editor box', select the fn toggle options(CIA|Encryption) --- should not has 'extra to box'
        1.6.3 Submit the message by clicking the 'send box' -- fn hackjacket message should show in the editor with invitation footer
    1.7 After the message has been submitted, the URL is changed like this 'https://www.facebook.com/messages/550901973'
        check the fn hackjacket message with invitation footer is well presented by fn invitation ui.
    
    2.1 user2 : Start and login fnclient in a computers , the fnclient is installed and 1 user is logged in.
    2.2 Open facebook in fnbrowser and login facebook (uer:fntest002@gmail.com/pwd:123Yp456)(It is John Smith)
    2.3 Navigate to the message sent in step 1.6
    2.3 Click the 'View Content' in fn invitation ui.
    2.4 open fn client contact book, check the fn user user1 is added in the ' fn client contact book'
    
    3.1 user1 : log out the fnclient(or re start computer)
    3.2 login fnclient again ,
    3.3 open fn client contact book, check the fn user user2 is added in the ' fn client contact book'
    
    
    