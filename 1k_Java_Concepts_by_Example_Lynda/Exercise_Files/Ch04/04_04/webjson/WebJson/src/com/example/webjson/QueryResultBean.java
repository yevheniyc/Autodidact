package com.example.webjson;

public class QueryResultBean {
	private String[] tags;
	
	
	private Owner owner;
	public static class Owner {
		private int reputation;
		private int user_id;
		private String user_type;
		private int accept_rate;
		private String profile_image;
		private String display_name;
		private String link;
	}
	private boolean is_answered;
	private int view_count;
	private int accepted_answer_id;
	private int answer_count;
	private int score;
	private long last_activity_date;
	private long creation_date;
	private long last_edit_date;
	private long question_id;
	private String link;
	private String title;
	
	
}
