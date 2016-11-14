####Java Concepts by Example - Lynda.com
Intermediate level tutorial for Java Overview

#####Using Eclipse w/ Exercise Files
README for Learn Java Concepts by Example with Julian Robichaux

The Eclipse workspace files for the individual chapters for this course are now zipped together 
in the Exercise Files folder. Files for chapter 1 are in the Ch01.zip file, files for 
chapter 2 are in the Ch02.zip file, etc.

On Windows, you might get "Path too long" errors if you use native Windows functionality 
to unzip the files in a parent folder that already has a long file path. If this happens, your 
two options are as follows:

1) Use a parent folder with a shorter name (like c:\java).
2) Use an unzip program that can properly handle long file names, like 7zip (http://www.7-zip.org). 

If you open a folder as an Eclipse workspace and you don't see any projects listed in Package 
Explorer, you will need to import the project files into Eclipse manually. 

1) Choose the Eclipse menu option File > Import from the workspace.
2) From the Import dialog, choose the option General > Existing Projects into Workspace.
3) Choose a root directory corresponding to the project you want to open. For example, 
   c:\java\Ch01\01_02\filesearch\FileSearch.
4) Click the Finish button to import the project files.

If you have errors corresponding to "Java build path problems" in your project, you probably 
need to change your Eclipse JRE settings.

1) Choose the Eclipse menu option Project > Properties.
2) Click the "Java Build Path" entry.
3) Go to the Libraries tab.
4) Select JRE System Library [JavaSE-1.8] and click the Edit button.
5) Choose Workplace default JRE and click the Finish button, followed by the OK button.

If you are using a version of Java older than 1.8, you might also have to adjust the Compiler 
compliance levels from the menu item Project > Properties > Java Compiler, so they match the 
version of Java you are using.