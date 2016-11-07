
public class RunnerClass {

	public static int[] buffer = new int[100];
	public static Object lock = new Object();
	public static void main(String[] args) {
		
		for(int i = 0;i<100;i++){
			buffer[i] = -1;
 		}
		Producer p = new Producer();
		Consumer odd = new Consumer(0);
		Consumer even = new Consumer(1);
		Thread p_thread = new Thread(p);
		Thread odd_thread = new Thread(odd);
		Thread even_thread = new Thread(even);
		
		p_thread.start();
		odd_thread.start();
		even_thread.start();
		
	}

}
