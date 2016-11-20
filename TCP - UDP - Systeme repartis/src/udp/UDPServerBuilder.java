package udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class UDPServerBuilder extends UDPInfo
{
		InetSocketAddress address;
		DatagramSocket socket;
		DatagramPacket req, rep;
		 
		UDPServerBuilder()
		{ 
			address = null; 
			socket = null; 
			req = rep = null; 
		}
		 
		protected void setConnection() throws IOException 
		{
			socket = new DatagramSocket();
			address = new InetSocketAddress("localhost",8080);
		}


}
