import java.net.*;
import java.io.*;

public class Client {
	public static void main(String[] args) throws Exception {
		Socket socket = new Socket("localhost",3000);
		DataInputStream dis = new DataInputStream(socket.getInputStream());
		FileOutputStream fos = new FileOutputStream("Received.txt");
		String data = dis.readUTF();
		byte[] b = data.getBytes();
		fos.write(b);
		fos.close();
		dis.close();
		socket.close();
	}
}
