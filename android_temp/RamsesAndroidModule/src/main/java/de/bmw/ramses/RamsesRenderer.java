package de.bmw.ramses;

import android.view.Surface;

public class RamsesRenderer
{
    public RamsesRenderer(Surface surface, int width, int height,
                          String interfaceSelectionIP, String daemonIP)
    {
        m_nativeHandle = createRendererNative(surface, width, height, interfaceSelectionIP, daemonIP);
    }

    public void dispose()
    {
        disposeRamsesRendererNative(m_nativeHandle);
    }

    private long m_nativeHandle;

    private native long createRendererNative(Surface surface, int width, int height, String interfaceSelectionIP, String daemonIP);
    private native void disposeRamsesRendererNative(long handle);
}

