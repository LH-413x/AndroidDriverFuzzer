package com.cts.androiddriverfuzzer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    final String TAG=getClass().getName();
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("hiddenapi-bypass");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(getApplicationContext().getPackageName());
    }

    @Override
    protected void onStart(){
        super.onStart();
        enableDisable();
        test();
        while(true){
            randomCallCollect();
            simpleRandomCallCollect();
        }

    }

    private void enableDisable(){
        re.android.hiddenapi.MainActivity ma=new re.android.hiddenapi.MainActivity();
        ma.disable();
        if(!ma.isHiddenApiEnabled()){
            Log.d(TAG,"hiddlen api enabled");
        }
        if(!ma.isProtectedNamespaceEnabled()){
            Log.d(TAG,"protected namespace enabled");
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void test();
    public native void randomCallCollect();
    public native void simpleRandomCallCollect();
}
