package com.example.webjson;

import java.util.List;

import com.example.webjson.StackQuery.SortBy;
import com.example.webjson.StackQuery.SortOrder;

public class ApiTest {

	public void test1() {
		StackQuery query = new StackQuery();
		
		query.setSearchTerm("Hello World");
		query.setSortBy(SortBy.RELEVANCE);
		query.setSortOrder(SortOrder.ASCENDING);
		
		Object result = query.execute();
	}
	
	
	
	
	
	
	
	
	
	
	
	public boolean isResultValid(List<QueryResultBean> results) {
		if (results == null) { return false; }
		
		for (QueryResultBean result : results) {
			if (result.getTitle() == null) { return false; }
			if (result.getCreation_date() == 0) { return false; }
			if (result.getLink() == null) { return false; }
			
			OwnerData owner = result.getOwner();
			if (owner == null) { return false; }
			if (owner.getDisplay_name() == null) { return false; }
			if (owner.getUser_id() == 0) { return false; }
		}
		
		return true;
	}
}
