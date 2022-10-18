import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;

public class MoneyBanana {
    private State InitialState;
    private State TargetState;
    private Map<State,StateSwitchAction> map=new HashMap<>();
    
    
    public MoneyBanana(State initialState, State targetState) {
	super();
	InitialState = initialState;
	TargetState = targetState;
    }

    // �ܴ�u����v����ת�Ƶ�v�����򷵻�false
    private boolean Goto(State state,char u,char v) {
	if (!state.OnBox&&state.Money==u&&u!=v) {
	    state.Money=v;
	    return true;
	}
	return false;
    }
    
    // ����������ͬ��v������ת�Ƶ�w������������ӵ�w
    private boolean PushBox(State state,char v,char w) {
	if (!state.OnBox&&state.Money==v&&state.Box==v&&v!=w) {
	    state.Money=w;
	    state.Box=w;
	    return true;
	}
	return false;
    }
    
    // ������������ͬһλ�ã��Ҳ��������ϣ���������
    private boolean ClimbBox(State state) {
	if (!state.OnBox&&state.Money==state.Box) {
	    state.OnBox=true;
	    return true;
	}
	return false;
    }
    
    // ���������������㽶�������Ϸ�����ץȡ�㽶
    private boolean Grasp(State state) {
	if (state.OnBox&&state.Box=='B'&&!state.HB) {
	    state.HB=true;
	    return true;
	}
	return false;
    }
    
    public boolean solution() {
	Queue<State> q=new LinkedList<>();
	Set<State> states=new HashSet<>();
	q.add(InitialState);
	while(!q.isEmpty()) {
	    State s=q.poll();
	    State temp;
	    states.add(s);
	    // ��������Goto��������Ľڵ�
	    for (char i='A';i<='C';i++) {
		temp=s.copy();
		if (Goto(temp, temp.Money, i)&&!states.contains(temp)) {
		    states.add(temp);
		    q.add(temp);
		    StateSwitchAction ssa=new StateSwitchAction(s, temp, "Goto("+s.Money+","+temp.Money+")");
		    map.put(temp, ssa);
		}
	    }
	    // ��������PushBox��������Ľڵ�
	    for (char i='A';i<='C';i++) {
		temp=s.copy();
		if (PushBox(temp, temp.Money, i)&&!states.contains(temp)) {
		    states.add(temp);
		    q.add(temp);
		    StateSwitchAction ssa=new StateSwitchAction(s, temp, "PushBox("+s.Money+","+temp.Money+")");
		    map.put(temp, ssa);		}
	    }
	    
	    temp=s.copy();
	    if (ClimbBox(temp)&&!states.contains(temp)) {
		states.add(temp);
		q.add(temp);
		StateSwitchAction ssa=new StateSwitchAction(s, temp, "ClimbBox");
		map.put(temp, ssa);
	    }
	    
	    temp=s.copy();
	    if (Grasp(temp)&&temp.equals(TargetState)) {
		StateSwitchAction ssa=new StateSwitchAction(s, temp, "Grasp");
		map.put(temp, ssa);
		return true;
	    }
	}
	return false;
    }
    
    public void Display() {
	Stack<StateSwitchAction> stacks=new Stack<>();
	State s=TargetState;
	StateSwitchAction ssa = null;
	while (map.get(s)!=null) {
	    stacks.add(map.get(s));
	    s=map.get(s).getFromState();
	}
	while (!stacks.isEmpty()) {
	    ssa=stacks.pop();
	    System.out.println(ssa);
	}
    }
    
    public static void main(String[] args) {
	State InitialState=new State('A', 'C', false, false);
	State TargetState=new State('B', 'B', true, true);
	MoneyBanana m=new MoneyBanana(InitialState,TargetState);
	if (m.solution()) {
	    m.Display();
	}
    }

}
