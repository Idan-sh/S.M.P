# S.M.P
a Social-Media-Platform made in C++ language.

## 1) About
SMP app allows members to socialize and comunicate with their friends.   
Each member is defined by a unique name, and his date of birth.   
   
The member will be promped with a menu of options, and will choose the desired option to use by entering its option number. 
   
The database of `members` / `fan pages` will be read from a database file each time the app will run. All of the changes will be saved into this file after the exit option is chosen.    
   
> In case the database file does not exist (as when running the program the first time), it will be created with a set of pre-made members and fan pages made for testing.
<br />

## 2) Member Options
### 2.1) Add a New Member
Creates a new member and adds him to the database.   
Checks for validity of the date of birth.   

Each member consists of:
* `name` - a unique name of the member, defined in the fan page class
* `memberArray` and `statusArray` as defined in the fan page class
* `date of birth` - a date struct containing: year (4 digits), month (1 or 2 digits), day (1 or 2 digits)
* `fpArray` - array of pointers to the fan pages that the member is a fan of
* `feedArray` - array of statuses posted in the member's feed
* `memberNamesOfStatuses` - array of the member names for each status posted in the member's feed, with corresponding indexes between them

> The `Member` class inherits from the `fanPage` class.
<br />

### 2.2) Add a New Fan Page
Creates a new fan page and edds it to the database.
a fan page represents a business or a shared interest.   

Each fan page consists of:
* `name` - a unique name of the fan page
* `memberArray` - an array of members that are fans of this fan page
* `statusArray`- an array of statuses that were posted in the fan page
<br />   

### 2.3) Add a Status to a Member / Fan Page
Creates a new status and adds it to a member **OR** to a fan page's `statusArray`.   
Checks for input errors, and lets the user choose if the status will be a   
`Status (text)` / `ImageStatus` / `VideoStatus`.   

> The user will get an option to choose between the options.

Each status has:
* `content` - a description of the status image/video or some text
* `timeOfUpload` - a string representing when the status was uploaded.

> The `ImageStatus` and `VideoStatus` classes inherits from the `Status` class.
<br />

### 2.4) Show All Statuses of a Member / Fan Page
Prints to the screen all the statuses in the `statusArray` of a member / fan page.

> The user will get an option to choose between the options.

The format will be:
```
   On {time of upload}
   {content}
   {the type of the status - Status/ImageStatus/VideoStatus}
```  
<br />

For example for a `ImageStatus` uploaded by user1:
```
   On May 21 17:25:54 2012
   hello im user1
   This status is in black and white.
```
<br />  
 
### 2.5) Show 10 of the Most Recent Statuses of a Member / Fan Page
Prints the 10 most recent status posts of a member **OR** a fan page.   

> The user will get an option to choose between the options.
<br />  

### 2.6) Connect Two Members - Add a Friendship
**Adds** a **friendship** between two **members**.   
Searches the members in the `members` array of `SMP`, adds each one to the other's `memberArray`.   
<br />  

### 2.7) Disconnect Two Members - Remove a Friendship
**Remove** a **friendship** that exists between two **members**.
Searches for the members in the `members` array of `SMP`
* If both found - tries to remove each member from the other's `memberArray`
* If they are not friend - an exception will be thrown
<br />  

### 2.8) Add a Member as a Fan of a Fan Page
Add an existing member as a fan to an existing fan page.
Searches for the member in the `members` array of `SMP`
Seaches for the fan page in the `fanPages` array of `SMP`
* If both found - tries to add the member to the fan page's `memberArray`, and tries to add the fan page to the member's `fpArray`
* If at least one was not found - an exception will be thrown
<br />  

### 2.9) Remove a Member (a Fan) of a Fan Page
Remove a fan to an existing fan page.
Searches for the member in the `members` array of `SMP`
Seaches for the fan page in the `fanPages` array of `SMP`
* If both found - tries to remove the member to the fan page's `memberArray`, and tries to remove the fan page to the member's `fpArray`
* If at least one was not found - an exception will be thrown
<br />  

### 2.10) Show All Members and Fan Pages in the system
Print all existing members in the `members` array of `SMP`,   
Print all existing fan pages in the `fanPages` array of `SMP`.   
<br />  

### 2.11) Show All Fans / Friends of a Fan Page / Member
Print all members that were set as fans of a fan page **OR**   
Print all the members that were set as friends of a member.  

> The user will get an option to choose between the options.
<br />  

### 2.12) Finish and Quit
This option will close the program and save all the `members`, `fan pages` and all of the changes made since starting the program into a `database` file.   

> Overwrites the database file if one already exists
