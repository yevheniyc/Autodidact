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
