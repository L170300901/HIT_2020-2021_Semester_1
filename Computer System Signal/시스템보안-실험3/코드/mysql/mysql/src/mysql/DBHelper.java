package mysql;
import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;  
import java.sql.SQLException;

public class DBHelper {
	public static final String url = "jdbc:mysql://localhost:3306/STOREHOUSE?useSSL=false&allowPublicKeyRetrieval=true&serverTimezone=UTC";  
    public static final String name = "com.mysql.cj.jdbc.Driver";  
    public String user;  
    public String password;  
 
    public Connection conn = null;  
    public PreparedStatement pst = null;  
 
    public DBHelper(String user, String password,String sql) {
    	this.user = user;
    	this.password = password;
        try {  
            Class.forName(name);//ָ����������  
            conn = DriverManager.getConnection(url,user,password);//��ȡ����  
            pst = conn.prepareStatement(sql);//׼��ִ�����  
        } catch (Exception e) {  
            System.out.println(e);  
        }  
    }
    
    public void newsql(String sql) {
    	try {
			pst = conn.prepareStatement(sql);
		} catch (Exception e) {
			System.out.println(e);  
		}//׼��ִ�����  
	}
 
    public void close() {  
        try {  
            this.conn.close();  
            this.pst.close();  
        } catch (SQLException e) {  
        	System.out.println(e);   
        }  
    }
}
