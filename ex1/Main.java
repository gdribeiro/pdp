public class Main {

    // Creates Threads of the type Thread extended
	// public static void main(String[] args) {
	// 	for (Integer i = 0; i < 10; i++) {
	// 		MinhaThreadThread t = new MinhaThreadThread(i.toString());
	// 		t.start();
	// 	}
	// }


    // Creates Threads of the type Runnable implemented
	public static void main(String[] args) {
		for (Integer i = 0; i < 10; i++) {
			MinhaThreadRunnable t = new MinhaThreadRunnable(i.toString());
			(new Thread(t)).start();
		}
	}
}
