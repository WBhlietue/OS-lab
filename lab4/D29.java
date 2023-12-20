import java.util.*;
import java.io.*;
import java.net.*;
import java.time.*;

public class D29 {
    public static void main(String[] args) {

        try {
            ServerSocket serverSocket = new ServerSocket(17);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                new TThread(clientSocket).start();
            }
        } catch (Exception err) {
            System.err.println(err);
        }
    }

    public static class TThread extends Thread {
        Socket client;

        public TThread(Socket client){
            this.client = client;
        }

        public void run() {
            try{
            InputStream input = client.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            String message;
            while ((message = reader.readLine()) != null) {
                OutputStream output = client.getOutputStream();
                PrintWriter pout = new PrintWriter(output, true);
                pout.println("echo -> " + message + "\n");
            }
            client.close();
        }catch(Exception e){

        }
        }
    }
}
