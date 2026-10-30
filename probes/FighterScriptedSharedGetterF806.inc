// F806: original 0052CB47 is reached only by original early
// action 0/2/4/5 JMPs. Ordinary cases and the native default
// go to epilogue without this extra lookup.
    return;
native_script_shared_getter:
    GetNativeActionAt40FA30();
