public class Consumer implements Runnable {

	int type,i = 0,temp;
		
	public Consumer(int type){
		this.type = type;
	}
	
	public void run() {
		while(true){
				temp = RunnerClass.buffer[i];
				if(temp >= 0 && temp % 2 == type){
					System.out.println("from consumer " + type + " " +temp);
					synchronized(RunnerClass.lock){
						RunnerClass.buffer[i] = -1;
					}
				}
			i = i+1;
			i = (i)%(RunnerClass.buffer.length);
		}
	}

}
