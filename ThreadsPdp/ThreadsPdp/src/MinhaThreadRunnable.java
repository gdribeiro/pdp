
public class MinhaThreadRunnable implements Runnable {

	String nome;
	
	public MinhaThreadRunnable(String nome) {
		this.nome = nome;
	}
	
	@Override
	public void run() {
		System.out.println(nome);
		System.out.println(Thread.currentThread().getPriority());
		System.out.println(Thread.currentThread());
		
	}

	
	
	
}
