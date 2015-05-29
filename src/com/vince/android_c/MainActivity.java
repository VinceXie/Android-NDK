package com.vince.android_c;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity {

	private static final String TAG = "java log";

	private int ival;
	private float fval;
	private String str;
	
	static {
		System.loadLibrary("jni_hello");
		System.loadLibrary("jni_chatBasic");
		System.loadLibrary("jni_chatPerson");
	}

	public native String sayHello(); // native lib name;
	public native String dynamicHello();
	
	public native void intJtoC(int val);
	public native int intJfromC();
	
	public native void floatJtoC(float val);
	public native float floatJfromC();
	
	public native void stringJtoC(String val);
	public native String stringJfromC();
	
	private native int getPersonInfoByIndex(Person person, int index);

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		new AlertDialog.Builder(this).setMessage(sayHello()).show();
		new AlertDialog.Builder(this).setMessage(dynamicHello()).show();

		// basic chat
		intJtoC((int)123);		
		Log.d(TAG,"intJfromC="+intJfromC());
		
		floatJtoC((float)123.444);
		Log.d(TAG, "floatJfromC="+floatJfromC());
		
		stringJtoC("vince j to c");
		Log.d(TAG,"stringJfromC="+stringJfromC());
		
		Person person = new Person();
        for (int i=0; i<3; i++) {
            getPersonInfoByIndex(person, i);
            Log.d(TAG, "person["+i+"] -- "+person);
        }
		

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
