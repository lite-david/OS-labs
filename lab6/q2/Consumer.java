
public class Consumer extends Thread{
	BoundedBuffer buffer;
	boolean isOddCondition;
	public Consumer(BoundedBuffer bounB, boolean condition){
		buffer = bounB;
		isOddCondition = condition;
	}
	
	public void run(){
		if(isOddCondition){
			while(true){
				buffer.popOdd();
			}
		}else{
			while(true){
				buffer.popEven();
			}
		}
	}
}
