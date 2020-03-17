package org.himbeerkuchen.hotroad;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;

import org.himbeerkuchen.hotroadlib.Impulse;

import java.io.IOException;

/**
 * Activity for controlling the car.
 *
 * @author Marijanovic Bernard
 */
public class ControlActivity extends Activity
{
	private CarClient client;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		client = CarClient.getInstance();
		setContentView(R.layout.control_activity);
		WebView wv = (WebView) findViewById(R.id.vision);
		wv.setWebViewClient(new WebViewClient());
		wv.getSettings().setJavaScriptEnabled(true);
		wv.loadUrl("http://" + client.getIpAddress() + "/");
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		try
		{
			CarClient.destroyInstance();
		}
		catch (IOException e)
		{
			Log.d(getClass().getSimpleName(), e.toString());
		}
	}

	/**
	 * Standard sendImpulse() function sends a quit signal to the server.
	 */
	public void sendImpulse()
	{
		try
		{
			client.send(Impulse.QUIT);
		}
		catch (IOException ex)
		{
			Toast.makeText(this, R.string.connection_error, Toast.LENGTH_SHORT).show();
		}
	}

	/**
	 * Overridden sendImpulse() function is only called via buttons from the activity. Therefore the parameter.
	 *
	 * @param v The calling button to determine the impulse type
	 */
	public void sendImpulse(View v)
	{
		try
		{
			switch (v.getId())
			{
				case R.id.forward:
					client.send(Impulse.FORWARD);
					break;
				case R.id.right:
					client.send(Impulse.RIGHT);
					break;
				case R.id.backward:
					client.send(Impulse.BACKWARD);
					break;
				case R.id.left:
					client.send(Impulse.LEFT);
					break;
				case R.id.reset:
					client.send(Impulse.RESET);
					break;
			}
		}
		catch (IOException ex)
		{
			Toast.makeText(this, R.string.connection_error, Toast.LENGTH_SHORT).show();
		}
	}
}
