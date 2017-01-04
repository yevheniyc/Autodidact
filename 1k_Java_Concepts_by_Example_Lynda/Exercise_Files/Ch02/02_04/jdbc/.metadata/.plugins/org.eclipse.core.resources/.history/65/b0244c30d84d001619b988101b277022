package com.example.jdbc;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.Date;
import java.util.Properties;
import java.util.Random;

public class DatabaseTest {
	private static final String DB_PASSWORD = "dbPassword";
	private static final String DB_USER = "dbUser";
	private static final String DB_URL = "dbUrl";
	private static final String DB_PROPERTIES = "db.properties";
	private String dbUrl;
	private String dbUser;
	private String dbPassword;
	private Properties globalProps;
	
	
	public void writeProperties() throws IOException {
		Properties prop = new Properties();
		prop.setProperty(DB_URL, "localhost");
		prop.setProperty(DB_USER, "username");
		prop.setProperty(DB_PASSWORD, "password");

		try (OutputStream out = new FileOutputStream("project.properties")) {
			prop.store(out, "Database Properties File");
		}
	}



	public void readProperties() throws IOException {
		try (InputStream in = new FileInputStream(DB_PROPERTIES)) {
			globalProps = new Properties();
			globalProps.load(in);
		}
	}
	
	
	
	public Connection connectToDatabase() throws SQLException {
		Properties connectionProps = new Properties();
		connectionProps.put("user", "jsmith");
		connectionProps.put("password", "pwd");
		
		// registerDriver is optional for some drivers, required for others
		DriverManager.registerDriver(new org.apache.derby.jdbc.EmbeddedDriver());
		Connection conn = DriverManager.getConnection(
				"jdbc:derby:test.db;create=true",
				connectionProps);
		return conn;
	}
	
	
	
	
	
	public Connection connectUsingDataSource() throws SQLException {
		EmbeddedDataSource ds = new org.apache.derby.jdbc.EmbeddedDataSource();
		ds.setDatabaseName("test.db;create=true");
		ds.setUser( globalProps.getProperty(DB_USER) );
		ds.setPassword( globalProps.getProperty(DB_PASSWORD) );
		Connection conn = ds.getConnection();
		
		// paranoid mode for connection pools: make sure autoCommit is on
		conn.setAutoCommit(true);
		return conn;
	}
	
	
	
	
	
	
	public void createDatabaseTable(Connection conn) throws SQLException {
		Statement s = conn.createStatement();
		s.executeUpdate("CREATE TABLE testdata(" + 
				"num INT, " + 
				"dt TIMESTAMP, " + 
				"txt VARCHAR(256))");
		s.close();
	}
	
	
	
	
	
	
	
	
	
	
	public void addData(Connection conn) throws SQLException {
		String sql = "INSERT INTO testdata VALUES (?,?,?)";
		try (PreparedStatement ps = conn.prepareStatement(sql)) {
			Random rnd = new Random();
			long timenow = System.currentTimeMillis();
			
			for (int i = 0; i < 10; i++) {
				int num = rnd.nextInt(1000);
				long time = timenow - (num ^ 2);
				
				ps.setInt(1, num);
				ps.setTimestamp(2, new Timestamp(time));
				ps.setString(3, time + ": " + (new Date(time)));
				ps.executeUpdate();
			}
		}
	}
	
	
	public void readData(Connection conn) throws SQLException {
		try (Statement query = conn.createStatement()) {
			String sql = "SELECT * FROM testdata";
			query.setFetchSize(100);
			
			try (ResultSet rs = query.executeQuery(sql)) {
				while (!rs.isClosed() && rs.next()) {
					int num = rs.getInt(1);
					Timestamp dt = rs.getTimestamp(2);
					String txt = rs.getString(3);
					System.out.println(num + "; " + dt + "; " + txt);
				}
			}
			
		}
	}
	
	
	
	public void closeDatabaseConnection(Connection conn) throws SQLException {
		conn.close();
		
		try {
			// we do this because we are accessing a database file directly; 
			// if we were connecting to a database server we would never do this
			DriverManager.getConnection("jdbc:derby:test.db;shutdown=true");
		} catch (SQLException sqe) {
			if ((sqe.getErrorCode() == 45000) || (sqe.getErrorCode() == 50000)) {
				// Ignore these error codes; Derby ALWAYS throws an error when 
				// you shutdown a database: 08006 (45000) if it's a single 
				// database, XJ015 (50000) if you close all databases
			} else {
				throw sqe;
			}
		}
	}
	
	
	
	public void testConnection() throws IOException, SQLException {
		readProperties();
		Connection conn = connectToDatabase();
		
		try {
			createDatabaseTable(conn);
			addData(conn);
		} catch (SQLException e) {
			System.out.println("Database table already exists");
		}
		
		readData(conn);
		closeDatabaseConnection(conn);
	}
	
}


