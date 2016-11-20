import java.net.*;
import java.io.*;
import java.util.*;

class TCPServer extends TCPServerBuilder implements Runnable
{
	public void run( ) 
	{
		try 
		{
			serverSocket = new ServerSocket();
			serverSocket.bind(inetSocketAddress);
			socket = serverSocket.accept();
			socket.close();
		}
		catch(IOException e)
		{ System.out.println("IOException TCPServer "); }
	}
}
