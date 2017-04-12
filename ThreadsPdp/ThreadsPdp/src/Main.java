
public class Main {

	public static void main(String[] args) {
//		// Creates Threads of the time Threads that are extended
//		for (Integer i = 0; i < 10; i++) {
//			MinhaThreadThread t = new MinhaThreadThread(i.toString());
//			t.start();
//		}
		// Creates Threads of the time Threads that are extended
		for (Integer i = 0; i < 10; i++) {
			
			(new Thread(new MinhaThreadRunnable(i.toString()))).start();
		}
	}
}