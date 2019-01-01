import java.io.*;
import java.net.*;

public class Server {
	public static void main(String[] args) throws Exception {
		ServerSocket socket = new ServerSocket(3000);
		Socket sock = socket.accept();
		FileInputStream fis = new FileInputStream("Send.txt");
		BufferedInputStream bis = new BufferedInputStream(fis);
		String data = "";
		while(bis.available() > 0) {
			data += (char)bis.read();
		}
		DataOutputStream dos = new DataOutputStream(sock.getOutputStream());
		dos.writeUTF(data);
		dos.close();
		bis.close();
		fis.close();
		socket.close();
	}
}
