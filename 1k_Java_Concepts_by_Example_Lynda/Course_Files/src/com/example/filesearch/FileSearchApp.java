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
