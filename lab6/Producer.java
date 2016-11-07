import java.util.Random;


public class Producer implements Runnable {

	int i = 0;
	Random randomGenerator;
	
	
	Producer(){
		randomGenerator = new Random();
	}
	
	public void run() {
		while(true){
					if(RunnerClass.buffer[i] == -1){
						synchronized(RunnerClass.buffer){
						RunnerClass.buffer[i] = randomGenerator.nextInt(100);
						}
				}
				i+=1;
				i = i%RunnerClass.buffer.length;
			}
		}
	}
	
