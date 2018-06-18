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

public class Chat_Client extends JFrame{

  private JButton btn_Send = new JButton("Send");
  private JTextField TextShow = new JTextField("Chat Box");
  private JTextField TextSend = new JTextField("Text Send");
  String  s ="Chat_Box";
  private JTextArea AreaText = new JTextArea(s);
  JScrollPane scrollPane;

  public static void main(String[] args){
    Chat_Client f = new Chat_Client();
    f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    //f.setLayout(new FlowLayout());
    //f.pack();
    f.setVisible(true);
    //new Chat_Client();
  }

  public Chat_Client(){
    setTitle("Chat_Client");
    setSize(400,400);
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
    add(btn_Send);
    //add(TextShow);
    add(TextSend);
    add(scrollPane);
    //add(AreaText);
    //pack();
  }

  private void initEvent(){
    btn_Send.addActionListener(new ActionListener(){
      public void actionPerformed(ActionEvent e){
        btn_SendClick(e);
      }
    });
  }

  private void btn_SendClick(ActionEvent evt){
    System.exit(0);
  }
}
