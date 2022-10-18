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
    	//�û��������룬ÿ��ֻ����һ�����
    	String user = unp[0];
    	String password = unp[1];
    	
    	while(true) {
    		printmenu();
        	inputString = scanner.nextLine();
        	int choice = Integer.parseInt(inputString);
        	
        	// �˳�����
        	if(choice == 0) {
        		break;
        	}
        	// �л��û�
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
        	// ��ѯ����
        	else if(choice == 2) {
        		System.out.println("Please input table name and properties with "
        				+ "format 'tablename:property1,property2...':");
            	inputString = scanner.nextLine();
            	String[] tni = inputString.split(":");
            	sql = "select " + tni[1] + " from " + tni[0];//SQL���  
            	db1 = new DBHelper(user, password, sql);//����DBHelper����
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
            	try {  
            		ret = db1.pst.executeQuery();//ִ����䣬�õ������
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
            		}//��ʾ����  
            		ret.close();  
            		db1.close();//�ر�����  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// ���ӱ���
        	else if(choice == 3) {
        		sql = "use database storehouse";//SQL���  ******************
            	db1 = new DBHelper(user, password, sql);//����DBHelper����
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
            		db1.pst.execute();//ִ����䣬�õ������
            		db1.close();//�ر�����  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// ɾ��������ݱ���name����ɾ����
        	else if(choice == 4) {
        		sql = "use database storehouse";//SQL���  *********************
            	db1 = new DBHelper(user, password, sql);//����DBHelper����
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
            		db1.pst.execute();//ִ����䣬�õ������
            		db1.close();//�ر�����  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// �޸ı�����ݱ���name�����޸ģ�
        	else if(choice == 5) {
        		sql = "use database storehouse";//SQL���  
            	db1 = new DBHelper(user, password, sql);//����DBHelper����
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
            		db1.pst.execute();//ִ����䣬�õ������
            		db1.close();//�ر�����  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// �鿴�����û�Ȩ��
        	else if(choice == 6) {
            	sql = "select db,user,table_name,grantor,table_priv,column_priv "
            			+ "from mysql.tables_priv where `db`='storehouse';";//SQL���  
            	db1 = new DBHelper(user, password, sql);//����DBHelper����
            	if(db1.pst == null) {
            		System.out.println("An error is occured! Error message ^^^^^");
            		break;
            	}
            	System.out.println("db\t|user\t|table_name\t|grantor\t|"
            		+ "table_priv\t|column_priv");  
            	try {  
            		ret = db1.pst.executeQuery();//ִ����䣬�õ������
            		while (ret.next()) {
            			System.out.print(ret.getString(1) + "\t|");
            			System.out.print(ret.getString(2) + "\t|");
            			System.out.print(ret.getString(3) + "\t|");
            			System.out.print(ret.getString(4) + "\t|");
            			System.out.print(ret.getString(5) + "\t|");
            			System.out.print(ret.getString(6));
            			System.out.print("\n");
            		}//��ʾ����  
            		ret.close();  
            		db1.close();//�ر�����  
            	} catch (SQLException e) {
            		System.out.println(e);
            	}
        	}
        	// �����û�Ȩ��
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
                		    + users[i] + "'@'localhost';";//SQL���  
        				if(i == 0) {
        					db1 = new DBHelper(user, password, sql);//����DBHelper����
        					if(db1.pst == null) {
        						System.out.println("An error is occured! Error message ^^^^^");
        						break;
        					} 			
        				}
        				else {
        					db1.newsql(sql);
        				}
        				try {  
        					db1.pst.execute();//ִ����䣬�õ������
        				} catch (SQLException e) {
        					db1.close();//�ر�����  
        					System.out.println(e);
        				}
        			}
        			db1.close();//�ر�����  
        		}
        		else if(parameters.length == 4) {
        			if(parameters[3].equalsIgnoreCase("wgo")) {
        				int people_num = users.length;
            			for(int i = 0; i < people_num; i++) {
            				sql = "grant " + parameters[1] + " on storehouse." + parameters[2] + " to '" 
                    		    + users[i] + "'@'localhost' with grant option;";//SQL���  
            				if(i == 0) {
            					db1 = new DBHelper(user, password, sql);//����DBHelper����
            					if(db1.pst == null) {
            						System.out.println("An error is occured! Error message ^^^^^");
            						break;
            					} 			
            				}
            				else {
            					db1.newsql(sql);
            				}
            				try {  
            					db1.pst.execute();//ִ����䣬�õ������
            				} catch (SQLException e) {
            					db1.close();//�ر�����  
            					System.out.println(e);
            				}
            			}
            			db1.close();//�ر�����  
        			}
        			else {
        				int people_num = users.length;
            			for(int i = 0; i < people_num; i++) {
            				sql = "grant " + parameters[1] + " (" + parameters[3] + ") " + " on storehouse." 
                			    + parameters[2] + " to '" + users[i] + "'@'localhost';";//SQL���  
            				if(i == 0) {
            					db1 = new DBHelper(user, password, sql);//����DBHelper����
            					if(db1.pst == null) {
            						System.out.println("An error is occured! Error message ^^^^^");
            						break;
            					} 			
            				}
            				else {
            					db1.newsql(sql);
            				}
            				try {  
            					db1.pst.execute();//ִ����䣬�õ������
            				} catch (SQLException e) {
            					db1.close();//�ر�����  
            					System.out.println(e);
            				}
            			}
            			db1.close();//�ر�����  
        			}
        		}
                else if(parameters.length == 5) {
                	int people_num = users.length;
        			for(int i = 0; i < people_num; i++) {
        				sql = "grant " + parameters[1] + " (" + parameters[3] + ") " + " on storehouse." 
                			+ parameters[2] + " to '" + users[i] + "'@'localhost' with "
                	        + "grant option;";//SQL���   
        				if(i == 0) {
        					db1 = new DBHelper(user, password, sql);//����DBHelper����
        					if(db1.pst == null) {
        						System.out.println("An error is occured! Error message ^^^^^");
        						break;
        					} 			
        				}
        				else {
        					db1.newsql(sql);
        				}
        				try {  
        					db1.pst.execute();//ִ����䣬�õ������
        				} catch (SQLException e) {
        					db1.close();//�ر�����  
        					System.out.println(e);
        				}
        			}
        			db1.close();//�ر�����  
        		}
                else {
                	System.out.println("Illegal input! Grant failed!");
                	continue;
                }
        	}
        	// �ջ��û�Ȩ��
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
        			        + users[i] + "'@'localhost'";//SQL���  
        				if(i == 0) {
        					db1 = new DBHelper(user, password, sql);//����DBHelper����
        					if(db1.pst == null) {
        						System.out.println("An error is occured! Error message ^^^^^");
        						break;
        					} 			
        				}
        				else {
        					db1.newsql(sql);
        				}
        				try {  
        					db1.pst.execute();//ִ����䣬�õ������
        				} catch (SQLException e) {
        					db1.close();//�ر�����  
        					System.out.println(e);
        				}
        			}
        			db1.close();//�ر�����  
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
		System.out.println("�˵�:");
		System.out.println("1. �л��û�.");
		System.out.println("2. ��ѯ�ֿ���Ʒ.");
		System.out.println("3. ��ֿ������Ʒ.");
		System.out.println("4. ɾ���ֿ���Ʒ.");
		System.out.println("5. �޸Ĳֿ���Ʒ.");
		System.out.println("6. �鿴�û�Ȩ��.");
		System.out.println("7. ��������Ȩ��.");
		System.out.println("8. �ջ�����Ȩ��.");
		System.out.println("0. Exit�˳�.");
	}
}
