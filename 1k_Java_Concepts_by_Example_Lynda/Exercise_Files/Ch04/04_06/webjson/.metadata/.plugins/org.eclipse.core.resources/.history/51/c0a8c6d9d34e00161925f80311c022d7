package com.example.webjson;

public class StackConnection {
	private static final String BASE_URL = "https://api.stackexchange.com/2.2/search?";
	private static final String PARAM_SITE = "site=";
	private static final String PARAM_PAGE_SIZE = "&pagesize=";
	private static final String PARAM_ORDER = "&order=";
	private static final String PARAM_SORT = "&sort";
	private static final String PARAM_TAG = "&tagged=";
	private static final String PARAM_FILTER = "&filter=";
	private static final String PARAM_SEARCH_TERM = "&intitle=";
	
	private String site = "stackoverflow";
	private int pageSize = 5;
	private SortOrder sortOrder = SortOrder.ASCENDING;
	private SortBy sortBy = SortBy.RELEVANCE;
	private String tag = "java";
	private String searchTerm = "";
	
	public enum SortOrder {
		ASCENDING   ("asc"), 
		DESCENDING  ("desc");
		
		private final String key;
		SortOrder(String key) { this.key = key; }
		
		public String toString() { return key; }
	}
	
	
	public enum SortBy {
		RELEVANCE	("relevance"), 
		VOTES		("votes"), 
		CREATION	("creation"), 
		ACTIVITY	("activity");
		
		private final String key;
		SortBy(String key) { this.key = key; }
		
		public String toString() { return key; }
	}
	
}
