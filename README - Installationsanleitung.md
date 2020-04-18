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

### Was ist alles am Repo?
 - **Client**: Hier befindet sich der Source Code beider Clients, mit denen man den Roboter ansteuren kann. Es gibt einen Desktop-Client für  den Rechner und einen Andriod-Client für das Handy. 
 - **Server**: Hier befindet sich der Source Code für den Server (denn man auf dem Raspberry ausführen muss) welcher die Signale der Clients interpretiert.
 - **FührerscheinBuilder**: Hier befindet sich die Anwendung, mit der man die Führerscheine erstellen und als PDF exportieren kann um diese anschließend auszudrucken.
 - **Requirements**: Hier befindet sich einerseits die mpjpg_streamer Library welche für den Raspberry zum Streamen der Kamerabilder benötigt wird, und die JoyToKey Anwendung welche man benötigt um die Controller Inputs auf die richtigen Tastatur Inputs umwandelt.
 - **Documents**: Hier befinden sich alle wichtigen Information für das Projekt sowie Schaltplan, Liste der Teile etc... .
    
2. **Packages, packages, packages**<br>
    You now need to install a few packages, which are necessary for **HOTRoad** to even function. You’ll need:   
    
    ```
    $ apt-get install hostapd isc-dhcp-server libjpeg8-dev imagemagick libv4l-dev
    ```
    Now comes the fun part.
    
    
3. **Configuring hostapd**<br>
    Open up “/etc/hostapd/hostapd.conf” add the following lines:
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

    If you know how, change the settings appealing to your needs!
    Now open up **“/etc/default/hostapd”** and add:
	```
	DAEMON_CONF=”/etc/hostapd/hostapd.conf”
    ```
    
    **For EDIMAX adapters**<br>
    If you are using a EDIMAX adapter you need to change the hostapd binary. Copy the given hostapd binary with the following script:
	```
	 $ mv /usr/sbin/hostapd /usr/sbin/hostapd.bak
	 $ cp /home/pi/dat/hostapd /usr/sbin/
	```
	
4. **Configuring isc-dhcp-server**<br>
    Edit **“/etc/dhcp/dhcpd.conf”** and add the following:
	```
	subnet 10.10.0.0 netmask 255.255.0.0 {
        range 10.10.0.25 10.10.0.50;
        option domain-name-servers 8.8.4.4;
        option routers 10.10.0.1;
        interface wlan0;
    }
    ```

    Override the existing settings in **“/etc/network/interfaces”** with:
	```
	iface wlan0 inet static
	address 10.10.0.1
	netmask 255.255.255.0
	```
	
	
5. **Configuring mjpg-streamer**<br>
    You need to build the given version of mjpg-streamer (no really, only the given version is working – at least for me). To achieve this you need to follow these commands:
    ```
    $ cd /home/pi/mjpg-streamer
	$ ln –s /usr/include/linux/videodev2.h
    $ make mjpg_streamer input_file.so output_file.so
    ```

6. **Start scripts**<br>
    Everything is going well? This is the last step in this guide. You now need to tell the system to start everything when it boots. Create a file called **"hrinit.sh"** and add the following lines:
    ```
    #!/bin/sh
    sleep 15
    cd "/home/pi/mjpg-streamer/"
    sudo java -jar "home/pi/dist/HOTRoad.jar" & sudo mjpg_streamer -i "./input_uvc.so -n -y -f 15 -q 20 -r 320x240" -o "./output_http.so -n -w ./www -p 80"
    ```
    Save the file under **“/etc/init.d/”** and run:
	```
	$ update-rc.d /etc/init.d/hrinit.sh defaults
    ```
    Ignore the warnings: You are running a patchwork product.
    Now run these:
	```
	$ update-rc.d hostapd enable
	$ update-rc.d isc-dhcp-server enable
    ```
### Good Job. You are done. Now restart your Raspberry Pi and get driving.


PS.: Addition from 2016
In the new pimped version you need to create a folder “/home/pi/music”. You also need to build the JARs yourself. The hostapd binary and the mjpg-streamer source code are under the folder “Other”.
