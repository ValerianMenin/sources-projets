import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketTimeoutException;


public class TCPRW extends TCPInfo
{
	private int bufferSize = 65536;
	
	public TCPRW() { super(); }
	
	public String receive(InputStream in )
	{
		String message = null;
		try
		{
			byte[] buffer = new byte[bufferSize];
			int count = in.read(buffer);
			message = new String(buffer, 0, count);
		}
		catch(SocketTimeoutException e)
		{
			System.out.println("Time out");
		}
		catch(IOException e)
		{
			System.out.println("IOException in TCPRW - receive() " + e.getMessage());
		}
		return message;
	}
	
	public void send(OutputStream out , String message)
	{
		try
		{
			out.write(message.getBytes());
			out.flush();
		}
		catch(Exception e)
		{
			System.out.println("IOException in TCPRW - send() " + e.getMessage());
		}
	}
}
