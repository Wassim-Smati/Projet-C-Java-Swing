import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.*;
import java.net.Socket;

public class MainFrame extends JFrame {

    private static final long serialVersionUID = 1L;
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3331;

    private final String host;
    private final int port;

    private Socket socket;
    private BufferedReader input;
    private BufferedWriter output;

    private final JTextArea textArea = new JTextArea(12, 40);
    private final JTextField inputField = new JTextField(24);

    public MainFrame() {
        this(DEFAULT_HOST, DEFAULT_PORT);
    }

    public MainFrame(String host, int port) {
        super("INF224 - Telecommande Java/Swing");
        this.host = host;
        this.port = port;

        initUi();
        connectServer();

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void connectServer() {
        try {
            socket = new Socket(host, port);
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            textArea.append("Connecte au serveur " + host + ":" + port + "\n");
        } catch (IOException e) {
            textArea.append("Connexion impossible au serveur " + host + ":" + port + "\n");
            JOptionPane.showMessageDialog(this, "Impossible de se connecter au serveur C++", "Erreur reseau", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void initUi() {
        setLayout(new BorderLayout());

        textArea.setEditable(false);
        add(new JScrollPane(textArea), BorderLayout.CENTER);

        Action sendAction = new AbstractAction("Envoyer") {
            @Override
            public void actionPerformed(ActionEvent e) {
                sendRequest();
            }
        };

        Action clearAction = new AbstractAction("Supprimer") {
            @Override
            public void actionPerformed(ActionEvent e) {
                textArea.setText("");
            }
        };

        Action quitAction = new AbstractAction("Quitter") {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                System.exit(0);
            }
        };

        JPanel inputPanel = new JPanel();
        inputPanel.add(new JLabel("Commande:"));
        inputPanel.add(inputField);
        inputField.addActionListener(sendAction);
        add(inputPanel, BorderLayout.NORTH);

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(new JButton(sendAction));
        buttonPanel.add(new JButton(clearAction));
        buttonPanel.add(new JButton(quitAction));
        add(buttonPanel, BorderLayout.SOUTH);

        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Commandes");
        menu.add(new JMenuItem(sendAction));
        menu.add(new JMenuItem(clearAction));
        menu.addSeparator();
        menu.add(new JMenuItem(quitAction));
        menuBar.add(menu);
        setJMenuBar(menuBar);

        JToolBar toolBar = new JToolBar();
        toolBar.add(sendAction);
        toolBar.add(clearAction);
        toolBar.add(quitAction);
        add(toolBar, BorderLayout.PAGE_START);
    }

    private void sendRequest() {
        String request = inputField.getText().trim();
        if (request.isEmpty()) {
            return;
        }

        if (output == null || input == null) {
            textArea.append("[Erreur] Pas de connexion serveur.\n");
            return;
        }

        try {
            output.write(request + "\n");
            output.flush();
            String response = input.readLine();
            textArea.append("> " + request + "\n");
            textArea.append((response != null ? response : "[Aucune reponse]") + "\n");
            inputField.setText("");
        } catch (IOException ex) {
            textArea.append("[Erreur IO] " + ex.getMessage() + "\n");
        }
    }
}
