import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

class TCPServer {
	
	private ServerSocket server;
	private Socket sock;
	private DataOutputStream dos;
	private DataInputStream dis;
	
	TCPServer() throws IOException {
		server = new ServerSocket(3000);
		sock = server.accept();
		dis = new DataInputStream(sock.getInputStream());
		dos = new DataOutputStream(sock.getOutputStream());
	}
	
	
	public void calculator() throws IOException {
		int ch = dis.readInt();
		float res = 0,num1 = 0,num2 = 0;
		double deg = 0, rad = 0;
		switch(ch) {
		case 1: dos.writeUTF("Enter 1st number- ");
				num1 = dis.readFloat();
				dos.writeUTF("Enter 2nd number- ");
				num2 = dis.readFloat();
				res = num1 + num2;
				break;
		case 2: dos.writeUTF("Enter 1st number- ");
				num1 = dis.readFloat();
				dos.writeUTF("Enter 2nd number- ");
				num2 = dis.readFloat();
				res = num1 - num2;
				break;
		case 3: dos.writeUTF("Enter 1st number- ");
				num1 = dis.readFloat();
				dos.writeUTF("Enter 2nd number- ");
				num2 = dis.readFloat();
				res = num1 * num2;
				break;
		case 4: dos.writeUTF("Enter 1st number- ");
				num1 = dis.readFloat();
				dos.writeUTF("Enter 2nd number- ");
				num2 = dis.readFloat();
				res = num1 / num2;
				break;
		case 5: dos.writeUTF("Enter angle in degrees- ");
				deg = dis.readDouble();
				rad = Math.toRadians(deg);
				res = (float) Math.sin(rad);
				break;
		case 6: dos.writeUTF("Enter angle in degrees- ");
				deg = dis.readDouble();
				rad = Math.toRadians(deg);
				res = (float) Math.cos(rad); 
				break;
		}
		dos.writeUTF("Result is " + res);
	}
	
	public void FileTransfer() throws IOException {
		FileInputStream fis = new FileInputStream("Send.txt");
		BufferedInputStream bis = new BufferedInputStream(fis);
		String data = "";
		while(bis.available() > 0) {
			data += (char)bis.read();
		}
		dos.writeUTF(data);
		bis.close();
		fis.close();
	}
	
	public static void main(String[] args) throws IOException {
		TCPServer obj = new TCPServer();
		int ch = obj.dis.readInt();
		switch(ch) {
		case 1: obj.calculator();
		break;
		case 2: obj.FileTransfer();
		break;
		}
		obj.dis.close();
		obj.dos.close();
		obj.sock.close();
		obj.server.close();
	}
}
