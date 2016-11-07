import java.util.*;
public class Producer  extends Thread{
	BoundedBuffer bb;
	public Producer(BoundedBuffer bounB){
		bb = bounB;
	}
	
	public void run(){
		Random random = new Random();
		for(int i=0; i<100; i++){
			int n = random.nextInt(100)+1;
			bb.push(n);
		}		
	}
}
