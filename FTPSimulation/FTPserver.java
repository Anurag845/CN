import java.net.*;
import java.io.*;

class FTPserver {
	
	private ServerSocket serverSocket = null;
	private DataInputStream dis = null;
	private DataOutputStream dos = null;
	
	FTPserver() {
		try {
			String input;
			serverSocket = new ServerSocket(3000);
			Socket socket = null;
			socket = serverSocket.accept();
			dis = new DataInputStream(socket.getInputStream());
			dos = new DataOutputStream(socket.getOutputStream());
			input = dis.readUTF();
			if(input.equals("ftp")) {
				dos.writeUTF("ftp> ");
				input = dis.readUTF();
				dos.writeUTF("Connected to 10.10.10.212\n220 (vsFTPd 3.0.2)\nName (10.10.10.212:root): ");
				input = dis.readUTF();
				dos.writeUTF("331 Please specify the password.\nPassword: ");
				input = dis.readUTF();
				dos.writeUTF("230 Login successful.\nRemote system type is UNIX\nUse binary mode to transfer files\nftp> ");
				input = dis.readUTF();       //receive mget
				dos.writeUTF("ftp> ");
				input = dis.readUTF();       //receive mput
				dos.writeUTF("ftp> ");
				input = dis.readUTF();       //receive exit
				dos.writeUTF("Goodbye");
			}
			dis.close();
			dos.close();
			socket.close();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		FTPserver ftp = new FTPserver();
	}
}
