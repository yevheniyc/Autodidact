package com.example.webjson;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.zip.GZIPInputStream;

import com.example.webjson.data.ResultData;
import com.example.webjson.parsers.IJsonParser;
import com.example.webjson.parsers.JacksonJsonParser;
import com.example.webjson.parsers.JsonpJsonParser;

/**
 * The StackQuery class allows you to send a custom query string to StackOverflow 
 * and obtain a list of {@link ResultData} objects back, with information about 
 * Java questions that match your query. 
 * <p>
 * You can customize the order of your results with the {@link #setSortBy(SortBy)} 
 * and {@link #setSortOrder(SortOrder)} methods.
 * 
 * @author julian
 * @since 1.0
 */
public class StackQuery {
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
	
	private ParserType parserType = ParserType.JSONP;
	
	
	/**
	 * Specifies the library that will be used for parsing the 
	 * JSON results of the query
	 * 
	 * @author julian
	 * @since 1.0
	 */
	public enum ParserType { 
		/** use the javax.json (JSON-P) parser */
		JSONP, 
		/** use the Jackson parser */
		JACKSON 
	}
	
	
	/**
	 * Specifies the sort order of your {@link StackQuery} results
	 * 
	 * @author julian
	 * @since 1.0
	 */
	public enum SortOrder {
		/** results should be returned in ascending order */
		ASCENDING   ("asc"), 
		/** results should be returned in descending order */
		DESCENDING  ("desc");
		
		private final String key;
		SortOrder(String key) { this.key = key; }
		
		/** returns the key assigned to this SortOrder */
		public String toString() { return key; }
	}
	
	
	/**
	 * Specifies the method by which your {@link StackQuery} results 
	 * are sorted: by relevance, by creation date, etc.
	 * 
	 * @author julian
	 * @since 1.0
	 */
	public enum SortBy {
		/** results should be sorted by relevance */
		RELEVANCE	("relevance"), 
		/** results should be sorted by number of votes */
		VOTES		("votes"), 
		/** results should be sorted by creation date */
		CREATION	("creation"), 
		/** results should be sorted by last activity date */
		ACTIVITY	("activity");
		
		private final String key;
		SortBy(String key) { this.key = key; }
		
		/** returns the key assigned to this SortOrder */
		public String toString() { return key; }
	}
	
	
	
	/**
	 * Executes a query based on the search term, sort order, and sort method 
	 * that were given, and returns a List of {@link ResultData} objects 
	 * containing the results of the query.
	 * 
	 * @return  a List of {@link ResultData} objects
	 * @throws IOException  if there was an error connecting to the server or 
	 *                      parsing the data that was returned
	 */
	public List<ResultData> execute() throws IOException {
		// create a URL
		URL url = buildUrl();
		
		// connect to a server
		URLConnection connection = url.openConnection();
		InputStream in = connection.getInputStream();
		if ("gzip".equals(connection.getContentEncoding())) {
			in = new GZIPInputStream(in);
		}
		
		List<ResultData> result;
		IJsonParser parser = createParser();
		result = parser.parseJson(in);
		in.close();
		
		// get information back
		// return data
		return result;
	}
	
	
	
	
	
	
	
	/**
	 * Creates an {@link IJsonParser} based on the parser type 
	 * specified by {@link #setParserType(ParserType)}. 
	 * Default parser is {@link JsonpJsonParser}.
	 * 
	 * @return  an {@link IJsonParser}
	 */
	public IJsonParser createParser() {
		IJsonParser parser;
		switch (parserType) {
			case JACKSON: 
				parser = new JacksonJsonParser();
				break;
			case JSONP: 
			default:
				parser = new JsonpJsonParser();
		}
		return parser;
	}
	
		
	
	
	
	
	
	
	
	/**
	 * Builds and returns a URL based on the search term, sort order, 
	 * and sort method that were given.
	 * 
	 * @return  a URL that can be used for REST operations
	 * @throws MalformedURLException  if the URL is invalid based on the 
	 *                                parameters we have provided
	 */
	public URL buildUrl() throws MalformedURLException {
		StringBuilder urlString = new StringBuilder();
		urlString.append(BASE_URL);
		urlString.append(PARAM_SITE).append(this.site);
		urlString.append(PARAM_PAGE_SIZE).append(this.pageSize);
		urlString.append(PARAM_ORDER).append(this.sortOrder);
		urlString.append(PARAM_SORT).append(this.sortBy);
		urlString.append(PARAM_TAG).append(this.tag);
		urlString.append(PARAM_SEARCH_TERM).append(this.searchTerm);
		
		URL url = new URL(urlString.toString());
		
		try {
			URI uri = new URI(url.getProtocol(), url.getHost(), url.getPath(), 
					url.getQuery(), null);
			url = uri.toURL();
		} catch (URISyntaxException e) {
			throw new MalformedURLException(e.getMessage());
		}
		
		return url;
	}
	
	
	
	
	

	


	/**
	 * Indicates the sort order for the results that are returned
	 * 
	 * @param sortOrder  the sort order to use
	 */
	public void setSortOrder(SortOrder sortOrder) {
		this.sortOrder = sortOrder;
	}

	
	/**
	 * Indicates the sort method for the results that are returned
	 * 
	 * @param sortBy  the sort method to use
	 */
	public void setSortBy(SortBy sortBy) {
		this.sortBy = sortBy;
	}

	
	/**
	 * Indicates the search term we are using to search for results. 
	 * This can be a single word or multiple words separated by 
	 * spaces.
	 * 
	 * @param searchTerm  the search term to use
	 */
	public void setSearchTerm(String searchTerm) {
		this.searchTerm = searchTerm;
	}

		
	/**
	 * Indicates which {@link IJsonParser} we should use to process 
	 * the results of the search. Don't set this unless you know what 
	 * you are doing!
	 * 
	 * @param parserType  the {@link IJsonParser} to use
	 * @see JacksonJsonParser
	 * @see JsonpJsonParser
	 */
	public void setParserType(ParserType parserType) {
		this.parserType = parserType;
	}
	
}
