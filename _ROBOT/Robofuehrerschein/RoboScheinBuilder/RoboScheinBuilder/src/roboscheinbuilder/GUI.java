/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roboscheinbuilder;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Properties;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;


/**
 *
 * @author Jochen Bamminger
 */
public class GUI extends JFrame implements ActionListener {

    String pfad = "C:\\Users\\living\\Desktop\\Robofuehrerschein\\RoboScheinBuilder";              // Pfad des Ordners wo das Projekt, die Datein robo-schein.jpg, roboschein.pdf und robschein.xfd sind
    String searchPath = "C:\\Users\\living\\Desktop\\";        // Basispfad, wenn das Fenster für die Bildersuche sich öffnet

    /*
     * WICHTIG
     *
     * In der Datei 'roboschein.xfd' muss der Pfad auch aktualisiert werden!
     * 
     */
    JFrame mainFrame;
    JLabel vorName;
    JLabel nachName;
    JLabel gebDat;
    JLabel meldung;
    JPanel name;
    JPanel vorNamePanel;
    JPanel nachNamePanel;
    JPanel gebDatPanel;
    JPanel buttonPanel;
    JTextField vorNameTxt;
    JTextField nachNameTxt;
    JTextField gebDatTxt;
    JFileChooser file;
    JButton picture;
    JButton printPDF;

    public GUI() {
        try {
            read();
        } catch (FileNotFoundException f) {
            JOptionPane.showMessageDialog(this, f.getMessage(), "Datei - Fehler", JOptionPane.OK_OPTION);
            System.exit(1);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, e.getMessage(), "Fehler", JOptionPane.OK_OPTION);
            System.exit(1);
        }

        mainFrame = new JFrame("RoboFührerscheinBuilder");
        mainFrame.setBounds(300, 200, 400, 235);
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        vorName = new JLabel("    Vorname:     ");
        vorNameTxt = new JTextField(20);
        nachName = new JLabel("   Nachname:   ");
        nachNameTxt = new JTextField(20);
        gebDat = new JLabel("Geburtsdatum:");
        gebDatTxt = new JTextField(20);
        gebDatTxt.setToolTipText("Datum im Format dd-mm-yyyy");
        meldung = new JLabel();

        vorNamePanel = new JPanel();
        vorNamePanel.add(vorName);
        vorNamePanel.add(vorNameTxt);

        nachNamePanel = new JPanel();
        nachNamePanel.add(nachName);
        nachNamePanel.add(nachNameTxt);

        gebDatPanel = new JPanel();
        gebDatPanel.add(gebDat);
        gebDatPanel.add(gebDatTxt);

        file = new JFileChooser(searchPath);

        picture = new JButton("Bild auswählen");
        picture.addActionListener(this);
        printPDF = new JButton("PDF erstellen");
        printPDF.addActionListener(this);

        buttonPanel = new JPanel();
        buttonPanel.add(picture);
        buttonPanel.add(printPDF);

        name = new JPanel();
        name.add(vorNamePanel);
        name.add(nachNamePanel);
        name.add(gebDatPanel);
        name.add(buttonPanel);

        mainFrame.add(new JLabel("\r\n"), BorderLayout.NORTH);
        mainFrame.add(name, BorderLayout.CENTER);
        mainFrame.add(meldung, BorderLayout.SOUTH);

        mainFrame.setVisible(true);
    }

    public void read() throws Exception {
        File file = new File("ini.properties");
        if (!file.exists()) {
            throw new FileNotFoundException("ini Datei nicht vorhanden!");
        }

        Properties prop = new Properties();
        try {

            prop.load(new FileInputStream("ini.properties"));
            pfad = prop.getProperty("path");
            searchPath = prop.getProperty("searchPath");

        } catch (Exception e) {
            System.out.println("FileNotFoundException");
        }
    }

    public static void main(String[] args) {
        System.out.println("RoboFührerscheinBuilder - start");
        new GUI();
        System.out.println("RoboFührerscheinBuilder - finished");
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == printPDF) {
            RoboScheinBuilder robo = new RoboScheinBuilder();
            String vorname = vorNameTxt.getText();
            String nachname = nachNameTxt.getText();
            String gesname="";
            String geburtsdatum = gebDatTxt.getText();
            String ausstellungsdatum;
            SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
            ausstellungsdatum = dateFormat.format(new Date());
            String path = "";
            
            if (file.getSelectedFile() != null) {
                path = file.getSelectedFile().getPath();
            }
            else
            {
                gesname=nachname+" "+vorname;
                path=searchPath+gesname+".png";
            }
            meldung.setText(" " + robo.generatePDF(pfad, vorname, nachname, geburtsdatum, ausstellungsdatum, path));
            path = null;
            file.setSelectedFile(null);
            Process p;
            try {
                p = Runtime.getRuntime().exec("rundll32 url.dll,FileProtocolHandler "+pfad+"roboschein.pdf");
                p.waitFor();
            } catch (Exception ex) {
            }
        } else if (e.getSource() == picture) {
            try {
                String[] nameParts = null;
                String firstname = null;
                String lastname = null;
                
                file.showOpenDialog(this);
                String datei = file.getSelectedFile().getName();
                meldung.setText(datei);
                nameParts = datei.split("_");
                
                if(nameParts.length > 1){
                    firstname = nameParts[1];
                    firstname = firstname.substring(0, firstname.length() - 4);
                }
                if(nameParts.length > 0){
                    lastname = nameParts[0];
                    
                    if(nameParts.length < 2){
                        lastname = lastname.substring(0, lastname.length() - 4);
                    }
                }
                if(nameParts.length <= 0){
                    lastname = "no_name";
                }
                
                vorNameTxt.setText(firstname);
                nachNameTxt.setText(lastname);
                meldung.setText(" " + datei + " ausgewählt");
            } catch (Exception ex) {
                meldung.setText(" Fehler bei der Dateiauswahl!");
            }
        }
    }
}
