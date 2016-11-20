import java.net.Socket;

class Main 
{
	public static void main(String[] args) 
	{
		//new Thread(new TCPServer()).start();
		//new Thread(new TCPClientMsg()).start();
		//new Thread(new TCPClientLMsg()).start();
		new Thread(new TCPClientBuffer()).start();
		
	}
}
