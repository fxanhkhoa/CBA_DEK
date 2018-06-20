//package Chat_Client;

import javax.swing.*;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JComboBox;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Dimension;
import java.awt.FlowLayout;

import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Chat_Client extends JFrame {

private JButton btn_Send = new JButton("Send");
private JTextField TextShow = new JTextField("Chat Box");
private JTextField TextSend = new JTextField("Text Send");

private static JTextField Server_IP_Text = new JTextField("10.0.3.101");
private JButton btn_Connect = new JButton("Connect");


private static String string ="Chat_Box";
private static JTextArea AreaText = new JTextArea(string);
private static JScrollPane scrollPane;

final static int ServerPort = 1234;
private static InetAddress ip;
private static String IP_Text;
private static Socket s;
private static DataInputStream dis;
private static DataOutputStream dos;

static Thread readMessage;
static RecieveThread _R;

public static void main(String[] args) throws UnknownHostException, IOException {
        Chat_Client f = new Chat_Client();
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);

        /*Thread sendMessage = new Thread(new Runnable()
           {
           @Override
           public void run(){
            while (true) {
              try{
                String text = TextSend.getText();
                dos.writeUTF(text);
              } catch (IOException e){
                e.printStackTrace();
              }
            }
           }
           });*/

        //sendMessage.start();
}

public Chat_Client(){
        setTitle("Chat_Client");
        setSize(400,450);
        setLocation(new Point(300,200));
        setLayout(null);
        setResizable(false);

        initComponent();
        initEvent();

        setVisible(true);
}

private void initComponent(){
        btn_Send.setBounds(300,300,80,25);
        //TextShow.setBounds(10,10,300,250);
        TextSend.setBounds(10,300,250,25);
        //TextShow.setHorizontalAlignment(SwingConstants.LEFT);
        //TextShow.setVerticalAlignment(SwingConstants.TOP);
        //AreaText.setBounds(10,10,300,250);

        //AreaText.setPreferredSize(new Dimension(100, 100));
        AreaText.setLineWrap(true);
        scrollPane = new JScrollPane(AreaText,JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        scrollPane.setBounds(10,10,300,250);

        btn_Connect.setBounds(290,350,100,25);
        Server_IP_Text.setBounds(10,350,250,25);
        add(btn_Send);
        //add(TextShow);
        add(TextSend);
        add(scrollPane);
        add(btn_Connect);
        add(Server_IP_Text);
        //add(AreaText);
        TextSend.setEditable(false);
}

private void initEvent(){
        btn_Send.addActionListener(new ActionListener(){
                        public void actionPerformed(ActionEvent e){
                                btn_SendClick(e);
                        }
                });

        btn_Connect.addActionListener(new ActionListener(){
                        public void actionPerformed(ActionEvent e){
                                btn_ConnectClick(e);
                        }
                });
}

private void btn_SendClick(ActionEvent evt){
        //System.exit(0);
        try{
                String text = TextSend.getText();
                dos.writeUTF(text);
                //dos.writeShort(5);
        } catch (IOException e) {
                e.printStackTrace();
        }
}

private void btn_ConnectClick(ActionEvent evt){
        //System.exit(0);
        try{
                // geting localhost ip
                IP_Text = Server_IP_Text.getText();
                ip = InetAddress.getByName(IP_Text);

                // Establish the connection
                s = new Socket(ip, ServerPort);

                // Obtaining input and out streams
                dis = new DataInputStream(s.getInputStream());
                dos = new DataOutputStream(s.getOutputStream());

                TextSend.setEditable(true);
        } catch (IOException e) {
                e.printStackTrace();
        }

        readMessage = new Thread(new Runnable(){
                        public void run(){
                                while (true) {

                                        try{
                                                // Read Message then send to JTextField
                                                String msg ="";
                                                //while ((msg =(char) dis.read()) == '');
                                                msg = dis.readLine();
                                                if (msg != null) {
                                                        msg.trim();
                                                        msg.replace("null","");
                                                        System.out.print(msg);
                                                        System.out.print(msg);
                                                        AreaText.append("" + msg + "\n");
                                                        //scrollPane.add(AreaText);
                                                }
                                                if (msg == null) {
                                                        System.out.print("server died\n");
                                                        readMessage.stop();
                                                }
                                        } catch (IOException e) {
                                                e.printStackTrace();
                                        }
                                        //System.out.print("out\n");
                                }
                        }
                });
        readMessage.start();
}
}

class RecieveThread implements Runnable
{
Socket sock = null;
DataInputStream dis = null;

public RecieveThread(Socket sock)
{
        this.sock = sock;
}

public void run(){

        while(true) {
                try{
                        dis = new DataInputStream(sock.getInputStream());
                        // Read Message then send to JTextField
                        char msg;
                        //while ((msg = dis.readLine()) == null);
                        msg = (char)dis.read();
                        System.out.print(msg);
                        //AreaText.append(msg);
                        //scrollPane.add(AreaText);
                } catch (IOException e) {
                        e.printStackTrace();
                }
        }

}
}
