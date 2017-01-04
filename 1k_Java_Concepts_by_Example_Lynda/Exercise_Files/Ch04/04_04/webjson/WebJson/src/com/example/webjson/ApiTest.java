package com.example.webjson;

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
}
