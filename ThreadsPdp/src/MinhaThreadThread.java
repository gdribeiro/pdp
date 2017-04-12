


public class MinhaThreadThread extends Thread {
	String nome;
	
	
	public MinhaThreadThread(String nome) {
		this.nome = nome;
	}

	@Override
	public void run() {
		System.out.println(nome);
		System.out.println(this.getPriority());
		System.out.println(Thread.currentThread());
	}
}
