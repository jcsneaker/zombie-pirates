package de.bmw.ramses;

import android.content.res.AssetManager;
import android.view.Surface;
import android.util.Log;

public class RamsesTriangleRenderer
{
    public RamsesTriangleRenderer(Surface surface, AssetManager amgr, int width, int height)
    {
        Log.v("MyActivity", "calling native load assmanager");
        load(amgr);

        Log.v("MyActivity", "constructor");
        m_nativeHandle = createTriangleRendererNative(surface, width, height);

    }

    public void dispose()
    {
        disposeTriangleRendererNative(m_nativeHandle);
    }

    private long m_nativeHandle;

    private native long createTriangleRendererNative(Surface surface, int width, int height);
    private native void disposeTriangleRendererNative(long handle);

    private static native void load(AssetManager mgr);
}
