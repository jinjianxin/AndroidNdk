package simple.ndk.wxelife.com.androidndk;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


// https://github.com/googlesamples/android-ndk
public class MainActivity extends AppCompatActivity {

    private EditText mThreadCount;
    private EditText mIterationCount;
    private TextView mTextView = null;
    private Button mStartButton = null;

    private void assignViews() {
        mThreadCount = (EditText) findViewById(R.id.thread_count);
        mIterationCount = (EditText) findViewById(R.id.iteration_count);
        mTextView =(TextView) findViewById(R.id.log_text_view);
        mStartButton =(Button) findViewById(R.id.startButton);

        mStartButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                    startThreads(5,10);
            }
        });
    }

    private void startThreads(int threads,int interations)
    {
       // javaThreads(threads,interations);
        nativeWThreads(threads,interations);

    }

    private void javaThreads(int threads,final int interations)
    {
        for(int i=0;i<threads;i++)
        {
            final int id = i;

            Thread thread = new Thread()
            {
                @Override
                public void run() {
                    super.run();
                    nativeWorker(id, interations);
                }
            };

            thread.start();
        }
    }

    static
    {
        System.loadLibrary("JniHelper");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d("guidongli", getCLanguageString());

        nativeInit();

        assignViews();
    }

    private void OnNativeMessage(final String message)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mTextView.append(message);
                mTextView.append("\n");
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeFree();
    }

    private native  String getCLanguageString();
    private native  void nativeInit();
    private native  void nativeFree();
    private native  void nativeWorker(int id,int iterations);
    private native  void nativeWThreads(int id,int iterations);



}
