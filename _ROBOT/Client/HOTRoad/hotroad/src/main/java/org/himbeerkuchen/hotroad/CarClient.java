package org.himbeerkuchen.hotroad;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;

import org.himbeerkuchen.hotroadlib.Impulse;

/**
 * Client class for the car, to be able to communicate with the car server on the car server.
 *
 * @author Marijanovic Bernard
 */
public class CarClient implements Serializable
{
	private static CarClient INSTANCE;

	public static final int DEFAULT_PORT = 13730; //Default port number

	private Socket socket;
	private ObjectOutputStream stream;

	private CarClient()
	{
	}

	public synchronized static CarClient getInstance()
	{
		if (INSTANCE == null)
			INSTANCE = new CarClient();
		return INSTANCE;
	}

	/**
	 * Initializes the single instance.
	 *
	 * @param ipAddress The address to connect to.
	 * @throws IOException
	 */
	public synchronized void initializeClient(String ipAddress) throws IOException
	{
		socket = new Socket(ipAddress, DEFAULT_PORT);
		stream = new ObjectOutputStream(socket.getOutputStream());
	}

	/**
	 * Destroys the single instance of the client.
	 *
	 * @throws IOException
	 */
	public synchronized static void destroyInstance() throws IOException
	{
		INSTANCE.send(Impulse.QUIT);
		INSTANCE.stream.close();
		INSTANCE.socket.close();
		INSTANCE = null;
	}

	/**
	 * Function to send impulses to the car in order to control it.
	 *
	 * @param impulse Impulse to send to the car server.
	 */
	public void send(Impulse impulse) throws IOException
	{
		stream.writeObject(impulse);
	}


	/**
	 * Function to check if the client is initialized.
	 *
	 * @return Boolean wether the client is initialized or not.
	 */
	public boolean isInitialized()
	{
		return socket != null && socket.isConnected();
	}

	public String getIpAddress()
	{
		return socket.getInetAddress().toString();
	}
}
