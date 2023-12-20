import java.net.*;
import java.io.*;

public class Dasgal23 {
    public static void main(String[] args) {
        try {
            Socket sock = new Socket("127.0.0.1", 17);
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }
            sock.close();
        } catch (Exception err) {
            System.err.println(err);
        }
        try {
            Socket sock = new Socket("127.0.0.1", 6017);
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }
            sock.close();
        } catch (Exception err) {
            System.err.println(err);
        }
        try {
            Socket sock = new Socket("127.0.0.1", 5575);
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }
            sock.close();
        } catch (Exception err) {
            System.err.println(err);
        }
    }
}