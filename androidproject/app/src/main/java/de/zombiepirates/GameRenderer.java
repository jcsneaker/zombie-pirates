package de.zombiepirates;

import android.content.res.AssetManager;
import android.view.Surface;
import android.util.Log;

public class GameRenderer
{
    public GameRenderer(Surface surface, AssetManager amgr, int width, int height)
    {
        Log.v("MyActivity", "calling native load assmanager");
        load(amgr);

        Log.v("MyActivity", "constructor");
        m_nativeHandle = createGameNative(surface, width, height);

    }

    public void dispose()
    {
        disposeGameNative(m_nativeHandle);
    }

    private long m_nativeHandle;

    private native long createGameNative(Surface surface, int width, int height);
    private native void disposeGameNative(long handle);

    private static native void load(AssetManager mgr);
}
