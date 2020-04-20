# Cargo Dokumentation

## Hardware
### Bauteile
 - **Raspberry PI:**
    - Minicomputer
    - Hier befindet sich die Server-Software 
 - **Motor Driver:**
    - Führt die Befehle vom Raspberry PI aus
    - Steuert die DC Motoren
 - **2 DC Motoren:**
    - Treibt die Räder an
 - **Webcam:**
    - Zeichnet die Ego-Perspektive des Fahrzeugs auf
 - **Power Bank:**
    - Versorgt den Raspberry PI mit Strom
    
### Schalt- und Bauplan
![Schaltplan](Schaltplan.png?raw=true)
![Bauplan](Fritzing.png?raw=true)

## Software
### Server 
- **Main** 
    - Startet den VehicleServerThread  
- **VehicleServer**
    - Errichtet einen Socket  
    - Erstellt eine Instance von ***ImpulseProcessor***
    - Führt die Methode log() von der Klasse ***FileLogger*** aus
- **ImpulseProcessor**
    - Interpretiert die Impulsbefehle 
    - Steuert die Hardware-Komponente 
    - Implementiert das Interface ***ImpulseProcessorListener***
    - Führt ebenfalls die Methode FileLooger.getInstance().log() aus
- **Impulse**
    - Enum der Impulse (FORWARD, RIGHT, QUIT, etc.) 
- **FileLogger** 
    - Protokolliert die ausgeführten Prozesse [mittels log()]


### Server Klassendiagramm
![KlassendiagrammServer](ServerClassDiagramm.png?raw=true)

### Client
- **Main**
    - Startet die ***GUI***
- **GUI**
    - Name: view.fxml
    - Ist verbunden mit dem ***Controller***
- **Controller** 
    - Interpretiert die Befehle und Inputs des Benutzers
    - Erstellt eine Instanz von ***VehicleClient*** 
- **VehicleClient**
    - Stellt die Verbindung zum Server her
    - Kontrolliert die Verbindung
    - Sendet die Inputs an den Server
- **Impulse**
    - Enum der Impulse (FORWARD, RIGHT, QUIT, etc.) 
    
### Client Klassendiagramm
![KlassendiagrammServer](ClientClassDiagramm.png?raw=true)