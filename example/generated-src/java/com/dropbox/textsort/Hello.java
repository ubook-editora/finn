// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from example.djinni

package com.dropbox.textsort;

import java.util.concurrent.atomic.AtomicBoolean;
import javax.annotation.CheckForNull;
import javax.annotation.Nonnull;

/*package*/ interface Hello {
    @Nonnull
    public MyEnum sayHi();

    @Nonnull
    public MyRecord print(@Nonnull MyRecord rc);

    @CheckForNull
    public static Hello create()
    {
        return CppProxy.create();
    }

    static final class CppProxy implements Hello
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void _djinni_private_destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            _djinni_private_destroy();
            super.finalize();
        }

        @Override
        public MyEnum sayHi()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_sayHi(this.nativeRef);
        }
        private native MyEnum native_sayHi(long _nativeRef);

        @Override
        public MyRecord print(MyRecord rc)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_print(this.nativeRef, rc);
        }
        private native MyRecord native_print(long _nativeRef, MyRecord rc);

        @CheckForNull
        public static native Hello create();
    }
}
