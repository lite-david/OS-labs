
public class RunnerClass {
	public static void main(String[] args){
		BoundedBuffer buffer = new BoundedBuffer(10);
		Producer p_thread = new Producer(buffer);
		Consumer odd_thread = new Consumer(buffer, true);
		Consumer even_thread = new Consumer(buffer, false);
		p_thread.start();
		odd_thread.start();
		even_thread.start();
	}
}
