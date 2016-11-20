import java.io.IOException;


class TCPClientLMsg extends TCPClientBuilder implements Runnable
{
	@Override
	public void run()
	{
		try 
		{
			socket.connect(inetSocketAddress);
			
			out = socket.getOutputStream();
			in = socket.getInputStream();
			
			//System.out.println(receive(in));
			
			send(out, duplicateMessage(500)); // send 1st output
			//System.out.println(receive(in)); // get 1st input
			System.out.println("ok");
			System.out.println(receive(in)); // get 2nd input
			
			in.close();
			out.close();
			socket.close();
		}
		catch(IOException e)
		{ System.out.println("IOException TCPClientLMsg"); }
	}
	
	String duplicateMessage(int size)
	{ /** The size is in kbyte. */
		 StringBuffer msT; 
		 int time;
		 String ms = "Java TCP";
		 msT = new StringBuffer();
		 time = (size * 1024)/8;
		 for(int i = 0; i < time; i++)
			 msT.append(ms);
		 return msT.toString();
	 }
	
	 
}
