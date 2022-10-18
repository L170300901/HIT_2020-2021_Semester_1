package mysql;
import java.sql.ResultSet;  
import java.sql.SQLException;
import java.util.Scanner;

public class Demo {
	static String sql = null;  
    static DBHelper db1 = null;  
    static ResultSet ret = null;  
    
    public static void main(String[] args) {  
    	Scanner scanner = new Scanner(System.in);
    	System.out.println("Please input username and password with "
    			+ "format [user:pswd]:");
    	String inputString = scanner.nextLine();
    	String[] unp = inputString.split(":");
    	//用户名和密码，每次只能以一个身份
    	String user = unp[0];
    	String password = unp[1];
    	
    	while(true) {
    		printmenu();
        	inputString = scanner.nextLine();
        	int choice = Integer.parseInt(inputString);
        	
        	// 退出程序
        	if(choice == 0) {
        		break;
        	}
        	// 切换用户
        	else if(choice == 1) {
        		System.out.println("Please input username and password with "
        				+ "format [ user:pswd ]':");
            	inputString = scanner.nextLine();
            	unp = inputString.split(":");
            	user = unp[0];
            	password = unp[1];
            	System.out.println("Change user succeed! Current "
            			+ "user: [" + user + "]");
        	}
        	// 查询表项
        	else if(choice == 2) {
        		System.out.println("Please input table name and properties with "
        				+ "format 'tablename:property1,property2...':");
            	inputString = scanner.nextLine();
            	String[] tni = inputString.split(":");
            	sql = "select " + tni[1] + " from " + tni[0];//SQL语句  
            	db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
            	try {  
            		ret = db1.pst.executeQuery();//执行语句，得到结果集
            		String[] items = tni[1].split(",");
            		int size = items.length;
            		for(int i = 0; i < size; i++) {
        				System.out.print(items[i] + "\t");            				
        			}
        			System.out.print("\n");
            		while (ret.next()) {
            			for(int i = 0; i < size; i++) {
            				System.out.print(ret.getString(i+1) + "\t");            				
            			}
            			System.out.print("\n");
            		}//显示数据  
            		ret.close();  
            		db1.close();//关闭连接  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// 增加表项
        	else if(choice == 3) {
        		sql = "use database storehouse";//SQL语句  ******************
            	db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
        		System.out.println("Please input table name:");
            	inputString = scanner.nextLine();
            	if(inputString.equalsIgnoreCase("good")) {//********************************
            		System.out.println("Please input values with format [id,'name',"
            				+ "price,'position']:");  //*********************
            		inputString = scanner.nextLine();
            		sql = "insert into good values(" + inputString + ")";
            		db1.newsql(sql);
            	}
            	else if(inputString.equalsIgnoreCase("people")) {//*****************************
            		System.out.println("Please input values with format [id,'name',"
            				+ "'sex',age,salary]:");//**********************
            		inputString = scanner.nextLine();
            		sql = "insert into people values(" + inputString + ")";
            		db1.newsql(sql);
            	}
            	else {
					System.out.println("No such table named with '" 
            	        + inputString.toLowerCase() + "'");
					continue;
				}
            	try {  
            		db1.pst.execute();//执行语句，得到结果集
            		db1.close();//关闭连接  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// 删除表项（根据表项name属性删除）
        	else if(choice == 4) {
        		sql = "use database storehouse";//SQL语句  *********************
            	db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
        		System.out.println("Please input table name:");
            	inputString = scanner.nextLine();
            	if(inputString.equalsIgnoreCase("good")) {  //***************
            		System.out.println("Please input the item's name that you want "
            				+ "to delete:");
            		inputString = scanner.nextLine();
            		sql = "delete from good where name='" + inputString.toLowerCase() + "'";
            		db1.newsql(sql);
            	}
            	else if(inputString.equalsIgnoreCase("people")) {
            		System.out.println("Please input the item's name that you want "
            				+ "to delete:");
            		inputString = scanner.nextLine();
            		sql = "delete from good where name='" + inputString.toLowerCase() + "'";
            		db1.newsql(sql);
            	}
            	else {
					System.out.println("No such table named with '" 
            	        + inputString.toLowerCase() + "'");
					continue;
				}
            	try {  
            		db1.pst.execute();//执行语句，得到结果集
            		db1.close();//关闭连接  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// 修改表项（根据表项name属性修改）
        	else if(choice == 5) {
        		sql = "use database storehouse";//SQL语句  
            	db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
        		System.out.println("Please input table name:");
            	inputString = scanner.nextLine();
            	if(inputString.equalsIgnoreCase("good")) {
            		System.out.println("Please input the item's name, aim property "
            				+ "and the new value that you want to modify:");
            		System.out.println("format: [name,property,value](if value "
            				+ "is a number) or [name,property,'value'](if value is a string");
            		inputString = scanner.nextLine();
            		String[] npv = inputString.split(",");
            		sql = "update good set `" + npv[1].toLowerCase() + "`=" + npv[2] 
            				+ " where `name`='" + npv[0] + "'";
            		db1.newsql(sql);
            	}
            	else if(inputString.equalsIgnoreCase("people")) {
            		System.out.println("Please input the item's name, aim property "
            				+ "and the new value that you want to modify:");
            		System.out.println("format: [name,property,value](if value "
            				+ "is a number) or [name,property,'value'](if value is a string");
            		inputString = scanner.nextLine();
            		String[] npv = inputString.split(",");
            		sql = "update people set `" + npv[1].toLowerCase() + "`=" + npv[2] 
            				+ " where `name`='" + npv[0] + "'";
            		db1.newsql(sql);
            	}
            	else {
					System.out.println("No such table named with '" 
            	        + inputString.toLowerCase() + "'");
					continue;
				}
            	try {  
            		db1.pst.execute();//执行语句，得到结果集
            		db1.close();//关闭连接  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// 查看所有用户权限
        	else if(choice == 6) {
            	sql = "select db,user,table_name,grantor,table_priv,column_priv "
            			+ "from mysql.tables_priv where `db`='storehouse';";//SQL语句  
            	db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
            	System.out.println("db\t|user\t|table_name\t|grantor\t|"
            		+ "table_priv\t|column_priv");  
            	try {  
            		ret = db1.pst.executeQuery();//执行语句，得到结果集
            		while (ret.next()) {
            			System.out.print(ret.getString(1) + "\t|");
            			System.out.print(ret.getString(2) + "\t|");
            			System.out.print(ret.getString(3) + "\t|");
            			System.out.print(ret.getString(4) + "\t|");
            			System.out.print(ret.getString(5) + "\t|");
            			System.out.print(ret.getString(6));
            			System.out.print("\n");
            		}//显示数据  
            		ret.close();  
            		db1.close();//关闭连接  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// 发放用户权限
        	else if(choice == 7) {
        		System.out.println("Please input some information to grant privileges:");
        		System.out.println("format: [user1,user2...:priv1,priv2...:tablename(:property_name)"
        				+ "(:wgo)]('wgo' means 'with grant option')");
        		System.out.println("Privilege hint: insert, select, update, delete...");
        		inputString = scanner.nextLine();
        		String[] parameters = inputString.split(":");
        		String[] users = parameters[0].split(",");
        		if(parameters.length == 3) {
        			int people_num = users.length;
        			for(int i = 0; i < people_num; i++) {
        				sql = "grant " + parameters[1] + " on storehouse." + parameters[2] + " to '" 
                		    + users[i] + "'@'localhost';";//SQL语句  
        				if(i == 0) {
        					db1 = new DBHelper(user, password, sql);//创建DBHelper对象
        					if(db1.pst == null) {
        						System.out.println("An error is occured! Error message ^^^^^");
        						break;
        					} 			
        				}
        				else {
        					db1.newsql(sql);
        				}
        				try {  
        					db1.pst.execute();//执行语句，得到结果集
        				} catch (SQLException e) {
        					db1.close();//关闭连接  
        					System.out.println(e);
        				}
        			}
        			db1.close();//关闭连接  
        		}
        		else if(parameters.length == 4) {
        			if(parameters[3].equalsIgnoreCase("wgo")) {
        				int people_num = users.length;
            			for(int i = 0; i < people_num; i++) {
            				sql = "grant " + parameters[1] + " on storehouse." + parameters[2] + " to '" 
                    		    + users[i] + "'@'localhost' with grant option;";//SQL语句  
            				if(i == 0) {
            					db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            					if(db1.pst == null) {
            						System.out.println("An error is occured! Error message ^^^^^");
            						break;
            					} 			
            				}
            				else {
            					db1.newsql(sql);
            				}
            				try {  
            					db1.pst.execute();//执行语句，得到结果集
            				} catch (SQLException e) {
            					db1.close();//关闭连接  
            					System.out.println(e);
            				}
            			}
            			db1.close();//关闭连接  
        			}
        			else {
        				int people_num = users.length;
            			for(int i = 0; i < people_num; i++) {
            				sql = "grant " + parameters[1] + " (" + parameters[3] + ") " + " on storehouse." 
                			    + parameters[2] + " to '" + users[i] + "'@'localhost';";//SQL语句  
            				if(i == 0) {
            					db1 = new DBHelper(user, password, sql);//创建DBHelper对象
            					if(db1.pst == null) {
            						System.out.println("An error is occured! Error message ^^^^^");
            						break;
            					} 			
            				}
            				else {
            					db1.newsql(sql);
            				}
            				try {  
            					db1.pst.execute();//执行语句，得到结果集
            				} catch (SQLException e) {
            					db1.close();//关闭连接  
            					System.out.println(e);
            				}
            			}
            			db1.close();//关闭连接  
        			}
        		}
                else if(parameters.length == 5) {
                	int people_num = users.length;
        			for(int i = 0; i < people_num; i++) {
        				sql = "grant " + parameters[1] + " (" + parameters[3] + ") " + " on storehouse." 
                			+ parameters[2] + " to '" + users[i] + "'@'localhost' with "
                	        + "grant option;";//SQL语句   
        				if(i == 0) {
        					db1 = new DBHelper(user, password, sql);//创建DBHelper对象
        					if(db1.pst == null) {
        						System.out.println("An error is occured! Error message ^^^^^");
        						break;
        					} 			
        				}
        				else {
        					db1.newsql(sql);
        				}
        				try {  
        					db1.pst.execute();//执行语句，得到结果集
        				} catch (SQLException e) {
        					db1.close();//关闭连接  
        					System.out.println(e);
        				}
        			}
        			db1.close();//关闭连接  
        		}
                else {
                	System.out.println("Illegal input! Grant failed!");
                	continue;
                }
        	}
        	// 收回用户权限
        	else if(choice == 8) {
        		System.out.println("Please input some information to revoke privileges:");
        		System.out.println("format: [user1,user2...:priv1,priv2...:tablename");
        		System.out.println("Privilege hint: insert, select, update, delete...");
        		inputString = scanner.nextLine();
        		String[] parameters = inputString.split(":");
        		String[] users = parameters[0].split(",");
        		if(parameters.length == 3) {
        			int people_num = users.length;
        			for(int i = 0; i < people_num; i++) {
        				sql = "revoke " + parameters[1] + " on storehouse." + parameters[2] + " from '" 
        			        + users[i] + "'@'localhost'";//SQL语句  
        				if(i == 0) {
        					db1 = new DBHelper(user, password, sql);//创建DBHelper对象
        					if(db1.pst == null) {
        						System.out.println("An error is occured! Error message ^^^^^");
        						break;
        					} 			
        				}
        				else {
        					db1.newsql(sql);
        				}
        				try {  
        					db1.pst.execute();//执行语句，得到结果集
        				} catch (SQLException e) {
        					db1.close();//关闭连接  
        					System.out.println(e);
        				}
        			}
        			db1.close();//关闭连接  
        		}
                else {
                	System.out.println("Illegal input! Grant failed!");
                	continue;
                }
        	}
        	else {
        	    System.out.println("Illegal input!");
        	    continue;
        	}
    	}
    	System.out.println("Bye!");
        scanner.close();
    }
    
    private static void printmenu() {
		System.out.println("菜单:");
		System.out.println("1. 切换用户.");
		System.out.println("2. 查询仓库物品.");
		System.out.println("3. 向仓库添加物品.");
		System.out.println("4. 删除仓库物品.");
		System.out.println("5. 修改仓库物品.");
		System.out.println("6. 查看用户权限.");
		System.out.println("7. 授予他人权限.");
		System.out.println("8. 收回他人权限.");
		System.out.println("0. Exit退出.");
	}
}
