package udp;

import java.io.IOException;
import java.net.DatagramPacket;

class UDPClientHello extends UDPClientBuilder implements Runnable 
{
	private final int size = 1024;
	
	public void run() 
	{
		try 
		{
			setConnection();
			
			request = new DatagramPacket(new byte[size], 0, size, address.getAddress(), address.getPort());
			socket.send(request);
			System.out.println("request sent");
			
			reply = new DatagramPacket(new byte[size],size);
			socket.receive(reply);
			System.out.println("reply received");
			
			socket.close();
		}
		catch(IOException e)
		{ 
			System.out.println("IOException UDPClient"); 
		}
	}
} 
