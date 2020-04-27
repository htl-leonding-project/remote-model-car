# Cargo Anleitung

## Bedienungsanleitung

### Vorraussetzungen:
- **Alle Bauteile sind vorhanden und einsatzbereit**
- **Das Auto ist richtig zusammengebaut.** 
- **Der WLAN-Hotspot ist richtig konfiguriert.**

### 1. Verbindungsaufbau: 
Den PC mit dem konfigurierten WLAN verbinden.

### 2. Software starten:
- Client Software starten
- IP Adresse und Port konfiguren <br>
![GUI](/Documents/GUI.jpeg?raw=true)

### 3. Auto steuern:
- Bei erfolgreicher Verbindung einfach loslegen

## Installationsanleitung:

### Was liegt am Repo?
 - **Client**: Hier befindet sich der Source Code des Clients, mit denen man den Roboter steuren kann. 
 - **Server**: Hier befindet sich der Source Code für den Server (denn man auf dem Raspberry PI ausführen muss), welcher die Signale der Clients interpretiert.
 - **Requirements**: Hier befindet sich einerseits die mpjpg_streamer Library welche für den Raspberry zum Streamen der Kamerabilder benötigt wird, und die JoyToKey Anwendung welche man benötigt um die Controller Inputs auf die richtigen Tastatur Inputs umwandelt.
 - **Documents**: Hier befinden sich alle genaueren Information für das Projekt, wie Schaltplan und Stückliste.
   
### Am Server (Raspberry PI): 
1) **Benötigte Packages**<br>
    Damit **Cargo** überhaupt funktioniert, ist es nötig, ein paar packages zu installieren.
    Folgender Befehl ist auszuführen:   
    ```
    $ apt-get install hostapd isc-dhcp-server libjpeg8-dev imagemagick libv4l-dev
    ```
        
2) **Konfiguration von hostapd**<br>
    Im Verzeichnis “/etc/hostapd/" liegt ein File namens ***hostapd.conf***. <br>
    Folgende Zeilen sind in diesem File zu ergänzen:
    ```
    interface=wlan0
    driver=nl80211  ---> Use rtl871xdrv for EDIMAX adapters
    ssid=HOTRoad
    hw_mode=g
    channel=11
    wpa=1 wpa_passphrase=himbeerkuchen
    wpa_key_mgmt=WPA-PSK
    wpa_pairwise=TKIP CCMP
    wpa_ptk_rekey=600
    macaddr_acl=0
    ```
   
    Öffnen Sie **“/etc/default/hostapd”** und fügen Sie folgende Zeile hinzu:
	```
	DAEMON_CONF=”/etc/hostapd/hostapd.conf”
    ```
 
3) **Konfiguration vom isc-dhcp-server**<br>
    Bearbeiten Sie **“/etc/dhcp/dhcpd.conf”** wie folgt.<br>
    Schreiben Sie diese Zeilen hinzu:
	```
	subnet 10.10.0.0 netmask 255.255.0.0 {
        range 10.10.0.25 10.10.0.50;
        option domain-name-servers 8.8.4.4;
        option routers 10.10.0.1;
        interface wlan0;
    }
    ```
    Überschreiben Sie die vorhandenen Einstellungen in **“/etc/network/interfaces”** mit folgenden Zeilen:
	```
	iface wlan0 inet static
	address 10.10.0.1
	netmask 255.255.255.0
	```
		
4) **Konfiguration des mjpg-streamers**<br>
    Sie müssen die gegebene Version vom mjpeg-streamer. 
    Um dies zu erreichen, sind folgende Befehle notwendig:
    ```
    $ cd /home/pi/mjpg-streamer
	$ ln –s /usr/include/linux/videodev2.h
    $ make mjpg_streamer input_file.so output_file.so
    ```

5) **Starten der Scripts**<br>
    Zuguterletzt müssen Sie dem System mitteilen, dass es beim Boot-Vorgang automatisch alles starten soll.<br>
    Erstellen Sie ein File namens **"hrinit.sh"** und schreiben Sie folgende Zeilen hinein:
    ```
    #!/bin/sh
    sleep 15
    cd "/home/pi/mjpg-streamer/"
    sudo java -jar "home/pi/dist/HOTRoad.jar" & sudo mjpg_streamer -i "./input_uvc.so -n -y -f 15 -q 20 -r 320x240" -o "./output_http.so -n -w ./www -p 80"
    ```
    Speichern das File unter **“/etc/init.d/”** führen Sie folgenden Befehl aus:
	```
	$ update-rc.d /etc/init.d/hrinit.sh defaults
    ```
    Führen Sie jetzt diese Befehle aus:
	```
	$ update-rc.d hostapd enable
	$ update-rc.d isc-dhcp-server enable
    ```
6) **Neustart**
    Sie sind fertig! Jetzt starten Sie noch den Raspberry PI neu und dann können Sie loslegen!

## Archiv

Stand Tag der offenen Tür 2020: <br>
https://github.com/1920-3ahitm-itp/HOTRoad.git

Dokumentation des Projekts: <br>
https://github.com/htl-leonding-project/remote-model-car/blob/master/Documents/Projekt-Dokumetation.md
