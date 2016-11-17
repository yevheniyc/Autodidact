####Java Concepts by Example - Lynda.com
Intermediate level tutorial for Java with practical examples.

#####Using Eclipse w/ Exercise Files
If you open a folder as an Eclipse workspace and you don't see any projects listed in Package Explorer, you will need to import the project files into Eclipse manually. 
- Choose the Eclipse menu option File > Import from the workspace.
- From the Import dialog, choose the option General > Existing Projects into Workspace.
- Choose a root directory corresponding to the project you want to open.
    For example, 
        c:\java\Ch01\01_02\filesearch\FileSearch.
-  Click the Finish button to import the project files.

If you have errors corresponding to "Java build path problems" in your project, you probably need to change your Eclipse JRE settings.

- Choose the Eclipse menu option Project > Properties.
- Click the "Java Build Path" entry.
- Go to the Libraries tab.
- Select JRE System Library [JavaSE-1.8] and click the Edit button.
- Choose Workplace default JRE and click the Finish button, followed by the OK button.

If you are using a version of Java older than 1.8, you might also have to adjust the Compiler compliance levels from the menu item Project > Properties > Java Compiler, so they match the version of Java you are using.

***

To start a project from scratch:
- From Eclipse interface click on the **New -> Java -> Java Project**
- Right-click on the **src -> New -> Class** 

#####Command-Line App for Searching Text Files
When creating Java Class, include the following configs:
- Source folder: FileSearch/src
- Package: com.example.filesearch
- Name: FileSearchApp
- Also check: public static void main - as it is a stand-along command-line app

```java
// When you run a Java class of the command-line, the Java Runtime looks
// for a main method in your class and it runs the code inside that method
// - this is very similar to C/C++
// The String[] args parameter is an array of strings representing all the
// command-line options that were passed throught the app at Runtime.

package com.example.filesearch;

public class FileSearchApp {
    public static void main(Stringp[] args) {

    }
}
```
To run the command-line program follow the steps:

```bash
cd ~/src        # the root of the application
javac com/example/filesearch/FileSearchApp.java  # compile the class
ls com/example/filesearch/FileSearchApp.class    # compiled files
java com.example.filesearch.FileSearchApp one two three # exacute *.class
# Output:
    # one
    # two
    # three
```
