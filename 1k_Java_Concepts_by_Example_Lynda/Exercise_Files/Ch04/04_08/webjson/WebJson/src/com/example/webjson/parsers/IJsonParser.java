package com.example.webjson.parsers;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import com.example.webjson.data.ResultData;

public interface IJsonParser {

	List<ResultData> parseJson(InputStream in) throws IOException;

}