package de.zombiepirates;

import android.content.res.AssetManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.app.Activity;

public class GameActivity extends Activity implements SurfaceHolder.Callback{
    private AssetManager mgr;
    MediaPlayer mPlayer;
    static {
        System.loadLibrary("zombiepirates_android");
        Log.v("MyActivity", "loaded lib");
    }
;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.v("MyActivity", "onCreate");
        super.onCreate(savedInstanceState);
        mgr = getResources().getAssets();
        Log.v("MyActivity", "remember assmanager");
        setContentView(R.layout.activity_main);

        SurfaceView surfaceView = (SurfaceView) findViewById(R.id.surfaceView);
        surfaceView.getHolder().addCallback(this);

        mPlayer = MediaPlayer.create(this, R.raw.pirates);
        mPlayer.start();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        mPlayer.pause();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        mPlayer.start();
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        mPlayer.stop();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.v("MyActivity", "surfaceChanged");
        if (gameRenderer != null)
        {
            gameRenderer.dispose();
        }

        gameRenderer = new GameRenderer(holder.getSurface(),mgr, width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        gameRenderer.dispose();
        gameRenderer = null;
    }

    private GameRenderer gameRenderer;
}
