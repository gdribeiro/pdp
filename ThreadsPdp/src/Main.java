public class Main {

	public static void main(String[] args) {
		for (Integer i = 0; i < 10; i++) {
			MinhaThreadThread t = new MinhaThreadThread(i.toString());
			t.start();
		}
	}
	
	public static void main(String[] args) {
		for (Integer i = 0; i < 10; i++) {
			MinhaThreadRunnable t = new MinhaThreadRunnable(i.toString());
			(new Thread(MinhaThreadRunnable)).start();
		}
	}
}
