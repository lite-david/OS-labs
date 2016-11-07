import java.util.*;
import java.util.concurrent.Semaphore;
public class BoundedBuffer {
	int BufferSize;
	int count;

	Vector<Integer> buffer;
	Semaphore mutex;
	Semaphore empty;
	Semaphore full;
	Semaphore even;
	Semaphore odd;
	
	public BoundedBuffer(int size){
		BufferSize = size;
		count = 0;
		buffer = new Vector<Integer>();
		mutex = new Semaphore(1);
		empty = new Semaphore(BufferSize);
		full = new Semaphore(0);
		odd = new Semaphore(0);
		even = new Semaphore(0);		
	}
	
	public void push(int num){
		//while(count==BufferSize){}
		try {
			empty.acquire();
			mutex.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		++count;
		buffer.add(num);
		if(count==BufferSize){
			System.out.println("Buffer Full Producer inserted "+ num);
		}else{
			System.out.println("Producer inserted "+num);
		}
		mutex.release();
		full.release();
		if(num%2==0)
			even.release();
		else
			odd.release();
	}
	
	public int popOdd(){
		int num = 0;
		//while(count==0){}
		try {
			odd.acquire();
			full.acquire();
			mutex.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		--count;
		for(int i=0; i<buffer.size(); i++){
			if(buffer.elementAt(i)%2!=0){
				num = buffer.remove(i);
				break;
			}
		}
			if(count==0){
				System.out.println("\tBuffer Empty Odd consumer consumed "+num);
			}else{
				System.out.println("\tOdd consumer consumed "+num);
			}
		mutex.release();
		empty.release();
		return num;
	}
	
	public int popEven(){
		int num = 0;
		while(count==0){}
		try {
			even.acquire();
			full.acquire();
			mutex.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		--count;
		for(int i=0; i<buffer.size(); i++){
			if(buffer.elementAt(i)%2==0){
				num = buffer.remove(i);
				break;
			}
		}
			if(count==0){
				System.out.println("\tBuffer Empty Even consumer consumed "+num);
			}else{
				System.out.println("\tEven consumer consumed "+num);
			}
		mutex.release();
		empty.release();
		return num;
	}
}
