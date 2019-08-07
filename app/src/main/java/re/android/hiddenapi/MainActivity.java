package re.android.hiddenapi;

public class MainActivity {
    static {
        System.loadLibrary("hiddenapi-bypass");
    }
    public void disable() {
        this.disableProtectedNamespace();
        this.disableHiddenApi();
    }

    public native boolean isHiddenApiEnabled();
    public native boolean isProtectedNamespaceEnabled();

    public native void disableProtectedNamespace();
    public native void disableHiddenApi();
}
