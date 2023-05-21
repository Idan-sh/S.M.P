# S.M.P
a Social-Media-Platform made in C++ language.

## 1. About
SMP app allows members to socialize and comunicate with their friends.   
Each member is defined by a unique name, and his date of birth.   
The member will be promped with a menu of options, and will choose the desired option to use by entering its option number. 
   
The database of `members` / `fan pages` will be read from a database file each time the app will run. All of the changes will be saved into this file after the exit option is chosen.   
<br />

## 2. Member Options
### 2.1 Add a New Member
Creates a new member and adds him to the database.   

Each member consists of:
* `name` - a unique name of the member, defined in the fan page class
* `memberArray` and `statusArray` as defined in the fan page class
* `date of birth` - a date struct containing: year (4 digits), month (1 or 2 digits), day (1 or 2 digits)
* `fpArray` - array of pointers to the fan pages that the member is a fan of
* `feedArray` - array of statuses posted in the member's feed
* `memberNamesOfStatuses` - array of the member names for each status posted in the member's feed, with corresponding indexes between them

> The member class inherits from the fan page class.
<br />

### 2.2 Add a New Fan Page
Creates a new fan page and edds it to the database.
a fan page represents a business or a shared interest.   

Each fan page consists of:
* `name` - a unique name of the fan page
* `memberArray` - an array of members that are fans of this fan page
* `statusArray`- an array of statuses that were posted in the fan page
<br />   

### 2.3 Add a Status to a Member / Fan Page
bla bla bla.  
<br />

### 2.4 Show All Statuses of a Member / Fan Page
bla bla bla.  
<br />  
 
### 2.5 Show 10 of the Most Recent Statuses of a Member / Fan Page
bla bla bla.  
<br />  

### 2.6 Connect Two Members - Add a Friendship
bla bla bla.  
<br />  

### 2.7 Disconnect Two Members - Remove a Friendship
bla bla bla.  
<br />  

### 2.8 Add a Member as a Fan of a Fan Page
bla bla bla.  
<br />  

### 2.9 Remove a Member as a Fan of a Fan Page
bla bla bla.  
<br />  

### 2.10 Show All Members and Fan Pages in the system
bla bla bla.  
<br />  

### 2.11 Show All Fans / Friends of a Fan Page / Member
bla bla bla.  
<br />  

### 2.12 Finish and Quit
This option will close the menu and save all the `members` / `fan pages` added and all of the changes made since starting the app into a database file.   
