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

Eclipse Preferences:
- Go to Window -> Properties -> General -> Appearance:
    - Colors and Themes - choose your theme
    - Choose Dark appearance
    - Golors and Fonts -> Git -> Change color for uncommited changes (this will fix the dark-on-dark bug in the Project Explorer)
- Go to Window -> Properties -> Java -> Syntax Highliting -> Comments -> light grey

Another gnarly setup to add transperancy to Eclipse or any other window in Ubuntu (i.e. VS Code, Sublime, etc.):
1. Download/Install **CompizConfig**
```bash
$ sudo apt-get install compizconfig-settings-manager compiz-plugins-extra
```
2. Open and enable **Opacity**
- Open CompizConfig in Ubuntu
- Scroll to Accessibility
- Check Opacity, Brightness and Saturation option

3. Press **Alt** + **+/-** to configure opacity on any window!

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
$ cd ~/src        # the root of the application
$ javac com/example/filesearch/FileSearchApp.java  # compile the class
$ ls com/example/filesearch/FileSearchApp.class    # compiled files
$ java com.example.filesearch.FileSearchApp one two three # exacute *.class
# Output:
    # one
    # two
    # three
```

1. Typical Java classes will have getter and setter methods for private variables that need to be accessed outside the class. This class will be self-contained, but we will add getter/setter methods anyway.
- Right-click anywhere in Eclipse
- Choose Source -> Generate getters/setters
- Select All - to generate getters/setters for all private variables
- Set the insertion point after main
2. In general, the main method should have very little code and do very little work - bootstrap the launch of the app
3. Let's also create placeholders for the following three methods:
- walkDirectory(String path) - that will walk the specified directory
- searchFile(File file) - search for a particular file
- addFileToZip (File file) - add the found file to the zip folder

```java
package com.example.filesearch;

import java.io.File;

public class FileSearchApp {
	String path;
	String regex;
	String zipFileName;
	
	public static void main(String[] args) {
		// 1. Create an instance of this class
		FileSearchApp app = new FileSearchApp();
		// 2. Process command-line arguments, ensuring
		// that no more than 3 is provided, else ignore
		switch(Math.min(args.length, 3)) {
		case 0: // in the case we get 0 args
			System.out.println("USAGE: FileSearchApp path [regex] [zipfile]");
			return;
		case 3: app.setZipFileName(args[2]); // 3rd arg is the zip file name
		case 2: app.setRegex(args[1]);       // 2nd is the regex
		case 1: app.setPath(args[0]); 		 // 1st is the path
		}
		
		// a placeholder for the walkDirectory method
		try {
			app.walkDirectory(app.getPath());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void walkDirectory(String path) {
		System.out.println("walkDirectory: " + path);
		searchFile(null);
		addFileToZip(null);
	}
	
	public void searchFile(File file) {
		System.out.println("searchFile: " + file);
	}
	
	public void addFileToZip(File file) {
		System.out.println("addFileToZip: " + file);
	}
	
	public String getPath() {
		return path;
	}
	
	public void setPath(String path) {
		this.path = path;
	}
	
	public String getRegex() {
		return regex;
	}
	
	public void setRegex(String regex) {
		this.regex = regex;
	}
	
	public String getZipFileName() {
		return zipFileName;
	}
	
	public void setZipFileName(String zipFileName) {
		this.zipFileName = zipFileName;
	}

}
```

The next step is to create a **walkDirectory** method. Below are three different implementations depending on the Java version used (Java6 == File Class; Java7 == NIO Classes;Java8 == Streams).

1. For Java6, use File(path) to specify directory and .listFiles() to list all the files
```java
public void walkDirectoryJava6(String path) throws IOException {
    File dir = new File(path);
    File[] files = dir.listFiles(); // list all of the files in the current dir
    // loop through the files, if another dir -> recursive, otherwise, process the file
    for (File file : files) {
        if (file.isDirectory()) {
            walkDirectoryJava6(file.getAbsolutePath());
        } else {
            processFile(file);
        }
    }
}
```
A few interesting point for the Java6 implementation:
-We're passing a string instead of a file as a parameter because we got a string as a command line argument telling us which directory to walk. It's better to encapsulate all the file handling logic in this method instead of forcing the main method to figure out how to convert a string into a file. This will also make it easier to substitute this method with the other methods we're going to write for Java 7 and Java 8, as we'll see in a minute.
- The list files method lists both files and subdirectories that exist under a given directory. It doesn't list all the files in the subdirectories for us, so we need to process the subdirectories manually.
- When we do encounter a subdirectory reference we can make a recursive call to check the subdirectories as we do here. 
- When we encounter a file reference we pass it to the process file method, and this method will do something to the file. It will be responsible for searching the file and possibly adding it to the zip file. We keep it separate so it's easily reusable, and so each method in this class has a distinct responsibility. The Walk Directory method walks directories. The Process File method processes files.

2. For Java7, use the new NIO files class that has built-in functionality for copying files, processing files, etc.
```java
public void walkDirectoryJava7(String path) throws IOException {
    Files.walkFileTree(Paths.get(path), new SimpleFileVisitor<Path>() {
        @Override
        public FileVisitResult visitFile(Path file, BasicFileAttributes attrs)
                throws IOException {
            processFile(file.toFile());
            return FileVisitResult.CONTINUE;
        }
    });
}
```
A few interesting points:
- The ```Files.walkFileTree``` method has a checked exception, so we need to either use a try-catch block inside the method, or throw an IOException in the method signature. It's almost always better to throw the exception in this case, and the calling method (the one that gave us the path in the first place) can deal with it. We throw the exception here in the method signature.
- ```Files.walkFileTree``` parameters:
    - The first parameter of the walkFileTree method takes a path object, not a file. The Path class was new in Java 7. Since we are getting the original path as a string when this method is called, we can easily convert the string to a path using the call to ```Paths.get```. 
    - The second parameter fo the walkFileTree method is a File Visitor object (new in Java7). We can either create a brand new implementation of FileVisotr, or implement SimpleFileVisitor and override whatever methods we need. In this case, the only method that is important is the visitFile method. It is called once for each file in the directory being walked. So every time we visit a file, we can call processFile, and then we need to return FileVisitResult.CONTINUE. 
- Finally, note that the walkFileTree method automatically processes all files in the directory and all subdirectories by default.This is good if you want to process subdirectories like we wanna do here, because there's less code to write. However, if you do not want to process subdirectories, watch out.

3. For Java8, everything becomes easier by using Streams and Lambda functions.
- **Streams**: one byte at a time. Good for binary data.
- **Readers/Writers**: one character at a time. Good for text data.
- **Anything Buffered**: many bytes/characters at a time. Good almost all the time.
```java
// 3. Using Streams and Lambda functions
public void walkDirectoryJava8(String path) throws IOException {
    Files.walk(Paths.get(path))
        .forEach(f -> processFile(f.toFile()));
}
```
- We can shorten everything to a single line of code like this. Java 8 introduced the Files.walk method, which returns a stream. We can then operate on each item in the stream with the forEach method.

**Next** step is to focus on the ```processFile()``` method

1. Structure processFile method:

```java
public void processFile(File file) throws FileNotFoundException {
    // this try/catch will ensure that if one of the files is broken,
    // the code will continue processing the rest of the files
    try {
        // search the file for regex
        if (searchFile(file)) {
            // if regex found, add to zip
            addFileToZip(file); 	
        }
    } catch (IOException|UncheckedIOException e) {
        // e.printStackTrace();
        System.out.println("Error processing file: " +
                file + ": " + e);
    }
        
}
```
2. Open and Search the file
- Java 6 - FileScanner
- Java 7 - Files class
- Java 8 using streams


FileScanner:

```java
// searchFile for Java 5 & 6
public boolean searchFileJava6(File file) throws FileNotFoundException {
    boolean found = false;
    Scanner scanner = new Scanner(file, "UTF-8");
    while (scanner.hasNextLine()) {
        found = searchText(scanner.nextLine());
        if (found) { break; }
    }
    scanner.close();
    return found;
}
```
- The steps involved in this method are first, you create a scanner object.
- The scanner reads a given file using UTF-8 encoding. Obviously there's no guarantee that the file actually is UTF-8 encoded, but there's no guarantee it's even a text file. UTF-8 is just our best guess here. 
- Next, using the scanner, we read each line of the file. 
- Then, we send each line to a searchText method to see if it has the regular expression we're searching for. We can break out of the loop the first time we find a match. 
- Lastly, close the scanner and return the boolean result of our search.
- There's also a FileNotFoundException we need to worry about here. That's because it's a checked exception that might be thrown when we create the scanner. We have a choice to catch it or throw it. That's a tough decision because on the one hand this is a self-contained process and we know where the file came from, so we can probably safely ignore the exception. On the other hand, it's usually a bad idea to discard exceptions because we think we don't need them. So I'm gonna go ahead and throw the exception here, because this is something that other implementations of searchFile will need to deal with too. And that way we can handle the exception at a higher level of processing.

Files Class:

```java
// searchFile for Java 7
public boolean searchFileJava7(File file) throws IOException {
    List<String> lines = Files.readAllLines(file.toPath(),
            StandardCharsets.UTF_8);
    for (String line : lines) {
        if (searchText(line)) {
            return true;
        }
    }
    return false;
}
```
- Java 7 gave us a convenience method in the files class called ```readAllLines```.
- This reads the entire file into memory as a list of strings, so it's really not a good technique for large files.
- The readAllFiles method can throw an IOException, so we let the caller deal with it

Streams:

```java

```
-  With Java 8 we can use streams, and this gives us the option to perform the entire operation using a single line. A few interesting points about this technique: 
    - First the Files.lines method actually reads the file using UTF-8 by default, so we can remove the StandardCharsets parameter if we want to. I left it there just to make the code match the other methods a little better and to show that you can change the character set if you want. After that, the anyMatch method in the Java streams class is what's referred to as a **short-circuiting** method. In other words, it will stop and return true automatically the first time any of the elements of the stream return true for the given condition. Before we had to manually break out of a loop when we found a true condition. Methods like anyMatch have this logic built in.
    - The Files.lines method throws an IOException, just like the previous two methods did, so, just like the methods we wrote before, we'll have to throw an IOException and let the caller of the method deal with that problem.

Stack trace so far:
```bash
# first we encounter . and a few other dirs
Error processing file: .: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com/example: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com/example/filesearch: java.io.UncheckedIOException: java.io.IOException: Is a directory
# now we get binary files with MalformedInputException
Error processing file: ./com/example/filesearch/FileSearchApp$1.class: java.io.UncheckedIOException: java.nio.charset.MalformedInputException: Input length = 1
Error processing file: ./com/example/filesearch/FileSearchApp.class: java.io.UncheckedIOException: java.nio.charset.MalformedInputException: Input length = 1
package com.example.filesearch;
# here is the java file ready to be zipped
addFileToZip: ./com/example/filesearch/FileSearchApp.java
```

**Next** step is to implement searchText() method
1. Simplified version: finding a substring in a string

```java
private boolean searchText(String text) {
    // below code searches for substrings in a text, and not regex
    // because the regex arg is option, let's code defensively
    return (this.getRegex() == null) ? true :
        text.toLowerCase().contains(this.getRegex().toLowerCase());
}
```

2. Using regular expressions:
- a language for describing a string by describing a text search with certain qualities:
    - win.ini => ^win\.ini$  - start and end with the string
    - w*.*    => ^w.*\.      - start with a ```w``` + ```.```(any number of times ```*```), followed by a ```.```, and anything else (absence of the ```?```)
    - ???.*   => ^[\w]{3}\.  - start with any 3 alphanumeric, followed by a ```.```, and anything else (absence of the ```?```)

```java
private boolean searchText(String text) {
    // below code searches for regex in the text
    // because the regex arg is optional, let's code defensively
    return (this.getRegex() == null) ? true :
        text.matches(this.getRegex());
}
```
-  A regular expression pattern is always compiled before it's applied to a string for the purpose of matching text. It takes very little time to compile a pattern but it does take a finite amount of work. So if you're gonna use the same regular expression over and over again in your code, it's best to pre-compile it first. In Java there's a pattern class we can use for just this purpose. Using the pattern class, we can pre-complile our regular expression once and then use it as many times as we want to in our program without incurring the penalty of compiling it over and over. The easiest way to do this here is to compile the expression at the same time we get it from the command line. So let's add a pattern variable to the class and then compile the pattern in the set regex method.

```java
import java.utils.regex;
//...
Pattern pattern;
//...
public void setRegex(String regex) {
    this.regex = regex;
    // precompiling regex, if used a lot
    this.pattern = Pattern.compile(regex);
}
//...
private boolean searchText(String text) {
    // below code searches for regex in the text
    // because the regex arg is option, let's code defensively
    return (this.getRegex() == null) ? true :
        // we are suing the matches method of the matcher class
        this.pattern.matcher(text).matches();
}
```

Note: something to be awere of: 
- the **matches** methods for both regex and precompiled regex look for the entire text mathing
- the **find** method looks for regex anywhere in the string

```java
Pattern.compile("x").matcher("example").matches() = false
Pattern.compile("x").matcher("exaple").find() = true

// analyze the followings
"example".matches("x");                             // False
Pattern.compile("x").matcher("example").matches();  // False
Pattern.compile("^x$").matcher("example").find();   // False

Pattern.compile("x").matcher("example").find();     // True
```

**Next** zip-up the matching files that we found (the files that contained regex) with addFileToZip()
- Arrays:
    - some limitations of arrays: to extend arrays once created requires creating a copy of the initial array
- Collections:
    - Sort
    - Search
    - Convert to streams (Java 8)
```java
// String arrays
String[] letters = new String[3];
letters[0] = "a";
letters[1] = "b";
letters[2] = "c";

or 

String[] letters = new String[] {"a", "b", "c"};
```

- use array list collection for automatically resizing listss
```java
// Array List - resizing automatically

// the only objects put in the list will be strings: Java Generics:
    // tell the compiler to catch errors as you go in case you added
    // the wrong type of object into collection
List<String> letters = new ArrayList<String>();

// or

// we can use a Non-generic approach, telling Java compiler to use any
// object in the list
List letters = new ArrayList();

letters.add("a");
letters.add("b");
letters.add("c");

letters.remove("b");
```

- we can also cast collect's array list items back into array, if needed:
```java
// Generics - the list is strongly types
List<String> letters = new ArrayList<String>();
String[] letterArray = letters.toArray(new String[0]);

// No Generics - the list is not strongly typed
List letters = new ArrayList();
String[] letterArray = (String[])letters.toArray(new String[0]);
```

- or we can convert generic arrays into Collections
```java
String[] letters = new String[] {"a", "b", "c"};
List<String> letterList = Arrays.asList(letters);
```

**Next** creating a ZIP file:
1. Create a ZipOutputStream
2. Add files to the ZipOutputStream
3. Close the ZipOutputStream

- Add all matched files to array list zipFiles

```java
public void addFileToZip(File file) {
    if (getZipFileName() != null) {
        zipFiles.add(file);
    }
}
```

- Zip all of the files at once

```java
// utility method for getting relative filenames
public String getRelativeFilename(File file, File baseDir) {
    String fileName = file.getAbsolutePath().substring(
            baseDir.getAbsolutePath().length());
    // IMPORTANT: the ZipEntry file name must us "/", not "\".
    fileName = fileName.replace("\\", "/");
    // fileName cannot start with /
    while (fileName.startsWith("/")) {
        fileName = fileName.substring(1);
    }
    return fileName;
}
```

```java
// Java 6
public void zipFilesJava6() throws IOException {
    ZipOutputStream out = null;
    // if error happens within the block, the ZipOutputStream will be
    // properly closed!
    try {
        out = new ZipOutputStream(new FileOutputStream(getZipFileName()));
        File baseDir = new File(getPath());
        
        for (File file : zipFiles) {
            // fileName must be a relative path, not an absolute one.
            String fileName = getRelativeFilename(file, baseDir);
            // adding zip entry to the output stream
            ZipEntry zipEntry = new ZipEntry(fileName);
            zipEntry.setTime(file.lastModified());
            out.putNextEntry(zipEntry);
            // write all of the bytes in the file to the ZipOutputStream,
            // using buffer as an intermediary
            int bufferSize = 2048;
            byte[] buffer = new byte[bufferSize];
            int len = 0;
            BufferedInputStream in = new BufferedInputStream(
                    new FileInputStream(file), bufferSize);
            while((len = in.read(buffer, 0, bufferSize)) != -1) {
                out.write(buffer, 0, len);
            }
            in.close(); 		// close the buffer
            out.closeEntry();	// close the output stream
        }
    } finally {
        out.close();
    }
}
```

```java
// Java 7
public void zipFilesJava7() throws IOException {
    // Java 7 - try with resources block, which allows us to skip finally block
    try (ZipOutputStream out =
            new ZipOutputStream(new FileOutputStream(getZipFileName()))) {
        File baseDir = new File(getPath());
        
        for (File file : zipFiles) {
            // fileName must be a relative path, not an absolute one.
            String fileName = getRelativeFilename(file, baseDir);
            
            ZipEntry zipEntry = new ZipEntry(fileName);
            zipEntry.setTime(file.lastModified());
            out.putNextEntry(zipEntry);
            // no need for buffers as in Java 6 example
            Files.copy(file.toPath(), out);
            
            out.closeEntry();
        }
    }
}
```

```bash
# all files that contain work "file"
$ java com.example.filesearch.FileSearchApp ./ .*file.* ../test.zip
Error processing file: .: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com/example: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com/example/filesearch: java.io.UncheckedIOException: java.io.IOException: Is a directory
Error processing file: ./com/example/filesearch/FileSearchApp$1.class: java.io.UncheckedIOException: java.nio.charset.MalformedInputException: Input length = 1
Error processing file: ./com/example/filesearch/FileSearchApp.class: java.io.UncheckedIOException: java.nio.charset.MalformedInputException: Input length = 1

$ unzip test.zip -d test
$ ls test
# will contain the file(s) and the directory tree
```

######Final result of section 1
- look for all files that contains a regex and add them to the zip file

```java
package com.example.filesearch;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class FileSearchApp {
	String path;
	String regex;
	String zipFileName;
	Pattern pattern; // precompiling regex
	List<File> zipFiles = new ArrayList<File>();
	
	public static void main(String[] args) {
		// 1. Create an instance of this class
		FileSearchApp app = new FileSearchApp();
		// 2. Process command-line arguments, ensuring
		// that no more than 3 is provided, else ignore
		switch(Math.min(args.length, 3)) {
		case 0: // in the case we get 0 args
			System.out.println("USAGE: FileSearchApp path [regex] [zipfile]");
			return;
		case 3: app.setZipFileName(args[2]); // 3rd arg is the zip file name
		case 2: app.setRegex(args[1]);       // 2nd is the regex
		case 1: app.setPath(args[0]); 		 // 1st is the path
		}
		
		// a placeholder for the walkDirectory method
		try {
			app.walkDirectory(app.getPath());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void walkDirectory(String path) throws IOException {
		walkDirectoryJava8(path);
		zipFilesJava7();
	}
	
	// depending on the Java version, different ways of walking are shown:
	// 1. Using .listFiles()
	public void walkDirectoryJava6(String path) throws IOException {
		File dir = new File(path);
		File[] files = dir.listFiles(); // list all of the files in the current dir
		// loop through the files, if another dir -> recursive, otherwise, process
		// the file
		for (File file : files) {
			if (file.isDirectory()) {
				walkDirectoryJava6(file.getAbsolutePath());
			} else {
				processFile(file);
			}
		}
	}
	
	// 2. Using Files.walkFileTree
	public void walkDirectoryJava7(String path) throws IOException {
		Files.walkFileTree(Paths.get(path), new SimpleFileVisitor<Path>() {
			@Override
			public FileVisitResult visitFile(Path file, BasicFileAttributes attrs)
					throws IOException {
				processFile(file.toFile());
				return FileVisitResult.CONTINUE;
			}
		});
	}
	
	// 3. Using Streams and Lambda functions
	public void walkDirectoryJava8(String path) throws IOException {
		Files.walk(Paths.get(path))
			.forEach(f -> {
				try {
					processFile(f.toFile());
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				}
			});
	}
	
	public void processFile(File file) throws FileNotFoundException {
		// this try/catch will ensure that if one of the files is broken,
	    // the code will continue processing the rest of the files
		try {
			// search the file for regex
			if (searchFile(file)) {
				// if regex found, add to zip
				addFileToZip(file); 	
			}
		} catch (IOException|UncheckedIOException e) {
			// e.printStackTrace();
			System.out.println("Error processing file: " +
					file + ": " + e);
		}
		 
	}
	
	// an overall example of searchFile()
	public boolean searchFile(File file) throws IOException {
		return searchFileJava8(file);
	}
	
	// searchFile for Java 5 & 6
	public boolean searchFileJava6(File file) throws FileNotFoundException {
		boolean found = false;
		Scanner scanner = new Scanner(file, "UTF-8");
		while (scanner.hasNextLine()) {
			found = searchText(scanner.nextLine());
			if (found) { break; }
		}
		scanner.close();
		return found;
	}
	
	// searchFile for Java 7
	public boolean searchFileJava7(File file) throws IOException {
		List<String> lines = Files.readAllLines(file.toPath(),
				StandardCharsets.UTF_8);
		for (String line : lines) {
			if (searchText(line)) {
				return true;
			}
		}
		return false;
	}
	
	// searchFile for Java 8
	public boolean searchFileJava8(File file) throws IOException {
		return Files.lines(file.toPath())
				// returns true if any elements of the streaming condition return true
				.anyMatch(t -> searchText(t));
	}
	
	private boolean searchText(String text) {
		// below code searches for regex in the text
		// because the regex arg is option, let's code defensively
		return (this.getRegex() == null) ? true :
			// we are suing the matches method of the matcher class
			this.pattern.matcher(text).matches();
	}

	public void addFileToZip(File file) {
		if (getZipFileName() != null) {
			zipFiles.add(file);
		}
	}
	
	public String getRelativeFilename(File file, File baseDir) {
		String fileName = file.getAbsolutePath().substring(
				baseDir.getAbsolutePath().length());
		// IMPORTANT: the ZipEntry file name must us "/", not "\".
		fileName = fileName.replace("\\", "/");
		// fileName cannot start with /
		while (fileName.startsWith("/")) {
			fileName = fileName.substring(1);
		}
		return fileName;
	}
	
	public void zipFilesJava6() throws IOException {
	    ZipOutputStream out = null;
	    // if error happens within the block, the ZipOutputStream will be
	    // properly closed!
	    try {
	        out = new ZipOutputStream(new FileOutputStream(getZipFileName()));
	        File baseDir = new File(getPath());
	        
	        for (File file : zipFiles) {
	        	// fileName must be a relative path, not an absolute one.
	        	String fileName = getRelativeFilename(file, baseDir);
	        	// adding zip entry to the output stream
	        	ZipEntry zipEntry = new ZipEntry(fileName);
	        	zipEntry.setTime(file.lastModified());
	        	out.putNextEntry(zipEntry);
	        	// write all of the bytes in the file to the ZipOutputStream,
	        	// using buffer as an intermediary
	        	int bufferSize = 2048;
	        	byte[] buffer = new byte[bufferSize];
	        	int len = 0;
	        	BufferedInputStream in = new BufferedInputStream(
	        			new FileInputStream(file), bufferSize);
	        	while((len = in.read(buffer, 0, bufferSize)) != -1) {
	        		out.write(buffer, 0, len);
	        	}
	        	in.close(); 		// close the buffer
	        	out.closeEntry();	// close the output stream
	        }
	    } finally {
	    	out.close();
	    }
	}
	
	public void zipFilesJava7() throws IOException {
		// Java 7 - try with resources block, which allows us to skip finally block
		try (ZipOutputStream out =
				new ZipOutputStream(new FileOutputStream(getZipFileName()))) {
			File baseDir = new File(getPath());
			
			for (File file : zipFiles) {
				// fileName must be a relative path, not an absolute one.
				String fileName = getRelativeFilename(file, baseDir);
				
				ZipEntry zipEntry = new ZipEntry(fileName);
				zipEntry.setTime(file.lastModified());
				out.putNextEntry(zipEntry);
				// no need for buffers as in Java 6 example
				Files.copy(file.toPath(), out);
				
				out.closeEntry();
			}
		}
	}
	
	public String getPath() {
		return path;
	}
	
	public void setPath(String path) {
		this.path = path;
	}
	
	public String getRegex() {
		return regex;
	}
	
	public void setRegex(String regex) {
		this.regex = regex;
		// precompiling regex, if used a lot
		this.pattern = Pattern.compile(regex);
	}
	
	public String getZipFileName() {
		return zipFileName;
	}
	
	public void setZipFileName(String zipFileName) {
		this.zipFileName = zipFileName;
	}
}
```

***

#####Create a Command-Line Application That Accesses a Database
Goals for this section:
- Build an app that connects to a relational database, and read some data from it. 
- Touch on Java cryptography as it relates to encrypting and decrypting strings
- Java logging of information and errors
- How to package your finished application in a jar file

Our sample app will be a commandline application, similar to the example in the previous section. However, in the previous section, we received runtime options as commandline parameters. In this example, the runtime options will be stored in a properties file. A standard Java properties file is structured very much like a Windows INI file.

Properties File Structure
```text
# Watch out for spacing at the end!
dbUser=jsmith
dbPassword=pwd
dbUrl = jdbc:derby:test.db;create=true
```

Write out properties file programmatically:

```java
package com.example.jdbc;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Properties;

public class DatabaseTest {
	// Generate Properties file programmatically
	private String dbUrl;
	private String dbUser;
	private String dbPassword;
	
	public void writeProperties() throws IOException {
		Properties prop = new Properties();
		prop.setProperty("dbUrl", "localhost");
		prop.setProperty("dbUser", "username");
		prop.setProperty("dbPassword", "password");
		
		try (OutputStream out = new FileOutputStream("project.properties")) {
			prop.store(out, "Database Properties File");
		}
	}

}
```

Properties files main contains:
- database connections specifics
- colors and Fonts
- often used for localicatin purposes (i.e. containing a button' text in various languages)

In the readProperties method, we will use **public constant** variables for the db properties, so that we can reuse these properties within or outside the class. If the variable names inside the properties files aren't clear, use globals to de-obfuscate the meaning:

```java
String WINDOW_TITLE = "wndttl";
```

DatabaseTest.java - modified:

```java
public class DatabaseTest {
	private static final String DB_PROPERTIES = "db.properties";
	private static final String DB_USER = "dbUser";
	private static final String DB_URL = "dbUrl";
	private static final String DB_PASSWORD = "dbPassword";
	private Properties globalProps;
	
	public void writeProperties() throws IOException {
		// Generate Properties file programmatically
		Properties prop = new Properties();
		prop.setProperty(DB_URL, "localhost");
		prop.setProperty(DB_USER, "username");
		// be aware!
		prop.setProperty(DB_PASSWORD, "password");
		
		try (OutputStream out = new FileOutputStream("project.properties")) {
			prop.store(out, "Database Properties File");
		}
	}
	
	public void readProperties() throws IOException {
		// get the db.properties file and read it and all its vars/properties
        // as an input stream
		try (InputStream in = new FileInputStream(DB_PROPERTIES)) {
			globalProps = new Properties();
			globalProps.load(in);
		}
	}
}
```

**Next** Accessing Relational Databases using Java
- Java Database Connectivity API - used for database Connectivity
- Each database type has its own drive, so you need a specify JDBC driver
- JDBC comes with the Apache Derby driver on Windows
- JDBC drivers for MySQL, Oracle needs to be installed separately
- The installation basically means - downlaod the jdbc driver .jar file and make sure it is on the local classpath.
- At the end of this lecture, we will learn how to add the jdbc .jar file into my .jar file when distributing the application. This will give us a way to distribute our application with the jdbc driver .jar file already included.
- Some vendors require their Licence file (which is also packaged into a separate .jar file) to be distributed with the jdbc driver .jar file

Below is the usual workflow for database connection:
1. Make sure you have a JDBC driver on your classpath
2. Create or register an instance of the JDBC driver with the driver manager
3. Connect to the database
4. Use SQL querries to put data in or get data out
5. Close database connection

For the following example we will be using the Apache Derby driver
