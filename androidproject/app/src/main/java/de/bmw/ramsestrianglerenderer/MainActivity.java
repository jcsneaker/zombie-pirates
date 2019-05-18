package de.bmw.ramsestrianglerenderer;

import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.app.Activity;

import de.bmw.ramses.RamsesTriangleRenderer;

public class MainActivity extends Activity implements SurfaceHolder.Callback{

    static {
        System.loadLibrary("gles3jni");
        Log.v("MyActivity", "loaded lib");
    }
;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.v("MyActivity", "onCreate");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SurfaceView surfaceView = (SurfaceView) findViewById(R.id.surfaceView);
        surfaceView.getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.v("MyActivity", "surfaceChanged");
        if (ramsesTriangleRenderer != null)
        {
            ramsesTriangleRenderer.dispose();
        }

        ramsesTriangleRenderer = new RamsesTriangleRenderer(holder.getSurface(), width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        ramsesTriangleRenderer.dispose();
        ramsesTriangleRenderer = null;
    }

    private RamsesTriangleRenderer ramsesTriangleRenderer;
}
