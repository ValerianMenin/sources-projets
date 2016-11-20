import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;


class TCPServerBuilder
{
	protected ServerSocket serverSocket;
	protected InetSocketAddress inetSocketAddress;
	protected Socket socket;
	protected InputStream in;
	protected OutputStream out;
	
	
	TCPServerBuilder()
	{
		serverSocket = null ;
		socket = null;
		inetSocketAddress = new InetSocketAddress("localhost",8080);
	}
	
	public void serverInitialize()
	{
		try
		{
			serverSocket = new ServerSocket();
			serverSocket.setSoTimeout(20000);
			serverSocket.bind(inetSocketAddress);
		}
		catch(IOException e)
		{
			System.out.println("Could not initialize server socket");
		}
	}
}
