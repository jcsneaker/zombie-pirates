package de.bmw.ramses;

public class UniformInput {
    public UniformInput(long handle)
    {
        m_nativeHandle = handle;
    }

    public void setValueFloat(float x)
    {
        setValueFloatNative(m_nativeHandle, x);
    }

    public void dispose()
    {
        disposeNative(m_nativeHandle);
    }

    private long m_nativeHandle;

    private native void setValueFloatNative(long handle, float x);
    private native void disposeNative(long handle);
}
