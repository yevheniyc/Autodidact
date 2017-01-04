package com.example.webjson;

public class OwnerData {
	private int reputation;
	private int user_id;
	private String user_type;
	private int accept_rate;
	private String profile_image;
	private String display_name;
	private String link;

	public OwnerData() {
	}

	public int getReputation() {
		return reputation;
	}

	public void setReputation(int reputation) {
		this.reputation = reputation;
	}

	public int getUser_id() {
		return user_id;
	}

	public void setUser_id(int user_id) {
		this.user_id = user_id;
	}

	public String getUser_type() {
		return user_type;
	}

	public void setUser_type(String user_type) {
		this.user_type = user_type;
	}

	public int getAccept_rate() {
		return accept_rate;
	}

	public void setAccept_rate(int accept_rate) {
		this.accept_rate = accept_rate;
	}

	public String getProfile_image() {
		return profile_image;
	}

	public void setProfile_image(String profile_image) {
		this.profile_image = profile_image;
	}

	public String getDisplay_name() {
		return display_name;
	}

	public void setDisplay_name(String display_name) {
		this.display_name = display_name;
	}

	public String getLink() {
		return link;
	}

	public void setLink(String link) {
		this.link = link;
	}
}